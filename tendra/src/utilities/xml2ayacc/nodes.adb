with Nodes.Database;
with Ada.Strings.Fixed;
with Ada.Characters.Handling;

package body Nodes is

   ----------------
   -- Capitalise --
   ----------------

   function Capitalise (Name : String) return String is
      use Ada.Characters.Handling;
      Buffer          : String := Name;
      Capitalise_Next : Boolean := True;
   begin
      for I in Buffer'Range loop
         if Capitalise_Next then
            Buffer (I) := To_Upper (Buffer (I));
            Capitalise_Next := False;
         elsif Buffer (I) = '_' or Buffer (I) = '.' then
            Capitalise_Next := True;
         else
            Buffer (I) := To_Lower (Buffer (I));
         end if;
      end loop;
      return Buffer;
   end Capitalise;

   ------------------------
   -- Get_Node_Type_Name --
   ------------------------

   function Get_Node_Type_Name (Name : String) return String is
      use Nodes.Database;
      use Ada.Strings.Fixed;

      Type_Name : constant String := Capitalise (Name & "_Node");
      Node      : Node_Index;
      Found     : Boolean;
   begin
      if Name'Length > 4 and then
        Name (Name'Last - 4 .. Name'Last) = ".List" then

         return Type_Name;

      end if;

      Find_Node (Type_Name, Node, Found);

      if not Found and Index (Type_Name, "_Definition") > 0 then
         declare
            Def_Pos  : constant Positive :=
              Index (Type_Name, "_Definition");
            Def_Name : constant String :=
              Delete (Type_Name, Def_Pos, Def_Pos + 10);
         begin
            Find_Node (Def_Name, Node, Found);
            if Found then
               return Def_Name;
            end if;
         end;
--         Ada.Text_IO.Put_Line ("Error: type " & Type_Name & " not found");
      end if;
      if not Found then
         return "";
      end if;

      return Type_Name;

   end Get_Node_Type_Name;

   ----------------------
   -- Get_Pointer_Name --
   ----------------------

   function Get_Pointer_Name (Type_Name : String) return String is
   begin
      if Type_Name'Length > 9 and then
        Type_Name (Type_Name'Last - 9 .. Type_Name'Last) = ".List_Node" then

         return Type_Name (1 .. Type_Name'Last - 5);

      end if;
      return Type_Name (1 .. Type_Name'Last - 4) & "Ptr";
   end Get_Pointer_Name;

   ----------------
   -- Initialize --
   ----------------

   procedure Initialize is
   begin
      null;
   end Initialize;

   --------------------
   -- Find_Procedure --
   --------------------

   function Find_Procedure
     (Node_Type_Name : String;
      Attr_Name      : String) return String
   is
      use Nodes.Database;

      Node      : Node_Index;
      Attr      : Attribute_Index;
      Found     : Boolean;
   begin
      if Attr_Name = "" then
         return "";
      end if;
      Find_Node (Node_Type_Name, Node, Found);
      if not Found then
         return "";
      end if;
      Find_Attribute (Attr_Name, Node, Attr, Found);
      if Found then
         return "Set_" & Attribute_Name (Node, Attr);
      end if;
      return "";
   end Find_Procedure;

   function Find_Attribute
     (Node_Type_Name : String;
      Attr_Name      : String) return String
   is
      use Nodes.Database;

      Node      : Node_Index;
      Attr      : Attribute_Index;
      Found     : Boolean;
   begin
      if Attr_Name = "" then
         return "";
      end if;
      Find_Node (Node_Type_Name, Node, Found);
      if not Found then
         return "";
      end if;
      Find_Attribute (Capitalise (Attr_Name), Node, Attr, Found);
      if not Found then
         Find_Attribute (Capitalise (Attr_Name & "s"), Node, Attr, Found);
         if not Found then
            return "";
         end if;
      end if;
      return Attribute_Name (Node, Attr);
   end Find_Attribute;

   function Find_Attr_By_Type
     (Node_Type_Name : String;
      Attr_Type_Name : String) return String
   is
      use Nodes.Database;

      Node      : Node_Index;
      Attr      : Attribute_Index;
      Found     : Boolean;
   begin
      if Attr_Type_Name = "" then
         return "";
      end if;
      Find_Node (Node_Type_Name, Node, Found);
      if not Found then
         return "";
      end if;
      Find_Attribute_By_Type (Attr_Type_Name, Node, Attr, Found);
      if not Found then
         return "";
      end if;
      return Attribute_Name (Node, Attr);
   end Find_Attr_By_Type;

   function Attribute_Type
     (Node_Type_Name : String;
      Attr_Name      : String) return String is
      use Nodes.Database;

      Node      : Node_Index;
      Attr      : Attribute_Index;
      Found     : Boolean;
   begin
      if Attr_Name = "" then
         return "";
      end if;
      Find_Node (Node_Type_Name, Node, Found);
      if not Found then
         return "";
      end if;
      Find_Attribute (Attr_Name, Node, Attr, Found);
      if not Found then
         return "";
      end if;
      return Attribute_Type (Node, Attr);
   end Attribute_Type;

end Nodes;



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
