------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Real_Time;
with Ada.Task_Identification;

package Ada.Execution_Time is

   type CPU_Time is private;

   CPU_Time_First : constant CPU_Time;
   CPU_Time_Last  : constant CPU_Time;
   CPU_Time_Unit  : constant := implementation-defined-real-number;

   CPU_Tick : constant Ada.Real_Time.Time_Span;

   function Clock (T : in Ada.Task_Identification.Task_Id
                     := Ada.Task_Identification.Current_Task)
     return CPU_Time;

   function "+" (Left  : in CPU_Time;
                 Right : in Ada.Real_Time.Time_Span)
     return CPU_Time;

   function "+" (Left  : in Ada.Real_Time.Time_Span;
                 Right : in CPU_Time)
     return CPU_Time;

   function "-" (Left  : in CPU_Time;
                 Right : in Ada.Real_Time.Time_Span)
     return CPU_Time;

   function "-" (Left  : in CPU_Time;
                 Right : in CPU_Time)
     return Ada.Real_Time.Time_Span;

   function "<" (Left  : in CPU_Time;
                 Right : in CPU_Time)
     return Boolean;

   function "<=" (Left  : in CPU_Time;
                  Right : in CPU_Time)
     return Boolean;

   function ">" (Left  : in CPU_Time;
                 Right : in CPU_Time)
     return Boolean;

   function ">=" (Left  : in CPU_Time;
                  Right : in CPU_Time)
     return Boolean;

   procedure Split (T  : in     CPU_Time;
                    SC :    out Ada.Real_Time.Seconds_Count;
                    TS :    out Ada.Real_Time.Time_Span);

   function Time_Of (SC : in Ada.Real_Time.Seconds_Count;
                     TS : in Ada.Real_Time.Time_Span
                       := Ada.Real_Time.Time_Span_Zero)
     return CPU_Time;

private

   pragma Import (Ada, CPU_Time);
   pragma Import (Ada, CPU_Time_First);
   pragma Import (Ada, CPU_Time_Last);
   pragma Import (Ada, CPU_Tick);

end Ada.Execution_Time;
