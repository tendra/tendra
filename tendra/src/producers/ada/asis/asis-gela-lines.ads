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
