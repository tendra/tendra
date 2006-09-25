with Asis;
with Ranges;
with States;
with XASIS.Classes;
with TenDRA.Streams;

package Declaration is

   procedure Compile
     (State    : access States.State;
      Decl     : in     Asis.Declaration);

   procedure Loop_Parameter
     (State    : access States.State;
      Decl     : in     Asis.Declaration;
      Def      :    out Asis.Discrete_Subtype_Definition;
      Tag      :    out TenDRA.Small;
      Incr     :    out Boolean;
      Context  :    out Ranges.Range_Context);

   procedure New_Tag
     (State : access States.State;
      Link  : in     States.Linkage_Access);

   procedure Output_Shape
     (State   : access States.State;
      Tipe    : in     XASIS.Classes.Type_Info;
      B       : in out TenDRA.Streams.Stream'Class;
      Unit    : in     States.Unit_Kinds);

end Declaration;


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
