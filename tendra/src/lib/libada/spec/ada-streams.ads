------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Streams is
   pragma Pure (Streams);

   type Root_Stream_Type is abstract tagged limited private;
   pragma Preelaborable_Initialization (Root_Stream_Type);

   type Stream_Element is mod implementation-defined;
   type Stream_Element_Offset is range
     implementation-defined .. implementation-defined;

   subtype Stream_Element_Count is
     Stream_Element_Offset range 0..Stream_Element_Offset'Last;

   type Stream_Element_Array is
     array (Stream_Element_Offset range <>) of aliased Stream_Element;

   procedure Read (Stream : in out Root_Stream_Type;
                   Item   : out Stream_Element_Array;
                   Last   : out Stream_Element_Offset) is abstract;

   procedure Write (Stream : in out Root_Stream_Type;
                    Item   : in Stream_Element_Array) is abstract;

private

   pragma Import (Ada, Root_Stream_Type);

end Ada.Streams;



