#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <fstream>

using namespace std;

string mieszanie(string s);
void menu();
void ramka();
void gra(int w);
int poziomTrudnosci();
void odgadywanie(string sw, int p);
void bazaMenu();
void zapisSlowaDoBazy();
void odczytBazy();

int main(){
	
	int nr;

	do{
		menu();
		cout << "Wybor: ";
		cin >> nr;
		ramka();
		
		switch(nr){
			case 1:
				gra(2); break;
			case 2:
				gra(1);	break;
			case 3:
				bazaMenu(); break;
		}
	}while(nr != 0);
	
	system("pause");
	return 0;
}

// fcja przestawiajaca litery w slowie
string mieszanie(string slowo){ 
	string slowoZmieszane;
	int pozycja = 0;
	
	while(slowo.size()){
		pozycja = rand() % slowo.size();
		slowoZmieszane += slowo[pozycja];
		slowo.erase(pozycja, 1);
	}
	
	cout <<"\n\nZaszyfrowane slowo: " << slowoZmieszane;
	return slowoZmieszane;
	
}

// wyswietlane menu poczatkowe
void menu(){
	ramka();
	cout << "ODGADYWANIE ZASZYFROWANEGO SLOWA\n";
	cout << "Wybierz:\n";
	cout << "\t1. Gra dla dwoch graczy\n";
	cout << "\t2. Gra dla jednego gracza\n";
	cout << "\t3. Baza slow\n";
	cout << "\t0. Wylacz gre\n";
	ramka();
}

// wyswietlania ramki
void ramka(){
	cout << "================================\n";
}

// fcja wypisujaca zaszyfrwane slowo, nastepnie przez inna funkcje sprawdza czy slowo odgadnieto poprawnie - docelowa gra
void gra(int wariant){
	int poziom = poziomTrudnosci();
	srand (time(0));
	
	string slowoWpisane, slowoZaszyfrowane;
	
	if(wariant == 2){
		cout << "\n\tGRACZ ZADAJACY:\n" << "Wpisz slowo do zaszyfrowania: ";
		cin >> slowoWpisane;
	}
	else if(wariant == 1){
		cout << "\n\tKOMPUTER:\n";
	}
	
	slowoZaszyfrowane = mieszanie(slowoWpisane);
	
	cout << "\n\n\tGRACZ ODPOWIADAJCY:\n" << "Odgadnij zaszyfrowane slowo: ";
	
	odgadywanie(slowoWpisane, poziom);
}

// wybor poziomu trudnosci gry - liczba mozliwych zlych odpowiedzi
// warto dodac jeszcze liczbe slow do odgadniecia
int poziomTrudnosci(){
	int wybor;
	cout << "WYBIERZ POZIOM TRUDNOSCI\n";
	cout << "\t1. latwy  - 5 szans\n";
	cout << "\t2. sredni - 3 szanse\n";
	cout << "\t3. trudny - 1 szansa\n";
	cout << "Wybor: ";
	cin >> wybor;
	
	switch(wybor){
		case 1: 
			wybor = 5;
			break;
		case 2:
			wybor = 3;
			break;
		case 3:
			wybor = 1;
			break;
	};
	
	ramka();
	return wybor;
}

// funckja sprawdzajaca czy slowo wpisane przez gracza jest takie samo jak zadane i zwracajaca wynik
void odgadywanie(string slowoWpisane, int poziom){
	string slowoOdgadywane;
	
	for (int i = poziom; i>0; i--){
		cin >> slowoOdgadywane;
		
		if(slowoOdgadywane == slowoWpisane){
			cout << "\nDOBRZE!\n Udalo Ci sie za" << poziom - i + 1 << "razem\n\n";
			break;
		}
		else{
			cout << "\nNIEPOPRAWNIE!\n";
			if(i>1) cout << "Odgadnij jeszcze raz (pozostalo szans: " << i << "): ";
			else if(i==1) cout << "Odgadnij jeszcz raz (ostatnia szansa): ";
		}
	}
	
	if(slowoOdgadywane != slowoWpisane) cout << "PRZEGRALES\n";
}

// wyswietlanie i wybor opcji w menu bazy slow
void bazaMenu(){
	ramka();
	int nr;
	do{
		cout << "\t1. Sprawdz slowa w bazie\n";
		cout << "\t2. Sprawdz slowa w bazie - alfabetycznie\n";
		cout << "\t3. Sprawdz slowa w bazie - w zaleznosci od dlugosci\n";
		cout << "\t4. Dodaj slowo do bazy\n";
		cout << "\t0. Wroc do poprzedniego okna\n";
		cout << "Wybor: ";
		cin >> nr;
		
		switch(nr){
			case 1: 
				odczytBazy();		break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				zapisSlowaDoBazy(); break;
			case 0:
				break;
		};
	}while(nr!=0);
}

void zapisSlowaDoBazy(){// zapis slowa do bazy z warunkiem niewystepowania wczesniej
	
	string slowo;
	bool czyBylo=false; char c; int i=0;

	cout << "Podaj nowe slowo: "; cin >> slowo;
	
	while(slowo[i]) {
		c = slowo[i];
		slowo[i] = toupper(c);
		i++;
	}

	{// sprawdzanie czy slowo juz wystepuje w bazie
		fstream plik;
		plik.open("bazaslow.txt", ios::in);
		
		if(!plik.good()){
		cout << "Plik nie istnieje!";
		exit(0);
		}
		
		string slowoLinia;
		
		while(getline(plik, slowoLinia)){
			
			if(slowo == slowoLinia){
				cout << "Takie slowo juz istnieje w bazie!\n";	
				czyBylo = true;
				break;
			} 	
		}
		plik.close();
	}
	
	{// faktyczny zapis slowa do bazy
		fstream plik;
		plik.open("bazaslow.txt", ios::out | ios::app);
		if (czyBylo==false){
				plik << slowo << endl;
				cout << "Dodano do bazy\n";
			}
			
		plik.close();
	}
	
}

// odczyt slow z bazy i wyswietlenie w konsoli
void odczytBazy(){
	
	fstream plik;
	plik.open("bazaslow.txt", ios::in);
	
	if(!plik.good()){
		cout << "Plik nie istnieje!";
		exit(0);
	}
	
	string slowoLinia;
	ramka();
	cout << endl;
	
	while(getline(plik, slowoLinia)){
		cout << "\t" <<  slowoLinia << "\n";
	}
	
	cout << endl;
	ramka();		
	plik.close();
}

