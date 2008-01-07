------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Storage pool for compilation.
--  Using this storage pool we can deallocate whole compilation
--  in one shot. This is much faster then deallocate each AST node.
--  Such deallocation needed to IDE for fast recompilation of 
--  changed source.

with System.Storage_Pools;
with System.Storage_Elements; use System.Storage_Elements;

package Asis.Gela.Pools is
   pragma Preelaborate;

   type Storage_Pool is
     new System.Storage_Pools.Root_Storage_Pool with private;

   procedure Allocate
     (Pool                     : in out Storage_Pool;
      Storage_Address          :    out System.Address;
      Size_In_Storage_Elements : in     Storage_Count;
      Alignment                : in     Storage_Count);

   procedure Deallocate
     (Pool                     : in out Storage_Pool;
      Storage_Address          : in     System.Address;
      Size_In_Storage_Elements : in     Storage_Count;
      Alignment                : in     Storage_Count);

   function Storage_Size (Pool : in Storage_Pool) return Storage_Count;

   type Pool_State is private;

   function State (Pool : in Storage_Pool) return Pool_State;

   procedure Set_State
     (Pool  : in out Storage_Pool;
      State : in     Pool_State);

   procedure Deallocate_All (Pool  : in out Pool_State);

   function New_Pool      return Pool_State;

private

   Block_Size : constant := 4096;

   type Storage_Block;
   type Block_Access is access Storage_Block;

   type Storage_Block is record
      Head : Block_Access;
      Prev : Block_Access;
      Last : Storage_Count := 0;
      Data : Storage_Array (1 .. Block_Size);
   end record;

   type Storage_Pool is new System.Storage_Pools.Root_Storage_Pool with record
      Last : Block_Access;
   end record;

   type Pool_State is record
      Head : Block_Access;
   end record;

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
