#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Funkcja pomocnicza do obliczenia sumy elementów wektora
int suma(const vector<int>& wektor) { //przyjmuje referencję do wektora wektor, zamiast kopiowac dane/const aby nie zmienic wartosci
    int sumaCalkowita = 0;
    for (int liczba : wektor) { //petla range for, liczba w kolejnych iteracjach przyjmuje kolejne wartosci w wektorze wektor
        sumaCalkowita += liczba;
    }
    return sumaCalkowita;
}

//! Funkcja usuwająca powtórzenia z listy podzbiorów !!!FUNKCJA TA WYKORZYSTUJE ALGORYTM SORTUJACY PRZEZ WYBRANIE!!!
void usunPowtorzenia(vector<vector<int>>& podzbiory) {
    for (auto& podzbior : podzbiory) { //auto automatycznie określa typ zmiennej na podstawie jej wartości początkowej
            for (int i = 0; i < podzbior.size()-1; i++) {
                for (int j = 0; j < podzbior.size()-1; j++) {
                    if(podzbior[j+1]<podzbior[j])swap(podzbior[j],podzbior[j+1]);
                }


            }

        }

    set<vector<int>> unikalnePodzbiory(podzbiory.begin(), podzbiory.end()); //wywolanie set przyjmuje jedynie unikalne rekordy przez co znikaja powtorzenia
    podzbiory.assign(unikalnePodzbiory.begin(), unikalnePodzbiory.end()); //przywracamy podzbiory do swojej początkowej formy
}

// Funkcja generująca wszystkie podzbiory i sprawdzająca warunek
void znajdzPodzbiory(vector<int>& liczby) {
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
        for (const auto& podzbior : poprawnePodzbiory) {
            if (podzbior.size() == minimalnyRozmiar){
                cout << "[";
                for (size_t i = 0; i < podzbior.size(); ++i) {
                    cout << podzbior[i];
                    if (i < podzbior.size() - 1)cout << ", ";
                }
            cout << "]\n";
            }
        }
    }
}

int main() {
    vector<int> liczby = {2,1,1,4,7,10,7}; // Przykładowe dane
    znajdzPodzbiory(liczby); //wywolanie funckji

    return 0;
}


