with Asis.Gela.Scanner_Tables;
with Gela.Classificators.UTF_16;

use Gela;
use type Asis.Gela.Scanner_Tables.Character_Class;

package Asis.Gela.Classificators_Ada_UTF_16 is new
  Classificators.UTF_16 (Scanner_Tables.Get_Class,
                         Scanner_Tables.Character_Class'Last - 1);
