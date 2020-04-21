# PIZZERIA BIG BAD AZZ

## Pasi:

### Clasa pur abstarcta:
   Clasa pur abstracta este o clasa care contine cel putin o metoda virtula de genul:  
   ```
   virtual type name() = 0;
   ```
### Clasa Produs
* Continut:
  * Avem niste atribute simple: denumire, cantitate, pret unita(il vezi cum vrei)
  * Constructori de initializare si de copoiere.
  * Ceva get-eri si set-eri, pt eventuale nevoi
  * functii de citire si afisare
  * supraincarcare pe <<, >>, =
* Obiectiv:
  * Va fi folosita pt lista de ingrediente necesare producelor
### Clasa Pizza
* Continut:
 * Atibute: denumire, lista de ingrediente, manopera.
 * Constructori cu parametri pentru denumire, lista de ingrediente si manopera. Sau doar denumire si manopera. Lista poate fi adaugata mai tarziu.
 * Constructor de copiere, supraincarcare pe =
 * Set-eri si get-eri pentru atributele clasei.
 * Metode de manipulare a listei de ingrediente:
   * schimbarea intregii liste cu alta deja existenta
   * adaugarea stergerea unui ingredient. Stergerea se poate face dupa index sau dupa denumirea ingredientului.
 * Metode de afisare si de citire.
