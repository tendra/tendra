------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $

package System.Storage_Elements is
   pragma Preelaborate (System.Storage_Elements);

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
