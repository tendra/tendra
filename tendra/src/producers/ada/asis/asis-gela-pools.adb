with Ada.Unchecked_Deallocation;

package body Asis.Gela.Pools is

   --------------
   -- Allocate --
   --------------

   procedure Allocate
     (Pool                     : in out Storage_Pool;
      Storage_Address          :    out System.Address;
      Size_In_Storage_Elements : in     Storage_Count;
      Alignment                : in     Storage_Count)
   is
      Too_Large : exception;
      Block     : Block_Access  := Pool.Last;
      Offset    : Storage_Count :=
        (Block.Last + Alignment - 1) / Alignment * Alignment + 1;
   begin
      if Size_In_Storage_Elements > Block_Size then
         raise Too_Large;
      end if;

      if Offset + Size_In_Storage_Elements - 1 > Block_Size then
         Block           := new Storage_Block;
         Block.Head      := Pool.Last.Head;
         Block.Prev      := Pool.Last;
         Block.Head.Prev := Block;
         Pool.Last       := Block;
         Offset          := 1;
      end if;

      Storage_Address := Block.Data (Offset)'Address;
      Block.Last      := Offset + Size_In_Storage_Elements - 1;
   end Allocate;

   ----------------
   -- Deallocate --
   ----------------

   procedure Deallocate
     (Pool                     : in out Storage_Pool;
      Storage_Address          : in     System.Address;
      Size_In_Storage_Elements : in     Storage_Count;
      Alignment                : in     Storage_Count)
   is
      Individual_Deallocation : exception;
   begin
      raise Individual_Deallocation;
   end Deallocate;

   --------------------
   -- Deallocate_All --
   --------------------

   procedure Deallocate_All (Pool  : in out Pool_State) is
      procedure Free is new Ada.Unchecked_Deallocation
        (Storage_Block, Block_Access);

      Block : Block_Access := Pool.Head.Prev;
      Next  : Block_Access := Block.Prev;
   begin
      while Block /= Pool.Head loop
         Free (Block);
         Block := Next;
         Next  := Block.Prev;
      end loop;

      Free (Pool.Head);
   end Deallocate_All;

   --------------
   -- New_Pool --
   --------------

   function New_Pool return Pool_State is
      Block : constant Block_Access := new Storage_Block;
   begin
      Block.Head := Block;
      Block.Prev := Block;
      return (Head => Block);
   end New_Pool;

   ---------------
   -- Set_State --
   ---------------

   procedure Set_State
     (Pool  : in out Storage_Pool;
      State : in     Pool_State)
   is
   begin
      if State.Head = null then
         Pool.Last := null;
      else
         Pool.Last := State.Head.Prev;
      end if;
   end Set_State;

   -----------
   -- State --
   -----------

   function State (Pool : in Storage_Pool) return Pool_State is
   begin
      if Pool.Last = null then
         return (Head => null);
      else
         return (Head => Pool.Last.Head);
      end if;
   end State;

   ------------------
   -- Storage_Size --
   ------------------

   function Storage_Size (Pool : in Storage_Pool) return Storage_Count is
   begin
      return Storage_Count'Last;
   end Storage_Size;

end Asis.Gela.Pools;



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
