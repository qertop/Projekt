#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
using namespace std;

// Funkcja pomocnicza do obliczenia sumy elementow wektora
int suma(const vector<int>& wektor) { //przyjmuje referencje
//do wektora wektor, zamiast kopiowac dane
//const aby nie zmienic wartosci
    int sumaCalkowita = 0;
    for (int liczba : wektor) { //petla range for, liczba
    //w kolejnych iteracjach przyjmuje kolejne wartosci
    //w wektorze wektor
        sumaCalkowita += liczba;
    }
    return sumaCalkowita;
}

// Funkcja generujaca wszystkie podzbiory i sprawdzajaca warunek
void znajdzPodzbiory(vector<int>& liczby) {
    int n = liczby.size();
    int sumaCalkowita = suma(liczby);
    vector<vector<int>> poprawnePodzbiory; //wektor wektorow
    //(w pewnym sensie tablica liczb) przechowujacy podzbiory
    //spelniajace warunki

    // Iterujemy po wszystkich podzbiorach (2^n mozliwosci)
    for (int maska = 0; maska < (1 << n); ++maska) {
        vector<int> podzbior;
        for (int i = 0; i < n; ++i) {
            if (maska & (1 << i)) {
                podzbior.push_back(liczby[i]);
            }
        }
        // Sprawdzamy czy suma podzbioru spelnia warunek
        int sumaPodzbioru = suma(podzbior);
        int sumaPozostalych = sumaCalkowita - sumaPodzbioru;
        if ((sumaPodzbioru > sumaPozostalych)&&
        (podzbior.size()<liczby.size()-podzbior.size())) {
            poprawnePodzbiory.push_back(podzbior);
        }
    }



    // Wypisujemy wyniki
    if (poprawnePodzbiory.empty()) {
        cout << "Brak podzbiorow";
        cout << "spelniajacych zadane kryteria." << endl;
    }
    else {
        int minimalnyRozmiar=poprawnePodzbiory[0].size();
        for(int i=0;i<poprawnePodzbiory.size();i++){
        if(poprawnePodzbiory[i].size()<minimalnyRozmiar){
        minimalnyRozmiar=poprawnePodzbiory[i].size();}}
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

/////////////////////////////
bool wczytajPlik()
{
    ifstream plik("liczby.txt");
    if (!plik.is_open())
        return false;

    string linia;
    while (getline(plik, linia)) // Wczytaj linia po linii
    {
        vector<int> liczby;
        stringstream ss(linia); // Zamieñ liniê na strumieñ do wczytywania liczb
        int liczba;

        while (ss >> liczba) // Wczytuj liczby z bie¿¹cej linii
        {
            liczby.push_back(liczba);
        }

        if (!liczby.empty()) // Jeœli znaleziono liczby, przeka¿ je do funkcji
        {
            znajdzPodzbiory(liczby);
            cout<<endl;
        }
    }

    return true;
}

/////////////////////////////




int main() {
    vector<int> liczby = {2,7,3,1}; // Przykladowe dane
    //znajdzPodzbiory(liczby); //wywolanie funckji
    wczytajPlik();
    return 0;
}
