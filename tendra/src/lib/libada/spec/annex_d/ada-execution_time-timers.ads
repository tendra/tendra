------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with System;

package Ada.Execution_Time.Timers is

   type Timer (T : not null access constant Ada.Task_Identification.Task_Id) is
     tagged limited private;

   type Timer_Handler is access protected procedure (TM : in out Timer);

   Min_Handler_Ceiling : constant System.Any_Priority :=
     implementation-defined;

   procedure Set_Handler (TM      : in out Timer;
                          In_Time : in     Ada.Real_Time.Time_Span;
                          Handler : in     Timer_Handler);

   procedure Set_Handler (TM      : in out Timer;
                          At_Time : in     CPU_Time;
                          Handler : in     Timer_Handler);

   function Current_Handler (TM : Timer) return Timer_Handler;

   procedure Cancel_Handler (TM            : in out Timer;
                                 Cancelled :    out Boolean);

   function Time_Remaining (TM : Timer) return Ada.Real_Time.Time_Span;

   Timer_Resource_Error : exception;

private

   pragma Import (Ada, Timer);

end Ada.Execution_Time.Timers;
