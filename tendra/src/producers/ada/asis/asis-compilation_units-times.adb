------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Procedural wrapper over Object-Oriented ASIS implementation

package body Asis.Compilation_Units.Times is

   --------------------
   -- Attribute_Time --
   --------------------

   function Attribute_Time
     (Compilation_Unit : in Asis.Compilation_Unit;
      Attribute        : in Wide_String)
      return Ada.Calendar.Time
   is
   begin
      return Nil_ASIS_Time;
   end Attribute_Time;

   ------------------------------
   -- Compilation_CPU_Duration --
   ------------------------------

   function Compilation_CPU_Duration
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Standard.Duration
   is
   begin
      return 0.0;
   end Compilation_CPU_Duration;

   -------------------------
   -- Time_Of_Last_Update --
   -------------------------

   function Time_Of_Last_Update
     (Compilation_Unit : in Asis.Compilation_Unit)
      return Ada.Calendar.Time
   is
   begin
      return Nil_ASIS_Time;
   end Time_Of_Last_Update;

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
