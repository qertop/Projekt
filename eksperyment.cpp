#include <iostream>
#include <vector>
#include <set>

using namespace std;
vector<vector<int>> wyniki;

vector<int> powtorki(vector<int>liczby){
for(int i=0;i<liczby.size()-1;i++){
    for(int j=liczby.size()-1;j>i;j--){
        if(liczby[i]==liczby[j])swap(liczby[i+1],liczby[j]);
    }
}
return liczby;
}

int suma(const vector<int>& wektor) { //przyjmuje referencjê do wektora wektor, zamiast kopiowac dane/const aby nie zmienic wartosci
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

void generator(const vector<int> liczby,int rozmiar,vector <int> aktualny, int indeks)
{
    //vector<int>tester; //WIELE DO ZMIANY
    if(aktualny.size()>rozmiar)return;
    if(aktualny.size()==rozmiar){
            //tester=aktualny;
           /*
        for(int liczba : aktualny){
            //cout<<liczba<<" ";
            tester.push_back(liczba);
        }
    */
        if(suma(aktualny)*2>suma(liczby)){//for(int a : tester)cout<<a<<",";
        wyniki.push_back(aktualny);
        //cout<<endl;
        }
        //return
    }
    for(int i=indeks;i<liczby.size();++i){
        aktualny.push_back(liczby[i]);
        generator(liczby,rozmiar,aktualny,i+1);
        aktualny.pop_back();
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
cout<<rozmiarPod<<"<--";
//!ZNALEZIONO ROZMIAR NAJMNIESZEGO PODZIORU
//teraz generujemy mozliwe podzbiory, a te ktore spelniaja warunek dodajemy do wyniki
vector<int> aktualny;
generator(liczby,rozmiarPod,aktualny,0);
set<vector<int>> unikalneWyniki(wyniki.begin(), wyniki.end()); //wywolanie set przyjmuje jedynie unikalne rekordy przez co znikaja powtorzenia
wyniki.assign(unikalneWyniki.begin(), unikalneWyniki.end());
for(int i=0;i<wyniki.size();i++)wypisz(wyniki[i]);
}

int main() {
    vector<int> wejscie = {63,3,3,3,1,2,3,4,6,4,76,8,5,76,3,3,5,7,6,33,63,9,9,100,55,23};
    cout<<suma(wejscie)<<endl;
    cout<<"Rozmiar najmniejszego ";
    //wejscie=powtorki(wejscie);
    wypisz(wejscie);
    RozmiarNajmniejszyDominujacyPodzbior(powtorki(wejscie),suma(wejscie),wejscie.size());
    //vector<vector<int>> wyniki = najmniejszyDominujacyPodzbior(wejscie,suma(wejscie));
//if(wyniki.empty())cout<<"Brak";

    return 0;
}
