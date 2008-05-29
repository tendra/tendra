------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

generic
   type Real is digits <>;

package Ada.Numerics.Generic_Real_Arrays is

   pragma Pure (Generic_Real_Arrays);

   --  Types

   type Real_Vector is array (Integer range <>) of Real'Base;

   type Real_Matrix is array (Integer range <>, Integer range <>) of Real'Base;

   --  Subprograms for Real_Vector types

   --  Real_Vector arithmetic operations

   function "+" (Right : in Real_Vector) return Real_Vector;

   function "-" (Right : in Real_Vector) return Real_Vector;

   function "abs" (Right : in Real_Vector) return Real_Vector;

   function "+" (Left  : in Real_Vector;
                 Right : Real_Vector)
     return Real_Vector;

   function "-" (Left  : in Real_Vector;
                 Right : Real_Vector)
     return Real_Vector;

   function "*" (Left  : in Real_Vector;
                 Right : Real_Vector)
     return Real'Base;

   function "abs" (Right : in Real_Vector) return Real'Base;

   --  Real_Vector scaling operations

   function "*" (Left  : in Real'Base;
                 Right : in Real_Vector)
     return Real_Vector;

   function "*" (Left  : in Real_Vector;
                 Right : in Real'Base)
     return Real_Vector;

   function "/" (Left  : in Real_Vector;
                 Right : in Real'Base)
     return Real_Vector;

   --  Other Real_Vector operations

   function Unit_Vector (Index : in Integer;
                         Order : in Positive;
                         First : in Integer := 1)
     return Real_Vector;

   --  Subprograms for Real_Matrix types

   --  Real_Matrix arithmetic operations

   function "+" (Right : in Real_Matrix) return Real_Matrix;

   function "-" (Right : in Real_Matrix) return Real_Matrix;

   function "abs" (Right : in Real_Matrix) return Real_Matrix;

   function Transpose (X : in Real_Matrix) return Real_Matrix;

   function "+" (Left  : in Real_Matrix;
                 Right : in Real_Matrix)
     return Real_Matrix;

   function "-" (Left  : in Real_Matrix;
                 Right : in Real_Matrix)
     return Real_Matrix;

   function "*" (Left  : in Real_Matrix;
                 Right : in Real_Matrix)
     return Real_Matrix;

   function "*" (Left  : in Real_Matrix;
                 Right : in Real_Vector)
     return Real_Matrix;

   function "*" (Left  : in Real_Vector;
                 Right : in Real_Matrix)
     return Real_Vector;

   function "*" (Left  : in Real_Matrix;
                 Right : in Real_Vector)
     return Real_Vector;

   --  Real_Matrix scaling operations

   function "*" (Left  : in Real'Base;
                 Right : in Real_Matrix)
     return Real_Matrix;

   function "*" (Left  : in Real_Matrix;
                 Right : in Real'Base)
     return Real_Matrix;

   function "/" (Left  : in Real_Matrix;
                 Right : in Real'Base)
     return Real_Matrix;

   --  Real_Matrix inversion and related operations

   function Solve (A : in Real_Matrix;
                   X : in Real_Vector)
     return Real_Vector;

   function Solve (A : in Real_Matrix;
                   X : in Real_Matrix)
     return Real_Matrix;

   function Inverse (A : in Real_Matrix) return Real_Matrix;

   function Determinant (A : in Real_Matrix) return Real'Base;

   --  Eigenvalues and vectors of a real symmetric matrix

   function Eigenvalues (A : in Real_Matrix) return Real_Vector;

   procedure Eigensystem (A       : in     Real_Matrix;
                          Values  :    out Real_Vector;
                          Vectors :    out Real_Matrix);

   --  Other Real_Matrix operations

   function Unit_Matrix (Order   : Positive;
                         First_1 : Integer := 1;
                         First_2 : Integer := 1)
     return Real_Matrix;

end Ada.Numerics.Generic_Real_Arrays;
