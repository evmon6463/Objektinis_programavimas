#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::ofstream;

struct duomenys {
    string Vardas;
    string Pavarde;
    int egzamino_rezultatas;
    float galutinis_rezultatas;
    int nd_rezultatai[100];
};

double findMedian(int a[], int n)
{
    std::sort(a, a+n);
    if (n % 2 != 0)
        return (double)a[n/2];
    return (double)(a[(n-1)/2] + a[n/2])/2.0;
}
int main()
{
    duomenys studentas[5];
    int n=0;
    int nd_skaicius=0;
    for (int j=0; j<2; j++) {
        nd_skaicius=0;
        studentas[j].galutinis_rezultatas = 0;
        float vidurkis = 0;
        float suma = 0;
        cout << "Iveskite studento varda, pavarde, namu darbu rezultatus ir egzamino rezultata: " << endl;
        cin >> studentas[j].Vardas >> studentas[j].Pavarde;
        while(nd_skaicius<5) {
            cin >> studentas[j].nd_rezultatai[nd_skaicius];
            suma = suma + studentas[j].nd_rezultatai[nd_skaicius];
            nd_skaicius ++;
        }
        vidurkis = suma / nd_skaicius;
        cin >> studentas[j].egzamino_rezultatas;
        studentas[j].galutinis_rezultatas = vidurkis * (float) 0.4 +
                                            studentas[j].egzamino_rezultatas * (float) 0.6;
    }
    cout << "Vardas:\t" << "Pavarde:\t"<< "Galutinis vidurkis/Galutine mediana:\t" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - -"<<endl;
    for (int g=0; g<2; g++) {
        cout << studentas[g].Vardas << "\t" << studentas[g].Pavarde << "\t"
             << std::setprecision(2) << std::fixed
             << studentas[g].galutinis_rezultatas << "\t\t" << std::setprecision(2) << std::fixed
             << findMedian(studentas[g].nd_rezultatai, nd_skaicius)
             << endl;
    }

    ofstream myfile;
    myfile.open ("example.txt");
    myfile << "Vardas:\t" << "Pavarde:\t"<< "Galutinis rezultatas/Galutine mediana:\t" << endl;
    myfile << "- - - - - - - - - - - - - - - - - - - - - - -"<<endl;
    for (int g=0; g<2; g++)
        myfile << studentas[g].Vardas << "\t" << studentas[g].Pavarde << "\t\t"
                << std::setprecision(2) << std::fixed
               << studentas[g].galutinis_rezultatas << "\t\t" << std::setprecision(2) << std::fixed
               << findMedian(studentas[g].nd_rezultatai, nd_skaicius)
               << endl;
    myfile.close();

}