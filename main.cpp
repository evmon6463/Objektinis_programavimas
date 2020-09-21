#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include<time.h>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::ofstream;

struct studentas {
    string Vardas;
    string Pavarde;
    int egzamino_rezultatas;
    float galutinis_rezultatas = 0;
    int nd_rezultatai[1000];
    float mediana;
};

int random() {
    int randomNumber = rand() % 10 + 1;
    return randomNumber;
}

float galutinisRezultatas(int kiek, int j, studentas studentas[]) {
    float suma = 0;
    float vidurkis = 0;
    for (int i = 0; i < kiek; i++) {
        suma = suma + studentas[j].nd_rezultatai[i];
    }
    vidurkis = suma / kiek;
    studentas[j].galutinis_rezultatas = vidurkis * (float) 0.4 +
                                        studentas[j].egzamino_rezultatas * (float) 0.6;
    return studentas[j].galutinis_rezultatas;
}

float mediana(studentas studentas[], int j, int kiek) {
    std::sort(studentas[j].nd_rezultatai, studentas[j].nd_rezultatai + kiek);
    if (kiek % 2 == 0) {
        studentas[j].mediana = ((studentas[j].nd_rezultatai[kiek / 2 - 1] + studentas[j].nd_rezultatai[kiek / 2]) /
                                2.0);
        return studentas[j].mediana;
    } else {
        studentas[j].mediana = studentas[j].nd_rezultatai[kiek / 2];
        return studentas[j].mediana;
    }
}

int main() {
    studentas studentas[5];
    for (int j = 0; j < 2; j++) {
        int kiek = 0;
        float vidurkis = 0;
        float suma = 0;
        string pazymiai;
        string delimiter = " ";
        size_t pos = 0;
        string token;
        string klausimas;
        cout << "Iveskite studento varda, pavarde: " << endl;
        cin >> studentas[j].Vardas >> studentas[j].Pavarde;
        cout << "Ar norite, kad pazymiai ir egzamino rezultatas butu sugeneruotas atsitiktinai?" << endl
             << "(Iveskite taip arba ne)";
        cin >> klausimas;
        if (klausimas == "ne" || klausimas == "Ne") {
            cout << "Iveskite studento namu darbu rezultatus: ";
            std::getline(std::cin >> std::ws, pazymiai);
            while ((pos = pazymiai.find(delimiter)) != std::string::npos) {
                token = pazymiai.substr(0, pos);
                studentas[j].nd_rezultatai[kiek] = stoi(token);
                pazymiai.erase(0, pos + delimiter.length());
                kiek++;
            }
            cout << "Iveskite egzamino rezultata: " << endl;
            cin >> studentas[j].egzamino_rezultatas;
            galutinisRezultatas(kiek, j, studentas);
            mediana(studentas, j, kiek);
        } else if (klausimas == "taip" || klausimas == "Taip") {
            cout << "Kiek pazymiu sugeneruoti?";
            cin >> kiek;
            srand(time(NULL));
            for (int i = 0; i < kiek; i++) {
                studentas[j].nd_rezultatai[i] = random();
                cout << studentas[j].nd_rezultatai[i] << endl;
            }
            srand(time(NULL));
            studentas[j].egzamino_rezultatas = random();
            cout << studentas[j].egzamino_rezultatas << endl;
            galutinisRezultatas(kiek, j, studentas);
            mediana(studentas, j, kiek);
        } else {
            cout << "Blogai ivestas rezultatas. Iveskite taip arba ne." << endl;
        }

    }
    cout << "Vardas:\t" << "Pavarde:\t" << "Galutinis vidurkis/Galutine mediana:\t" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
    for (int g = 0; g < 2; g++) {
        cout << studentas[g].Vardas << "\t" << studentas[g].Pavarde << "\t\t" << std::setprecision(2) << std::fixed
             << studentas[g].galutinis_rezultatas << "\t\t" << std::setprecision(2)
             << studentas[g].mediana
             << endl;
    }

    ofstream myfile;
    myfile.open("example.txt");
    myfile << "Vardas:\t" << "Pavarde:\t" << "Galutinis rezultatas/Galutine mediana:\t" << endl;
    myfile << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
    for (int g = 0; g < 2; g++)
        myfile << studentas[g].Vardas << "\t" << studentas[g].Pavarde << "\t\t" << std::setprecision(2)
               << std::fixed
               << studentas[g].galutinis_rezultatas << "\t\t" << std::setprecision(2)
               << studentas[g].mediana
               << endl;
    myfile.close();
//galutinis rezultatas
    /*for (int i = 0; i < kiek; i++) {
        suma = suma + studentas[j].nd_rezultatai[i];
    }
    vidurkis = suma / kiek;
    cout << "Iveskite egzamino rezultata: " << endl;
    cin >> studentas[j].egzamino_rezultatas;
    studentas[j].galutinis_rezultatas = vidurkis * (float) 0.4 +
                                        studentas[j].egzamino_rezultatas * (float) 0.6;


//mediana
    std::sort(studentas[j].nd_rezultatai, studentas[j].nd_rezultatai + kiek);
    if (kiek % 2 == 0) {
        studentas[j].mediana = ((studentas[j].nd_rezultatai[kiek / 2 - 1] + studentas[j].nd_rezultatai[kiek / 2]) /
                                2.0);
    } else {
        studentas[j].mediana = studentas[j].nd_rezultatai[kiek / 2];
    }
}*/
}
