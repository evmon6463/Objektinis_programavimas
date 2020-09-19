#include <iostream>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;
using std::cin;

struct duomenys {
    string Vardas;
    string Pavarde;
    int nd_rezultatai[10];
    int egzamino_rezultatas;
    float galutinis_rezultatas;
};
int main()
{
    duomenys studentas;
    float suma = 0;
    cout << "Iveskite studento varda, pavarde, namu darbu rezultatus ir egzamino rezultata: " << endl;
    cin >> studentas.Vardas >> studentas.Pavarde;
    for (int i = 0; i < 5; i++) {
        cin >> studentas.nd_rezultatai[i];
        suma = suma + studentas.nd_rezultatai[i];
    }
    float vidurkis = suma / 5;
    cin >> studentas.egzamino_rezultatas;
    studentas.galutinis_rezultatas = vidurkis * (float)0.4 + studentas.egzamino_rezultatas * (float)0.6;
    cout << "Vardas:\t" << "Pavarde:\t"<< "Galutinis rezultatas:\t" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - -"<<endl;
    cout << studentas.Vardas<<"\t"<<studentas.Pavarde <<"\t\t"<<std::setprecision (2) << std::fixed<< studentas.galutinis_rezultatas<<"\t"<<endl;
}
