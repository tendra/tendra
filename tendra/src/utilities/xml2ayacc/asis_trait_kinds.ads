package Asis_Trait_Kinds is

   type Trait_Kinds is (

     Not_A_Trait,                         --  An unexpected element

     An_Ordinary_Trait,                --  The declaration or definition does
                                       --  not contain the reserved words
                                       --  "aliased", "reverse", "private",
                                       --  "limited", "abstract", or
                                       --  "access" in an access_definition

     An_Aliased_Trait,                    --  "aliased" is present
     An_Access_Definition_Trait,          --  "access" in an access_definition
                                          --  is present
     A_Reverse_Trait,                     --  "reverse" is present
     A_Private_Trait,                     --  Only "private" is present
     A_Limited_Trait,                     --  Only "limited" is present
     A_Limited_Private_Trait,             --  "limited" and "private" are
                                          --  present


     An_Abstract_Trait,                   --  Only "abstract" is present
     An_Abstract_Private_Trait,           --  "abstract" and "private" are
                                          --  present
     An_Abstract_Limited_Trait,           --  "abstract" and "limited" are
                                          --  present
     An_Abstract_Limited_Private_Trait);  --  "abstract", "limited", and
                                          --  "private" are present

end Asis_Trait_Kinds;


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
