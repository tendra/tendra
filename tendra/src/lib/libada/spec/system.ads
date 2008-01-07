------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$

package System is
   pragma Preelaborate (System);

   type Name is (Gela);
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
   pragma Convention (Intrinsic, ">=");
   pragma Convention (Intrinsic, ">=");
   pragma Convention (Intrinsic, "=");
   -- and so on for all language-defined subprograms in this package

   -- Other System-Dependent Declarations:
   type Bit_Order is (High_Order_First, Low_Order_First);
   Default_Bit_Order : constant Bit_Order;

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
   pragma Import (Intrinsic, ">=");
   pragma Import (Intrinsic, ">=");
   pragma Import (Intrinsic, "=");
   pragma Import (Ada, Default_Bit_Order);

end System;


------------------------------------------------------------------------------
--  Copyright (c) 2006, Maxim Reznik
--  All rights reserved.
--
--  Redistribution and use in source and binary forms, with or without
--  modification, are permitted provided that the following conditions are met:
--
--     * Redistributions of source code must retain the above copyright notice,
--     * this list of conditions and the following disclaimer.
--     * Redistributions in binary form must reproduce the above copyright
--     * notice, this list of conditions and the following disclaimer in the
--     * documentation and/or other materials provided with the distribution.
--
--  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
--  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
--  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
--  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
--  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
--  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
--  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
--  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
--  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
--  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
--  POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------
