------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Real_Time is

   type Time is private;

   Time_First : constant Time;
   Time_Last  : constant Time;

   Time_Unit : constant := implementation-defined-real-number;

   type Time_Span is private;

   Time_Span_First : constant Time_Span;
   Time_Span_Last  : constant Time_Span;
   Time_Span_Zero  : constant Time_Span;
   Time_Span_Unit  : constant Time_Span;
   Tick            : constant Time_Span;

   function Clock return Time;

   function "+" (Left  : in Time;
                 Right : in Time_Span)
     return Time;

   function "+" (Left  : in Time_Span;
                 Right : in Time)
     return Time;

   function "-" (Left  : in Time;
                 Right : in Time_Span)
     return Time;

   function "-" (Left  : in Time;
                 Right : in Time)
     return Time_Span;

   function "<" (Left  : in Time;
                 Right : in Time)
     return Boolean;

   function "<=" (Left  : in Time;
                  Right : in Time)
     return Boolean;

   function ">" (Left  : in Time;
                 Right : in Time)
     return Boolean;

   function ">=" (Left  : in Time;
                  Right : in Time)
     return Boolean;

   function "+" (Left  : in Time_Span;
                 Right : in Time_Span)
     return Time_Span;

   function "-" (Left  : in Time_Span;
                 Right : in Time_Span)
     return Time_Span;

   function "-" (Right : in Time_Span) return Time_Span;

   function "*" (Left  : in Time_Span;
                 Right : in Integer)
     return Time_Span;

   function "*" (Left  : in Integer;
                 Right : Time_Span)
     return Time_Span;

   function "/" (Left  : in Time_Span;
                 Right : in Time_Span)
     return Integer;

   function "/" (Left  : in Time_Span;
                 Right : in Integer)
     return Time_Span;

   function "abs" (Right : in Time_Span) return Time_Span;

   function "<" (Left  : in Time_Span;
                 Right : in Time_Span)
     return Boolean;

   function "<=" (Left  : in Time_Span;
                  Right : in Time_Span)
     return Boolean;

   function ">" (Left  : in Time_Span;
                 Right : in Time_Span)
     return Boolean;

   function ">=" (Left  : in Time_Span;
                  Right : in Time_Span)
     return Boolean;

   function To_Duration (TS : in Time_Span) return Duration;

   function To_Time_Span (D : in Duration) return Time_Span;

   function Nanoseconds (NS : in Integer) return Time_Span;

   function Microseconds (US : in Integer) return Time_Span;

   function Milliseconds (MS : in Integer) return Time_Span;

   function Seconds (S : in Integer) return Time_Span;

   function Minutes (M : in Integer) return Time_Span;

   type Seconds_Count is
     range implementation-defined .. implementation-defined;

   procedure Split (T  : in     Time;
                    SC :    out Seconds_Count;
                    TS :    out Time_Span);

   function Time_Of (SC : in Seconds_Count;
                     TS : in Time_Span)
     return Time;

private

   pragma Import (Ada, Time);
   pragma Import (Ada, Time_First);
   pragma Import (Ada, Time_Last);

   pragma Import (Ada, Time_Span);
   pragma Import (Ada, Time_Span_First);
   pragma Import (Ada, Time_Span_Last);
   pragma Import (Ada, Time_Span_Zero);
   pragma Import (Ada, Time_Span_Unit);
   pragma Import (Ada, Tick);

end Ada.Real_Time;
