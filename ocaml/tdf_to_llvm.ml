class tdf_to_llvm (capsule : Tdf_types.s_capsule) = object (self)
  val context : Llvm.llcontext = Llvm.global_context ()

  val mutable the_module : Llvm.llmodule = Llvm.create_module
      (Llvm.global_context ()) "module id"

  val mutable builder : Llvm.llbuilder = Llvm.builder
      (Llvm.global_context ())

  val mutable extern_links = [||];
    (* we are intrested in tags' extern links. Keep them here *)
  val mutable tag = 0; (* index of "tag" in CAPSULE_LINK *)

  method get_donothing () =
    let name = "llvm.donothing" in
    let found = Llvm.lookup_function name the_module in
    match found with
    | Some value -> value
    | None ->
        let void = Llvm.void_type context in
        let ft = Llvm.function_type void [||] in
        Llvm.declare_function "llvm.donothing" ft the_module 
    (* declare void @llvm.donothing() nounwind readnone *)
    
  method dump_module () =
    Llvm.dump_module the_module

  method compile_capsule = function
      Tdf_types.C_make_capsule (prop_names,cap_linking,ext_linkage,groups) ->
        (* Find "tag" capsule_link,
           remember its index in tag and create empty extern_links *)
        let rec find_tag index list =
          if list <> [] then
            let head = List.hd list in
            match head with Tdf_types.C_make_capsule_link (sn, n) ->
              if sn = "tag" then
                (tag <- index;
                 extern_links <- Array.make n "")
              else
                find_tag (index+1) (List.tl list)
        in find_tag 1 cap_linking;

        (* Fill extern_links *)
        let rec find_tag_links index list =
          if index = 1 then
            let head = List.hd list in
            match head with Tdf_types.C_make_extern_link (x) ->
              List.iter self#compile_linkextern x
          else
            find_tag_links (index-1) (List.tl list)
        in find_tag_links tag ext_linkage;

        (* Compile each group of units *)
        List.iter
          (function Tdf_types.C_make_group (x) ->
            List.iter self#compile_unit x) groups;

        Llvm.dump_module the_module
        

  method compile_linkextern = function
      Tdf_types.C_make_linkextern (internal, ext) ->
        self#compile_external internal ext

  method compile_external internal = function
      Tdf_types.C_string_extern (s) ->
        extern_links.(internal) <- s
    | _ -> failwith "compile_external not implemented"
    
  method compile_unit = function
      Tdf_types.C_make_unit (local_vars, lks, properties) ->
        (* Fetch tags' count from local_vars *)
        let rec find_tag_count index list =
          if list = [] then
            0
          else if index = 1 then
            List.hd list
          else
            find_tag_count (index-1) (List.tl list)
        in
        let count = find_tag_count tag local_vars in
        (* Create mapping from units namespace to capsule namespace for tags *)
        let links = Array.make count (-1) in
        let rec find_tag_links index list =
          if index = 0 || lks = [] then
            ()
          else if index = 1 then
            self#compile_links links (List.hd list)
          else
            find_tag_links (index-1) (List.tl list)
        in
        find_tag_links tag lks;
        (* Compile body of the unit *)
        self#compile_props links properties

  method compile_links links = function
      Tdf_types.C_make_links ls ->
        List.iter
          (function Tdf_types.C_make_link (unit_name, capsule_name) ->
            links.(unit_name) <- capsule_name) ls
        
  method compile_props links = function
      Tdf_types.C_tagdef_props tagdefs ->
        self#compile_tagdefs links tagdefs
    | _ -> ()

  method compile_tagdefs links = function
      Tdf_types.C_make_tagdefs (no_labels, tds) ->
        List.iter (self#compile_tagdef links) tds

  method compile_tagdef links = function
      Tdf_types.C_make_id_tagdef (t,signature,e) ->
        let name = extern_links.(links.(t)) in
          self#id_tagdef_exp links name e
    | _ -> ()

  method id_tagdef_exp links name = function
      (* Compile exp enclosed in tagdef directly *)
      Tdf_types.C_make_proc (result_shape,params_intro,var_intro,body) ->
        let result_type = self#compile_shape result_shape in
        let rec compile_tagshaccs list =
          if list = [] then
            [||]
          else
            Array.append
              (Array.make 1
                 (self#compile_tagshacc (List.hd list)))
              (compile_tagshaccs (List.tl list))
        in
        let arg_types = compile_tagshaccs params_intro in
        let ft = Llvm.function_type result_type arg_types in
        let f = Llvm.declare_function name ft the_module in
        let bb = Llvm.append_block context "entry" f in
        Llvm.position_at_end bb builder;
        let _ = self#compile_bottom_exp body in
        Llvm_analysis.assert_valid_function f;
    | _ -> ()

  method compile_bottom_exp = function
      Tdf_types.C_sequence (statements,result) ->
        let rec compile list =
          if list = [] then
            ()
          else
            (ignore (self#compile_bottom_exp (List.hd list));
             compile (List.tl list))
        in
        compile statements;
(*        let _ = self#compile_bottom_exp result in
        ()
*)
    | Tdf_types.C_make_top ->
        let donothing = self#get_donothing () in
        let _ = Llvm.build_call donothing [||] "" builder in
        ()
    | Tdf_types.C_return (arg1) ->
        let ret_val = self#compile_exp arg1 in
        let _ = Llvm.build_ret ret_val builder in
        ()
    | x -> failwith "compile_bottom_exp not implemented"

  method compile_exp = function
      Tdf_types.C_make_int (v,value) ->
        let tp = self#compile_variety v in
        let nat = self#get_signed_nat value in
        Llvm.const_int tp nat
    | _ -> failwith "compile_exp not implemented"
        
  method compile_tagshacc = function
      Tdf_types.C_make_tagshacc (sha,opt_access,tg_intro) ->
        self#compile_shape sha

  method compile_variety = function
      Tdf_types.C_var_width (signed_width,width) ->
        let value = self#get_nat width in
        Llvm.integer_type context value
    | _ -> failwith "compile_variety not implemented"
        
  method compile_shape = function
      Tdf_types.C_integer var ->
        self#compile_variety var
    | _ -> failwith "compile_shape not implemented"

  method get_signed_nat = function
      Tdf_types.C_make_signed_nat (neg,n) ->
        if neg then (-n) else n
    | _ -> failwith "get_signed_nat not implemented"
          
  method get_nat = function
      Tdf_types.C_make_nat n -> n
   | _ -> failwith "get_nat not implemented"
          
  method compile () =
    self#compile_capsule capsule

end
;;
