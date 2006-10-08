with Asis;
with XASIS.Classes;
with TenDRA.Streams;
with Gela.Embeded_Links.Lists;

package States is

   type Unit_Kinds is (TOKDEC, TOKDEF, TAGDEC, TAGDEF);
   type Link_Kinds is (Tag, Token);

   type Linkage;
   type Linkage_Access is access all Linkage;

   type Unit_Count is array (Unit_Kinds) of TenDRA.Small;

   type Linkage_Kinds is
     (Tag, Proc_Tag, Shape_Token, Variety_Token,
      Name_Token, Value_Token, Support_Token, Type_Param_Token,
      Subtype_Attribute_Token);

   type Support_Kinds is
     (Compare_Integer_Value, Boolean_Jump, Constraint_Error_If,
      Enum_Succ_Pred_Attr, Signed_Succ_Pred_Attr,
      Enum_Val_Attr, Signed_Val_Attr, Signed_Base_Lower, Signed_Base_Upper,
      Mod_Plus, Mod_Minus, Mod_Multiply, Mod_Or, Mod_Xor, Mod_And,
      Mod_Not, Mod_Negative, Mod_Power,
      Test_Range_Jump,
      Make_Float_Id, Make_Float_Range_Id, Rep_Fv, Rep_Fv_Max_Val,

      Make_Denorm_Attribute,            Make_Machine_Emax_Attribute,
      Make_Machine_Emin_Attribute,      Make_Machine_Mantissa_Attribute,
      Make_Machine_Overflows_Attribute, Make_Machine_Radix_Attribute,
      Make_Machine_Rounds_Attribute,    Make_Signed_Zeros_Attribute,

      Make_Ceiling_Attribute,           Make_Floor_Attribute,
      Make_Rounding_Attribute,          Make_Truncation_Attribute,
      Make_Unbiased_Rounding_Attribute, Make_Exponent_Attribute, 
      Make_Fraction_Attribute,          Make_Machine_Attribute,
      Make_Model_Attribute,

      Make_Adjacent_Attribute,          Make_Copy_Sign_Attribute,
      Make_Remainder_Attribute,         Make_Leading_Part_Attribute,
      Make_Compose_Attribute,           Make_Scaling_Attribute,

      Compare_Float_Value);

   --  Float point attributes (as value):
   subtype Make_Float_Attr is Support_Kinds
     range Make_Denorm_Attribute .. Make_Signed_Zeros_Attribute;

   --  Float point attributes with 1 argument:
   subtype Make_Float_Attr_1 is Support_Kinds
     range Make_Ceiling_Attribute .. Make_Model_Attribute;

   --  Float point attributes with 2 arguments:
   subtype Make_Float_Attr_2 is Support_Kinds
     range Make_Adjacent_Attribute .. Make_Scaling_Attribute;

   type Type_Param_Kinds is
     (Lower, Upper, Base_Lower, Base_Upper, Float_Id);

   Nil      : constant TenDRA.Small := TenDRA.Small'Last;

   type Usages is mod 2 ** 4;
   --  Usage bits:
   Used     : constant Usages := 1;
   Declared : constant Usages := 2;
   Defined  : constant Usages := 4;
   Multiple : constant Usages := 8;

   type Linkage (Kind : Linkage_Kinds) Is record
      Next      : Linkage_Access;
      Code      : TenDRA.Small;
      Usage     : Usages;
      Unit_Code : Unit_Count;
      Extern    : Boolean;

      case Kind is
         when Tag | Proc_Tag | Name_Token | Value_Token =>
            Name    : Asis.Defining_Name;
         when Shape_Token | Variety_Token | Type_Param_Token =>
            Tipe    : XASIS.Classes.Type_Info;

            case Kind is
               when Type_Param_Token =>
                  Param   : Type_Param_Kinds;
               when others =>
                  null;
            end case;
         when Support_Token =>
            Support : Support_Kinds;
         when Subtype_Attribute_Token =>
            Subtype_Name : Asis.Declaration;
            Attribute    : Asis.Attribute_Kinds;
      end case;
   end record;

   function  Get_Next (Item : Linkage_Access) return Linkage_Access;
   procedure Set_Next (Item, Next : Linkage_Access);
   function "=" (Left, Right : Linkage) return Boolean;

   package Linkage_Lists is
      new Gela.Embeded_Links.Lists (Linkage, Linkage_Access);

   type Stream_Access is access all TenDRA.Streams.Memory_Stream;

   type Unit_Streams   is array (Unit_Kinds) of Stream_Access;
   type Counts         is array (Unit_Kinds, Link_Kinds) of TenDRA.Small;
   type Linkages_Array is array (Link_Kinds) of Linkage_Lists.List;
   type Link_Counts    is array (Link_Kinds) of TenDRA.Small;

   type Loop_Info;
   type Loop_Info_Access is access all Loop_Info;

   type Loop_Info is record
      Next         : Loop_Info_Access;
      Element      : Asis.Statement;
      Repeat_Label : TenDRA.Small;
      Exit_Label   : TenDRA.Small;
   end record;

   type State is record
      Units          : Unit_Streams;
      Linkages       : Linkages_Array;
      Total          : Link_Counts;
      Extern         : Link_Counts;
      Unit_Total     : Counts;
      Unit_Extern    : Counts;
      Labels         : Unit_Count;
      Length         : Unit_Count;
      Unit           : Asis.Compilation_Unit;
   end record;

   procedure Initialize (Object : in out State);

   procedure Create_Capsule
     (Object    : in out State;
      File_Name : in     String);

   function Find
     (Object : access State;
      Link   : in     Linkage;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return Linkage_Access;

   function Find
     (Object : access State;
      Link   : in     Linkage;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small;

   function Find_Tag
     (Object : access State;
      Name   : in     Asis.Defining_Name;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small;

   function Find_Shape
     (Object : access State;
      Tipe   : in     XASIS.Classes.Type_Info;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small;

   function Find_Variety
     (Object : access State;
      Tipe   : in     XASIS.Classes.Type_Info;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small;

   function Find_Type_Param
     (Object : access State;
      Tipe   : in     XASIS.Classes.Type_Info;
      Param  : in     Type_Param_Kinds;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small;

   function Find_Attribute
     (Object : access State;
      Tipe   : in     Asis.Declaration;
      Attr   : in     Asis.Attribute_Kinds;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small;

   function Find_Support
     (Object : access State;
      Kind   : in     Support_Kinds;
      Unit   : in     Unit_Kinds := TAGDEF) return TenDRA.Small;

   function Find_Proc
     (Object : access State;
      Name   : in     Asis.Defining_Name;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small;

   function Find_Name
     (Object : access State;
      Name   : in     Asis.Defining_Name;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small;

   function Find_Value
     (Object : access State;
      Name   : in     Asis.Defining_Name;
      Unit   : in     Unit_Kinds := TAGDEF;
      Usage  : in     Boolean := True) return TenDRA.Small;

   Empty : TenDRA.Streams.Memory_Stream;

   Error : exception;

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
