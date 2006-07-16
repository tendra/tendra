with XASIS.Utils;
with Asis.Elements;
with Ada.Characters.Handling;

with TenDRA.Types;
with TenDRA.Output;
with TenDRA.Streams;

with Token;
with Declaration;

package body States is

   function External_Image (Link : Linkage) return String;
   procedure Start_Units (Object : in out State);

   procedure Output_Unit
     (Object : in out State;
      O      : in out TenDRA.Streams.File_Stream;
      Unit   : in     Unit_Kinds);

   function Visible (Link : Linkage) return Boolean;

   procedure On_New_Linkage
     (Object : access State;
      Result : in     Linkage_Access);

   ---------
   -- "=" --
   ---------

   function "=" (Left, Right : Linkage) return Boolean is
      use Asis.Elements;
      use type Asis.Attribute_Kinds;
   begin
      if Left.Kind = Right.Kind then
         case Left.Kind is
            when Tag | Proc_Tag | Name_Token =>
               return Is_Equal (Left.Name, Right.Name);
            when Shape_Token | Variety_Token | Type_Param_Token =>
               return XASIS.Classes.Is_Equal (Left.Tipe, Right.Tipe)
                 and then (Left.Kind /= Type_Param_Token
                           or else Left.Param = Right.Param);
            when Support_Token =>
               return Left.Support = Right.Support;
            when Subtype_Attribute_Token =>
               return Is_Equal (Left.Subtype_Name, Right.Subtype_Name)
                 and then Left.Attribute = Right.Attribute;
         end case;
      else
         return False;
      end if;
   end "=";

   --------------------
   -- Create_Capsule --
   --------------------

   procedure Create_Capsule
     (Object    : in out State;
      File_Name : in     String)
   is
      use TenDRA;
      use TenDRA.Types;

      S : State               renames Object;
      O : Streams.File_Stream;
      M : Streams.Memory_Stream;

      --------------------
      -- Write_Linkages --
      --------------------

      procedure Write_Linkages (List : Linkage_Lists.List) is
         Link : aliased Linkage_Access;
      begin
         while Linkage_Lists.Iterate (List, Link'Access) loop
            if Link.Extern then
               Output.TDF (O, c_make_linkextern);
               Output.TDFINT (O, Link.Code);
               Output.TDF (O, c_string_extern);
               Output.TDFIDENT (O, External_Image (Link.all));
            end if;
         end loop;
      end Write_Linkages;

      ---------------
      -- Write_TLD --
      ---------------

      procedure Write_TLD (List : Linkage_Lists.List) is
         Link : aliased Linkage_Access;
      begin
         while Linkage_Lists.Iterate (List, Link'Access) loop
            if Link.Extern then
               Output.TDFINT (M, Small (Link.Usage), Check => False);
            end if;
         end loop;
      end Write_TLD;

      -------------------------
      -- Write_Unit_Linkages --
      -------------------------

      procedure Write_Unit_Linkages
        (Unit : Unit_Kinds; List : Linkage_Lists.List)
      is
         Link : aliased Linkage_Access;
      begin
         while Linkage_Lists.Iterate (List, Link'Access) loop
            if Link.Unit_Code (Unit) /= Nil and then Link.Code /= Nil then
               Output.TDF (O, c_make_link);
               Output.TDFINT (O, Link.Unit_Code (Unit));
               Output.TDFINT (O, Link.Code);
            end if;
         end loop;
      end Write_Unit_Linkages;

      Group_Count   : constant := 6;
      Linkage_Count : constant := Linkages_Array'Length;
   begin
      Streams.Create (O, File_Name);
      Streams.Save (O, Character'Pos ('T'));
      Streams.Save (O, Character'Pos ('D'));
      Streams.Save (O, Character'Pos ('F'));
      Streams.Save (O, Character'Pos ('C'));

      Output.TDFINT (O, Types.Version_Major, Check => False);
      Output.TDFINT (O, Types.Version_Minor, Check => False);
      Streams.Expect (O, Dummy, (1 => (CAPSULE_SORT, Singular, False)));
      Output.TDF (O, c_make_capsule);

      Output.List_Count (O, Group_Count);
      Output.TDFIDENT (O, "tld");
      Output.TDFIDENT (O, "versions");
      Output.TDFIDENT (O, "tokdec");
      Output.TDFIDENT (O, "tokdef");
      Output.TDFIDENT (O, "tagdec");
      Output.TDFIDENT (O, "tagdef");

      Output.List_Count (O, Linkage_Count);

      for Link_Kind in Link_Kinds loop
         Output.TDF (O, c_make_capsule_link);

         case Link_Kind is
            when Tag =>   Output.TDFIDENT (O, "tag");
            when Token => Output.TDFIDENT (O, "token");
         end case;

         Output.TDFINT (O, Object.Total (Link_Kind));
      end loop;

      Output.List_Count (O, Linkage_Count);

      for Link_Kind in Link_Kinds loop
         Output.TDF (O, c_make_extern_link);
         Output.List_Count (O, Object.Extern (Link_Kind));
         Write_Linkages (Object.Linkages (Link_Kind));
      end loop;

      Output.List_Count (O, Group_Count);

      --  TLD unit
      Output.TDF (O, c_make_group);
      Output.List_Count (O, 1);
      Output.TDF (O, c_make_unit);
      Output.List_Count (O, 0);
      Output.List_Count (O, 0);

      Streams.Reset (M);
      Output.TDFINT (M, 1, Check => False);
      Write_TLD (Object.Linkages (Tag));
      Write_TLD (Object.Linkages (Token));
      Output.BYTESTREAM (O, M);

      --  VERSION unit
      Output.TDF (O, c_make_group);
      Output.List_Count (O, 1);
      Output.TDF (O, c_make_unit);
      Output.List_Count (O, Linkage_Count);

      for Link_Kind in Link_Kinds loop
         Output.TDFINT (O, 0);
      end loop;

      Output.List_Count (O, Linkage_Count);

      for Link_Kind in Link_Kinds loop
         Output.TDF (O, c_make_links);
         Output.List_Count (O, 0);
      end loop;

      Streams.Reset (M);
      Streams.Expect (M, Dummy, (1 => (VERSION_PROPS_SORT, Singular, False)));
      Output.TDF (M, c_make_versions);
      Output.List_Count (M, 1);
      Output.TDF (M, c_make_version);
      Output.TDFINT (M, Types.Version_Major);
      Output.TDFINT (M, Types.Version_Minor);

      Output.BYTESTREAM (O, M);

      --  other units
      for Unit in Unit_Kinds loop
         Output.TDF (O, c_make_group);
         Output.List_Count (O, 1);
         Output.TDF (O, c_make_unit);
         Output.List_Count (O, Linkage_Count);

         for Link_Kind in Link_Kinds loop
            Output.TDFINT (O, S.Unit_Total (Unit, Link_Kind));
         end loop;

         Output.List_Count (O, Linkage_Count);

         for Link_Kind in Link_Kinds loop
            Output.TDF (O, c_make_links);
            Output.List_Count (O, S.Unit_Extern (Unit, Link_Kind));
            Write_Unit_Linkages (Unit, Object.Linkages (Link_Kind));
         end loop;

         Output_Unit (Object, O, Unit);
      end loop;

      TenDRA.Streams.Flush_Byte (O);
   end Create_Capsule;

   --------------------
   -- External_Image --
   --------------------

   function External_Image (Link : Linkage) return String is
      use Ada.Characters.Handling;

      function Suffix return String is
      begin
         case Link.Kind is
            when Variety_Token => return ".V";
            when Name_Token    => return ".N";
            when Type_Param_Token =>
               return "." & Type_Param_Kinds'Image (Link.Param);
            when others        => return "";
         end case;
      end Suffix;

   begin
      case Link.Kind is
         when Tag | Proc_Tag | Name_Token =>
            return To_String (XASIS.Utils.External_Name_Image (Link.Name))
                 & Suffix;
         when Shape_Token | Variety_Token | Type_Param_Token =>
            declare
               Decl : constant Asis.Declaration :=
                 XASIS.Classes.Get_Declaration (Link.Tipe);
            begin
               return To_String (XASIS.Utils.External_Image (Decl))
                 & Suffix;
            end;
         when Support_Token =>
            return Support_Kinds'Image (Link.Support);
         when Subtype_Attribute_Token =>
            return To_String
              (XASIS.Utils.External_Image (Link.Subtype_Name))
              & '.' & Asis.Attribute_Kinds'Image (Link.Attribute);
      end case;

   end External_Image;

   ----------
   -- Find --
   ----------

   function Find
     (Object : access State;
      Link   : in     Linkage;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return Linkage_Access
   is
      use TenDRA;
      package Search is new Linkage_Lists.Generic_Search;

      Kind     : Link_Kinds;
      New_Link : Boolean := False;
      Result   : Linkage_Access;
   begin
      case Link.Kind is
         when Tag | Proc_Tag =>
           Kind := Tag;
         when Shape_Token
           | Variety_Token
           | Support_Token
           | Name_Token
           | Subtype_Attribute_Token
           | Type_Param_Token
           =>
            Kind := Token;
      end case;

      Result := Search.Find (Object.Linkages (Kind), Link);

      if Result = null then
         Result           := new Linkage'(Link);
         Result.Next      := null;
         Result.Code      := Nil;
         Result.Usage     := 0;
         Result.Unit_Code := (others => Nil);
         Result.Extern    := Visible (Result.all);

         if Result.Extern then
            Result.Code   := Object.Total (Kind);
            Inc (Object.Total (Kind));
            Inc (Object.Extern (Kind));
         end if;

         Linkage_Lists.Append (Object.Linkages (Kind), Result);
         New_Link := True;
      end if;

      if Result.Unit_Code (Unit) = Nil then
         if Result.Code = Nil
           and then Result.Unit_Code /= (Unit_Kinds => Nil)
         then
            Result.Code := Object.Total (Kind);
            Inc (Object.Total (Kind));

            for J in Unit_Kinds loop
               if Result.Unit_Code (J) /= Nil then
                  Inc (Object.Unit_Extern (J, Kind));
               end if;
            end loop;
         end if;

         Result.Unit_Code (Unit) := Object.Unit_Total (Unit, Kind);
         Inc (Object.Unit_Total (Unit, Kind));

         if Result.Code /= Nil then
            Inc (Object.Unit_Extern (Unit, Kind));
         end if;
      end if;

      if New_Link then
         On_New_Linkage (Object, Result);
      end if;

      if Usage and then (Result.Usage and Used) = 0 then
         Result.Usage := Result.Usage or Used;
      elsif not Usage and then (Result.Usage and Defined) = 0 then
         Result.Usage := Result.Usage or Defined;
      end if;

      return Result;
   end Find;

   ----------
   -- Find --
   ----------

   function Find
     (Object : access State;
      Link   : in     Linkage;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small
   is
      Found : constant Linkage_Access := Find (Object, Link, Unit, Usage);
   begin
      return Found.Unit_Code (Unit);
   end Find;

   --------------------
   -- Find_Attribute --
   --------------------

   function Find_Attribute
     (Object : access State;
      Tipe   : in     Asis.Declaration;
      Attr   : in     Asis.Attribute_Kinds;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small
   is
      Link : Linkage (Subtype_Attribute_Token);
   begin
      Link.Subtype_Name := Tipe;
      Link.Attribute    := Attr;

      return Find (Object, Link, Unit, Usage);
   end Find_Attribute;

   ---------------
   -- Find_Name --
   ---------------

   function Find_Name
     (Object : access State;
      Name   : in     Asis.Defining_Name;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small
   is
      Link : Linkage (Name_Token);
   begin
      Link.Name := Name;
      return Find (Object, Link, Unit, Usage);
   end Find_Name;

   ---------------
   -- Find_Proc --
   ---------------

   function Find_Proc
     (Object : access State;
      Name   : in     Asis.Defining_Name;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small
   is
      Link : Linkage (Proc_Tag);
   begin
      Link.Name := Name;
      return Find (Object, Link, Unit, Usage);
   end Find_Proc;

   --------------
   -- Find_Tag --
   --------------

   function Find_Tag
     (Object : access State;
      Name   : in     Asis.Defining_Name;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small
   is
      Link : Linkage (Tag);
   begin
      Link.Name := Name;
      return Find (Object, Link, Unit, Usage);
   end Find_Tag;

   ---------------------
   -- Find_Type_Param --
   ---------------------

   function Find_Type_Param
     (Object : access State;
      Tipe   : in     XASIS.Classes.Type_Info;
      Param  : in     Type_Param_Kinds;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small
   is
      Link : Linkage (Type_Param_Token);
   begin
      Link.Tipe  := Tipe;
      Link.Param := Param;
      return Find (Object, Link, Unit, Usage);
   end Find_Type_Param;

   ----------------
   -- Find_Shape --
   ----------------

   function Find_Shape
     (Object : access State;
      Tipe   : in     XASIS.Classes.Type_Info;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small
   is
      Link : Linkage (Shape_Token);
   begin
      Link.Tipe := Tipe;
      return Find (Object, Link, Unit, Usage);
   end Find_Shape;

   ------------------
   -- Find_Support --
   ------------------

   function Find_Support
     (Object : access State;
      Kind   : in     Support_Kinds;
      Unit   : in     Unit_Kinds := TAGDEF) return TenDRA.Small
   is
      Link : Linkage (Support_Token);
   begin
      Link.Support := Kind;
      return Find (Object, Link, Unit);
   end Find_Support;

   ------------------
   -- Find_Variety --
   ------------------

   function Find_Variety
     (Object : access State;
      Tipe   : in     XASIS.Classes.Type_Info;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small
   is
      Link : Linkage (Variety_Token);
   begin
      Link.Tipe := Tipe;
      return Find (Object, Link, Unit, Usage);
   end Find_Variety;

   --------------
   -- Get_Next --
   --------------

   function Get_Next (Item : Linkage_Access) return Linkage_Access is
   begin
      return Item.Next;
   end Get_Next;

   ----------------
   -- Initialize --
   ----------------

   procedure Initialize (Object : in out State) is
      Zeros : constant Counts := (others => (others => 0));
   begin
      Object.Units          := (others => new TenDRA.Streams.Memory_Stream);
      Object.Total          := (others => 0);
      Object.Extern         := (others => 0);
      Object.Unit_Total     := Zeros;
      Object.Unit_Extern    := Zeros;
      Object.Labels         := (others => 0);
      Object.Length         := (others => 0);
      Start_Units (Object);
   end Initialize;

   --------------------
   -- On_New_Linkage --
   --------------------

   procedure On_New_Linkage
     (Object : access State;
      Result : in     Linkage_Access)
   is
   begin
      case Result.Kind is
         when Shape_Token | Variety_Token | Support_Token | Name_Token
           | Subtype_Attribute_Token | Type_Param_Token =>
            Standard.Token.New_Token (Object, Result);
         when Tag | Proc_Tag =>
            Declaration.New_Tag (Object, Result);
      end case;
   end On_New_Linkage;

   -----------------
   -- Output_Unit --
   -----------------

   procedure Output_Unit
     (Object : in out State;
      O      : in out TenDRA.Streams.File_Stream;
      Unit   : in     Unit_Kinds)
   is
      use TenDRA;
      use TenDRA.Types;
      M : Streams.Memory_Stream;
   begin
      if Unit /= TOKDEC then
         Output.TDFINT (M, Object.Labels (Unit), Check => False);
      end if;

      Output.TDFINT (M, Object.Length (Unit), Check => False, Align => True);
      Streams.Prepend (Object.Units (Unit).all, M);
      Output.BYTESTREAM (O, Object.Units (Unit).all);
   end Output_Unit;

   --------------
   -- Set_Next --
   --------------

   procedure Set_Next (Item, Next : Linkage_Access) is
   begin
      Item.Next := Next;
   end Set_Next;

   -----------------
   -- Start_Units --
   -----------------

   procedure Start_Units (Object : in out State) is
      use TenDRA;
      use TenDRA.Types;

      procedure Skip_Labels (S : in out Streams.Stream'Class) is
      begin
         Streams.Check (S, TDFINT_SORT);
      end Skip_Labels;
   begin
      for Unit in Unit_Kinds loop
         case Unit is
            when TOKDEC =>
               Streams.Expect (Object.Units (Unit).all,
                               Dummy,
                               (1 => (TOKDEC_PROPS_SORT, Singular, False)));
               Output.TDF (Object.Units (Unit).all, c_make_tokdecs);
            when TOKDEF =>
               Streams.Expect (Object.Units (Unit).all,
                               Dummy,
                               (1 => (TOKDEF_PROPS_SORT, Singular, False)));
               Output.TDF (Object.Units (Unit).all, c_make_tokdefs);
               Skip_Labels (Object.Units (Unit).all);
            when TAGDEC =>
               Streams.Expect (Object.Units (Unit).all,
                               Dummy,
                               (1 => (TAGDEC_PROPS_SORT, Singular, False)));
               Output.TDF (Object.Units (Unit).all, c_make_tagdecs);
               Skip_Labels (Object.Units (Unit).all);
            when TAGDEF =>
               Streams.Expect (Object.Units (Unit).all,
                               Dummy,
                               (1 => (TAGDEF_PROPS_SORT, Singular, False)));
               Output.TDF (Object.Units (Unit).all, c_make_tagdefs);
               Skip_Labels (Object.Units (Unit).all);
         end case;

         --  Unit Length
         Output.List_Count (Object.Units (Unit).all, Streams.Unknown_Length);
      end loop;
   end Start_Units;

   -------------
   -- Visible --
   -------------

   function Visible (Link : Linkage) return Boolean is
      use XASIS.Utils;
   begin
      if Link.Kind = Tag and then Lexic_Level (Link.Name) > 1 then
         return False;
      else
         return True;   --  TODO
      end if;
   end Visible;

end States;


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
