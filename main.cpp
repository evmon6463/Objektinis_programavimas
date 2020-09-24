#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <vector>


using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::ofstream;
using std::vector;

struct studentas {
    string Vardas;
    string Pavarde;
    int egzamino_rezultatas;
    float galutinis_rezultatas = 0;
    float mediana;
};

int masyvo_ilgis(const int *pazymiu_masyvas);

int random() {
    int randomNumber = rand() % 10 + 1;
    return randomNumber;
}

int nuskaityti_pazymi(string skaicius_string) {

    while (true) {
        try {
            int ivestas_skaicius = stoi(skaicius_string);
            if (ivestas_skaicius > 0 & ivestas_skaicius <= 10) {
                return ivestas_skaicius;
            } else {
                cout << "Klaida! Skaicius nera tarp 1 ir 10. Pabandykite dar karta!" << endl;
                cin >> skaicius_string;
                continue;
            }
        }
        catch (std::invalid_argument &e) {
            cout << "Klaida! Jus ivedete ne skaiciu. Pabandykite dar karta!" << endl;
            cin >> skaicius_string;
            continue;
        }
    }
}

bool konvertuot(int pazymiu_masyvas[], const string &token, int kiek) {
    bool tesk = false;
    try {
        int skaicius = stoi(token);
        if (skaicius <= 0 | skaicius > 10) {
            tesk = true;
        }
        pazymiu_masyvas[kiek] = skaicius;
    } catch (std::invalid_argument &e) {
        cout << "Klaida" << endl;
        tesk = true;
    }
    return tesk;
}

int *eilutes_nuskaitymas(int pazymiu_masyvas[]) {
    string delimiter = " ";
    size_t pos = 0;
    string token;
    string pazymiai;

    while (true) {
        int kiek = 0;
        bool tesk = true;
        cout << "Iveskite studento namu darbu rezultatus:" << endl;
        std::getline(std::cin >> std::ws, pazymiai);

        while ((pos = pazymiai.find(delimiter)) != std::string::npos) {
            token = pazymiai.substr(0, pos);
            tesk = konvertuot(pazymiu_masyvas, token, kiek);
            if (tesk) {
                break;
            }
            pazymiai.erase(0, pos + delimiter.length());
            kiek++;
        }

        if (!tesk & !konvertuot(pazymiu_masyvas, pazymiai, kiek)) {
            return pazymiu_masyvas;
        }
    }
}

int masyvo_ilgis(const int *pazymiu_masyvas) {
    int i = 0;
    while (pazymiu_masyvas[i] != 0) {
        i++;
    }
    return i;
}

float galutinisRezultata(int *pazymiu_masyvas, string skaicius_string) {
    float suma = 0;
    int nd_skaicius = masyvo_ilgis(pazymiu_masyvas);
    for (int i = 0; i < nd_skaicius; i++) {
        suma = suma + pazymiu_masyvas[i];
    }
    float vidurkis = suma / nd_skaicius;
    int egzaminas = nuskaityti_pazymi(skaicius_string);
    float galutinis_pazymys;
    galutinis_pazymys = vidurkis * (float) 0.4 +
                        egzaminas * (float) 0.6;
    return galutinis_pazymys;
}

float median(int *pazymiu_masyvas) {
    int nd_skaicius = masyvo_ilgis(pazymiu_masyvas);

    std::sort(pazymiu_masyvas + 0, pazymiu_masyvas + nd_skaicius);
    double median;
    if (nd_skaicius % 2 == 0) {
        median = ((pazymiu_masyvas[nd_skaicius / 2] + pazymiu_masyvas[nd_skaicius / 2 - 1]) /
                  2.0);
        return median;
    } else {
        median = pazymiu_masyvas[nd_skaicius / 2];
        return median;
    }
}

string klausimai() {
    string klausimas;
    cout << "Ar norite, kad pazymiai ir egzamino rezultatas butu sugeneruotas atsitiktinai?" << endl
         << "(Iveskite taip arba ne)";
    cin >> klausimas;
    return klausimas;
}

int sugeneruotu_pazymiu_kiekis() {
    int kiek = 0;
    cout << "Kiek pazymiu sugeneruoti?";
    cin >> kiek;
    return kiek;
}

