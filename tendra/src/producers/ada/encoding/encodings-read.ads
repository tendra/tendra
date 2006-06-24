with Encodings.Maps;

package Encodings.Read is

   type Mapping
     (Start        : Character;
      Ranges_Count : Maps.Range_Count;
      Char_Count   : Maps.Backward_Index)
   is
      record
         Forward  : Maps.Forward_Map  (Start .. Character'Last);
         Ranges   : Maps.Wide_Ranges  (1 .. Ranges_Count);
         Backward : Maps.Backward_Map (1 .. Char_Count);
      end record;

   function Table (File_Name : String) return Mapping;

end Encodings.Read;
