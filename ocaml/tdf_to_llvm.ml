class tdf_to_llvm (capsule : Tdf_types.s_capsule) = object (self)
  val context : Llvm.llcontext = Llvm.global_context ()

  val mutable the_module : Llvm.llmodule = Llvm.create_module
      (Llvm.global_context ()) "module id"

  val mutable builder : Llvm.llbuilder = Llvm.builder
      (Llvm.global_context ())

  val mutable extern_links = [||];
    (* we are intrested in tags' extern links. Keep them here *)
  val mutable tag = 0;
    (* index of "tag" in CAPSULE_LINK *)
  val mutable links = [||];
    (* Mapping from units namespace to capsule namespace for tags. *)
    (* It's valid only inside of a unit *)
  val mutable tag_values = [||];
    (* Mapping from tag (in unit's namespace) to llvalue *)

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
        links <- Array.make count (-1);
        tag_values <- Array.make count None;

        let rec find_tag_links index list =
          if index = 0 || lks = [] then
            ()
          else if index = 1 then
            self#compile_links (List.hd list)
          else
            find_tag_links (index-1) (List.tl list)
        in
        find_tag_links tag lks;
        (* Compile body of the unit *)
        self#compile_props properties

  method compile_links = function
      Tdf_types.C_make_links ls ->
        List.iter
          (function Tdf_types.C_make_link (unit_name, capsule_name) ->
            links.(unit_name) <- capsule_name) ls
        
  method compile_props = function
      Tdf_types.C_tagdef_props tagdefs ->
        self#compile_tagdefs tagdefs
    | _ -> ()

  method compile_tagdefs = function
      Tdf_types.C_make_tagdefs (no_labels, tds) ->
        List.iter (self#compile_tagdef) tds

  method compile_tagdef = function
      Tdf_types.C_make_id_tagdef (t,signature,e) ->
        let name = extern_links.(links.(t)) in
          self#id_tagdef_exp name e
    | _ -> ()

  method id_tagdef_exp name = function
      (* Compile exp enclosed in tagdef directly *)
      Tdf_types.C_make_proc (result_shape,params_intro,var_intro,body) ->
        (* Compute function type from result and args types *)
        let result_type = self#compile_shape result_shape in

        let rec type_of_tagshaccs list =
          if list = [] then
            [||]
          else
            Array.append
              (Array.make 1
                 (self#type_of_tagshacc (List.hd list)))
              (type_of_tagshaccs (List.tl list))
        in

        let arg_types = type_of_tagshaccs params_intro in
        let ft = Llvm.function_type result_type arg_types in
        (* Create function with type ft and given name *)
        let f = Llvm.declare_function name ft the_module in
        let args = Llvm.params f in
        (* Create basic block *)
        let bb = Llvm.append_block context "entry" f in
        Llvm.position_at_end bb builder;

        (* LLVM provides only values of arguments, but TDF expect pointers
           to args. Allocate stack space and place arguments there. *)
        let rec alloc_tagshaccs arg list =
          if list = [] then
            [||]
          else
            Array.append
              (Array.make 1
                 (self#alloc_tagshacc (args.(arg)) (List.hd list)))
              (alloc_tagshaccs (arg + 1) (List.tl list))
        in
        let _ = alloc_tagshaccs 0 params_intro in
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
    | (Tdf_types.C_apply_proc (result_shape,p,params,var_param) as orig) ->
        (* LLVM expects full function profiles in function declaration, but
           TDF provides just PROC as SHAPE in make_tagdec. So we ignore
           make_tagdec and build function declaration using information from
           apply_proc constructs *)
 
        let ft = self#deduce_function_type orig in
        let callee = self#get_function ft p in

        (* Compute array of arguments *)
        let rec param_list list =
          if list = [] then
            [||]
          else
            let tp = self#compile_exp (List.hd list) in
            Array.append
              (Array.make 1 tp)
              (param_list (List.tl list))
        in
        let args = param_list params in
        Llvm.build_call callee args "" builder

    | Tdf_types.C_contents (s,arg1) ->
        (* Is shape s ignored indeed? *)
        let ptr = self#compile_exp arg1 in
        Llvm.build_load ptr "" builder

    | Tdf_types.C_make_int (v,value) ->
        let tp = self#compile_variety v in
        let nat = self#get_signed_nat value in
        Llvm.const_int tp nat

    | Tdf_types.C_obtain_tag (t) ->
        let tagno = self#get_tag t in
        let value = tag_values.(tagno) in
        let x = match value with
        | Some result -> result
        | None -> failwith "unknown tag in obtain_tag"
        in x

    | _ -> failwith "compile_exp not implemented"

  method get_tag = function
      (* Get integer value of TAG *)
      Tdf_types.C_make_tag (tagno) -> tagno
    | _ -> failwith "make_tag expected"
      
  method get_function ft = function
      (* Return llvalue corresponding to given exp of apply_proc *)
    | Tdf_types.C_obtain_tag (t) ->
        let tagno = self#get_tag t in
        let name = extern_links.(links.(tagno)) in
        let f = match Llvm.lookup_function name the_module with
        | None -> Llvm.declare_function name ft the_module
        | Some f ->
            if Llvm.element_type (Llvm.type_of f) <> ft then
              failwith "redefinition of function with different args";
            f
        in f
    | _ -> failwith "get_function not implemented"
        
  method deduce_function_type = function
      (* Compute function type for given apply_proc construct *)
    | Tdf_types.C_apply_proc (result_shape,p,params,var_param) ->
        let res = self#compile_shape result_shape in
        let rec param_list list =
          if list = [] then
            [||]
          else
            let tp = self#type_of_exp (List.hd list) in
            Array.append
              (Array.make 1 tp)
              (param_list (List.tl list))
        in
        let args = param_list params in
        Llvm.function_type res args
    | _ -> failwith "deduce_function_type expect apply_proc only"

  method type_of_exp = function
      (* Find out lltype of given exp *)
      Tdf_types.C_make_int (v,value) ->
        self#compile_variety v
    | _ -> failwith "type_of_exp not implemented"

  method type_of_tagshacc = function
      (* Find out lltype of given tagshacc *)
      Tdf_types.C_make_tagshacc (sha,opt_access,tg_intro) ->
        self#compile_shape sha

  method alloc_tagshacc arg = function
      (* Assign argument into allocated stack space for given arg/tagshacc *)
      Tdf_types.C_make_tagshacc (sha,opt_access,tg_intro) ->
        let tp = self#compile_shape sha in
        let tagno = self#get_tag tg_intro in
        let space = Llvm.build_alloca tp "" builder in
        let _ = Llvm.build_store arg space builder in
        tag_values.(tagno) <- Some (space);
        
  method compile_variety = function
      (* Return lltype from given variety *)
      Tdf_types.C_var_width (signed_width,width) ->
        let value = self#get_nat width in
        Llvm.integer_type context value
    | _ -> failwith "compile_variety not implemented"
        
  method compile_shape = function
      (* Return lltype from given shape *)
      Tdf_types.C_integer var ->
        self#compile_variety var
    | _ -> failwith "compile_shape not implemented"

  method get_signed_nat = function
      (* Return int from given signed_nat *)
      Tdf_types.C_make_signed_nat (neg,n) ->
        if neg then (-n) else n
    | _ -> failwith "get_signed_nat not implemented"
          
  method get_nat = function
      (* Return int from given nat *)
      Tdf_types.C_make_nat n -> n
   | _ -> failwith "get_nat not implemented"
          
  method get_donothing () =
    (* return no-operation intrinsic: *)
    (* declare void @llvm.donothing() nounwind readnone *)
    let name = "llvm.donothing" in
    let found = Llvm.lookup_function name the_module in
    match found with
    | Some value -> value
    | None ->
        let void = Llvm.void_type context in
        let ft = Llvm.function_type void [||] in
        Llvm.declare_function "llvm.donothing" ft the_module 
    
  method compile output =
    self#compile_capsule capsule;
    Llvm.print_module output the_module

end
;;
