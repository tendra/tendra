------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.IO_Exceptions;
generic
   type Element_Type is private;
package Ada.Direct_IO is

   type File_Type is limited private;

   type File_Mode is (In_File, Inout_File, Out_File);
   type Count     is range 0 .. implementation-defined;
   subtype Positive_Count is Count range 1 .. Count'Last;

   -- File management

   procedure Create (File : in out File_Type;
                     Mode : in File_Mode := Inout_File;
                     Name : in String := "";
                     Form : in String := "");

   procedure Open (File : in out File_Type;
                   Mode : in File_Mode;
                   Name : in String;
                   Form : in String := "");

   procedure Close (File : in out File_Type);
   procedure Delete (File : in out File_Type);
   procedure Reset (File : in out File_Type; Mode : in File_Mode);
   procedure Reset (File : in out File_Type);

   function Mode   (File : in File_Type) return File_Mode;
   function Name   (File : in File_Type) return String;
   function Form   (File : in File_Type) return String;

   function Is_Open (File : in File_Type) return Boolean;

   -- Input and output operations

   procedure Read (File : in File_Type; Item : out Element_Type;
                                        From : in  Positive_Count);
   procedure Read (File : in File_Type; Item : out Element_Type);

   procedure Write (File : in File_Type; Item : in Element_Type;
                                         To   : in Positive_Count);
   procedure Write (File : in File_Type; Item : in Element_Type);

   procedure Set_Index (File : in File_Type; To : in Positive_Count);

   function Index (File : in File_Type) return Positive_Count;
   function Size (File : in File_Type) return Count;

   function End_Of_File (File : in File_Type) return Boolean;

   -- Exceptions

   Status_Error : exception renames IO_Exceptions.Status_Error;
   Mode_Error   : exception renames IO_Exceptions.Mode_Error;
   Name_Error   : exception renames IO_Exceptions.Name_Error;
   Use_Error    : exception renames IO_Exceptions.Use_Error;
   Device_Error : exception renames IO_Exceptions.Device_Error;
   End_Error    : exception renames IO_Exceptions.End_Error;
   Data_Error   : exception renames IO_Exceptions.Data_Error;

private

   type File_Type is limited null record;

end Ada.Direct_IO;



