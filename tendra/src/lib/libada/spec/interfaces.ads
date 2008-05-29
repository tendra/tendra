------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Interfaces is
   pragma Pure(Interfaces);

   type Integer_8  is range -2**(8-1) .. 2**(8-1) - 1;
   type Unsigned_8 is mod 2**8;

   function Shift_Left  (Value : Unsigned_8; Amount : Natural)
                        return Unsigned_8;
   function Shift_Right (Value : Unsigned_8; Amount : Natural)
                        return Unsigned_8;
   function Shift_Right_Arithmetic (Value : Unsigned_8; Amount : Natural)
                                   return Unsigned_8;
   function Rotate_Left  (Value : Unsigned_8; Amount : Natural)
                         return Unsigned_8;
   function Rotate_Right (Value : Unsigned_8; Amount : Natural)
                         return Unsigned_8;

   type Integer_16  is range -2**(16-1) .. 2**(16-1) - 1;
   type Unsigned_16 is mod 2**16;

   function Shift_Left  (Value : Unsigned_16; Amount : Natural)
                        return Unsigned_16;
   function Shift_Right (Value : Unsigned_16; Amount : Natural)
                        return Unsigned_16;
   function Shift_Right_Arithmetic (Value : Unsigned_16; Amount : Natural)
                                   return Unsigned_16;
   function Rotate_Left  (Value : Unsigned_16; Amount : Natural)
                         return Unsigned_16;
   function Rotate_Right (Value : Unsigned_16; Amount : Natural)
                         return Unsigned_16;

   type Integer_32  is range -2**(32-1) .. 2**(32-1) - 1;
   type Unsigned_32 is mod 2**32;

   function Shift_Left  (Value : Unsigned_32; Amount : Natural)
                        return Unsigned_32;
   function Shift_Right (Value : Unsigned_32; Amount : Natural)
                        return Unsigned_32;
   function Shift_Right_Arithmetic (Value : Unsigned_32; Amount : Natural)
                                   return Unsigned_32;
   function Rotate_Left  (Value : Unsigned_32; Amount : Natural)
                         return Unsigned_32;
   function Rotate_Right (Value : Unsigned_32; Amount : Natural)
                         return Unsigned_32;

   type Integer_64  is range -2**(64-1) .. 2**(64-1) - 1;
   type Unsigned_64 is mod 2**64;

   function Shift_Left  (Value : Unsigned_64; Amount : Natural)
                        return Unsigned_64;
   function Shift_Right (Value : Unsigned_64; Amount : Natural)
                        return Unsigned_64;
   function Shift_Right_Arithmetic (Value : Unsigned_64; Amount : Natural)
                                   return Unsigned_64;
   function Rotate_Left  (Value : Unsigned_64; Amount : Natural)
                         return Unsigned_64;
   function Rotate_Right (Value : Unsigned_64; Amount : Natural)
                         return Unsigned_64;

end Interfaces;



