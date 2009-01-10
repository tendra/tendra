------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments-containers.adb 2455 2006-06-24 19:22:06Z $:

with Asis.Gela.Classificators_Ada_UTF_8;
with Asis.Gela.Classificators_Ada_UTF_16;
with Asis.Gela.Classificators_Ada_Fixed_Width_8;

function Asis.Gela.Classificators_Create
  (Encoding : Encodings.Encoding;
   Decoder  : Decoders.Decoder'Class) return Classificators.Classificator'Class
is
   use type Encodings.Encoding;
begin
   if Encoding in Encodings.Fixed_Width_Encoding then
      declare
         Result : Classificators_Ada_Fixed_Width_8.Classificator;
      begin
         Classificators_Ada_Fixed_Width_8.Initialize (Result, Decoder);
         return Result;
      end;
   elsif Encoding = Encodings.UTF_8 then
      declare
         Result : Classificators_Ada_UTF_8.Classificator;
      begin
         Classificators_Ada_UTF_8.Initialize;
         return Result;
      end;
   elsif Encoding = Encodings.UTF_16 then
      declare
         Result : Classificators_Ada_UTF_16.Classificator;
      begin
         Classificators_Ada_UTF_16.Initialize;
         return Result;
      end;
   else
      raise Program_Error;
   end if;
end Asis.Gela.Classificators_Create;


------------------------------------------------------------------------------
--  Copyright (c) 2009, Maxim Reznik
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
