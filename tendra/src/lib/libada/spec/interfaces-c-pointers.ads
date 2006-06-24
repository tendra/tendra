------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $

generic
   type Index is (<>);
   type Element is private;
   type Element_Array is array (Index range <>) of aliased Element;
   Default_Terminator : Element;
package Interfaces.C.Pointers is
   pragma Preelaborate(Pointers);

   type Pointer is access all Element;

   function Value (Ref        : in Pointer;
                   Terminator : in Element := Default_Terminator)
                  return Element_Array;

   function Value (Ref    : in Pointer;
                   Length : in ptrdiff_t)
                  return Element_Array;

   Pointer_Error : exception;

   -- C-style Pointer arithmetic

   function "+" (Left : in Pointer;   Right : in ptrdiff_t) return Pointer;
   function "+" (Left : in ptrdiff_t; Right : in Pointer)   return Pointer;
   function "-" (Left : in Pointer;   Right : in ptrdiff_t) return Pointer;
   function "-" (Left : in Pointer;   Right : in Pointer) return ptrdiff_t;

   procedure Increment (Ref : in out Pointer);
   procedure Decrement (Ref : in out Pointer);

   pragma Convention (Intrinsic, "+");
   pragma Convention (Intrinsic, "-");
   pragma Convention (Intrinsic, Increment);
   pragma Convention (Intrinsic, Decrement);

   function Virtual_Length (Ref        : in Pointer;
                            Terminator : in Element := Default_Terminator)
                           return ptrdiff_t;

   procedure Copy_Terminated_Array
     (Source     : in Pointer;
      Target     : in Pointer;
      Limit      : in ptrdiff_t := ptrdiff_t'Last;
      Terminator : in Element :=  Default_Terminator);

   procedure Copy_Array (Source  : in Pointer;
                         Target  : in Pointer;
                         Length  : in ptrdiff_t);

end Interfaces.C.Pointers;


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
