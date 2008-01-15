------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Abstract interface to source text buffers.
--
--  Such buffer contains source represented as array of code units.
--  Direct pointer to code units provided to speed access up. User is
--  responsible to watch pointer stay in buffer boundaries.

with System;
with Ada.Finalization;

package Gela.Source_Buffers is
   pragma Preelaborate;

   type Offset is range 0 .. Integer'Last;

   subtype Count is Offset range 1 .. Offset'Last;

   type Code_Unit_8 is mod 2 ** 8;
   type Code_Unit_8_Access is access all Code_Unit_8;

   type Code_Unit_16 is mod 2 ** 16;
   type Code_Unit_16_Access is access all Code_Unit_16;

   type Code_Unit_32 is mod 2 ** 32;
   type Code_Unit_32_Access is access all Code_Unit_32;

   function "+"
     (Left  : in Code_Unit_8_Access;
      Right : in Offset)
      return Code_Unit_8_Access;

   function "+"
     (Left  : in Code_Unit_16_Access;
      Right : in Offset)
      return Code_Unit_16_Access;

   function "+"
     (Left  : in Code_Unit_32_Access;
      Right : in Offset)
      return Code_Unit_32_Access;

   type Code_Unit_Size is (Unit_8, Unit_16, Unit_32);

   ----------------------------
   -- Abstract_Source_Buffer --
   ----------------------------

   type Abstract_Source_Buffer is abstract tagged limited private;

   function Data (This : in Abstract_Source_Buffer)
      return Code_Unit_8_Access;

   function Data (This : in Abstract_Source_Buffer)
      return Code_Unit_16_Access;

   function Data (This : in Abstract_Source_Buffer)
      return Code_Unit_32_Access;

   function Size
     (This      : in Abstract_Source_Buffer;
      Unit_Size : in Code_Unit_Size) return Offset;

   function Is_Open (This : in Abstract_Source_Buffer) return Boolean;

   procedure Close (This : in out Abstract_Source_Buffer) is abstract;

   Use_Error  : exception;

private
   pragma Inline ("+");
   pragma Inline (Is_Open);
   pragma Inline (Size);

   type Abstract_Source_Buffer is abstract
      new Ada.Finalization.Limited_Controlled
   with record
      Internal_Data : System.Address := System.Null_Address;
      Internal_Size : Offset         := 0;
   end record;

   procedure Finalize (This : in out Abstract_Source_Buffer);

end Gela.Source_Buffers;

------------------------------------------------------------------------------
--  Copyright (c) 2008, Maxim Reznik
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
--
--  Authors:
--    Andry Ogorodnik
--    Maxim Reznik
--    Vadim Godunko
------------------------------------------------------------------------------
