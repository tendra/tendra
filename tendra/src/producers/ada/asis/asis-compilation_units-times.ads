-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  11  package Asis.Compilation_Units.Times
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

with Ada.Calendar;
package Asis.Compilation_Units.Times is

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  Asis.Compilation_Units.Times encapsulates the time related functions used
--  within ASIS.
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  11.1        type Time
-------------------------------------------------------------------------------
--  ASIS uses the predefined Ada.Calendar.Time.
--  ASIS uses the predefined Standard.Duration.
--  The constant Nil_ASIS_Time is defined to support time queries where a
--  time is unavailable/unknown.
-------------------------------------------------------------------------------

   Nil_ASIS_Time : constant Ada.Calendar.Time :=
     Ada.Calendar.Time_Of (Year    => 1901,
                           Month   => 1,
                           Day     => 1,
                           Seconds => 0.0);

-------------------------------------------------------------------------------
--  11.2        function Time_Of_Last_Update
-------------------------------------------------------------------------------

   function Time_Of_Last_Update (Compilation_Unit : in Asis.Compilation_Unit)
                                return Ada.Calendar.Time;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit to query
--
--  Returns the time that this physical compilation unit was most recently
--  updated in its implementor's Ada Environment.  This will often be the
--  time of its last compilation.  The exact significance of the result is
--  implementation specific.
--  Returns Nil_ASIS_Time if the unit has a Nil or nonexistent unit kind, or if
--  the time of last update is not available, or not meaningful, for any
--  reason.
--
--  All Unit Kinds are appropriate.
--
-------------------------------------------------------------------------------
--  11.3        function Compilation_CPU_Duration
-------------------------------------------------------------------------------

   function Compilation_CPU_Duration
     (Compilation_Unit : in Asis.Compilation_Unit)
     return Standard.Duration;

-------------------------------------------------------------------------------
--  Compilation_Unit  - Specifies the unit to query
--
--  Returns the Central Processing Unit (CPU) duration used to compile the
--  physical compilation unit associated with the Compilation_Unit argument.
--  The exact significance, or accuracy, of the result is implementation
--  specific.  Returns a duration of 0.0 if the unit has a Nil or nonexistent
--  unit kind, or if the CPU duration for the last compilation is not available
--  for any reason. Returns a duration of 86_400.0 if the CPU duration for the
--  last compilation is greater than 1 day.
--
--  All Unit Kinds are appropriate.
--

-------------------------------------------------------------------------------
--  11.4        function Attribute_Time
-------------------------------------------------------------------------------

   function Attribute_Time
               (Compilation_Unit : in Asis.Compilation_Unit;
                Attribute        : in Wide_String)
               return Ada.Calendar.Time;

-------------------------------------------------------------------------------
--  Compilation_Unit    - Specifies the unit to query
--  Attribute           - Specifies the name of the attribute to query
--
--  Returns the Time value associated with the given attribute.  Returns
--  Nil_ASIS_Time if the argument is a Nil_Compilation_Unit, the unit does
--  not have the given Attribute, or the implementation does not record times
--  for attributes.
--
--  All Unit Kinds are appropriate.
--
--  Results of this query may vary across ASIS implementations.
--
-------------------------------------------------------------------------------

end Asis.Compilation_Units.Times;


------------------------------------------------------------------------------
--  Copyright (c) 2006, Maxim Reznik
--  All rights reserved.
--
--  Redistribution and use in source and binary forms, with or without
--  modification, are permitted provided that the following conditions are met:
--
--     * Redistributions of source code must retain the above copyright notice,
--     * this list of conditions and the following disclaimer.
--     * Redistributions in binary form must reproduce the above copyright
--     * notice, this list of conditions and the following disclaimer in the
--     * documentation and/or other materials provided with the distribution.
--
--  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
--  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
--  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
--  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
--  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
--  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
--  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
--  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
--  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
--  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
--  POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------
