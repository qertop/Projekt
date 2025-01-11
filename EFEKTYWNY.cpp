#include <iostream>
#include <vector>
#include <set>

using namespace std;

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

vector<vector<int>> najmniejszyDominujacyPodzbior(vector<int>& liczby) {
    vector<int>podzbior;
    vector<int>pozostale=liczby;
vector<vector<int>>wyniki;
int najw=0;
int pozNajw=0;
int rozmiarPod=0;
int ostatnia=-1;
int najmRozmiarPod=-1;
int najWsumaPod=0;
for(int a=0;a<liczby.size()*0.5;a++){
    pozNajw=0;
    najw=0;
    for (int j = 0; j < pozostale.size(); j++) {
        if(najw<pozostale[j]){najw=pozostale[j];pozNajw=j;}
    }
    if(rozmiarPod<najmRozmiarPod||wyniki.empty()){
        podzbior.push_back(najw);rozmiarPod++;
        pozostale.erase(pozostale.begin()+pozNajw);
    }
    if(suma(podzbior)>suma(pozostale)){
        najmRozmiarPod=rozmiarPod;
        wyniki.push_back(podzbior);
    }

}

    return vector<vector<int>>(wyniki.begin(), wyniki.end()); // Przekszta³camy set na vector
}

int main() {
    vector<int> wejscie = {5,4,3,1};
    vector<vector<int>> wyniki = najmniejszyDominujacyPodzbior(wejscie);
if(wyniki.empty())cout<<"Brak";
else for(int i=0;i<wyniki.size();i++)wypisz(wyniki[i]);
    return 0;
}
