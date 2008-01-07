------------------------------------------------------------------------------
--                           G E L A   X A S I S                            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Multyprecission integer arithmetic

with Ada.Strings.Unbounded;

package XASIS.Integers is

   type Value is private;

   function Literal (Text : String) return Value;

   function "and" (Left, Right : Value) return Value;
   function "or" (Left, Right : Value) return Value;
   function "xor" (Left, Right : Value) return Value;

   function "=" (Left, Right : Value) return Boolean;
   function ">" (Left, Right : Value) return Boolean;
   function "<" (Left, Right : Value) return Boolean;
   function ">=" (Left, Right : Value) return Boolean;
   function "<=" (Left, Right : Value) return Boolean;

   function "-" (Left : Value) return Value;
   function "+" (Left, Right : Value) return Value;
   function "-" (Left, Right : Value) return Value;
   function "*" (Left, Right : Value) return Value;
   function "/" (Left, Right : Value) return Value;
   function "mod" (Left, Right : Value) return Value;
   function "rem" (Left, Right : Value) return Value;
   function "**" (Left, Right : Value) return Value;
   function "abs" (Left : Value) return Value;
   function "not" (Left : Value) return Value;

   function Image (Left : Value) return String;

   Zero : constant Value;
   One  : constant Value;
   Two  : constant Value;
   Ten  : constant Value;

private

   package U renames Ada.Strings.Unbounded;
   type Value is new U.Unbounded_String;

   Zero : constant Value := To_Unbounded_String ("+");
   One  : constant Value := To_Unbounded_String ('+' & Character'Val (1));
   Two  : constant Value := To_Unbounded_String ('+' & Character'Val (2));
   Ten  : constant Value := To_Unbounded_String ('+' & Character'Val (10));

end XASIS.Integers;


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
