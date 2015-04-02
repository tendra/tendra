if Array.length Sys.argv > 1 then
  let capsule = Tdf_read.read Sys.argv.(1) in
  let compiler = new Tdf_to_llvm.tdf_to_llvm capsule in
  compiler#compile()
else
  print_string "Usage: trans capsule.t"
