------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $

generic
   type Float_Type is digits <>;

package Ada.Numerics.Generic_Elementary_Functions is
   pragma Pure (Generic_Elementary_Functions);

   function Sqrt
     (X           : Float_Type'Base) return Float_Type'Base;
   function Log
     (X           : Float_Type'Base) return Float_Type'Base;
   function Log
     (X, Base     : Float_Type'Base) return Float_Type'Base;
   function Exp
     (X           : Float_Type'Base) return Float_Type'Base;
   function "**"    (Left, Right : Float_Type'Base) return Float_Type'Base;

   function Sin
     (X           : Float_Type'Base) return Float_Type'Base;
   function Sin
     (X, Cycle    : Float_Type'Base) return Float_Type'Base;
   function Cos
     (X           : Float_Type'Base) return Float_Type'Base;
   function Cos
     (X, Cycle    : Float_Type'Base) return Float_Type'Base;
   function Tan
     (X           : Float_Type'Base) return Float_Type'Base;
   function Tan
     (X, Cycle    : Float_Type'Base) return Float_Type'Base;
   function Cot
     (X           : Float_Type'Base) return Float_Type'Base;
   function Cot
     (X, Cycle    : Float_Type'Base) return Float_Type'Base;

   function Arcsin
     (X           : Float_Type'Base) return Float_Type'Base;
   function Arcsin
     (X, Cycle    : Float_Type'Base) return Float_Type'Base;
   function Arccos
     (X           : Float_Type'Base) return Float_Type'Base;
   function Arccos
     (X, Cycle    : Float_Type'Base) return Float_Type'Base;
   function Arctan  (Y           : Float_Type'Base;
                     X           : Float_Type'Base := 1.0)
                    return Float_Type'Base;
   function Arctan  (Y           : Float_Type'Base;
                     X           : Float_Type'Base := 1.0;
                     Cycle       : Float_Type'Base) return Float_Type'Base;
   function Arccot  (X           : Float_Type'Base;
                     Y           : Float_Type'Base := 1.0)
                    return Float_Type'Base;
   function Arccot  (X           : Float_Type'Base;
                     Y           : Float_Type'Base := 1.0;
                     Cycle       : Float_Type'Base) return Float_Type'Base;

   function Sinh
     (X           : Float_Type'Base) return Float_Type'Base;
   function Cosh
     (X           : Float_Type'Base) return Float_Type'Base;
   function Tanh
     (X           : Float_Type'Base) return Float_Type'Base;
   function Coth
     (X           : Float_Type'Base) return Float_Type'Base;
   function Arcsinh
     (X           : Float_Type'Base) return Float_Type'Base;
   function Arccosh
     (X           : Float_Type'Base) return Float_Type'Base;
   function Arctanh
     (X           : Float_Type'Base) return Float_Type'Base;
   function Arccoth
     (X           : Float_Type'Base) return Float_Type'Base;

end Ada.Numerics.Generic_Elementary_Functions;


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
