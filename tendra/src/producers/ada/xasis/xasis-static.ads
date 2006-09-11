------------------------------------------------------------------------------
--                           G E L A   X A S I S                            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Static expression evaluation

with Asis;
with XASIS.Classes;
with XASIS.Integers;
with Ada.Finalization;

package XASIS.Static is

   type Value is private;

   Evaluation_Error : exception;

   function Evaluate (Element : Asis.Expression) return Value;

   function In_Range
     (Item    : Value;
      Element : Asis.Definition) return Boolean;

   function Image (Item : Value) return Wide_String;
   function Debug_Image (Item : Value) return Wide_String;
   function "+" (Item : Value) return Asis.ASIS_Integer;

   Static_False : constant Value;
   Static_True  : constant Value;
   Static_Zero  : constant Value;
   Static_One   : constant Value;

   function Undefined return Value;

   function Attribute_Designator_Expression
     (Attr : Asis.Expression) return Value;

   type Bound_Kinds is (Lower, Upper);

   type Error_Reason is
     (Not_Implemented, Internal_Error, Unexpected_Type,
      Division_By_Zero, Exceed_Modulus);

   procedure Last_Error (Reason  : out Error_Reason);

private
   type Static_Value_Kinds is
     (Static_Undefined, Static_Discrete, Static_String, Static_Float);

   type Integer_Array is
     array (Asis.ASIS_Positive range <>) of XASIS.Integers.Value;

   type Integer_Array_Access is access Integer_Array;

   type Integer_Array_Node is new Ada.Finalization.Controlled with record
      Data : Integer_Array_Access;
   end record;

   procedure Adjust   (Object : in out Integer_Array_Node);
   procedure Finalize (Object : in out Integer_Array_Node);

   type Value (Kind   : Static_Value_Kinds := Static_Undefined) is
      record
         case Kind is
            when Static_Discrete =>
               Pos    : XASIS.Integers.Value;
            when Static_String =>
               Lower  : XASIS.Integers.Value;
               Upper  : XASIS.Integers.Value;
               String : Integer_Array_Node;
            when Static_Float =>
               null;
            when Static_Undefined =>
               null;
         end case;
      end record;

   Static_False : constant Value :=
     (Static_Discrete, XASIS.Integers.Literal ("0"));

   Static_True  : constant Value :=
     (Static_Discrete, XASIS.Integers.Literal ("1"));

   Static_Zero  : constant Value :=
     (Static_Discrete, XASIS.Integers.Literal ("0"));

   Static_One   : constant Value :=
     (Static_Discrete, XASIS.Integers.Literal ("1"));

   type Type_Class is abstract tagged record
      Info   : Classes.Type_Info;
   end record;

   function Evaluate
     (Object : Type_Class;
      Kind   : Asis.Operator_Kinds;
      Args   : Asis.Association_List) return Value is abstract;

   function Evaluate
     (Object : Type_Class;
      Kind   : Asis.Attribute_Kinds;
      Args   : Asis.Association_List) return Value is abstract;

   function Evaluate
     (Object  : Type_Class;
      Kind    : Asis.Attribute_Kinds;
      Element : Asis.Expression) return Value is abstract;

   type Static_Range is array (Bound_Kinds) of Value;

   function Static_Range_Attribute
     (Attr   : Asis.Expression) return Static_Range;

   Last_Error_Reason  : Error_Reason;

   procedure Raise_Error (Reason  : Error_Reason);

   procedure Check_Zero (Item : Value);

end XASIS.Static;


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
