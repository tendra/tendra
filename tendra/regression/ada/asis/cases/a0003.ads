------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Check inherited subprogram declarations.
--
--  Used with 'name' test to find each corresponding declaration for all
--  names.

package A0003 is

   type Base_Type is new Boolean;
   --  Inherits False and True literals

   procedure Used_Defined (Item : Base_Type);

   type Derived_Type is new Base_Type;
   --  Inherits Used_Defined procedure

   procedure Test;

end A0003;
