# TEMA 2 - Mosteniri

## Clase
Se cere implementarea claselor:
* Persoana:
	* id
	* nume
	* cnp
* Abonat - derivat din Persoana:
	* numar de telefon
    * abonament
* Abonament:
	* nume abonament
	* pret
	* perioada (in luni)
* Abonament premium - derivat din abonament:
	* discount
* Clienti
  * constine un vector de abonati
___
## Implementarea cloaselor
Clasele sunt implementate cu get-eri pt atribute si set-eiri care aplica anumite restriciti, supra incarcare pe oeratorii "<<", ">>" si "=".

## Apliactia
Aplicatia pune la dispozitie operatorului un set de optiuni:
1. Introducere abonat nou.
1. Afisare abonati inregistrati.
1. Afisare numarului de abonati premium
1. Modificarea unui abonat(id, nume, tel, cnp, abonament).
   * Nume
   * CNP
   * Numar de telefon
   * abonament
1. Totalul platit de abonati.
___
Utilizatorul poate adauga mai multi abonati, ale caror date le poate modifica.  
Poate sa afle cat platesca sau au platit abonatii(depinde cum interpreteaza optiunea 5) si poate sa vada cati dintre abonati au un abonament premium.
