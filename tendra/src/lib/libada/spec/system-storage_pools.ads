------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Finalization;
with System.Storage_Elements;

package System.Storage_Pools is
   pragma Preelaborate (System.Storage_Pools);

   type Root_Storage_Pool is
     abstract new Ada.Finalization.Limited_Controlled with private;
   pragma Preelaborable_Initialization (Root_Storage_Pool);

   procedure Allocate
     (Pool                     : in out Root_Storage_Pool;
      Storage_Address          :    out Address;
      Size_In_Storage_Elements : in     Storage_Elements.Storage_Count;
      Alignment                : in     Storage_Elements.Storage_Count)
      is abstract;

   procedure Deallocate
     (Pool                     : in out Root_Storage_Pool;
      Storage_Address          : in     Address;
      Size_In_Storage_Elements : in     Storage_Elements.Storage_Count;
      Alignment                : in     Storage_Elements.Storage_Count)
      is abstract;

   function Storage_Size
     (Pool : Root_Storage_Pool)
     return Storage_Elements.Storage_Count
      is abstract;

private

   pragma Import (Ada, Root_Storage_Pool);

end System.Storage_Pools;



