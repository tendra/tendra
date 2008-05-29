------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Environment_Variables is

   pragma Preelaborate (Environment_Variables);

   function Value (Name : in String) return String;

   function Exists (Name : in String) return Boolean;

   procedure Set (Name  : in String;
                  Value : in String);

   procedure Clear (Name : in String);

   procedure Clear;

   procedure Iterate
    (Process : not null access procedure
                                (Name  : in String;
                                 Value : in String));

end Ada.Environment_Variables;
