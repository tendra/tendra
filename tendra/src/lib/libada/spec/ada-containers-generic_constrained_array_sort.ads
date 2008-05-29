------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

generic
   type Index_Type is (<>);
   type Element_Type is private;
   type Array_Type is array (Index_Type) of Element_Type;

   with function "<" (Left  : in Element_Type;
                      Right : in Element_Type)
          return Boolean is <>;

procedure Ada.Containers.Generic_Constrained_Array_Sort
 (Container : in out Array_Type);
pragma Pure (Ada.Containers.Generic_Constrained_Array_Sort);
