with States;
with TenDRA.Types;
with TenDRA.Streams;

package Token is

   procedure New_Token
     (State : access States.State;
      Link  : in     States.Linkage_Access);

   procedure Initialize
     (Stream : in out TenDRA.Streams.Memory_Stream;
      Kind   : in     States.Support_Kinds);

   type Arg_List  is array (Positive range <>) of TenDRA.Small;
   type Arg_Types is array (Positive range <>) of TenDRA.Types.Construct;

   procedure Open_Token_Def
     (State  : access States.State;
      D      : in out TenDRA.Streams.Memory_Stream;
      Args   :    out Arg_List;
      Types  : in     Arg_Types;
      Result : in     TenDRA.Types.Construct := TenDRA.Types.c_exp);

   procedure Open_Token_Def
     (State  : access States.State;
      D      : in out TenDRA.Streams.Memory_Stream;
      Result : in     TenDRA.Types.Construct := TenDRA.Types.c_exp);

   procedure Close_Token_Def
     (State : access States.State;
      D     : in out TenDRA.Streams.Memory_Stream;
      Tok   : in     TenDRA.Small);

end Token;


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
