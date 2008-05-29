------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Calendar.Time_Zones is

   --  Time zone manipulation:

   type Time_Offset is range -28 * 60 .. 28 * 60;

   Unknown_Zone_Error : exception;

   function UTC_Time_Offset (Date : in Time := Clock) return Time_Offset;

end Ada.Calendar.Time_Zones;
