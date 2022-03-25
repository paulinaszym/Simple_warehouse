#include <iostream>
#include <string>
#include "Magazyn.h"
//#include <thread>
#include <fstream>
#include "ProduktT.h"
using namespace std;

void chooseMagazyn(vector<Magazyn*>, Paleciak&, ifstream&);
void magazynMenu(Magazyn*, Paleciak&, ifstream&);
void addTowar(Magazyn*, ifstream&);
void addItems(Magazyn*, ifstream&);
void removeItems(Magazyn*, ifstream&);
int towarID(Magazyn*, ifstream&);

void deliveryTowar(Magazyn*, Paleciak&, ifstream&);
void acceptTowar(Magazyn*, Paleciak&, ifstream&);
void paleciakMenu(Magazyn*, Paleciak&, ifstream&);
int towarID(Paleciak&, ifstream&);

int readInt(ifstream&);
double readDouble(ifstream&);
string readString(ifstream&);

int main(int argc, char* argv[])
{
    ifstream in_file;
    if(argc==2)
        in_file.open(argv[1], ios::in);

    static int magID = -1;
    vector<Magazyn*> _mags;
    Paleciak u_paleciak(0);
    Magazyn* _mag;
    if(_mags.empty()) {
        _mag = new Magazyn(++magID);
        _mags.push_back(_mag);
    }

    int choice;
    do{
        cout << "=======================================\n"
                "Wybierz akcje:\n"
                "1. Menu do pracy z magazynem\n"
                "2. Stworz nowy magazyn\n"
                "3. Pokaz zawartosc wszystkich magazynow\n"
                "0. Zakoncz prace.\n"
                "=======================================\n"
                "Wybierz 0-3: " <<endl;
        choice=readInt(in_file);
        switch (choice)
        {
            case 0: break;
            case 1: chooseMagazyn(_mags, u_paleciak, in_file);
                break;
            case 2: {
                _mag = new Magazyn(++magID);
                _mags.push_back(_mag);
                cout << "Dodano magazyn o ID: " << magID << endl;
            }
                break;
            case 3: {
                for(auto& x : _mags) x->printM();
            }
                break;
            default: cout << "Niepoprawny wybor! Podaj ponownie!" << endl;
        }
        // this_thread::sleep_for(1s);
    }  while (choice != 0);

    for(auto&x : _mags) delete x;
    in_file.close();
    return 0;
}

