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
   with package Complex_Types is
     new Ada.Numerics.Generic_Complex_Types (<>);
package Ada.Wide_Text_IO.Complex_IO is

   use Complex_Types;

   Default_Fore : Field := 2;
   Default_Aft  : Field := Real'Digits - 1;
   Default_Exp  : Field := 3;

   procedure Get (File  : in  File_Type;
                  Item  : out Complex;
                  Width : in  Field := 0);

   procedure Get (Item  : out Complex;
                  Width : in  Field := 0);

   procedure Put (File : in File_Type;
                  Item : in Complex;
                  Fore : in Field := Default_Fore;
                  Aft  : in Field := Default_Aft;
                  Exp  : in Field := Default_Exp);

   procedure Put (Item : in Complex;
                  Fore : in Field := Default_Fore;
                  Aft  : in Field := Default_Aft;
                  Exp  : in Field := Default_Exp);

   procedure Get (From : in  Wide_String;
                  Item : out Complex;
                  Last : out Positive);

   procedure Put (To   : out Wide_String;
                  Item : in  Complex;
                  Aft  : in  Field := Default_Aft;
                  Exp  : in  Field := Default_Exp);

end Ada.Wide_Text_IO.Complex_IO;
