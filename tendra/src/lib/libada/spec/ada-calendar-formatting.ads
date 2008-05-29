------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Calendar.Time_Zones;

package Ada.Calendar.Formatting is

   --  Day of the week:

   type Day_Name is
     (Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday);

   function Day_of_Week (Date : in Time) return Day_Name;

   --  Hours:Minutes:Seconds access:

   subtype Hour_Number     is Natural range 0 .. 23;
   subtype Minute_Number   is Natural range 0 .. 59;
   subtype Second_Number   is Natural range 0 .. 59;
   subtype Second_Duration is Day_Duration range 0.0 .. 1.0;

   function Year (Date      : in Time;
                  Time_Zone : in Time_Zones.Time_Offset := 0)
     return Year_Number;

   function Month (Date      : in Time;
                   Time_Zone : in Time_Zones.Time_Offset := 0)
     return Month_Number;

   function Day (Date      : in Time;
                 Time_Zone : in Time_Zones.Time_Offset := 0)
     return Day_Number;

   function Hour (Date      : in Time;
                  Time_Zone : in Time_Zones.Time_Offset := 0)
     return Hour_Number;

   function Minute (Date      : in Time;
                    Time_Zone : in Time_Zones.Time_Offset := 0)
     return Minute_Number;

   function Second (Date : in Time) return Second_Number;

   function Sub_Second (Date : in Time) return Second_Duration;

   function Seconds_Of (Hour       : in Hour_Number;
                        Minute     : in Minute_Number;
                        Second     : in Second_Number   := 0;
                        Sub_Second : in Second_Duration := 0.0)
     return Day_Duration;

   procedure Split (Seconds    : in     Day_Duration;
                    Hour       :    out Hour_Number;
                    Minute     :    out Minute_Number;
                    Second     :    out Second_Number;
                    Sub_Second :    out Second_Duration);

   function Time_Of (Year        : in Year_Number;
                     Month       : in Month_Number;
                     Day         : in Day_Number;
                     Hour        : in Hour_Number;
                     Minute      : in Minute_Number;
                     Second      : in Second_Number;
                     Sub_Second  : in Second_Duration        := 0.0;
                     Leap_Second : in Boolean                := False;
                     Time_Zone   : in Time_Zones.Time_Offset := 0)
     return Time;

   function Time_Of (Year        : in Year_Number;
                     Month       : in Month_Number;
                     Day         : in Day_Number;
                     Seconds     : in Day_Duration           := 0.0;
                     Leap_Second : in Boolean                := False;
                     Time_Zone   : in Time_Zones.Time_Offset := 0)
     return Time;

   procedure Split (Date       : in     Time;
                    Year       :    out Year_Number;
                    Month      :    out Month_Number;
                    Day        :    out Day_Number;
                    Hour       :    out Hour_Number;
                    Minute     :    out Minute_Number;
                    Second     :    out Second_Number;
                    Sub_Second :    out Second_Duration;
                    Time_Zone  : in     Time_Zones.Time_Offset := 0);

   procedure Split (Date        : in     Time;
                    Year        :    out Year_Number;
                    Month       :    out Month_Number;
                    Day         :    out Day_Number;
                    Hour        :    out Hour_Number;
                    Minute      :    out Minute_Number;
                    Second      :    out Second_Number;
                    Sub_Second  :    out Second_Duration;
                    Leap_Second :    out Boolean;
                    Time_Zone   : in     Time_Zones.Time_Offset := 0);

   procedure Split (Date        : in     Time;
                    Year        :    out Year_Number;
                    Month       :    out Month_Number;
                    Day         :    out Day_Number;
                    Seconds     :    out Day_Duration;
                    Leap_Second :    out Boolean;
                    Time_Zone   : in     Time_Zones.Time_Offset := 0);

   --  Simple image and value:

   function Image (Date                  : in Time;
                   Include_Time_Fraction : in Boolean := False;
                   Time_Zone             : in Time_Zones.Time_Offset := 0)
     return String;

   function Value (Date      : in String;
                   Time_Zone : in Time_Zones.Time_Offset := 0)
     return Time;

   function Image (Elapsed_Time          : in Duration;
                   Include_Time_Fraction : in Boolean := False)
     return String;

   function Value (Elapsed_Time : in String) return Duration;

end Ada.Calendar.Formatting;
