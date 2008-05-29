------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Interfaces.C is
   pragma Pure(C);

   -- Declarations based on C's <limits.h>

   CHAR_BIT  : constant := implementation-defined;  -- typically 8
   SCHAR_MIN : constant := implementation-defined;  -- typically -128
   SCHAR_MAX : constant := implementation-defined;  -- typically 127
   UCHAR_MAX : constant := implementation-defined;  -- typically 255

   -- Signed and Unsigned Integers
   type int   is range implementation-defined .. implementation-defined;
   type short is range implementation-defined .. implementation-defined;
   type long  is range implementation-defined .. implementation-defined;

   type signed_char is range SCHAR_MIN .. SCHAR_MAX;
   for signed_char'Size use CHAR_BIT;

   type unsigned       is mod implementation-defined;
   type unsigned_short is mod implementation-defined;
   type unsigned_long  is mod implementation-defined;

   type unsigned_char is mod (UCHAR_MAX+1);
   for unsigned_char'Size use CHAR_BIT;

   subtype plain_char is unsigned_char; --  implementation-defined;

   type ptrdiff_t is range implementation-defined .. implementation-defined;

   type size_t is mod implementation-defined;

   -- Floating Point

   type C_float     is digits implementation-defined;

   type double      is digits implementation-defined;

   type long_double is digits implementation-defined;

   -- Characters and Strings

   type char is ('x'); --  implementation-defined character type;

   nul : constant char := implementation-defined;

   function To_C   (Item : in Character) return char;

   function To_Ada (Item : in char) return Character;

   type char_array is array (size_t range <>) of aliased char;
   pragma Pack (char_array);
   for char_array'Component_Size use CHAR_BIT;

   function Is_Nul_Terminated (Item : in char_array) return Boolean;

   function To_C   (Item       : in String;
                    Append_Nul : in Boolean := True)
                   return char_array;

   function To_Ada (Item     : in char_array;
                    Trim_Nul : in Boolean := True)
                   return String;

   procedure To_C (Item       : in String;
                   Target     : out char_array;
                   Count      : out size_t;
                   Append_Nul : in Boolean := True);

   procedure To_Ada (Item     : in char_array;
                     Target   : out String;
                     Count    : out Natural;
                     Trim_Nul : in Boolean := True);

   -- Wide Character and Wide String

   type wchar_t is (' ');  --  implementation-defined char type;

   wide_nul : constant wchar_t := implementation-defined;

   function To_C   (Item : in Wide_Character) return wchar_t;
   function To_Ada (Item : in wchar_t       ) return Wide_Character;

   type wchar_array is array (size_t range <>) of aliased wchar_t;

   pragma Pack (wchar_array);

   function Is_Nul_Terminated (Item : in wchar_array) return Boolean;

   function To_C   (Item       : in Wide_String;
                    Append_Nul : in Boolean := True)
                   return wchar_array;

   function To_Ada (Item     : in wchar_array;
                    Trim_Nul : in Boolean := True)
                   return Wide_String;

   procedure To_C (Item       : in  Wide_String;
                   Target     : out wchar_array;
                   Count      : out size_t;
                   Append_Nul : in  Boolean := True);

   procedure To_Ada (Item     : in  wchar_array;
                     Target   : out Wide_String;
                     Count    : out Natural;
                     Trim_Nul : in  Boolean := True);

   --  ISO/IEC 10646:2003 compatible types defined by ISO/IEC TR 19769:2004.

   type char16_t is ('x');  --  implementation-defined character type

   char16_nul : constant char16_t := implementation-defined;

   function To_C (Item : in Wide_Character) return char16_t;

   function To_Ada (Item : in char16_t) return Wide_Character;

   type char16_array is array (size_t range <>) of aliased char16_t;
   pragma Pack (char16_array);

   function Is_Nul_Terminated (Item : in char16_array) return Boolean;

   function To_C (Item       : in Wide_String;
                  Append_Nul : in Boolean := True)
                 return char16_array;

   function To_Ada (Item     : in char16_array;
                    Trim_Nul : in Boolean := True)
                   return Wide_String;

   procedure To_C (Item       : in     Wide_String;
                   Target     :    out char16_array;
                   Count      :    out size_t;
                   Append_Nul : in     Boolean := True);

   procedure To_Ada (Item     : in     char16_array;
                     Target   :    out Wide_String;
                     Count    :    out Natural;
                     Trim_Nul : in     Boolean := True);

   type char32_t is ('x');  --  implementation-defined character type

   char32_nul : constant char32_t := implementation-defined;

   function To_C (Item : in Wide_Wide_Character) return char32_t;

   function To_Ada (Item : in char32_t) return Wide_Wide_Character;

   type char32_array is array (size_t range <>) of aliased char32_t;
   pragma Pack (char32_array);

   function Is_Nul_Terminated (Item : in char32_array) return Boolean;

   function To_C (Item       : in Wide_Wide_String;
                  Append_Nul : in Boolean := True)
                 return char32_array;

   function To_Ada (Item     : in char32_array;
                    Trim_Nul : in Boolean := True)
                   return Wide_Wide_String;

   procedure To_C (Item       : in     Wide_Wide_String;
                   Target     :    out char32_array;
                   Count      :    out size_t;
                   Append_Nul : in     Boolean := True);

   procedure To_Ada (Item     : in     char32_array;
                     Target   :    out Wide_Wide_String;
                     Count    :    out Natural;
                     Trim_Nul : in     Boolean := True);

   Terminator_Error : exception;

end Interfaces.C;



