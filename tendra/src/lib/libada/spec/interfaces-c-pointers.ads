------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

generic
   type Index is (<>);
   type Element is private;
   type Element_Array is array (Index range <>) of aliased Element;
   Default_Terminator : Element;
package Interfaces.C.Pointers is
   pragma Preelaborate (Pointers);

   type Pointer is access all Element;

   function Value (Ref        : in Pointer;
                   Terminator : in Element := Default_Terminator)
                  return Element_Array;

   function Value (Ref    : in Pointer;
                   Length : in ptrdiff_t)
                  return Element_Array;

   Pointer_Error : exception;

   -- C-style Pointer arithmetic

   function "+" (Left : in Pointer;   Right : in ptrdiff_t) return Pointer;
   function "+" (Left : in ptrdiff_t; Right : in Pointer)   return Pointer;
   function "-" (Left : in Pointer;   Right : in ptrdiff_t) return Pointer;
   function "-" (Left : in Pointer;   Right : in Pointer) return ptrdiff_t;

   procedure Increment (Ref : in out Pointer);
   procedure Decrement (Ref : in out Pointer);

   pragma Convention (Intrinsic, "+");
   pragma Convention (Intrinsic, "-");
   pragma Convention (Intrinsic, Increment);
   pragma Convention (Intrinsic, Decrement);

   function Virtual_Length (Ref        : in Pointer;
                            Terminator : in Element := Default_Terminator)
                           return ptrdiff_t;

   procedure Copy_Terminated_Array
     (Source     : in Pointer;
      Target     : in Pointer;
      Limit      : in ptrdiff_t := ptrdiff_t'Last;
      Terminator : in Element :=  Default_Terminator);

   procedure Copy_Array (Source  : in Pointer;
                         Target  : in Pointer;
                         Length  : in ptrdiff_t);

end Interfaces.C.Pointers;



