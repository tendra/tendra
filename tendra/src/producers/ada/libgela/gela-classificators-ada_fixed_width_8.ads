with Gela.Scanner_Tables;
with Gela.Classificators.Fixed_Width_8;

package Gela.Classificators.Ada_Fixed_Width_8 is new
  Gela.Classificators.Fixed_Width_8 (To_Character_Class => Gela.Scanner_Tables.Get_Class);
