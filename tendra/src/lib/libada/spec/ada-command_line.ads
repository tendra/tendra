------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Command_Line is
   pragma Preelaborate (Command_Line);

   function Argument_Count return Natural;

   function Argument (Number : in Positive) return String;

   function Command_Name return String;

   type Exit_Status is range implementation-defined .. implementation-defined;

   Success : constant Exit_Status;
   Failure : constant Exit_Status;

   procedure Set_Exit_Status (Code : in Exit_Status);

private

   pragma Import (Ada, Success);
   pragma Import (Ada, Failure);

end Ada.Command_Line;



