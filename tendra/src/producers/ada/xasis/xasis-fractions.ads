------------------------------------------------------------------------------
--                           G E L A   X A S I S                            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Multyprecission fraction arithmetic

with XASIS.Integers;

package XASIS.Fractions is
   package I renames XASIS.Integers;

   type Fraction is record
      Numerator   : I.Value;
      Denominator : I.Value;
      Exponent    : I.Value;
   end record;

   function "=" (Left, Right : Fraction) return Boolean;
   function ">" (Left, Right : Fraction) return Boolean;
   function "<" (Left, Right : Fraction) return Boolean;
   function ">=" (Left, Right : Fraction) return Boolean;
   function "<=" (Left, Right : Fraction) return Boolean;

   function "-" (Left : Fraction) return Fraction;
   function "+" (Left, Right : Fraction) return Fraction;
   function "-" (Left, Right : Fraction) return Fraction;
   function "*" (Left, Right : Fraction) return Fraction;
   function "/" (Left, Right : Fraction) return Fraction;

   function "**" (Left : Fraction; Right : I.Value) return Fraction;
   function "abs" (Left : Fraction) return Fraction;

   function Image (Left : Fraction) return String;
   function Value (Text : String) return Fraction;
   function Int   (Value : I.Value) return Fraction;
   function Truncate (X : Fraction) return I.Value;

   Zero : constant Fraction := (I.Zero, I.One, I.Zero);
   One  : constant Fraction := (I.One, I.One, I.Zero);
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

