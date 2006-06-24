package Text_Streams is

   -----------------
   -- Text_Stream --
   -----------------

   type Text_Stream is abstract tagged limited null record;

   procedure Read
     (Object : in out Text_Stream;
      Text   :    out String;
      Last   :    out Natural) is abstract;

end Text_Streams;
