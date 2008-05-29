------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package System.Storage_Elements is
   pragma Pure (System.Storage_Elements);

   type Storage_Offset is
     range implementation-Defined .. implementation-defined;

   subtype Storage_Count is Storage_Offset range 0 .. Storage_Offset'Last;

   type Storage_Element is mod implementation-defined;
   for Storage_Element'Size use Storage_Unit;

   type Storage_Array is array
     (Storage_Offset range <>) of aliased Storage_Element;
   for Storage_Array'Component_Size use Storage_Unit;

   -- Address Arithmetic:

   function "+" (Left : Address; Right : Storage_Offset)
                return Address;
   function "+" (Left : Storage_Offset; Right : Address)
                return Address;
   function "-" (Left : Address; Right : Storage_Offset)
                return Address;
   function "-" (Left, Right : Address)
                return Storage_Offset;

   function "mod" (Left : Address; Right : Storage_Offset)
                  return Storage_Offset;

   -- Conversion to/from integers:

   type Integer_Address is mod implementation-defined;
   function To_Address (Value : Integer_Address) return Address;
   function To_Integer (Value : Address) return Integer_Address;

   pragma Convention (Intrinsic, "+");
   pragma Convention (Intrinsic, "-");
   pragma Convention (Intrinsic, "mod");
   pragma Convention (Intrinsic, "To_Address");
   pragma Convention (Intrinsic, "To_Integer");
   -- and so on for all language-defined subprograms declared in this package.
end System.Storage_Elements;



