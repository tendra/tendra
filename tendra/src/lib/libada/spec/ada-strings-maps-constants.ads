------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Strings.Maps.Constants is
   pragma Pure (Constants);

   Control_Set           : constant Character_Set;
   Graphic_Set           : constant Character_Set;
   Letter_Set            : constant Character_Set;
   Lower_Set             : constant Character_Set;
   Upper_Set             : constant Character_Set;
   Basic_Set             : constant Character_Set;
   Decimal_Digit_Set     : constant Character_Set;
   Hexadecimal_Digit_Set : constant Character_Set;
   Alphanumeric_Set      : constant Character_Set;
   Special_Set           : constant Character_Set;
   ISO_646_Set           : constant Character_Set;

   Lower_Case_Map        : constant Character_Mapping;
   --Maps to lower case for letters, else identity
   Upper_Case_Map        : constant Character_Mapping;
   --Maps to upper case for letters, else identity
   Basic_Map             : constant Character_Mapping;
   --Maps to basic letter for letters, else identity

private

   pragma Import (Ada, Control_Set);
   pragma Import (Ada, Graphic_Set);
   pragma Import (Ada, Letter_Set);
   pragma Import (Ada, Lower_Set);
   pragma Import (Ada, Upper_Set);
   pragma Import (Ada, Basic_Set);
   pragma Import (Ada, Decimal_Digit_Set);
   pragma Import (Ada, Hexadecimal_Digit_Set);
   pragma Import (Ada, Alphanumeric_Set);
   pragma Import (Ada, Special_Set);
   pragma Import (Ada, ISO_646_Set);

   pragma Import (Ada, Lower_Case_Map);
   pragma Import (Ada, Upper_Case_Map);
   pragma Import (Ada, Basic_Map);

end Ada.Strings.Maps.Constants;



