------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Strings.Wide_Wide_Maps.Wide_Wide_Constants is
   pragma Preelaborate (Wide_Wide_Constants);

   Control_Set           : constant Wide_Wide_Character_Set;
   Graphic_Set           : constant Wide_Wide_Character_Set;
   Letter_Set            : constant Wide_Wide_Character_Set;
   Lower_Set             : constant Wide_Wide_Character_Set;
   Upper_Set             : constant Wide_Wide_Character_Set;
   Basic_Set             : constant Wide_Wide_Character_Set;
   Decimal_Digit_Set     : constant Wide_Wide_Character_Set;
   Hexadecimal_Digit_Set : constant Wide_Wide_Character_Set;
   Alphanumeric_Set      : constant Wide_Wide_Character_Set;
   Special_Set           : constant Wide_Wide_Character_Set;
   ISO_646_Set           : constant Wide_Wide_Character_Set;

   Character_Set         : constant Wide_Wide_Character_Set;
   --  Contains each Wide_Wide_Character value WWC such that
   --  Characters.Conversions.Is_Character(WWC) is True

   Wide_Character_Set    : constant Wide_Wide_Character_Set;
   --  Contains each Wide_Wide_Character value WWC such that
   --  Characters.Conversions.Is_Wide_Character(WWC) is True

   Lower_Case_Map        : constant Wide_Wide_Character_Mapping;
   --Wide_Wide_Maps to lower case for letters, else identity
   Upper_Case_Map        : constant Wide_Wide_Character_Mapping;
   --Wide_Wide_Maps to upper case for letters, else identity
   Basic_Map             : constant Wide_Wide_Character_Mapping;
   --Wide_Wide_Maps to basic letter for letters, else identity

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
   pragma Import (Ada, Character_Set);
   pragma Import (Ada, Wide_Character_Set);

   pragma Import (Ada, Lower_Case_Map);
   pragma Import (Ada, Upper_Case_Map);
   pragma Import (Ada, Basic_Map);

end Ada.Strings.Wide_Wide_Maps.Wide_Wide_Constants;



