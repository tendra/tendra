------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.IO_Exceptions;

package Ada.Text_IO is

   type File_Type is limited private;

   type File_Mode is (In_File, Out_File, Append_File);

   type Count is range 0 .. implementation-defined;
   subtype Positive_Count is Count range 1 .. Count'Last;
   Unbounded : constant Count := 0; -- line and page length

   subtype Field       is Integer range 0 .. implementation-defined;
   subtype Number_Base is Integer range 2 .. 16;

   type Type_Set is (Lower_Case, Upper_Case);

   -- File Management

   procedure Create (File : in out File_Type;
                     Mode : in File_Mode := Out_File;
                     Name : in String    := "";
                     Form : in String    := "");

   procedure Open   (File : in out File_Type;
                     Mode : in File_Mode;
                     Name : in String;
                     Form : in String := "");

   procedure Close  (File : in out File_Type);
   procedure Delete (File : in out File_Type);
   procedure Reset  (File : in out File_Type; Mode : in File_Mode);
   procedure Reset  (File : in out File_Type);

   function  Mode   (File : in File_Type) return File_Mode;
   function  Name   (File : in File_Type) return String;
   function  Form   (File : in File_Type) return String;

   function  Is_Open(File : in File_Type) return Boolean;

   -- Control of default input and output files

   procedure Set_Input (File : in File_Type);
   procedure Set_Output(File : in File_Type);
   procedure Set_Error (File : in File_Type);

   function Standard_Input  return File_Type;
   function Standard_Output return File_Type;
   function Standard_Error  return File_Type;

   function Current_Input   return File_Type;
   function Current_Output  return File_Type;
   function Current_Error   return File_Type;

   type File_Access is access constant File_Type;

   function Standard_Input  return File_Access;
   function Standard_Output return File_Access;
   function Standard_Error  return File_Access;

   function Current_Input   return File_Access;
   function Current_Output  return File_Access;
   function Current_Error   return File_Access;

   --  Buffer control
   procedure Flush (File : in out File_Type);
   procedure Flush;

   -- Specification of line and page lengths

   procedure Set_Line_Length (File : in File_Type; To : in Count);
   procedure Set_Line_Length (To   : in Count);

   procedure Set_Page_Length (File : in File_Type; To : in Count);
   procedure Set_Page_Length (To   : in Count);

   function  Line_Length (File : in File_Type) return Count;
   function  Line_Length return Count;

   function  Page_Length (File : in File_Type) return Count;
   function  Page_Length return Count;

   -- Column, Line, and Page Control

   procedure New_Line   (File    : in File_Type;
                         Spacing : in Positive_Count := 1);
   procedure New_Line   (Spacing : in Positive_Count := 1);

   procedure Skip_Line  (File    : in File_Type;
                         Spacing : in Positive_Count := 1);
   procedure Skip_Line  (Spacing : in Positive_Count := 1);

   function  End_Of_Line (File : in File_Type) return Boolean;
   function  End_Of_Line return Boolean;

   procedure New_Page   (File : in File_Type);
   procedure New_Page;

   procedure Skip_Page  (File : in File_Type);
   procedure Skip_Page;

   function  End_Of_Page (File : in File_Type) return Boolean;
   function  End_Of_Page return Boolean;

   function  End_Of_File (File : in File_Type) return Boolean;
   function  End_Of_File return Boolean;

   procedure Set_Col (File : in File_Type; To : in Positive_Count);
   procedure Set_Col (To   : in Positive_Count);

   procedure Set_Line (File : in File_Type; To : in Positive_Count);
   procedure Set_Line (To   : in Positive_Count);

   function Col (File : in File_Type) return Positive_Count;
   function Col  return Positive_Count;

   function Line (File : in File_Type) return Positive_Count;
   function Line return Positive_Count;

   function Page (File : in File_Type) return Positive_Count;
   function Page return Positive_Count;

   -- Character Input-Output

   procedure Get (File : in  File_Type; Item : out Character);
   procedure Get (Item : out Character);

   procedure Put (File : in  File_Type; Item : in Character);
   procedure Put (Item : in  Character);

   procedure Look_Ahead (File        : in  File_Type;
                         Item        : out Character;
                         End_Of_Line : out Boolean);
   procedure Look_Ahead (Item        : out Character;
                         End_Of_Line : out Boolean);

   procedure Get_Immediate (File      : in  File_Type;
                            Item      : out Character);
   procedure Get_Immediate (Item      : out Character);

   procedure Get_Immediate (File      : in  File_Type;
                            Item      : out Character;
                            Available : out Boolean);
   procedure Get_Immediate (Item      : out Character;
                            Available : out Boolean);

   -- String Input-Output

   procedure Get (File : in  File_Type; Item : out String);
   procedure Get (Item : out String);

   procedure Put (File : in  File_Type; Item : in String);
   procedure Put (Item : in  String);

   procedure Get_Line (File : in  File_Type;
                       Item : out String;
                       Last : out Natural);
   procedure Get_Line (Item : out String; Last : out Natural);

   function Get_Line(File : in  File_Type) return String;

   function Get_Line return String;

   procedure Put_Line (File : in  File_Type; Item : in String);
   procedure Put_Line (Item : in  String);

   -- Generic packages for Input-Output of Integer Types

   generic
      type Num is range <>;
   package Integer_IO is

      Default_Width : Field := Num'Width;
      Default_Base  : Number_Base := 10;

      procedure Get (File  : in  File_Type;
                     Item  : out Num;
                     Width : in Field := 0);
      procedure Get (Item  : out Num;
                     Width : in  Field := 0);

      procedure Put (File  : in File_Type;
                     Item  : in Num;
                     Width : in Field := Default_Width;
                     Base  : in Number_Base := Default_Base);
      procedure Put (Item  : in Num;
                     Width : in Field := Default_Width;
                     Base  : in Number_Base := Default_Base);
      procedure Get (From : in  String;
                     Item : out Num;
                     Last : out Positive);
      procedure Put (To   : out String;
                     Item : in Num;
                     Base : in Number_Base := Default_Base);

   end Integer_IO;

   generic
      type Num is mod <>;
   package Modular_IO is

      Default_Width : Field := Num'Width;
      Default_Base  : Number_Base := 10;

      procedure Get (File  : in  File_Type;
                     Item  : out Num;
                     Width : in Field := 0);
      procedure Get (Item  : out Num;
                     Width : in  Field := 0);

      procedure Put (File  : in File_Type;
                     Item  : in Num;
                     Width : in Field := Default_Width;
                     Base  : in Number_Base := Default_Base);
      procedure Put (Item  : in Num;
                     Width : in Field := Default_Width;
                     Base  : in Number_Base := Default_Base);
      procedure Get (From : in  String;
                     Item : out Num;
                     Last : out Positive);
      procedure Put (To   : out String;
                     Item : in Num;
                     Base : in Number_Base := Default_Base);

   end Modular_IO;

   -- Generic packages for Input-Output of Real Types

   generic
      type Num is digits <>;
   package Float_IO is

      Default_Fore : Field := 2;
      Default_Aft  : Field := Num'Digits-1;
      Default_Exp  : Field := 3;

      procedure Get (File  : in  File_Type;
                     Item  : out Num;
                     Width : in  Field := 0);
      procedure Get (Item  : out Num;
                     Width : in  Field := 0);

      procedure Put (File : in File_Type;
                     Item : in Num;
                     Fore : in Field := Default_Fore;
                     Aft  : in Field := Default_Aft;
                     Exp  : in Field := Default_Exp);
      procedure Put (Item : in Num;
                     Fore : in Field := Default_Fore;
                     Aft  : in Field := Default_Aft;
                     Exp  : in Field := Default_Exp);

      procedure Get (From : in String;
                     Item : out Num;
                     Last : out Positive);
      procedure Put (To   : out String;
                     Item : in Num;
                     Aft  : in Field := Default_Aft;
                     Exp  : in Field := Default_Exp);
   end Float_IO;

   generic
      type Num is delta <>;
   package Fixed_IO is

      Default_Fore : Field := Num'Fore;
      Default_Aft  : Field := Num'Aft;
      Default_Exp  : Field := 0;

      procedure Get (File  : in  File_Type;
                     Item  : out Num;
                     Width : in  Field := 0);
      procedure Get (Item  : out Num;
                     Width : in  Field := 0);

      procedure Put (File : in File_Type;
                     Item : in Num;
                     Fore : in Field := Default_Fore;
                     Aft  : in Field := Default_Aft;
                     Exp  : in Field := Default_Exp);
      procedure Put (Item : in Num;
                     Fore : in Field := Default_Fore;
                     Aft  : in Field := Default_Aft;
                     Exp  : in Field := Default_Exp);

      procedure Get (From : in  String;
                     Item : out Num;
                     Last : out Positive);
      procedure Put (To   : out String;
                     Item : in Num;
                     Aft  : in Field := Default_Aft;
                     Exp  : in Field := Default_Exp);
   end Fixed_IO;

   generic
      type Num is delta <> digits <>;
   package Decimal_IO is

      Default_Fore : Field := Num'Fore;
      Default_Aft  : Field := Num'Aft;
      Default_Exp  : Field := 0;

      procedure Get (File  : in  File_Type;
                     Item  : out Num;
                     Width : in  Field := 0);
      procedure Get (Item  : out Num;
                     Width : in  Field := 0);

      procedure Put (File : in File_Type;
                     Item : in Num;
                     Fore : in Field := Default_Fore;
                     Aft  : in Field := Default_Aft;
                     Exp  : in Field := Default_Exp);
      procedure Put (Item : in Num;
                     Fore : in Field := Default_Fore;
                     Aft  : in Field := Default_Aft;
                     Exp  : in Field := Default_Exp);

      procedure Get (From : in  String;
                     Item : out Num;
                     Last : out Positive);
      procedure Put (To   : out String;
                     Item : in Num;
                     Aft  : in Field := Default_Aft;
                     Exp  : in Field := Default_Exp);
   end Decimal_IO;

   -- Generic package for Input-Output of Enumeration Types

   generic
      type Enum is (<>);
   package Enumeration_IO is

      Default_Width   : Field := 0;
      Default_Setting : Type_Set := Upper_Case;

      procedure Get (File : in  File_Type;
                     Item : out Enum);
      procedure Get (Item : out Enum);

      procedure Put (File  : in File_Type;
                     Item  : in Enum;
                     Width : in Field    := Default_Width;
                     Set   : in Type_Set := Default_Setting);
      procedure Put (Item  : in Enum;
                     Width : in Field    := Default_Width;
                     Set   : in Type_Set := Default_Setting);

      procedure Get (From : in  String;
                     Item : out Enum;
                     Last : out Positive);
      procedure Put (To   : out String;
                     Item : in  Enum;
                     Set  : in  Type_Set := Default_Setting);
   end Enumeration_IO;

   -- Exceptions

   Status_Error : exception renames IO_Exceptions.Status_Error;
   Mode_Error   : exception renames IO_Exceptions.Mode_Error;
   Name_Error   : exception renames IO_Exceptions.Name_Error;
   Use_Error    : exception renames IO_Exceptions.Use_Error;
   Device_Error : exception renames IO_Exceptions.Device_Error;
   End_Error    : exception renames IO_Exceptions.End_Error;
   Data_Error   : exception renames IO_Exceptions.Data_Error;
   Layout_Error : exception renames IO_Exceptions.Layout_Error;

private

   type File_Type is limited null record;

end Ada.Text_IO;



