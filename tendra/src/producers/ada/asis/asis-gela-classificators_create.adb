with Asis.Gela.Classificators_Ada_Fixed_Width_8;

function Asis.Gela.Classificators_Create
  (Encoding : Encodings.Encoding;
   Decoder  : Decoders.Decoder'Class) return Classificators.Classificator'Class
is
begin
   if Encoding in Encodings.Fixed_Width_Encoding then
      declare
         Result : Classificators_Ada_Fixed_Width_8.Classificator;
      begin
         Classificators_Ada_Fixed_Width_8.Initialize (Result, Decoder);
         return Result;
      end;
   else
      raise Program_Error;
   end if;
end Asis.Gela.Classificators_Create;
