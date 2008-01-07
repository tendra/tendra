------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Check some implicit declarations.
--  Used with 'name' test to find each corresponding declaration for all
--  names (like "and").

procedure A0002 is
   type My_Boolean is new Boolean;
   type My_Modular is mod 256;
   type Boolean_Array is array (1 .. 10) of Boolean;
   type My_Integer is range 1 .. 10;
   type My_Float is digits 8;
   type My_Fixed is delta 0.01 range 0.0 .. 1000.0;

   function F01 (L, R : My_Boolean) return My_Boolean renames "and";
   function F02 (L, R : My_Boolean) return My_Boolean renames "or";
   function F03 (L, R : My_Boolean) return My_Boolean renames "xor";

   function F11 (L, R : My_Modular) return My_Modular renames "and";
   function F12 (L, R : My_Modular) return My_Modular renames "or";
   function F13 (L, R : My_Modular) return My_Modular renames "xor";

   function F21 (L, R : Boolean_Array) return Boolean_Array renames "and";
   function F22 (L, R : Boolean_Array) return Boolean_Array renames "or";
   function F23 (L, R : Boolean_Array) return Boolean_Array renames "xor";

   function F04 (L, R : My_Boolean) return Boolean renames "=";
   function F05 (L, R : My_Boolean) return Boolean renames "/=";
   function F06 (L, R : My_Boolean) return Boolean renames "<";

   function F14 (L, R : My_Modular) return Boolean renames "=";
   function F15 (L, R : My_Modular) return Boolean renames "/=";
   function F16 (L, R : My_Modular) return Boolean renames "<";

   function F24 (L, R : Boolean_Array) return Boolean renames "=";
   function F25 (L, R : Boolean_Array) return Boolean renames "/=";
   function F26 (L, R : Boolean_Array) return Boolean renames "<";

   function F34 (L, R : My_Integer) return Boolean renames "=";
   function F35 (L, R : My_Integer) return Boolean renames "/=";
   function F36 (L, R : My_Integer) return Boolean renames "<";

   function F44 (L, R : My_Float) return Boolean renames "=";
   function F45 (L, R : My_Float) return Boolean renames "/=";
   function F46 (L, R : My_Float) return Boolean renames "<";

   function F54 (L, R : My_Fixed) return Boolean renames "=";
   function F55 (L, R : My_Fixed) return Boolean renames "/=";
   function F56 (L, R : My_Fixed) return Boolean renames "<";

   function F17 (L, R : My_Modular) return My_Modular renames "+";
   function F18 (L, R : My_Modular) return My_Modular renames "-";
   function F17 (L : My_Modular) return My_Modular renames "+";
   function F18 (L : My_Modular) return My_Modular renames "-";

   function F37 (L, R : My_Integer) return My_Integer renames "+";
   function F38 (L, R : My_Integer) return My_Integer renames "-";
   function F37 (L : My_Integer) return My_Integer renames "+";
   function F38 (L : My_Integer) return My_Integer renames "-";

   function F47 (L, R : My_Float) return My_Float renames "+";
   function F48 (L, R : My_Float) return My_Float renames "-";
   function F47 (L : My_Float) return My_Float renames "+";
   function F48 (L : My_Float) return My_Float renames "-";

   function F57 (L, R : My_Fixed) return My_Fixed renames "+";
   function F58 (L, R : My_Fixed) return My_Fixed renames "-";
   function F57 (L : My_Fixed) return My_Fixed renames "+";
   function F58 (L : My_Fixed) return My_Fixed renames "-";

   function F27 (L, R : Boolean_Array) return Boolean_Array renames "&";
   function F27 (L : Boolean_Array; R : Boolean) return Boolean_Array
     renames "&";
   function F27 (L : Boolean; R : Boolean_Array) return Boolean_Array
     renames "&";
   function F27 (L : Boolean; R : Boolean) return Boolean_Array
     renames "&";

   function F19 (L, R : My_Modular) return My_Modular renames "*";
   function F1A (L, R : My_Modular) return My_Modular renames "/";
   function F1B (L, R : My_Modular) return My_Modular renames "mod";
   function F1C (L, R : My_Modular) return My_Modular renames "rem";

   function F39 (L, R : My_Integer) return My_Integer renames "*";
   function F3A (L, R : My_Integer) return My_Integer renames "/";
   function F3B (L, R : My_Integer) return My_Integer renames "mod";
   function F3C (L, R : My_Integer) return My_Integer renames "rem";

   function F49 (L, R : My_Float) return My_Float renames "*";
   function F4A (L, R : My_Float) return My_Float renames "/";

   function F59 (L : My_Fixed; R : Integer) return My_Fixed renames "*";
   function F5A (L : Integer; R : My_Fixed) return My_Fixed renames "*";
   function F5B (L : My_Fixed; R : Integer) return My_Fixed renames "/";

   function F1D (L : My_Modular) return My_Modular renames "abs";
   function F3D (L : My_Integer) return My_Integer renames "abs";
   function F4D (L : My_Float) return My_Float renames "abs";
   function F5D (L : My_Fixed) return My_Fixed renames "abs";

   function F0E (L : My_Boolean) return My_Boolean renames "not";
   function F1E (L : My_Modular) return My_Modular renames "not";
   function F2E (L : Boolean_Array) return Boolean_Array renames "not";

   function F1F (L : My_Modular; R : Natural) return My_Modular renames "**";
   function F3F (L : My_Integer; R : Natural) return My_Integer renames "**";
   function F4F (L : My_Float; R : Integer'Base) return My_Float renames "**";

   type My_Enumeration is (A, B);

   function "=" (L, R : My_Enumeration) return Boolean;
   function F65 (L, R : My_Enumeration) return Boolean renames "/=";

   function "=" (L, R : My_Enumeration) return Boolean is
   begin
      return False;
   end "=";
begin
   null;
end;
