with Interfaces.C.Strings;       use Interfaces.C.Strings;

separate (Asis.Gela.Library)

function Env return String is
   use Interfaces;

   function getenv (Name : C.char_array) return chars_ptr;
   pragma Import (C, getenv, "getenv");

   C_Text : constant chars_ptr := getenv (C.To_C ("GELA_INCLUDE_PATH"));
begin
   if C_Text = Null_Ptr then
      return "";
   else
      return Value (C_Text);
   end if;
end Env;
