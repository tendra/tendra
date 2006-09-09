with Asis;
with States;
with TenDRA;
with TenDRA.Streams;

with XASIS.Classes;

package Expression is
   use TenDRA.Streams;

   procedure Compile
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   procedure Compile_Boolean
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Negative : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);
   --  Compile Boolean expression and return value

   procedure Compile_Boolean
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Negative : in     Boolean;
      Label    : in     TenDRA.Small;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);
   --  Compile Boolean expression and jump to Label

   procedure Invert_Boolean
     (State    : access States.State;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);
   --  Output invert operator for boolean value

   procedure Function_Call
     (State    : access States.State;
      Element  : in     Asis.Element;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   procedure Target_Name
     (State    : access States.State;
      Element  : in     Asis.Expression;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   procedure Computed_Static
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Tipe     : in     XASIS.Classes.Type_Info;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);
   --  Output computed static value of universal variety.
   --  Universal variety for Boolean is just Boolean.V
   --  Universal variety for other discrete types is universal
   --  integer variety.

   function Universal_Variety
     (State    : access States.State;
      Tipe     : in     XASIS.Classes.Type_Info;
      Unit     : in     States.Unit_Kinds) return TenDRA.Small;

   procedure Output_Signed_Nat
     (B        : in out Stream'Class;
      Value    : in     TenDRA.Small;
      Negative : in     Boolean := False);

end Expression;


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
