with Text_Streams;

package XML_IO.Decoders.Streams is

   type Stream (Input : access Text_Streams.Text_Stream'Class) is
     limited private;

   procedure Read
     (Input  : in out Stream;
      Buffer : in out String;
      Last   :    out Natural);

private

   type Stream (Input : access Text_Streams.Text_Stream'Class) is
     limited null record;

end XML_IO.Decoders.Streams;
