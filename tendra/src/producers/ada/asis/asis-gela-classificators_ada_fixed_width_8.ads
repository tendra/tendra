with Asis.Gela.Scanner_Tables;
with Gela.Classificators.Fixed_Width_8;

use Gela;

package Asis.Gela.Classificators_Ada_Fixed_Width_8 is new
  Classificators.Fixed_Width_8 (Scanner_Tables.Get_Class);
