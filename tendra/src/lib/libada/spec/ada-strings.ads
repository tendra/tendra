------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Strings is
   pragma Pure (Strings);

   Space           : constant Character      := ' ';
   Wide_Space      : constant Wide_Character := ' ';
   Wide_Wide_Space : constant Wide_Wide_Character := ' ';

   Length_Error, Pattern_Error, Index_Error, Translation_Error
     : exception;

   type Alignment  is (Left, Right, Center);
   type Truncation is (Left, Right, Error);
   type Membership is (Inside, Outside);
   type Direction  is (Forward, Backward);
   type Trim_End   is (Left, Right, Both);

end Ada.Strings;



