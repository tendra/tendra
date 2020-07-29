(*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 *
 * This is OCaml binding for TDF Specification.
 *
 * This function read binary file with TDF capsule.
 *
 *)

val read : string -> Tdf_types.s_capsule
(** Read TDF capsule from file with given name **)