int generuojamas_kiekis(int *pazymiu_masyvas) {
    while (true) {
        try {
            int kiek = sugeneruotu_pazymiu_kiekis();
            if (kiek > 0) {
                srand(time(NULL));
                for (int i = 0; i < kiek; i++) {
                    pazymiu_masyvas[i] = random();
                    cout << pazymiu_masyvas[i] << endl;
                }
                srand(time(NULL));
                return false;
            } else {
                cout << "Skaicius turi buti didesnis uz 0" << endl;
            }
        }
        catch (std::invalid_argument &e) {
            cout << "Pabandykite dar karta!" << endl;
            sugeneruotu_pazymiu_kiekis();
            continue;
        }
    }
}

int pradinis_klausimas() {
    string atsakymas;
    cout << "Ar ivesti nauja studenta?Iveskite taip arba ne" << endl;
    while (true) {
        cin >> atsakymas;
        try {
            if (atsakymas == "Taip" || atsakymas == "taip" || atsakymas == "TAIP")
                return 1;
            else if (atsakymas == "ne" || atsakymas == "Ne" || atsakymas == "NE")
                return 0;
            else {
                bool ar = false;
                cout << "Pabandykite dar karta!" << endl;
                continue;
            }
        }
        catch (std::invalid_argument &e) {
            cout << "Pabandykite dar karta!" << endl;
            cin >> atsakymas;
        }
    }
}

void grazina(const studentas *students, int i) {
    cout.width(20);
    cout << std::left <<  "Vardas" << std::setw(20) << "Pavarde" << std::setw(20) << "Galutinis vidurkis"
           << std::setw(20) << "Galutine mediana" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    ofstream myfile;
    myfile.open("example.txt");
    myfile.width(20);
    myfile << std::left <<  "Vardas" << std::setw(20) << "Pavarde" << std::setw(20) << "Galutinis vidurkis"
           << std::setw(20) << "Galutine mediana" << endl;
    myfile << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    for (int j = 0; j < i; j++) {
        cout.width(20);
        cout << students[j].Vardas << std::setw(20) << students[j].Pavarde
             << std::setw(20) << std::setprecision(2) << std::fixed
             << std::left << std::setw(20) << students[j].galutinis_rezultatas << std::setw(20)
             << std::setprecision(2) << std::fixed
             << students[j].mediana
             << endl;
        myfile.width(20);
        myfile << students[j].Vardas << std::setw(20) << students[j].Pavarde
               << std::setw(20) << std::setprecision(2) << std::fixed
               << std::left << std::setw(20) << students[j].galutinis_rezultatas << std::setw(20)
               << std::setprecision(2) << std::fixed
               << students[j].mediana
               << endl;
    }
    myfile.close();
}

int studento_duomenys(studentas *students, int *pazymiu_masyvas, string &skaicius_string, int i) {
    while (pradinis_klausimas() == 1) {
        cout << "Iveskite studento varda, pavarde: " << endl;
        cin >> students[i].Vardas >> students[i].Pavarde;
        string klausimas = klausimai();
        if (klausimas == "ne" || klausimas == "Ne" || klausimas == "NE") {
            string egzaminas;
            eilutes_nuskaitymas(pazymiu_masyvas);
            cout << "Iveskite egzamino rezultata: " << endl;
            cin >> skaicius_string;
            students[i].galutinis_rezultatas = galutinisRezultata(pazymiu_masyvas, skaicius_string);
            students[i].mediana = median(pazymiu_masyvas);
            i++;
        } else if (klausimas == "taip" || klausimas == "Taip" || klausimas == "TAIP") {
            generuojamas_kiekis(pazymiu_masyvas);
            students[i].egzamino_rezultatas = random();
            students[i].galutinis_rezultatas = galutinisRezultata(pazymiu_masyvas,
                                                                  std::to_string(students[i].egzamino_rezultatas));
            students[i].mediana = median(pazymiu_masyvas);
            i++;
        } else {
            cout << "Klaida. Ivaskite taip arba ne" << endl;
        }
    }
    return i;
}

int main() {
    studentas students[100];
    vector<string> eilute;
    int pazymiu_masyvas[100] = {0};
    string skaicius_string;
    int i = 0;
    i = studento_duomenys(students, pazymiu_masyvas, skaicius_string, i);
    grazina(students, i);
}












