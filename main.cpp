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

bool konvertuok_pazymius(int *pazymiu_masyvas, const string &token, int pazymio_indeksas) {
    bool tesk = false;
    try {
        int skaicius = stoi(token);
        if (skaicius <= 0 | skaicius > 10) {
            cout << "Klaida pazymys  turi buti nuo 0 iki 10" << endl;
            tesk = true;
        }
        pazymiu_masyvas[pazymio_indeksas] = skaicius;
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
        int pazymio_indeksas = 0;
        bool tesk = true;
        cout << "Iveskite studento namu darbu rezultatus:" << endl;
        getline(cin >> std::ws, pazymiai);
        while ((pos = pazymiai.find(delimiter)) != string::npos) {
            token = pazymiai.substr(0, pos);
            tesk = konvertuok_pazymius(pazymiu_masyvas, token, pazymio_indeksas);
            if (tesk) {
                break;
            }
            pazymiai.erase(0, pos + delimiter.length());
            pazymio_indeksas++;
        }
        if (!tesk) {
            if (!konvertuok_pazymius(pazymiu_masyvas, pazymiai, pazymio_indeksas)) {
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

float galutinis_rezultatas(int *pazymiu_masyvas, string skaicius_string) {
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

float mediana(int *pazymiu_masyvas) {
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

string ar_generuoti_rezultatus() {
    string atsakymas;
    cout << "Ar norite, kad pazymiai ir egzamino rezultatas butu sugeneruotas atsitiktinai?" << endl
         << "(Iveskite taip arba ne)";
    cin >> atsakymas;
    return atsakymas;
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

bool ivesti_nauja_studenta() {
    string atsakymas;
    cout << "Ar ivesti nauja studenta?Iveskite taip arba ne" << endl;
    while (true) {
        cin >> atsakymas;
        if (atsakymas == "Taip" || atsakymas == "taip" || atsakymas == "TAIP")
            return true;
        else if (atsakymas == "ne" || atsakymas == "Ne" || atsakymas == "NE")
            return false;
        else {
            cout << "Klaida. Iveskite taip arba ne." << endl;
            continue;
        }
    }
}

int studento_duomenys(studentas *students, int *pazymiu_masyvas, string &skaicius_string) {
    int studento_indeksas =  0;
    while (ivesti_nauja_studenta()) {
        cout << "Iveskite studento varda, pavarde: " << endl;
        cin >> students[studento_indeksas].Vardas >> students[studento_indeksas].Pavarde;
        while (true) {
            string atsakymas = ar_generuoti_rezultatus();
            if (atsakymas == "ne" || atsakymas == "Ne" || atsakymas == "NE") {
                pazymiu_nuskaitymas(pazymiu_masyvas);
                cout << "Iveskite egzamino rezultata: " << endl;
                cin >> skaicius_string;
                students[studento_indeksas].galutinis_rezultatas = galutinis_rezultatas(pazymiu_masyvas, skaicius_string);
                students[studento_indeksas].mediana = mediana(pazymiu_masyvas);
                studento_indeksas++;
                break;
            } else if (atsakymas == "taip" || atsakymas == "Taip" || atsakymas == "TAIP") {
                generuojami_skaiciai(pazymiu_masyvas);
                students[studento_indeksas].egzamino_rezultatas = random();
                students[studento_indeksas].galutinis_rezultatas = galutinis_rezultatas(pazymiu_masyvas,
                                                                                        to_string(students[studento_indeksas].egzamino_rezultatas));
                students[studento_indeksas].mediana = mediana(pazymiu_masyvas);
                studento_indeksas++;
                break;
            } else {
                cout << "Klaida. ";
                continue;
            }
        }
    }
    return studento_indeksas;
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
    int pazymiu_masyvas[100] = {0};
    string skaicius_string;
    int studento_nr = studento_duomenys(students, pazymiu_masyvas, skaicius_string);
    informacijos_isvedimas(students, studento_nr);
}
