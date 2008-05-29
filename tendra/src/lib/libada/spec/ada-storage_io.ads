------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.IO_Exceptions;
with System.Storage_Elements;

generic
   type Element_Type is private;
package Ada.Storage_IO is
   pragma Preelaborate (Storage_IO);

   Buffer_Size : constant System.Storage_Elements.Storage_Count
     := implementation-defined;

   subtype Buffer_Type is
     System.Storage_Elements.Storage_Array (1 .. Buffer_Size);

   -- Input and output operations

   procedure Read  (Buffer : in  Buffer_Type; Item : out Element_Type);
   procedure Write (Buffer : out Buffer_Type; Item : in  Element_Type);

   -- Exceptions

   Data_Error   : exception renames IO_Exceptions.Data_Error;

end Ada.Storage_IO;




