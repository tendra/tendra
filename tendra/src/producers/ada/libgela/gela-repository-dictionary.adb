
with Ada.Unchecked_Deallocation;
with Ada.Text_IO;

package body Gela.Repository.Dictionary is

   ------------
   -- Get_ID --
   ------------

   procedure Get_ID
     (This   : in out Gela_Dictionary;
      Value  : in     Code_Point_Array;
      Result :    out ID)
   is
      use Gela.Hash.CRC.b16;

      Position : Positive := 1;

      -- Insert --
      procedure Insert
      is
         Point : ID_Point;
      begin
         Point.Num  := Result;
         Point.Data := new Code_Point_Array'(Value);
         Point.Used := True;

         Insert (This, Position, Point);
         This.Changed := True;
      end Insert;

   begin
      if Value = "" then
         Result := 0;
         return;
      end if;

      Result   := Wide_Wide_Calculate (Value);
      Position := Find (This, Result);

      if Position > Count (this) then
         Insert;
         return;
      end if;

      if This.Data (Position).Num = Result then
         if This.Data (Position).Data.all /= Value then
            Ada.Text_IO.Put_Line ("Gela.Repository.Dictionary bug detected");
            Ada.Text_IO.Put_Line ("dublicate ID (CRC16) for differetn values");
            raise Constraint_Error;
         end if;

         This.Data (Position).Used := True;
      else
         Insert;
      end if;
   end Get_ID;

   --------------
   -- Get_Name --
   --------------

   function Get_Name
     (This  : in Gela_Dictionary;
      Value : in ID)
      return Code_Point_Array
   is
      Position : Positive := Find (This, Value);
   begin
      if Position > Count (this) then
         return "";
      end if;

      if This.Data (Position).Num = Value then
         This.Data (Position).Used := True;
         return This.Data (Position).Data.all;
      else
         return "";
      end if;
   end Get_Name;

   -----------
   -- Marck --
   -----------

   procedure Marck
     (This  : in Gela_Dictionary;
      Value : in ID)
   is
      Position : Positive := Find (This, Value);
   begin
      if Position <= Count (this) then
         if This.Data (Position).Num = Value then
            This.Data (Position).Used := True;
         end if;
      end if;
   end Marck;

   -----------
   -- Clear --
   -----------

   procedure Deallocate is
     new Ada.Unchecked_Deallocation
       (Code_Point_Array, Code_Point_Array_Access);

   procedure Deallocate is
     new Ada.Unchecked_Deallocation
       (ID_Point_Array, ID_Point_Array_Access);

   procedure Clear
     (This : in out Gela_Dictionary)
   is
   begin
      if This.Data = null then
         return;
      end if;

      for Index in reverse This.Data'Range loop
         Deallocate (This.Data (Index).Data);
      end loop;

      Deallocate (This.Data);
   end Clear;

   -----------
   -- Count --
   -----------

   function Count
     (This : in Gela_Dictionary)
      return Natural
   is
   begin
      if This.Data = null then
         return 0;
      else
         return This.Data'Length;
      end if;
   end Count;

   --------------
   -- Finalize --
   --------------

   procedure Finalize
     (This : in out Gela_Dictionary)
   is
   begin
      Free_Unused (This);

      if This.Changed then
         Redirect_Save (This);
      end if;

      Clear (This);
   end Finalize;

   -----------------
   -- Free_Unused --
   -----------------

   procedure Free_Unused
     (This : in out Gela_Dictionary)
   is
   begin
      if This.Data = null then
         return;
      end if;

      for Index in reverse This.Data'Range loop
         if not This.Data (Index).Used then
            Delete (This, Index);
            This.Changed := True;
         end if;
      end loop;
   end Free_Unused;

   -------------------
   -- Redirect_Save --
   -------------------

   procedure Redirect_Save
     (This : in out Gela_Dictionary'Class)
   is
   begin
      Save (This);
   end Redirect_Save;

   ----------
   -- Save --
   ----------

   procedure Save
     (This : in out Gela_Dictionary)
   is
   begin
      null;
   end Save;

   ----------
   -- Find --
   ----------

   function Find
     (This : in Gela_Dictionary;
      Num  : in    ID)
      return Natural
   is
      L, H, I : Natural;
   begin
      if This.Data = null then
         return 1;
      end if;

      L := 1;
      H := This.Data'Last;

      while L <= H loop
         I := (L + H) / 2;

         if This.Data (I).Num < Num then
            L := I + 1;
         else
            H := I - 1;

            if This.Data (I).Num = Num then
               L := I;
            end if;
         end if;
      end loop;

      return L;
   end Find;

   ------------
   -- Insert --
   ------------

   procedure Insert
     (This  : in out Gela_Dictionary;
      Index : in     Positive;
      Point : in     ID_Point)
   is
   begin
      if This.Data = null then
         This.Data := new ID_Point_Array (1 .. 1);
         This.Data (1) := Point;
      else
         declare
            Internal_Array : constant ID_Point_Array_Access :=
              new ID_Point_Array (1 .. This.Data'Last + 1);
         begin
            Internal_Array (1 .. Index - 1) := This.Data (1 .. Index - 1);
            Internal_Array (Index) := Point;
            Internal_Array (Index + 1 .. Internal_Array'Last) :=
              This.Data (Index .. This.Data'Last);

            Deallocate (This.Data);
            This.Data := Internal_Array;
         end;
      end if;
   end Insert;

   ------------
   -- Delete --
   ------------

   procedure Delete
     (This  : in out Gela_Dictionary;
      Index : in     Positive)
   is
   begin
      if This.Data'Length = 1 then
         Deallocate (This.Data);
      else
         declare
            Internal_Array : constant ID_Point_Array_Access :=
              new ID_Point_Array (1 .. This.Data'Last - 1);
         begin
            Internal_Array (1 .. Index - 1) := This.Data (1 .. Index - 1);
            Internal_Array (Index .. Internal_Array'Last) :=
              This.Data (Index + 1 .. This.Data'Last);

            Deallocate (This.Data);
            This.Data := Internal_Array;
         end;
      end if;
   end Delete;

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
