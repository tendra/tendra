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
--  Direct pointer (cursor) to code units provided to speed access up.
--  User is responsible to watch pointer stay in buffer boundaries.
--  Special code unit value (End_Of_File) is returned when end of
--  source buffer is reached.

with Interfaces.C.Pointers;

package Gela.Source_Buffers is
   pragma Preelaborate;

   type Cursor is private;

   type Source_Buffer is abstract tagged private;

   function Buffer_Start (Object : Source_Buffer) return Cursor is abstract;

   subtype Code_Unit is Character;

   function Element (Object : Cursor) return Code_Unit;

   procedure Next (Object : in out Cursor);

   End_Of_File : constant Code_Unit;

   Use_Error  : exception;

private
   pragma Inline (Element);
   pragma Inline (Next);

   End_Of_File : constant Code_Unit := Code_Unit'Val (0);

   type Code_Unit_Array is array (Positive range <>) of aliased Code_Unit;

   package Pointers is new Interfaces.C.Pointers
     (Index              => Positive,
      Element            => Code_Unit,
      Element_Array      => Code_Unit_Array,
      Default_Terminator => End_Of_File);

   type Cursor is new Pointers.Pointer;

   type Source_Buffer is abstract tagged null record;

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
