------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Numerics.Generic_Real_Arrays;
with Ada.Numerics.Generic_Complex_Types;

generic
   with package Real_Arrays is new Ada.Numerics.Generic_Real_Arrays (<>);

   with package Complex_Types is
     new Ada.Numerics.Generic_Complex_Types (Real_Arrays.Real);

package Ada.Numerics.Generic_Complex_Arrays is

   pragma Pure (Generic_Complex_Arrays);

   --  Types

   type Complex_Vector is array (Integer range <>) of Complex_Types.Complex;

   type Complex_Matrix is
     array (Integer range <>, Integer range <>) of Complex_Types.Complex;

   --  Subprograms for Complex_Vector types

   --  Complex_Vector selection, conversion and composition operations

   function Re (X : in Complex_Vector) return Real_Arrays.Real_Vector;

   function Im (X : in Complex_Vector) return Real_Arrays.Real_Vector;

   procedure Set_Re (X  : in out Complex_Vector;
                     Re : in     Real_Arrays.Real_Vector);

   procedure Set_Im (X  : in out Complex_Vector;
                     Im : in     Real_Arrays.Real_Vector);

   function Compose_From_Cartesian (Re : in Real_Arrays.Real_Vector)
     return Complex_Vector;

   function Compose_From_Cartesian (Re : in Real_Arrays.Real_Vector;
                                    Im : in Real_Arrays.Real_Vector)
     return Complex_Vector;

   function Modulus (X : in Complex_Vector) return Real_Arrays.Real_Vector;

   function "abs" (Right : in Complex_Vector) return Real_Arrays.Real_Vector
     renames Modulus;

   function Argument (X : in Complex_Vector) return Real_Arrays.Real_Vector;

   function Argument (X     : in Complex_Vector;
                      Cycle : in Real_Arrays.Real'Base)
     return Real_Arrays.Real_Vector;

   function Compose_From_Polar (Modulus  : in Real_Arrays.Real_Vector;
                                Argument : in Real_Arrays.Real_Vector)
     return Complex_Vector;

   function Compose_From_Polar (Modulus  : in Real_Arrays.Real_Vector;
                                Argument : in Real_Arrays.Real_Vector;
                                Cycle    : in Real_Arrays.Real'Base)
     return Complex_Vector;

   --  Complex_Vector arithmetic operations

   function "+" (Right : in Complex_Vector) return Complex_Vector;

   function "-" (Right : in Complex_Vector) return Complex_Vector;

   function Conjugate (X : in Complex_Vector) return Complex_Vector;

   function "+" (Left  : in Complex_Vector;
                 Right : in Complex_Vector)
     return Complex_Vector;

   function "-" (Left  : in Complex_Vector;
                 Right : in Complex_Vector)
     return Complex_Vector;

   function "*" (Left  : in Complex_Vector;
                 Right : Complex_Vector)
     return Complex_Types.Complex;

   function "abs" (Right : in Complex_Vector) return Complex_Types.Complex;

   --  Mixed Real_Arrays.Real_Vector and Complex_Vector arithmetic operations

   function "+" (Left  : in Real_Arrays.Real_Vector;
                 Right : in Complex_Vector)
     return Complex_Vector;

   function "+" (Left  : in Complex_Vector;
                 Right : in Real_Arrays.Real_Vector)
     return Complex_Vector;

   function "-" (Left  : in Real_Arrays.Real_Vector;
                 Right : in Complex_Vector)
     return Complex_Vector;

   function "-" (Left  : in Complex_Vector;
                 Right : in Real_Arrays.Real_Vector)
     return Complex_Vector;

   function "*" (Left  : in Real_Arrays.Real_Vector;
                 Right : in Complex_Vector)
     return Complex_Types.Complex;

   function "*" (Left  : in Complex_Vector;
                 Right : in Real_Arrays.Real_Vector)
     return Complex_Types.Complex;

   --  Complex_Vector scaling operations

   function "*" (Left  : in Complex_Types.Complex;
                 Right : in Complex_Vector)
     return Complex_Vector;

   function "*" (Left  : in Complex_Vector;
                 Right : in Complex_Types.Complex)
     return Complex_Vector;

   function "/" (Left  : in Complex_Vector;
                 Right : in Complex_Types.Complex)
     return Complex_Vector;

   function "*" (Left  : in Real_Arrays.Real'Base;
                 Right : in Complex_Vector)
     return Complex_Vector;

   function "*" (Left  : in Complex_Vector;
                 Right : in Real_Arrays.Real'Base)
     return Complex_Vector;

   function "/" (Left  : in Complex_Vector;
                 Right : in Real_Arrays.Real'Base)
     return Complex_Vector;

   --  Other Complex_Vector operations

   function Unit_Vector (Index : in Integer;
                         Order : in Positive;
                         First : in Integer := 1)
     return Complex_Vector;

   --  Subprograms for Complex_Matrix types

   --  Complex_Matrix selection, conversion and composition operations

   function Re (X : in Complex_Matrix) return Real_Arrays.Real_Matrix;

   function Im (X : in Complex_Matrix) return Real_Arrays.Real_Matrix;

   procedure Set_Re (X  : in out Complex_Matrix;
                     Re : in     Real_Arrays.Real_Matrix);

   procedure Set_Im (X  : in out Complex_Matrix;
                     Im : in     Real_Arrays.Real_Matrix);

   function Compose_From_Cartesian (Re : in Real_Arrays.Real_Matrix)
     return Complex_Matrix;

   function Compose_From_Cartesian (Re : in Real_Arrays.Real_Matrix;
                                    Im : in Real_Arrays.Real_Matrix)
     return Complex_Matrix;

   function Modulus (X : in Complex_Matrix) return Real_Arrays.Real_Matrix;

   function "abs" (Right : in Complex_Matrix) return Real_Arrays.Real_Matrix
     renames Modulus;

   function Argument (X : in Complex_Matrix) return Real_Arrays.Real_Matrix;

   function Argument (X     : in Complex_Matrix;
                      Cycle : in Real_Arrays.Real'Base)
     return Real_Arrays.Real_Matrix;

   function Compose_From_Polar (Modulus  : in Real_Arrays.Real_Matrix;
                                Argument : in Real_Arrays.Real_Matrix)
     return Complex_Matrix;

   function Compose_From_Polar (Modulus  : in Real_Arrays.Real_Matrix;
                                Argument : in Real_Arrays.Real_Matrix;
                                Cycle    : in Real_Arrays.Real'Base)
     return Complex_Matrix;

   --  Complex_Matrix arithmetic operations

   function "+" (Right : in Complex_Matrix) return Complex_Matrix;

   function "-" (Right : in Complex_Matrix) return Complex_Matrix;

   function Conjugate (X : in Complex_Matrix) return Complex_Matrix;

   function Transpose (X : in Complex_Matrix) return Complex_Matrix;

   function "+" (Left  : in Complex_Matrix;
                 Right : in Complex_Matrix)
     return Complex_Matrix;

   function "-" (Left  : in Complex_Matrix;
                 Right : in Complex_Matrix)
     return Complex_Matrix;

   function "*" (Left  : in Complex_Matrix;
                 Right : in Complex_Matrix)
     return Complex_Matrix;

   function "*" (Left  : in Complex_Vector;
                 Right : in Complex_Vector)
     return Complex_Matrix;

   function "*" (Left  : in Complex_Vector;
                 Right : in Complex_Matrix)
     return Complex_Vector;

   function "*" (Left  : in Complex_Matrix;
                 Right : in Complex_Vector)
     return Complex_Vector;

   --  Mixed Real_Arrays.Real_Matrix and Complex_Matrix arithmetic operations

   function "+" (Left  : in Real_Arrays.Real_Matrix;
                 Right : in Complex_Matrix)
     return Complex_Matrix;

   function "+" (Left  : in Complex_Matrix;
                 Right : in Real_Arrays.Real_Matrix)
     return Complex_Matrix;

   function "-" (Left  : in Real_Arrays.Real_Matrix;
                 Right : in Complex_Matrix)
     return Complex_Matrix;

   function "-" (Left  : in Complex_Matrix;
                 Right : in Real_Arrays.Real_Matrix)
     return Complex_Matrix;

   function "*" (Left  : in Real_Arrays.Real_Matrix;
                 Right : in Complex_Matrix)
     return Complex_Matrix;

   function "*" (Left  : in Complex_Matrix;
                 Right : in Real_Arrays.Real_Matrix)
     return Complex_Matrix;

   function "*" (Left  : in Real_Arrays.Real_Vector;
                 Right : in Complex_Vector)
     return Complex_Matrix;

   function "*" (Left  : in Complex_Vector;
                 Right : in Real_Arrays.Real_Vector)
     return Complex_Matrix;

   function "*" (Left  : in Real_Arrays.Real_Vector;
                 Right : in Complex_Matrix)
     return Complex_Vector;

   function "*" (Left  : in Complex_Vector;
                 Right : in Real_Arrays.Real_Matrix)
     return Complex_Vector;

   function "*" (Left  : in Real_Arrays.Real_Matrix;
                 Right : in Complex_Vector)
     return Complex_Vector;

   function "*" (Left  : in Complex_Matrix;
                 Right : in Real_Arrays.Real_Vector)
     return Complex_Vector;

   --  Complex_Matrix scaling operations

   function "*" (Left  : in Complex_Types.Complex;
                 Right : in Complex_Matrix)
     return Complex_Matrix;

   function "*" (Left  : in Complex_Matrix;
                 Right : in Complex_Types.Complex)
     return Complex_Matrix;

   function "/" (Left  : in Complex_Matrix;
                 Right : in Complex_Types.Complex)
     return Complex_Matrix;

   function "*" (Left  : in Real_Arrays.Real'Base;
                 Right : in Complex_Matrix)
     return Complex_Matrix;

   function "*" (Left  : in Complex_Matrix;
                 Right : in Real_Arrays.Real'Base)
     return Complex_Matrix;

   function "/" (Left  : in Complex_Matrix;
                 Right : in Real_Arrays.Real'Base)
     return Complex_Matrix;

   --  Complex_Matrix inversion and related operations

   function Solve (A : in Complex_Matrix;
                   X : in Complex_Vector)
     return Complex_Vector;

   function Solve (A : in Complex_Matrix;
                   X : in Complex_Matrix)
     return Complex_Matrix;

   function Inverse (A : in Complex_Matrix) return Complex_Matrix;

   function Determinant (A : in Complex_Matrix) return Complex_Types.Complex;

   --  Eigenvalues and vectors of a Hermitian matrix

   function Eigenvalues (A : in Complex_Matrix) return Real_Arrays.Real_Vector;

   procedure Eigensystem (A       : in     Complex_Matrix;
                          Values  :    out Real_Arrays.Real_Vector;
                          Vectors :    out Complex_Matrix);

   --  Other Complex_Matrix operations

   function Unit_Matrix (Order   : in Positive;
                         First_1 : in Integer := 1;
                         First_2 : in Integer := 1)
     return Complex_Matrix;

end Ada.Numerics.Generic_Complex_Arrays;