void chooseMagazyn(vector<Magazyn*> _m, Paleciak& paleciak, ifstream& file) {
    int ix;
    int size = static_cast<signed int>(_m.size()-1);
    if(!size) {
        cout << "Istnieje tylko jeden magazyn"<< endl;
        ix=0;
    }
    else {
        cout << "Podaj numer magazynu do pracy 0-" << size << endl;
        ix = readInt(file);
        if(ix>size) {
            cout << "Magazyn o podanym ID nie istnieje, podaj poprawne ID: "<<endl;
            ix = readInt(file);
        }
    }
    magazynMenu(_m[ix], paleciak, file);
}
void magazynMenu(Magazyn* magazyn, Paleciak& paleciak, ifstream& file) {

    int choice;
    do {
        if( magazyn->emptyM()) addTowar(magazyn, file);
        cout << "=======================================\n"
                "Wybierz akcje (magazyn):\n"
                "1. Dodaj towar \n2. Przyjmij ilosc towaru \n"
                "3. Pobierz ilosc towaru \n4. Pokaz caly magazyn \n"
                "5. Usun ostatni dodany rodzaj towaru\n"
                "6. Przenies towar z/na paleciak\n"
                "0. Powrot do menu glownego\n"
                "=======================================\n"
                "Wybierz 0-6: " <<endl;
        choice = readInt(file);
        switch (choice){
            case 0: break;
            case 1: addTowar(magazyn, file);
                break;
            case 2: addItems(magazyn, file);
                break;
            case 3: removeItems(magazyn, file);
                break;
            case 4: magazyn->printM();
                break;
            case 5: magazyn->deleteItem();
                break;
            case 6: paleciakMenu(magazyn, paleciak, file);
                break;
            default: cout << "Niepoprawny wybor! Podaj ponownie!" << endl;
        }
        // this_thread::sleep_for(1s);
    } while (choice != 0);
}
void addTowar(Magazyn* magazyn, ifstream& file)
{
    int choice;
    if( magazyn->emptyM()) cout << "Podaj nazwe pierwszego towaru w magazynie: " << endl;
    else cout << "Podaj nazwe towaru: " << endl;
    string name = readString(file);
    const char * cname = name.c_str();
    cout << "=======================================\n"
            "Wybierz rodzaj towaru:\n"
            "1. Na sztuki\n2. Sypki\n"
            "3. Ciekly \n"
            "=======================================\n"
            "Wybierz 1-3: " <<endl;
    choice=readInt(file);

    switch (choice) {
        case 0: break;
        case 1: {
            cout << "Podaj wage towaru: " << endl;
            double w = readDouble(file);
            unique_ptr<Produkt> x (new ProduktS<int>(++Magazyn::Id, cname, "na sztuki", w));
            magazyn->addItem(x);
        }
            break;
        case 2: {
            unique_ptr<Produkt> y (new ProduktS<double>(++Magazyn::Id, cname, "sypki"));
            magazyn->addItem(y); }
            break;
        case 3: {
            unique_ptr<Produkt> y (new ProduktS<float>(++Magazyn::Id, cname, "ciekly"));
            magazyn->addItem(y); }
            break;
        default: cout << "Niepoprawny wybor! Podaj ponownie!" << endl;
    }
    //this_thread::sleep_for(1s);
}
void addItems(Magazyn* magazyn, ifstream& file)
{
    int index = towarID(magazyn, file);
    cout << "Podaj ilosc sztuk do przyjecia: " << endl;
    double num = readDouble(file);
    magazyn->addM(index, num);
}
void removeItems(Magazyn* magazyn, ifstream& file)
{
    int index = towarID(magazyn, file);
    if(!static_cast<bool>(magazyn->getAmount(index))) {
        cout << "Brak sztuk do odbioru (towar ma 0 sztuk)" <<endl;
        return;
    }
    cout<<"Podaj ilosc sztuk do odbioru 0-"<<magazyn->getAmount(index)<<": "<< endl;

    double num = readDouble(file);

    bool trying =false;
    while(!trying){
        try {
            magazyn->removeM(index, num);
            trying=true;
        }
        catch(AmountError& x) {
            cerr << x.message << endl <<
             "Ilosc pobranych sztuk musi byc mniejsza lub rowna obecnej ilosci towaru. \n"
                    "Podaj poprawna ilosc 0-" << magazyn->getAmount(index)<<": "<< endl;
            num=readDouble(file);
        }
    }
}
int towarID(Magazyn* magazyn, ifstream& file)
{
    int index{};
    if(!magazyn->realSize()) cout << "Istnieje tylko jeden towar." << endl;
    else {
        magazyn->printM();
        cout << "Wybierz nr towaru 0-" << magazyn->realSize() << ": "<< endl;
        index = readInt(file);
        bool trying =false;
        while(!trying) {
            try {
                magazyn->getIndex(index);
                trying = true;
            }
            catch (IndexError &x) {
                cerr << x.message << endl <<
                 "Towar o podanym nr nie istnieje, podaj poprawne nr: " << endl;
                index = readInt(file);
            }
        }
    }
    return index;
}

