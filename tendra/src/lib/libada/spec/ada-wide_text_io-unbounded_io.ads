------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Strings.Wide_Unbounded;

package Ada.Wide_Text_IO.Unbounded_IO is

   procedure Put
     (File : in File_Type;
      Item : in Strings.Wide_Unbounded.Wide_Unbounded_String);

   procedure Put
     (Item : in Strings.Wide_Unbounded.Wide_Unbounded_String);

   procedure Put_Line
     (File : in File_Type;
      Item : in Strings.Wide_Unbounded.Wide_Unbounded_String);

   procedure Put_Line
     (Item : in Strings.Wide_Unbounded.Wide_Unbounded_String);

   function Get_Line
     (File : in File_Type)
     return Strings.Wide_Unbounded.Wide_Unbounded_String;

   function Get_Line
     return Strings.Wide_Unbounded.Wide_Unbounded_String;

   procedure Get_Line
     (File : in File_Type;
      Item : out Strings.Wide_Unbounded.Wide_Unbounded_String);

   procedure Get_Line
     (Item : out Strings.Wide_Unbounded.Wide_Unbounded_String);

end Ada.Wide_Text_IO.Unbounded_IO;

