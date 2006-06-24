
-- Module       : string_lists.ada
-- Component of : common_library
-- Version      : 1.2
-- Date         : 11/21/86  16:34:39
-- SCCS File    : disk21~/rschm/hasee/sccs/common_library/sccs/sxstring_lists.ada

with String_Pkg;
with Lists;

package String_Lists is new Lists(String_Pkg.String_Type, String_Pkg.Equal);
