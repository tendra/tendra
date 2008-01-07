with Ada.Strings.Fixed;
with Ada.Strings.Maps.Constants;

package body XASIS.Fractions is
   use XASIS.Integers;

   function Val (X : Integer) return I.Value;
   function NOD (X, Y : I.Value) return I.Value;

   procedure Simplify (X : in out Fraction);

   ---------
   -- Val --
   ---------

   function Val (X : Integer) return I.Value is
   begin
      return Literal (Integer'Image (X));
   end Val;

   ---------
   -- "*" --
   ---------

   function "*" (Left, Right : Fraction) return Fraction is
      Result : Fraction :=
        (Left.Numerator   * Right.Numerator,
         Left.Denominator * Right.Denominator,
         Left.Exponent + Right.Exponent);
   begin
      Simplify (Result);

      return Result;
   end "*";

   ----------
   -- "**" --
   ----------

   function "**" (Left : Fraction; Right : I.Value) return Fraction is
   begin
      if Right > I.Zero then
         return (Left.Numerator ** Right,
                 Left.Denominator ** Right,
                 Left.Exponent * Right);
      else
         return (One / Left) ** (-Right);
      end if;
   end "**";

   ---------
   -- "+" --
   ---------

   function "+" (Left, Right : Fraction) return Fraction is
      Min_Exp : I.Value := Left.Exponent;
      L       : Fraction := Left;
      R       : Fraction := Right;
      Result  : Fraction;
   begin
      if Min_Exp > Right.Exponent then
         Min_Exp := Right.Exponent;
      end if;

      if L.Exponent > Min_Exp then
         L.Numerator := L.Numerator * Ten ** (L.Exponent - Min_Exp);
      elsif R.Exponent > Min_Exp then
         R.Numerator := R.Numerator * Ten ** (R.Exponent - Min_Exp);
      end if;

      Result := (L.Numerator * R.Denominator + R.Numerator * L.Denominator,
                 L.Denominator * R.Denominator,
                 Min_Exp);

      Simplify (Result);

      return Result;
   end "+";

   ---------
   -- "-" --
   ---------

   function "-" (Left : Fraction) return Fraction is
   begin
      return (-Left.Numerator, Left.Denominator, Left.Exponent);
   end "-";

   ---------
   -- "-" --
   ---------

   function "-" (Left, Right : Fraction) return Fraction is
   begin
      return Left + (-Right);
   end "-";

   ---------
   -- "/" --
   ---------

   function "/" (Left, Right : Fraction) return Fraction is
      Reciprocal : constant Fraction :=
        (Right.Denominator, abs Right.Numerator, -Right.Exponent);
   begin
      if Right.Numerator = I.Zero then
         raise Constraint_Error;
      elsif Right.Numerator < I.Zero then
         return -(Left * Reciprocal);
      else
         return Left * Reciprocal;
      end if;
   end "/";

   ---------
   -- "<" --
   ---------

   function "<" (Left, Right : Fraction) return Boolean is
      Diff : constant Fraction := Left - Right;
   begin
      return Diff.Numerator < I.Zero;
   end "<";

   ----------
   -- "<=" --
   ----------

   function "<=" (Left, Right : Fraction) return Boolean is
      Diff : constant Fraction := Left - Right;
   begin
      return Diff.Numerator <= I.Zero;
   end "<=";

   ---------
   -- "=" --
   ---------

   function "=" (Left, Right : Fraction) return Boolean is
      Diff : constant Fraction := Left - Right;
   begin
      return Diff.Numerator = I.Zero;
   end "=";

   ---------
   -- ">" --
   ---------

   function ">" (Left, Right : Fraction) return Boolean is
      Diff : constant Fraction := Left - Right;
   begin
      return Diff.Numerator > I.Zero;
   end ">";

   ----------
   -- ">=" --
   ----------

   function ">=" (Left, Right : Fraction) return Boolean is
      Diff : constant Fraction := Left - Right;
   begin
      return Diff.Numerator >= I.Zero;
   end ">=";

   -----------
   -- "abs" --
   -----------

   function "abs" (Left : Fraction) return Fraction is
   begin
      return (abs Left.Numerator, Left.Denominator, Left.Exponent);
   end "abs";

   -----------
   -- Image --
   -----------

   function Image (Left : Fraction) return String is
   begin
      return Image (Left.Numerator) & 'e' & Image (Left.Exponent)
         & '/' & Image (Left.Denominator);
   end Image;

   ---------
   -- Int --
   ---------

   function Int (Value : I.Value) return Fraction is
   begin
      return (Value, I.One, I.Zero);
   end Int;

   ---------
   -- NOD --
   ---------

   function NOD (X, Y : I.Value) return I.Value is
      U : I.Value := X;
      V : I.Value := Y;
      R : I.Value;
   begin
      while V /= I.Zero loop
         R := U mod V;
         U := V;
         V := R;
      end loop;

      return U;
   end NOD;

   --------------
   -- Simplify --
   --------------

   procedure Simplify (X : in out Fraction) is
      N : I.Value;
   begin
      if X.Numerator = I.Zero then
         X := Zero;
         return;
      else
         N := NOD (abs X.Numerator, X.Denominator);
      end if;

      if N > I.One then
         X.Numerator   := X.Numerator / N;
         X.Denominator := X.Denominator / N;
      end if;

      while X.Numerator mod Ten = I.Zero loop
         X.Numerator := X.Numerator / Ten;
         X.Exponent  := X.Exponent + I.One;
      end loop;

      while X.Denominator mod Ten = I.Zero loop
         X.Denominator := X.Denominator / Ten;
         X.Exponent    := X.Exponent - I.One;
      end loop;
   end Simplify;

   --------------
   -- Truncate --
   --------------

   function Truncate (X : Fraction) return I.Value is
   begin
      if X.Exponent >= I.Zero then
         return X.Numerator * Ten ** X.Exponent / X.Denominator;
      else
         return X.Numerator / Ten ** (-X.Exponent) / X.Denominator;
      end if;
   end Truncate;

   -----------
   -- Value --
   -----------

   function Value (Text : String) return Fraction is
      use Ada.Strings.Fixed;
      use Ada.Strings.Maps.Constants;

      Result : Fraction;
      Base   : Positive := 10;
      Sharp  : Natural := Index (Text, "#");
      Dot    : Natural := Index (Text, ".");
      E      : Natural := Index (Text, "E", Mapping => Upper_Case_Map);

      function Count_Denominator (Text : String) return I.Value is
         Count : Natural := 0;
      begin
         for J in Text'Range loop
            if Text (J) /= '_' then
               Count := Count + 1;
            end if;
         end loop;

         return Val (Count);
      end Count_Denominator;
   begin
      if Sharp /= 0 then
         Base := Positive'Value (Text (Text'First .. Sharp - 1));
      else
         Sharp := Text'First - 1;
      end if;

      if E = 0 then
         Result.Numerator   := Literal (Text (Sharp + 1 .. Text'Last));
      else
         Result.Numerator   := Literal (Text (Sharp + 1 .. E - 1));
      end if;

      if Base = 10 then
         if E = 0 then
            Result.Exponent    := I.Zero -
              Count_Denominator (Text (Dot + 1 .. Text'Last));
         else
            Result.Exponent    := Literal (Text (E + 1 .. Text'Last)) -
              Count_Denominator (Text (Dot + 1 .. E - 1));
         end if;

         Result.Denominator := I.One;
      else
         if E = 0 then
            Result.Denominator := Val (Base) **
              Count_Denominator (Text (Dot + 1 .. Text'Last));
         else
            Result.Denominator := Val (Base) **
              Count_Denominator (Text (Dot + 1 .. E - 1));
         end if;

         Result.Exponent := I.Zero;
      end if;

      Simplify (Result);

      return Result;
   end Value;

end XASIS.Fractions;

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
