------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$:
--  Purpose:
--  Container for befin, end and comment position for each source line

with Gela.Source_Buffers;
with Gela.Containers.Vectors;

use Gela;

package Asis.Gela.Lines is
   pragma Preelaborate;

   type Line is record
      From, To, Comment : Source_Buffers.Cursor;
   end record;

   package Vectors is new Containers.Vectors (Line, ASIS_Positive);

   subtype Vector is Vectors.Vector;

end Asis.Gela.Lines;
