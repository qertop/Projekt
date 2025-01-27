#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;
vector<vector<int>> wyniki; //globalna zmienne przechowywujaca wyniki

vector<int> powtorki(vector<int>liczby){ //funckja zmieniajaca pozycje tych samych liczb (przydatne do set)
for(int i=0;i<liczby.size()-1;i++){
    for(int j=liczby.size()-1;j>i;j--){
        if(liczby[i]==liczby[j])swap(liczby[i+1],liczby[j]);
    }
}
return liczby;
}

int suma(const vector<int> wektor) {
    int sumaCalkowita = 0;
    for (int liczba : wektor) { //petla range for, liczba w kolejnych iteracjach przyjmuje kolejne wartosci w wektorze wektor
        sumaCalkowita += liczba;
    }
    return sumaCalkowita;
}

void wypisz(vector<int>podzbior)
{
    cout<<"[";
 for (int i = 0; i < podzbior.size(); i++) {
                cout << podzbior[i];
                if (i < podzbior.size() - 1) cout << ", ";
            }
    cout<<"]"<<endl;
}

void generator(const vector<int> liczby,int rozmiar,vector <int> aktualny, int indeks,int sumaliczby)
{
    if(aktualny.size()>rozmiar)return; //warunek przerwania
    if(aktualny.size()==rozmiar){ //analizujemy jedynie podzbiory o danym rozmiarze
        if(suma(aktualny)*2>sumaliczby){
        wyniki.push_back(aktualny);
        }
    }
    for(int i=indeks;i<liczby.size();++i){ //indeks przesuwa rekurencje na dalsze elementy zbioru liczby
        aktualny.push_back(liczby[i]); //dodajemy okreslona liczbe
        generator(liczby,rozmiar,aktualny,i+1,sumaliczby); //rekurencyjnie tworzy drzewo kombinacji
        aktualny.pop_back(); //usuwa najmlodszy element
    }
}

void RozmiarNajmniejszyDominujacyPodzbior(const vector<int>liczby, int SumaDoPrzebicia, int rozmiarDoPrzebicia) {
int najw=0;
int rozmiarPod=0;
int sumaPodzbioru=0;
int pozNajw=0;
vector <int>pozostale=liczby;
for(int a=0;a<liczby.size();a++){
    najw=0;
    for (int j = 0; j < pozostale.size(); j++) {
        if(najw<pozostale[j]){najw=pozostale[j];pozNajw=j;}
    }
    if(2*sumaPodzbioru<=SumaDoPrzebicia){
        sumaPodzbioru+=najw;rozmiarPod++;rozmiarDoPrzebicia--;
        pozostale.erase(pozostale.begin()+pozNajw);
    }
    if(rozmiarDoPrzebicia<rozmiarPod){
        cout<<"Brak";rozmiarPod=0;break;
    }
    if(2*sumaPodzbioru>SumaDoPrzebicia){
        break;
    }
}
cout<<rozmiarPod<<"<--"<<endl;
//!ZNALEZIONO ROZMIAR NAJMNIESZEGO PODZIORU
//teraz generujemy mozliwe podzbiory, a te ktore spelniaja warunek dodajemy do wyniki
vector<int> aktualny;
generator(liczby,rozmiarPod,aktualny,0,suma(liczby));
//segment usuwania powtorek
set<vector<int>> unikalneWyniki(wyniki.begin(), wyniki.end()); //wywolanie set przyjmuje jedynie unikalne rekordy przez co znikaja powtorzenia
wyniki.assign(unikalneWyniki.begin(), unikalneWyniki.end()); //przywróceie wyniki do postaci wektora
//for(int i=0;i<wyniki.size();i++)wypisz(wyniki[i]); //wypisanie wyników
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
                for (int i = 0; i < liczby.size(); ++i) {
                    cout << liczby[i];
                    if (i < liczby.size() - 1)cout << ", ";
                }
            cout << "]\n";
            auto begin = std::chrono::high_resolution_clock::now();
            RozmiarNajmniejszyDominujacyPodzbior(powtorki(liczby),suma(liczby),liczby.size());
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            printf("Zmierzony czas: %.10f seconds.\n", elapsed.count() * 1e-9);
            wyniki.clear();
            cout<<endl;
        }
    }

    return true;
}
int main() {
    wczytajPlik();
    return 0;
}
