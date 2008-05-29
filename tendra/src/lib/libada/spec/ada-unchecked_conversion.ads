------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

generic
   type Source (<>) is limited private;
   type Target (<>) is limited private;
function Ada.Unchecked_Conversion (S : Source) return Target;

pragma Convention (Intrinsic, Ada.Unchecked_Conversion);
pragma Pure (Ada.Unchecked_Conversion);



