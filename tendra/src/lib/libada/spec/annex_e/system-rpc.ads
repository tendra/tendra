------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Streams; -- see 13.13.1

package System.RPC is

   type Partition_Id is range 0 .. implementation-defined;

   Communication_Error : exception;

   type Params_Stream_Type (Initial_Size : Ada.Streams.Stream_Element_Count) is
     new Ada.Streams.Root_Stream_Type with private;

   procedure Read (Stream : in out Params_Stream_Type;
                   Item   :    out Ada.Streams.Stream_Element_Array;
                   Last   :    out Ada.Streams.Stream_Element_Offset);

   procedure Write (Stream : in out Params_Stream_Type;
                    Item   : in     Ada.Streams.Stream_Element_Array);

   --  Synchronous call

   procedure Do_RPC (Partition : in Partition_Id;
                     Params    : access Params_Stream_Type;
                     Result    : access Params_Stream_Type);

   --  Asynchronous call

   procedure Do_APC (Partition : in Partition_Id;
                     Params    : access Params_Stream_Type);

   --  The handler for incoming RPCs

   type RPC_Receiver is access procedure (Params : access Params_Stream_Type;
                                          Result : access Params_Stream_Type);

   procedure Establish_RPC_Receiver (Partition : in Partition_Id;
                                     Receiver  : in RPC_Receiver);

private

   pragma Import (Ada, Params_Stream_Type);

end System.RPC;
