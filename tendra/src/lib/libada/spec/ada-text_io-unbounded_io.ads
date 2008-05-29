------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Strings.Unbounded;

package Ada.Text_IO.Unbounded_IO is

   procedure Put
     (File : in File_Type;
      Item : in Strings.Unbounded.Unbounded_String);

   procedure Put
     (Item : in Strings.Unbounded.Unbounded_String);

   procedure Put_Line
     (File : in File_Type;
      Item : in Strings.Unbounded.Unbounded_String);

   procedure Put_Line
     (Item : in Strings.Unbounded.Unbounded_String);

   function Get_Line
     (File : in File_Type)
     return Strings.Unbounded.Unbounded_String;

   function Get_Line
     return Strings.Unbounded.Unbounded_String;

   procedure Get_Line
     (File : in File_Type; Item : out Strings.Unbounded.Unbounded_String);

   procedure Get_Line
     (Item : out Strings.Unbounded.Unbounded_String);

end Ada.Text_IO.Unbounded_IO;

