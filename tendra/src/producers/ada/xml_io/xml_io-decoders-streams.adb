package body XML_IO.Decoders.Streams is

   ----------
   -- Read --
   ----------

   procedure Read
     (Input  : in out Stream;
      Buffer : in out String;
      Last   :    out Natural) is
   begin
      Text_Streams.Read (Input.Input.all, Buffer, Last);
   end Read;

end XML_IO.Decoders.Streams;
