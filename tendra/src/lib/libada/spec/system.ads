------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package System is
   pragma Pure (System);

   type Name is (implementation_defined);
   --  implementation-defined-enumeration-type;
   System_Name : constant Name := implementation-defined;

   -- System-Dependent Named Numbers:

   Min_Int               : constant := root_integer'First;
   Max_Int               : constant := root_integer'Last;

   Max_Binary_Modulus    : constant := implementation-defined;
   Max_Nonbinary_Modulus : constant := implementation-defined;

   Max_Base_Digits       : constant := root_real'Digits;
   Max_Digits            : constant := implementation-defined;

   Max_Mantissa          : constant := implementation-defined;
   Fine_Delta            : constant := implementation-defined;

   Tick                  : constant := implementation-defined;

   -- Storage-related Declarations:

   type Address is private; --  implementation-defined;
   Null_Address : constant Address;

   Storage_Unit : constant := implementation-defined;
   Word_Size    : constant := implementation-defined * Storage_Unit;
   Memory_Size  : constant := implementation-defined;

   -- Address Comparison:
   function "<"  (Left, Right : Address) return Boolean;
   function "<=" (Left, Right : Address) return Boolean;
   function ">"  (Left, Right : Address) return Boolean;
   function ">=" (Left, Right : Address) return Boolean;
   function "="  (Left, Right : Address) return Boolean;
   -- function "/=" (Left, Right : Address) return Boolean;
   -- "/=" is implicitly defined
   pragma Convention (Intrinsic, "<");
   pragma Convention (Intrinsic, "<=");
   pragma Convention (Intrinsic, ">");
   pragma Convention (Intrinsic, ">=");
   pragma Convention (Intrinsic, "=");
   -- and so on for all language-defined subprograms in this package

   -- Other System-Dependent Declarations:
   type Bit_Order is (High_Order_First, Low_Order_First);
   Default_Bit_Order : constant Bit_Order := implementation-defined;

   -- Priority-related declarations (see D.1):
   subtype Any_Priority is
     Integer range implementation-defined .. implementation-defined;
   subtype Priority is
     Any_Priority range Any_Priority'First .. implementation-defined;
   subtype Interrupt_Priority is Any_Priority
     range Priority'Last + 1 .. Any_Priority'Last;

   Default_Priority : constant Priority :=
     (Priority'First + Priority'Last) / 2;

private

   pragma Import (Ada, Address);
   pragma Import (Ada, Null_Address);
   pragma Import (Intrinsic, "<");
   pragma Import (Intrinsic, "<=");
   pragma Import (Intrinsic, ">");
   pragma Import (Intrinsic, ">=");
   pragma Import (Intrinsic, "=");

end System;



