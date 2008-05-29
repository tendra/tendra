------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Real_Time;
with System;

package Ada.Dispatching.Round_Robin is

   Default_Quantum : constant Ada.Real_Time.Time_Span :=
     implementation-defined;

   procedure Set_Quantum (Pri     : in System.Priority;
                          Quantum : in Ada.Real_Time.Time_Span);

   procedure Set_Quantum (Low     : in System.Priority;
                          High    : in System.Priority;
                          Quantum : in Ada.Real_Time.Time_Span);

   function Actual_Quantum (Pri : in System.Priority)
     return Ada.Real_Time.Time_Span;

   function Is_Round_Robin (Pri : in System.Priority) return Boolean;

end Ada.Dispatching.Round_Robin;
