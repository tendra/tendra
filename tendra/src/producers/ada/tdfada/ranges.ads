with Asis;
with States;
with XASIS.Classes;
with XASIS.Static;
with TenDRA.Streams;

package Ranges is
   use TenDRA.Streams;

   type Range_Context is private;

   procedure New_Context
     (State    : access States.State;
      Element  : in     Asis.Range_Constraint;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Context  :    out Range_Context);

   procedure Compile
     (State    : access States.State;
      Element  : in     Asis.Range_Constraint;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Context  : in     Range_Context;
      Bound    : in     XASIS.Static.Bound_Kinds);

   procedure New_Context_Discrete
     (State    : access States.State;
      Element  : in     Asis.Discrete_Range;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Context  :    out Range_Context);

   procedure Compile_Discrete
     (State    : access States.State;
      Element  : in     Asis.Discrete_Range;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Context  : in     Range_Context;
      Bound    : in     XASIS.Static.Bound_Kinds);

private
   type Range_Context is null record;
end Ranges;

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
