------------------------------------------------------------------------------
--                         G E L A   H A S H                                --
--                 Repository implementation for Gela                       --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  Purpose:
--  Hash by SHA algoritm
--

with Ada.Streams;

package Gela.Hash.SHA is

   type Hasher is
     abstract tagged private;

   procedure Update
     (This  : in out Hasher'Class;
      Value : in     String);

   procedure Wide_Update
     (This  : in out Hasher'Class;
      Value : in     Wide_String);

   procedure Wide_Wide_Update
     (This  : in out Hasher'Class;
      Value : in     Wide_Wide_String);

   procedure Update
     (This  : in out Hasher;
      Value : in     Ada.Streams.Stream_Element_Array) is abstract;

private

   type Hasher is abstract tagged record
      Length : Natural := 0;
      Last   : Ada.Streams.Stream_Element_Offset := 0;
   end record;

end Gela.Hash.SHA;

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
