------------------------------------------------------------------------------
--                   G E L A   R E P O S I T O R Y                          --
--                 Repository implementation for Gela                       --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  Purpose:
--  Dictionary for set keyword's ID, with automatic clean unused IDs.

with Ada.Finalization;
with Gela.Hash.CRC_16;

package Gela.Repository.Dictionary is

   type ID is private;

   subtype Code_Point is Wide_Wide_Character range
     Wide_Wide_Character'Val (0) .. Wide_Wide_Character'Val (16#10FFFF#);

   type Code_Point_Array is array (Positive range <>) of Code_Point;

   type Gela_Dictionary is abstract
     new Ada.Finalization.Limited_Controlled with private;

   function Get_ID
     (This  : in Gela_Dictionary;
      Value : in Code_Point_Array)
      return ID is abstract;

private

   type ID is new Gela.Hash.CRC_16.CRC_Type;

   type Gela_Dictionary is abstract
     new Ada.Finalization.Limited_Controlled with null record;

end Gela.Repository.Dictionary;

------------------------------------------------------------------------------
--  Copyright (c) 2006, Andry Ogorodnik
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
