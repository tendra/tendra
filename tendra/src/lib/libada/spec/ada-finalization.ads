------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Finalization is
   pragma Preelaborate (Finalization);
   pragma Remote_Types (Finalization);

   type Controlled is abstract tagged private;
   pragma Preelaborable_Initialization (Controlled);

   procedure Initialize  (Object : in out Controlled) is null;
   procedure Adjust      (Object : in out Controlled) is null;
   procedure Finalize    (Object : in out Controlled) is null;

   type Limited_Controlled is abstract tagged limited private;
   pragma Preelaborable_Initialization (Limited_Controlled);

   procedure Initialize  (Object : in out Limited_Controlled) is null;
   procedure Finalize    (Object : in out Limited_Controlled) is null;

private

   pragma Import (Ada, Controlled);
   pragma Import (Ada, Limited_Controlled);

end Ada.Finalization;



