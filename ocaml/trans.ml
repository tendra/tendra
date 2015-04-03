if Array.length Sys.argv > 2 then
  let capsule = Tdf_read.read Sys.argv.(1) in
  let compiler = new Tdf_to_llvm.tdf_to_llvm capsule in
  compiler#compile(Sys.argv.(2))
else
  print_string "Usage: trans capsule.t output.ll"
