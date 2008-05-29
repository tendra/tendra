------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Calendar is
   type Time is private;

   subtype Year_Number  is Integer range 1901 .. 2399;
   subtype Month_Number is Integer range 1 .. 12;
   subtype Day_Number   is Integer range 1 .. 31;
   subtype Day_Duration is Duration range 0.0 .. 86_400.0;

   function Clock return Time;

   function Year   (Date : Time) return Year_Number;
   function Month  (Date : Time) return Month_Number;
   function Day    (Date : Time) return Day_Number;
   function Seconds(Date : Time) return Day_Duration;

   procedure Split (Date  : in Time;
                    Year    : out Year_Number;
                    Month   : out Month_Number;
                    Day     : out Day_Number;
                    Seconds : out Day_Duration);

   function Time_Of(Year  : Year_Number;
                    Month   : Month_Number;
                    Day     : Day_Number;
                    Seconds : Day_Duration := 0.0)
                   return Time;

   function "+" (Left : Time;   Right : Duration) return Time;
   function "+" (Left : Duration; Right : Time) return Time;
   function "-" (Left : Time;   Right : Duration) return Time;
   function "-" (Left : Time;   Right : Time) return Duration;

   function "<" (Left, Right : Time) return Boolean;
   function "<="(Left, Right : Time) return Boolean;
   function ">" (Left, Right : Time) return Boolean;
   function ">="(Left, Right : Time) return Boolean;

   Time_Error : exception;

private

   pragma Import (Ada, Time);

end Ada.Calendar;



