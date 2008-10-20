with Gela.Classificators.Ada_Fixed_Width_8;

function Gela.Classificators.Create
  (Encoding : Encodings.Encoding;
   Decoder  : Decoders.Decoder'Class) return Classificator'Class is
begin
   if Encoding in Encodings.Fixed_Width_Encoding then
      declare
         Result : Classificators.Ada_Fixed_Width_8.Classificator;
      begin
         Classificators.Ada_Fixed_Width_8.Initialize (Result, Decoder);
         return Result;
      end;
   else
      raise Program_Error;
   end if;
end Gela.Classificators.Create;
