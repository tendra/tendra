------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Real_Time.Timing_Events is

   type Timing_Event is tagged limited private;

   type Timing_Event_Handler is
     access protected procedure (Event : in out Timing_Event);

   procedure Set_Handler (Event   : in out Timing_Event;
                          At_Time : in     Time;
                          Handler : in     Timing_Event_Handler);

   procedure Set_Handler (Event   : in out Timing_Event;
                          In_Time : in     Time_Span;
                          Handler : in     Timing_Event_Handler);

   function Current_Handler (Event : in Timing_Event)
     return Timing_Event_Handler;

   procedure Cancel_Handler (Event     : in out Timing_Event;
                             Cancelled :    out Boolean);

   function Time_Of_Event (Event : in Timing_Event) return Time;

private

   pragma Import (Ada, Timing_Event);

end Ada.Real_Time.Timing_Events;
