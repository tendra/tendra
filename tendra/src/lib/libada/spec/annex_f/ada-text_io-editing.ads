------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Text_IO.Editing is

   type Picture is private;

   function Valid (Pic_String      : in String;
                   Blank_When_Zero : in Boolean := False) return Boolean;

   function To_Picture (Pic_String      : in String;
                        Blank_When_Zero : in Boolean := False)
                       return Picture;

   function Pic_String      (Pic : in Picture) return String;
   function Blank_When_Zero (Pic : in Picture) return Boolean;

   Max_Picture_Length  : constant := implementation_defined;

   Picture_Error       : exception;

   Default_Currency    : constant String    := "$";
   Default_Fill        : constant Character := '*';
   Default_Separator   : constant Character := ',';
   Default_Radix_Mark  : constant Character := '.';

   generic
      type Num is delta <> digits <>;

      Default_Currency   : in String    := Text_IO.Editing.Default_Currency;
      Default_Fill       : in Character := Text_IO.Editing.Default_Fill;
      Default_Separator  : in Character := Text_IO.Editing.Default_Separator;
      Default_Radix_Mark : in Character := Text_IO.Editing.Default_Radix_Mark;
   package Decimal_Output is
      function Length (Pic      : in Picture;
                       Currency : in String := Default_Currency)
                      return Natural;

      function Valid (Item     : in Num;
                      Pic      : in Picture;
                      Currency : in String := Default_Currency)
                     return Boolean;

      function Image (Item       : in Num;
                      Pic        : in Picture;
                      Currency   : in String    := Default_Currency;
                      Fill       : in Character := Default_Fill;
                      Separator  : in Character := Default_Separator;
                      Radix_Mark : in Character := Default_Radix_Mark)
                     return String;

      procedure Put (File       : in File_Type;
                     Item       : in Num;
                     Pic        : in Picture;
                     Currency   : in String    := Default_Currency;
                     Fill       : in Character := Default_Fill;
                     Separator  : in Character := Default_Separator;
                     Radix_Mark : in Character := Default_Radix_Mark);

      procedure Put (Item       : in Num;
                     Pic        : in Picture;
                     Currency   : in String    := Default_Currency;
                     Fill       : in Character := Default_Fill;
                     Separator  : in Character := Default_Separator;
                     Radix_Mark : in Character := Default_Radix_Mark);

      procedure Put (To         : out String;
                     Item       : in Num;
                     Pic        : in Picture;
                     Currency   : in String    := Default_Currency;
                     Fill       : in Character := Default_Fill;
                     Separator  : in Character := Default_Separator;
                     Radix_Mark : in Character := Default_Radix_Mark);
   end Decimal_Output;

private
   pragma Import (Ada, Picture);
end Ada.Text_IO.Editing;
