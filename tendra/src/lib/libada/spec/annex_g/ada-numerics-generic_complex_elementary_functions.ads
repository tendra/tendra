------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Numerics.Generic_Complex_Types;

generic
   with package Complex_Types is new Ada.Numerics.Generic_Complex_Types (<>);

package Ada.Numerics.Generic_Complex_Elementary_Functions is

   pragma Pure (Generic_Complex_Elementary_Functions);

   function Sqrt (X : in Complex_Types.Complex) return Complex_Types.Complex;

   function Log (X : in Complex_Types.Complex) return Complex_Types.Complex;

   function Exp (X : in Complex_Types.Complex) return Complex_Types.Complex;

   function Exp (X : in Complex_Types.Imaginary) return Complex_Types.Complex;

   function "**" (Left  : in Complex_Types.Complex;
                  Right : in Complex_Types.Complex)
     return Complex_Types.Complex;

   function "**" (Left  : in Complex_Types.Complex;
                  Right : in Complex_Types.Real'Base)
     return Complex_Types.Complex;

   function "**" (Left  : in Complex_Types.Real'Base;
                  Right : in Complex_Types.Complex)
     return Complex_Types.Complex;

   function Sin (X : in  Complex_Types.Complex) return Complex_Types.Complex;

   function Cos (X : in  Complex_Types.Complex) return Complex_Types.Complex;

   function Tan (X : in  Complex_Types.Complex) return Complex_Types.Complex;

   function Cot (X : in  Complex_Types.Complex) return Complex_Types.Complex;

   function Arcsin (X : in  Complex_Types.Complex)
     return Complex_Types.Complex;

   function Arccos (X : in  Complex_Types.Complex)
     return Complex_Types.Complex;

   function Arctan (X : in  Complex_Types.Complex)
     return Complex_Types.Complex;

   function Arccot (X : in  Complex_Types.Complex)
     return Complex_Types.Complex;

   function Sinh (X : in Complex_Types.Complex) return Complex_Types.Complex;

   function Cosh (X : in Complex_Types.Complex) return Complex_Types.Complex;

   function Tanh (X : in Complex_Types.Complex) return Complex_Types.Complex;

   function Coth (X : in Complex_Types.Complex) return Complex_Types.Complex;

   function Arcsinh (X : in Complex_Types.Complex)
     return Complex_Types.Complex;

   function Arccosh (X : in Complex_Types.Complex)
     return Complex_Types.Complex;

   function Arctanh (X : in Complex_Types.Complex)
     return Complex_Types.Complex;

   function Arccoth (X : in Complex_Types.Complex)
     return Complex_Types.Complex;

end Ada.Numerics.Generic_Complex_Elementary_Functions;
