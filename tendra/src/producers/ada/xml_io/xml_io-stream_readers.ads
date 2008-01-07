with XML_IO.Decoders;
with XML_IO.Decoders.Streams;
with XML_IO.Base_Readers_Streams;

package XML_IO.Stream_Readers is
   new XML_IO.Base_Readers_Streams (Decoders.Implementation,
                                    Decoders.Streams.Stream,
                                    Decoders.Streams.Read);
