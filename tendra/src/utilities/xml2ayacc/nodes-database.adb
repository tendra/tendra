with Ada.Strings.Unbounded;      use Ada.Strings.Unbounded;

package body Nodes.Database is

   type Attribute is record
      Name      : Unbounded_String;
      Type_Name : Unbounded_String;
   end record;

   type Attributes is array (Attribute_Index) of Attribute;

   type Node is record
      Name      : Unbounded_String;
      Attrs     : Attributes;
      Last_Attr : Attribute_Index;
   end record;

   type Nodes is array (Node_Index) of Node;

   All_Nodes : Nodes;

   Last_Node_Index : Node_Index;

   First_Node : Boolean := True;
   First_Attr : Boolean := True;

   --------------------
   -- Attribute_Name --
   --------------------

   function Attribute_Name
     (Node      : Node_Index;
      Attribute : Attribute_Index)
      return String
   is
   begin
      return To_String (All_Nodes (Node).Attrs (Attribute).Name);
   end Attribute_Name;

   --------------------
   -- Attribute_Type --
   --------------------

   function Attribute_Type
     (Node      : Node_Index;
      Attribute : Attribute_Index)
      return String
   is
   begin
      return To_String (All_Nodes (Node).Attrs (Attribute).Type_Name);
   end Attribute_Type;

   ----------------------
   -- Create_Attribute --
   ----------------------

   procedure Create_Attribute
      (Name      : String;
       Type_Name : String)
   is
      N : Node renames All_Nodes (Last_Node_Index);
   begin
      if First_Attr then
         First_Attr := False;
      else
         N.Last_Attr := N.Last_Attr + 1;
      end if;

      N.Attrs (N.Last_Attr).Name := To_Unbounded_String (Name);
      N.Attrs (N.Last_Attr).Type_Name := To_Unbounded_String (Type_Name);
   end Create_Attribute;

   -----------------
   -- Create_Node --
   -----------------

   procedure Create_Node
     (Name   : String;
      Parent : String)
   is
      Found  : Boolean;
      Upper  : Node_Index;
   begin
      if First_Node then
         Last_Node_Index := 1;
         First_Node := False;
      else
         Last_Node_Index := Last_Node_Index + 1;
      end if;
      All_Nodes (Last_Node_Index).Name := To_Unbounded_String (Name);
      All_Nodes (Last_Node_Index).Last_Attr := 1;
      First_Attr := True;
      if Parent /= "" then
         Find_Node (Parent, Upper, Found);
         for I in 1 .. Last_Attribute (Upper) loop
            Create_Attribute (Attribute_Name (Upper, I),
                              Attribute_Type (Upper, I));
         end loop;
      end if;
   end Create_Node;

   --------------------
   -- Find_Attribute --
   --------------------

   procedure Find_Attribute
     (Name      : in     String;
      Node      : in     Node_Index;
      Attribute :    out Attribute_Index;
      Found     :    out Boolean)
   is
      Count : constant Attribute_Index := All_Nodes (Node).Last_Attr;
      Attrs : Attributes renames All_Nodes (Node).Attrs;
   begin
      for I in 1 .. Count loop
         if Attrs (I).Name = Name then
            Attribute := I;
            Found := True;
            return;
         end if;
      end loop;
      Found := False;
   end Find_Attribute;

   ----------------------------
   -- Find_Attribute_By_Type --
   ----------------------------

   procedure Find_Attribute_By_Type
     (Type_Name : in     String;
      Node      : in     Node_Index;
      Attribute :    out Attribute_Index;
      Found     :    out Boolean)
   is
      Count : constant Attribute_Index := All_Nodes (Node).Last_Attr;
      Attrs : Attributes renames All_Nodes (Node).Attrs;
   begin
      Found := False;
      for I in 1 .. Count loop
         if Attrs (I).Type_Name = Type_Name then
            Attribute := I;
            if Found then         --  too much found
               Found := False;
               return;
            end if;
            Found := True;
         end if;
      end loop;
   end Find_Attribute_By_Type;

   ---------------
   -- Find_Node --
   ---------------

   procedure Find_Node
     (Name  : in     String;
      Node  :    out Node_Index;
      Found :    out Boolean)
   is
   begin
      for I in 1 .. Last_Node_Index loop
         if All_Nodes (I).Name = Name then
            Node := I;
            Found := True;
            return;
         end if;
      end loop;
      Found := False;
   end Find_Node;

   --------------------
   -- Last_Attribute --
   --------------------

   function Last_Attribute
     (Node      : Node_Index)
      return Attribute_Index
   is
   begin
      return All_Nodes (Node).Last_Attr;
   end Last_Attribute;

   ---------------
   -- Last_Node --
   ---------------

   function Last_Node return Node_Index is
   begin
      return Last_Node_Index;
   end Last_Node;

   ---------------
   -- Node_Name --
   ---------------

   function Node_Name (Node : Node_Index) return String is
   begin
      return To_String (All_Nodes (Node).Name);
   end Node_Name;

end Nodes.Database;



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
