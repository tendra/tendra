------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Task_Identification;
with Ada.Exceptions;

package Ada.Task_Termination is
   pragma Preelaborate(Task_Termination);

   type Cause_Of_Termination is (Normal, Abnormal, Unhandled_Exception);

   type Termination_Handler is access protected procedure
     (Cause : in Cause_Of_Termination;
      T     : in Ada.Task_Identification.Task_Id;
      X     : in Ada.Exceptions.Exception_Occurrence);

   procedure Set_Dependents_Fallback_Handler
     (Handler: in Termination_Handler);

   function Current_Task_Fallback_Handler return Termination_Handler;

   procedure Set_Specific_Handler
     (T       : in Ada.Task_Identification.Task_Id;
      Handler : in Termination_Handler);

   function Specific_Handler (T : Ada.Task_Identification.Task_Id)
                             return Termination_Handler;

end Ada.Task_Termination;
