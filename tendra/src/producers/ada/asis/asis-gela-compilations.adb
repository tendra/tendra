with Asis.Gela.Lists;
with Asis.Gela.Unit_Utils;

with Ada.Unchecked_Deallocation;

package body Asis.Gela.Compilations is

   use type U.Unbounded_Wide_String;

   procedure Free is new Ada.Unchecked_Deallocation
     (Compilation_List_Node, Compilation_List);

   Version : Version_Count := 0;

   -------------
   -- Decoder --
   -------------

   function Decoder
     (List : Compilation_List;
      Item : Compilation) return Text_Utils.Decoder_Access
   is
   begin
      if Valid_Version (List, Item) then
         return List.Nodes (Item.Index).Decoder;
      else
         return null;
      end if;
   end Decoder;

   ----------------------
   -- Drop_Compilation --
   ----------------------

   procedure Drop_Compilation
     (List : in out Compilation_List;
      Item : in     Compilation)
   is
   begin
      if Valid_Version (List, Item) then
         Version := Version + 1;
         List.Nodes (Item.Index).Version   := Version;
         List.Nodes (Item.Index).File_Name := U.Null_Unbounded_Wide_String;
         Pools.Deallocate_All (List.Nodes (Item.Index).Pool);
         Text_Utils.Free (List.Nodes (Item.Index).Buffer);
      end if;
   end Drop_Compilation;

   ---------------
   -- Enclosing --
   ---------------

   function Enclosing (Object : Asis.Element) return Compilation is
   begin
      return Enclosing (Enclosing_Compilation_Unit (Object.all));
   end Enclosing;

   ---------------
   -- Enclosing --
   ---------------

   function Enclosing (Object : Asis.Compilation_Unit) return Compilation is
   begin
      return Unit_Utils.Compilation (Object);
   end Enclosing;

   --------------
   -- Finalize --
   --------------

   procedure Finalize (List : in out Compilation_List) is
   begin
      if List = null then
         return;
      end if;

      for J in 1 .. List.Last loop
         if List.Nodes (J).File_Name /= U.Null_Unbounded_Wide_String then
            Pools.Deallocate_All (List.Nodes (J).Pool);
         end if;
      end loop;

      Free (List);
   end Finalize;

   ---------------------
   -- Get_Compilation --
   ---------------------

   function Get_Compilation
     (List : in Compilation_List;
      File : in Wide_String)
      return Compilation
   is
      Max : Compilation_Count := 0;
      Ver : Version_Count     := 0;
   begin
      for J in 1 .. List.Last loop
         if List.Nodes (J).File_Name = File then
            if Max = 0
              or else Version - List.Nodes (J).Version < Version - Ver
            then
               Max := J;
               Ver := List.Nodes (J).Version;
            end if;
         end if;
      end loop;

      if Max = 0 then
         return (1, 0);
      end if;

      return (Max, Ver);
   end Get_Compilation;

   ----------------
   -- Initialize --
   ----------------

   procedure Initialize (List : out Compilation_List) is
   begin
      List      := new Compilation_List_Node (10);
      List.Last := 0;
   end Initialize;

   ---------------------
   -- New_Compilation --
   ---------------------

   procedure New_Compilation
     (List     : in out Compilation_List;
      File     : in     Wide_String;
      Buffer   : in     Text_Utils.Source_Buffer_Access;
      Decoder  : in     Text_Utils.Decoder_Access;
      Item     :    out Compilation)
   is
      Index : Compilation_Count := List.Last + 1;
   begin
      for J in 1 .. List.Last loop
         if List.Nodes (J).File_Name = U.Null_Unbounded_Wide_String then
            Index := J;
            exit;
         end if;
      end loop;

      if Index > List.Length then
         declare
            Save : constant Compilation_List :=
              new Compilation_List_Node (2 * List.Length);
         begin
            Save.Nodes (1 .. List.Last) := List.Nodes (1 .. List.Last);
            Save.Last := List.Last;
            Free (List);
            List := Save;
         end;
      end if;

      if Index > List.Last then
         List.Last := Index;
      end if;

      Pools.Set_State (Lists.Pool, Pools.New_Pool);

      Version                      := Version + 1;
      List.Nodes (Index).File_Name := U.To_Unbounded_Wide_String (File);
      List.Nodes (Index).Version   := Version;
      List.Nodes (Index).Pool      := Pools.State (Lists.Pool);
      List.Nodes (Index).Buffer    := Buffer;
      List.Nodes (Index).Decoder   := Decoder;

      Item                         := (Index, Version);
   end New_Compilation;

   -------------------
   -- Source_Buffer --
   -------------------

   function Source_Buffer
     (List : Compilation_List;
      Item : Compilation) return Text_Utils.Source_Buffer_Access
   is
   begin
      if Valid_Version (List, Item) then
         return List.Nodes (Item.Index).Buffer;
      else
         return null;
      end if;
   end Source_Buffer;

   -------------------
   -- Valid_Version --
   -------------------

   function Valid_Version
     (List : Compilation_List;
      Item : Compilation)
      return Boolean
   is
   begin
      return List.Nodes (Item.Index).Version = Item.Version;
   end Valid_Version;

end Asis.Gela.Compilations;



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
