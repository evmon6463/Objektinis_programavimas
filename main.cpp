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
using std::invalid_argument;
using std::getline;
using std::to_string;
using std::setw;
using std::setprecision;
using std::fixed;
using std::left;

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

int patikrink_egzamino_pazymi(string skaicius_string) {
    while (true) {
        try {
            int ivestas_skaicius = stoi(skaicius_string);
            if (ivestas_skaicius > 0 & ivestas_skaicius <= 10) {
                return ivestas_skaicius;
            } else {
                cout << "Klaida! Skaicius nera tarp 1 ir 10. Pabandykite dar karta!" << endl;
                continue;
            }
        }
        catch (invalid_argument &e) {
            cout << "Klaida! Jus ivedete ne skaiciu. Pabandykite dar karta!" << endl;
            cin >> skaicius_string;
            continue;
        }
    }
}

bool konvertuok_pazymius(int *pazymiu_masyvas, const string &token, int kiek) {
    bool tesk = false;
    try {
        int skaicius = stoi(token);
        if (skaicius <= 0 | skaicius > 10) {
            cout << "Klaida pazymys  turi buti nuo 0 iki 10" << endl;
            tesk = true;
        }
        pazymiu_masyvas[kiek] = skaicius;
    } catch (invalid_argument &e) {
        cout << "Klaida. Jus ivedete ne skaiciu. Pabandykite dar karta!" << endl;
        tesk = true;
    }
    return tesk;
}

int *pazymiu_nuskaitymas(int *pazymiu_masyvas) {
    string delimiter = " ";
    size_t pos = 0;
    string token;
    string pazymiai;
    while (true) {
        int kiek = 0;
        bool tesk = true;
        cout << "Iveskite studento namu darbu rezultatus:" << endl;
        getline(cin >> std::ws, pazymiai);
        while ((pos = pazymiai.find(delimiter)) != string::npos) {
            token = pazymiai.substr(0, pos);
            tesk = konvertuok_pazymius(pazymiu_masyvas, token, kiek);
            if (tesk) {
                break;
            }
            pazymiai.erase(0, pos + delimiter.length());
            kiek++;
        }
        if (!tesk) {
            if (!konvertuok_pazymius(pazymiu_masyvas, pazymiai, kiek)) {
                return pazymiu_masyvas;
            }
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
    int egzaminas = patikrink_egzamino_pazymi(skaicius_string);
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

string generavimo_klausimas() {
    string klausimas;
    cout << "Ar norite, kad pazymiai ir egzamino rezultatas butu sugeneruotas atsitiktinai?" << endl
         << "(Iveskite taip arba ne)";
    cin >> klausimas;
    return klausimas;
}

int sugeneruotu_pazymiu_kiekis() {
    string kiek;
    cout << "Kiek pazymiu sugeneruoti?";
    while (true) {
        cin >> kiek;
        try {
            if (!kiek.find_first_not_of(" 0123456789")) {
                cout << "Klaida. Ivedete ne skaicius" << endl;
                continue;
            } else {
                return stoi(kiek);
            }
        } catch (std::invalid_argument &e) {
            cout << "Klaida. Ivedete ne skaicius. Pabandykite dar karta!" << endl;
        }
    }
}

int generuojami_skaiciai(int *pazymiu_masyvas) {
    while (true) {
        int kiek = sugeneruotu_pazymiu_kiekis();
        if (kiek > 0 & kiek < 100) {
            srand(time(NULL));
            for (int i = 0; i < kiek; i++) {
                pazymiu_masyvas[i] = random();
            }
            srand(time(NULL));
            return false;
        } else {
            cout << "Skaicius turi buti didesnis uz 0 ir mazesnis nei 100" << endl;
        }
    }
}

int studento_ivedimo_klausimas() {
    string atsakymas;
    cout << "Ar ivesti nauja studenta?Iveskite taip arba ne" << endl;
    while (true) {
        cin >> atsakymas;
        if (atsakymas == "Taip" || atsakymas == "taip" || atsakymas == "TAIP")
            return 1;
        else if (atsakymas == "ne" || atsakymas == "Ne" || atsakymas == "NE")
            return 0;
        else {
            cout << "Klaida. Iveskite taip arba ne." << endl;
            continue;
        }
    }
}

int studento_duomenys(studentas *students, int *pazymiu_masyvas, string &skaicius_string, int i) {
    while (studento_ivedimo_klausimas() == 1) {
        cout << "Iveskite studento varda, pavarde: " << endl;
        cin >> students[i].Vardas >> students[i].Pavarde;
        while (true) {
            string klausimas = generavimo_klausimas();
            if (klausimas == "ne" || klausimas == "Ne" || klausimas == "NE") {
                string egzaminas;
                pazymiu_nuskaitymas(pazymiu_masyvas);
                cout << "Iveskite egzamino rezultata: " << endl;
                cin >> skaicius_string;
                students[i].galutinis_rezultatas = galutinisRezultata(pazymiu_masyvas, skaicius_string);
                students[i].mediana = median(pazymiu_masyvas);
                i++;
                break;
            } else if (klausimas == "taip" || klausimas == "Taip" || klausimas == "TAIP") {
                generuojami_skaiciai(pazymiu_masyvas);
                students[i].egzamino_rezultatas = random();
                students[i].galutinis_rezultatas = galutinisRezultata(pazymiu_masyvas,
                                                                      to_string(students[i].egzamino_rezultatas));
                students[i].mediana = median(pazymiu_masyvas);
                i++;
                break;
            } else {
                cout << "Klaida. ";
                continue;
            }
        }
    }
    return i;
}

void informacijos_isvedimas(const studentas *students, int i) {
    cout.width(20);
    cout << std::left << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis vidurkis"
         << setw(20) << "Galutine mediana" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    for (int j = 0; j < i; j++) {
        cout.width(20);
        cout << students[j].Vardas << setw(20) << students[j].Pavarde
             << setw(20) << setprecision(2) << fixed
             << left << setw(20) << students[j].galutinis_rezultatas << setw(20)
             << setprecision(2) << fixed
             << students[j].mediana
             << endl;
    }
}

int main() {
    studentas students[100];
    vector<string> eilute;
    int pazymiu_masyvas[100] = {0};
    string skaicius_string;
    int i = 0;
    i = studento_duomenys(students, pazymiu_masyvas, skaicius_string, i);
    informacijos_isvedimas(students, i);
}
