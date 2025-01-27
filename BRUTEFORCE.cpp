#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Funkcja pomocnicza do obliczenia sumy elementów wektora
int suma(const vector<int> wektor) { //const aby nie zmienic wartosci
    int sumaCalkowita = 0;
    for (int liczba : wektor) { //petla range for, liczba w kolejnych iteracjach przyjmuje kolejne wartosci w wektorze wektor
        sumaCalkowita += liczba;
    }
    return sumaCalkowita;
}
vector<int> powtorki(vector<int>liczby){ //funckja zmieniajaca pozycje tych samych liczb (przydatne do set)
for(int i=0;i<liczby.size()-1;i++){
    for(int j=liczby.size()-1;j>i;j--){
        if(liczby[i]==liczby[j])swap(liczby[i+1],liczby[j]);
    }
}
return liczby;
}
// Funkcja generująca wszystkie podzbiory i sprawdzająca warunek
void znajdzPodzbiory(vector<int> liczby) {
    int n = liczby.size();
    int sumaCalkowita = suma(liczby);
    vector<vector<int>> poprawnePodzbiory; //wektor wektorow (w pewnym sensie tablica liczb) przechowujacy podzbiory spelniajace warunki

    // Iterujemy po wszystkich podzbiorach (2^n możliwości)
    for (int maska = 0; maska < (1 << n); ++maska) {
        vector<int> podzbior;
        for (int i = 0; i < n; ++i) {
            if (maska & (1 << i)) {
                podzbior.push_back(liczby[i]);
            }
        }
        // Sprawdzamy czy suma podzbioru spełnia warunek
        int sumaPodzbioru = suma(podzbior);
        int sumaPozostalych = sumaCalkowita - sumaPodzbioru;
        if ((sumaPodzbioru > sumaPozostalych)&&(podzbior.size()<=liczby.size()-podzbior.size())) {//!PYTANIE!Warunek posiada takze zabezpieczenie przed podzbiorami ktore sa wieksze niz podzbior pozostalych liczb
            poprawnePodzbiory.push_back(podzbior);
        }
    }

    // Usuwamy powtórzenia
    //usunPowtorzenia(poprawnePodzbiory);

    // Wypisujemy wyniki
    if (poprawnePodzbiory.empty()) {
        cout << "Brak podzbiorów spełniających zadane kryteria." << endl;
    }
    else {
        int minimalnyRozmiar=poprawnePodzbiory[0].size();
        for(int i=0;i<poprawnePodzbiory.size();i++)if(poprawnePodzbiory[i].size()<minimalnyRozmiar)minimalnyRozmiar=poprawnePodzbiory[i].size();
        set<vector<int>> unikalneWyniki(poprawnePodzbiory.begin(), poprawnePodzbiory.end()); //wywolanie set przyjmuje jedynie unikalne rekordy przez co znikaja powtorzenia
        poprawnePodzbiory.assign(unikalneWyniki.begin(), unikalneWyniki.end()); //przywróceie poprawneWyniki do postaci wektora
        for (vector <int> podzbior : poprawnePodzbiory) {
            if (podzbior.size() == minimalnyRozmiar){
                cout << "[";
                for (int i = 0; i < podzbior.size(); ++i) {
                    cout << podzbior[i];
                    if (i < podzbior.size() - 1)cout << ", ";
                }
            cout << "]\n";
            }
        }
    }
}

int main() {
    vector<int> liczby = {2,1,3,9,3}; // Przykładowe dane
    znajdzPodzbiory(powtorki(liczby)); //wywolanie funckji

    return 0;
}


