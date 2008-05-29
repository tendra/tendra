------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Synchronous_Task_Control is

   pragma Preelaborate (Synchronous_Task_Control);

   type Suspension_Object is limited private;

   procedure Set_True (S : in out Suspension_Object);

   procedure Set_False (S : in out Suspension_Object);

   function Current_State (S : in Suspension_Object) return Boolean;

   procedure Suspend_Until_True (S : in out Suspension_Object);

private

   pragma Import (Ada, Suspension_Object);

end Ada.Synchronous_Task_Control;
