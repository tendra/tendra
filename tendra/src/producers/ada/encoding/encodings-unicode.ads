package Encodings.Unicode is

   type Unicode_Character is mod 16#11_0000#;

   Empty_Buffer : constant Unicode_Character := Unicode_Character'Last;

   procedure Decode
     (Buffer : in     String;
      Index  : in out Positive;
      Free   : in     Positive;
      Map    : in     Encoding;
      Char   :    out Unicode_Character);

   --  Decode one Unicode character Char from Buffer (Index .. Free - 1)
   --  and advance Index.
   --  If Free < Index use cycle Buffer (get Buffer'First after Buffer'Last).
   --  Return Empty_Buffer if not enough characters in the Buffer.

   pragma Inline (Decode);

end Encodings.Unicode;