void paleciakMenu(Magazyn* magazyn, Paleciak& paleciak, ifstream& file)
{
    int choice;
    do {
        if( paleciak.emptyP()) deliveryTowar(magazyn, paleciak, file);
        cout << "=======================================\n"
                "Wybierz akcje (paleciak):\n"
                "1. Dodaj towar na paleciak\n"
                "2. Zabierz towar z paleciaka\n"
                "3. Pokaz caly paleciak\n"
                "0. Powrot do menu magazynu\n"
                "=======================================\n"
                "Wybierz 0-3: " <<endl;
        choice=readInt(file);
        switch (choice) {
            case 0: break;
            case 1: deliveryTowar(magazyn, paleciak, file);
                break;
            case 2: acceptTowar(magazyn, paleciak, file);
                break;
            case 3: paleciak.printP();
                break;
            default: cout << "Niepoprawny wybor!" << endl;
        }
        //this_thread::sleep_for(1s);
    }  while (choice != 0);
}
void deliveryTowar(Magazyn* magazyn, Paleciak& paleciak, ifstream& file)
{
    int index = towarID(magazyn, file);
    if(!static_cast<bool>(magazyn->getAmount(index))) {
        cout << "Brak sztuk do odbioru (towar ma 0 sztuk)" <<endl;
        return;
    }
    cout<<"Podaj ilosc sztuk do odbioru 0-"<<magazyn->getAmount(index)<<": "<< endl;

    double num = readDouble(file);

    bool trying =false;
    while(!trying) {
        try {
            magazyn->deliveryM(paleciak, index, num);
            trying=true;
        }
        catch (AmountError &x) {
            cerr << x.message << endl
            << "Ilosc pobranych sztuk musi byc mniejsza lub rowna obecnej ilosci towaru. \n"
                    "Podaj poprawna ilosc 0-" << magazyn->getAmount(index) << ": " << endl;
            num = readDouble(file);
            magazyn->deliveryM(paleciak, index, num);
        }
    }
}
void acceptTowar(Magazyn* magazyn, Paleciak& paleciak, ifstream& file)
{
    int index = towarID(paleciak, file);
    if(!static_cast<bool>(paleciak.getAmount(index))) {
        cout << "Brak sztuk do odbioru (towar ma 0 sztuk)" <<endl;
        return;
    }
    cout<<"Podaj ilosc do odbioru 0-"<<paleciak.getAmount(index)<<": "<< endl;

    double num = readDouble(file);

    bool trying =false;
    while(!trying) {
        try {
            paleciak.deleteItemP(magazyn, index, num);
            trying = true;
        }
        catch (AmountError &x) {
            cerr << x.message << endl
            << "Ilosc pobranych sztuk musi byc mniejsza lub rowna obecnej ilosci towaru. \n"
                    "Podaj poprawna ilosc 0-" << paleciak.getAmount(index) << ": " << endl;
            num = readDouble(file);
        }
    }
}
int towarID(Paleciak& paleciak, ifstream& file)
{
    int index{};
    if(!paleciak.realSize()) cout << "Istnieje tylko jeden towar." << endl;
    else {
        paleciak.printP();
        cout << "Wybierz nr towaru 0-" << paleciak.realSize() << ": "<< endl;
        index = readInt(file);

        bool trying =false;
        while(!trying) {
            try {
                paleciak.getIndex(index);
                trying = true;
            }
            catch (IndexError &x) {
                cerr << x.message << endl
                << "Towar o podanym nr nie istnieje, podaj poprawne nr: " << endl;
                index = readInt(file);
            }
        }
    }
    return index;
}

int readInt(ifstream& file) {
    string line;
    if(file.is_open())
    {
        getline(file, line);
        cout << line << endl;
    }
    else getline(cin, line);
    return strtol(line.c_str(),nullptr,10);
}
double readDouble(ifstream& file) {
    string line;
    if(file.is_open()) {
        getline(file, line);
        cout << line << endl;
    }
    else getline(cin, line);
    return strtod(line.c_str(),nullptr);
}
string readString(ifstream& file) {
    string line;
    if(file.is_open()) {
        getline(file, line);
        cout << line << endl;
    }
    else getline(cin, line);
    return line;
}
