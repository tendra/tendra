------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $

with Ada.Numerics.Generic_Complex_Types;
pragma Elaborate_All(Ada.Numerics.Generic_Complex_Types);

package Interfaces.Fortran is
   pragma Pure(Fortran);

   type Fortran_Integer  is 
     range implementation-defined .. implementation-defined;
   type Real             is digits implementation-defined;
   type Double_Precision is digits implementation-defined;

   type Logical is new Boolean;

   package Single_Precision_Complex_Types is
      new Ada.Numerics.Generic_Complex_Types (Real);

   type Complex is new Single_Precision_Complex_Types.Complex;

   subtype Imaginary is Single_Precision_Complex_Types.Imaginary;
   i : Imaginary renames Single_Precision_Complex_Types.i;
   j : Imaginary renames Single_Precision_Complex_Types.j;

   type Character_Set is new Character; --  implementation-defined;

   type Fortran_Character is array (Positive range <>) of Character_Set;
   pragma Pack (Fortran_Character);

   function To_Fortran (Item : in Character) return Character_Set;
   function To_Ada (Item : in Character_Set) return Character;

   function To_Fortran (Item : in String) return Fortran_Character;
   function To_Ada     (Item : in Fortran_Character) return String;

   procedure To_Fortran (Item       : in String;
                         Target     : out Fortran_Character;
                         Last       : out Natural);

   procedure To_Ada (Item     : in Fortran_Character;
                     Target   : out String;
                     Last     : out Natural);

end Interfaces.Fortran;


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
