------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $

generic
   type Real is digits <>;
package Ada.Numerics.Generic_Complex_Types is
   pragma Pure (Generic_Complex_Types);

   type Complex is
      record
         Re, Im : Real'Base;
      end record;

   type Imaginary is private;

   i : constant Imaginary;
   j : constant Imaginary;

   function Re (X : Complex)   return Real'Base;
   function Im (X : Complex)   return Real'Base;
   function Im (X : Imaginary) return Real'Base;

   procedure Set_Re (X  : in out Complex;
                     Re : in     Real'Base);
   procedure Set_Im (X  : in out Complex;
                     Im : in     Real'Base);
   procedure Set_Im (X  :    out Imaginary;
                     Im : in     Real'Base);

   function Compose_From_Cartesian (Re, Im : Real'Base) return Complex;
   function Compose_From_Cartesian (Re     : Real'Base) return Complex;
   function Compose_From_Cartesian (Im     : Imaginary) return Complex;

   function Modulus (X     : Complex) return Real'Base;
   function "abs"   (Right : Complex) return Real'Base renames Modulus;

   function Argument (X     : Complex)   return Real'Base;
   function Argument (X     : Complex;
                      Cycle : Real'Base) return Real'Base;

   function Compose_From_Polar (Modulus, Argument        : Real'Base)
                               return Complex;
   function Compose_From_Polar (Modulus, Argument, Cycle : Real'Base)
                               return Complex;

   function "+"       (Right : Complex) return Complex;
   function "-"       (Right : Complex) return Complex;
   function Conjugate (X     : Complex) return Complex;

   function "+" (Left, Right : Complex) return Complex;
   function "-" (Left, Right : Complex) return Complex;
   function "*" (Left, Right : Complex) return Complex;
   function "/" (Left, Right : Complex) return Complex;

   function "**" (Left : Complex; Right : Integer) return Complex;

   function "+"       (Right : Imaginary) return Imaginary;
   function "-"       (Right : Imaginary) return Imaginary;
   function Conjugate (X     : Imaginary) return Imaginary renames "-";
   function "abs"     (Right : Imaginary) return Real'Base;

   function "+" (Left, Right : Imaginary) return Imaginary;
   function "-" (Left, Right : Imaginary) return Imaginary;
   function "*" (Left, Right : Imaginary) return Real'Base;
   function "/" (Left, Right : Imaginary) return Real'Base;

   function "**" (Left : Imaginary; Right : Integer) return Complex;

   function "<"  (Left, Right : Imaginary) return Boolean;
   function "<=" (Left, Right : Imaginary) return Boolean;
   function ">"  (Left, Right : Imaginary) return Boolean;
   function ">=" (Left, Right : Imaginary) return Boolean;

   function "+" (Left : Complex;   Right : Real'Base) return Complex;
   function "+" (Left : Real'Base; Right : Complex)   return Complex;
   function "-" (Left : Complex;   Right : Real'Base) return Complex;
   function "-" (Left : Real'Base; Right : Complex)   return Complex;
   function "*" (Left : Complex;   Right : Real'Base) return Complex;
   function "*" (Left : Real'Base; Right : Complex)   return Complex;
   function "/" (Left : Complex;   Right : Real'Base) return Complex;
   function "/" (Left : Real'Base; Right : Complex)   return Complex;

   function "+" (Left : Complex;   Right : Imaginary) return Complex;
   function "+" (Left : Imaginary; Right : Complex)   return Complex;
   function "-" (Left : Complex;   Right : Imaginary) return Complex;
   function "-" (Left : Imaginary; Right : Complex)   return Complex;
   function "*" (Left : Complex;   Right : Imaginary) return Complex;
   function "*" (Left : Imaginary; Right : Complex)   return Complex;
   function "/" (Left : Complex;   Right : Imaginary) return Complex;
   function "/" (Left : Imaginary; Right : Complex)   return Complex;

   function "+" (Left : Imaginary; Right : Real'Base) return Complex;
   function "+" (Left : Real'Base; Right : Imaginary) return Complex;
   function "-" (Left : Imaginary; Right : Real'Base) return Complex;
   function "-" (Left : Real'Base; Right : Imaginary) return Complex;
   function "*" (Left : Imaginary; Right : Real'Base) return Imaginary;
   function "*" (Left : Real'Base; Right : Imaginary) return Imaginary;
   function "/" (Left : Imaginary; Right : Real'Base) return Imaginary;
   function "/" (Left : Real'Base; Right : Imaginary) return Imaginary;

private

   type Imaginary is new Real'Base;
   i : constant Imaginary := 1.0;
   j : constant Imaginary := 1.0;

end Ada.Numerics.Generic_Complex_Types;


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
