#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;
vector<int> powtorki(vector<int>liczby){ //funckja zmieniajaca pozycje tych samych liczb (przydatne do set)
for(int i=0;i<liczby.size()-1;i++){
    for(int j=liczby.size()-1;j>i;j--){
        if(liczby[i]==liczby[j])swap(liczby[i+1],liczby[j]);
    }
}
return liczby;
}
// Funkcja pomocnicza do obliczenia sumy elementow wektora
int suma(const vector<int>& wektor) { //const aby nie zmienic wartosci
    int sumaCalkowita = 0;
    for (int liczba : wektor) { //petla range for, liczba
    //w kolejnych iteracjach przyjmuje kolejne wartosci
    //w wektorze wektor
        sumaCalkowita += liczba;
    }
    return sumaCalkowita;
}

// Funkcja generujaca wszystkie podzbiory i sprawdzajaca warunek
void znajdzPodzbiory(vector<int> liczby) {
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
        cout << " spelniajacych zadane kryteria." << endl;
    }
    else {
        int minimalnyRozmiar=poprawnePodzbiory[0].size();
        for(int i=0;i<poprawnePodzbiory.size();i++){
        if(poprawnePodzbiory[i].size()<minimalnyRozmiar){
        minimalnyRozmiar=poprawnePodzbiory[i].size();}}
        set<vector<int>> unikalneWyniki(poprawnePodzbiory.begin(), poprawnePodzbiory.end()); //wywolanie set przyjmuje jedynie unikalne rekordy przez co znikaja powtorzenia
        poprawnePodzbiory.assign(unikalneWyniki.begin(), unikalneWyniki.end()); //przywróceie poprawneWyniki do postaci wektora
        for (const auto podzbior : poprawnePodzbiory) {
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
    ifstream plik("danepomiarowe.txt");
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



                cout << "[";
                for (size_t i = 0; i < liczby.size(); ++i) {
                    cout << liczby[i];
                    if (i < liczby.size() - 1)cout << ", ";
                }
            cout << "]\n";
            auto begin = std::chrono::high_resolution_clock::now();
            znajdzPodzbiory(powtorki(liczby));
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            printf("Zmierzony czas: %.10f seconds.\n", elapsed.count() * 1e-9);
            cout<<endl;
        }
    }

    return true;
}

/////////////////////////////




int main() {
    wczytajPlik();
    return 0;
}
