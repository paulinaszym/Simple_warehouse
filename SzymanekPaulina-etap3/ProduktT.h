#ifndef MAGAZYNU_TOWAR_H
#define MAGAZYNU_TOWAR_H
#include <cstring>
#include "Produkt.h"

class Produkt;
template<typename P>
class ProduktS : public Produkt {
    P _amount{};
    double _weight{};

    void printItem() override
    {
        std::cout << "ID: " << _ID << " | Nazwa: " << _name;
        if(!strcmp(_type,"na sztuki")) std::cout << " | Ilosc sztuk: " << _amount <<
                                         " | Waga: " << _weight << " kg" << " (Razem: " << getWeight() << " kg) "<< std::endl;
        else if(!strcmp(_type,"sypki")) std::cout << " | Waga: " << _amount << " kg"  << std::endl;
        else if(!strcmp(_type,"ciekly")) std::cout << " | Objetosc: " << _amount << " l" << std::endl;
    }

    void addI(double amount) override { _amount += static_cast<P>(amount); }
    void removeI(double amount) override { _amount -= static_cast<P>(amount); }
    double getAmountI() override { return _amount; };
    int getID() override { return _ID; };

    Produkt* divideI(double amount) override { //podziel
        auto x= new ProduktS(_ID, _name, _type, _weight, static_cast<P>(amount));
        removeI(static_cast<int>(amount));
        return x;
    }
    void mergeI(Produkt* p) override {
        addI(p->getAmountI());
        delete p;
    }
    double getWeight() override { return _weight*_amount;};

public:
    explicit ProduktS(int ID, const char* name=nullptr, const char* type=nullptr, double weight=1, P amount=0) : Produkt(ID, name, type), _weight(weight), _amount(amount)
    { };
    //ProduktS(int ID, std::string& name) : Produkt(ID, name.c_str()) {};
    //ProduktS(const Produkt &p) : Produkt(p._ID, p._name) { };
    ~ProduktS() override =default;
};

#endif //MAGAZYNU_TOWAR_H