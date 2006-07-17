with Asis;
with States;
with TenDRA;
with TenDRA.Streams;

with XASIS.Classes;

package Expression is

   procedure Compile
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Tipe     : in     XASIS.Classes.Type_Info);

   --  Compile Boolean expression and return value
   procedure Compile_Boolean
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Negative : in     Boolean);

   --  Compile Boolean expression and jump to Label
   procedure Compile_Boolean
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Negative : in     Boolean;
      Label    : in     TenDRA.Small);

   --  Output invert operator for boolean value
   procedure Invert_Boolean (State : access States.State);

   procedure Static_Signed_Nat
     (State   : access States.State;
      Element : in     Asis.Expression;
      B       : in out TenDRA.Streams.Stream'Class);

   procedure Function_Call
     (State   : access States.State;
      Element : in     Asis.Element;
      Tipe    : in     XASIS.Classes.Type_Info);

   procedure Target_Name
     (State    : access States.State;
      Element  : in     Asis.Expression);

   procedure Apply_Defining_Name
     (B       : in out TenDRA.Streams.Memory_Stream;
      State   : access States.State;
      Name    : in     Asis.Defining_Name;
      L_Value : in     Boolean := False;
      Unit    : in     States.Unit_Kinds := States.TAGDEF);

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
