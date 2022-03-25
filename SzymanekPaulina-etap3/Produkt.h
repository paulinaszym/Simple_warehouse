#ifndef SZYMANEKPAULINA_ETAP2_PRODUKT_H
#define SZYMANEKPAULINA_ETAP2_PRODUKT_H
#include <iostream>

class Produkt {
protected:
    int _ID;
    char* _name;
    char* _type;
    static void copyString(const char *s1, char **s2);

public:
    virtual void printItem()=0;
    virtual void addI(double amount) =0;
    virtual void removeI(double amount) =0;
    virtual double getAmountI() =0;
    virtual int getID()=0;
    virtual Produkt* divideI(double amount)=0; //podziel
    virtual void mergeI(Produkt* p)=0; //scal
    virtual double getWeight()=0;

    explicit Produkt( int ID, const char* name=nullptr, const char* type=nullptr) : _ID(ID), _name(nullptr), _type(nullptr) {
        copyString(name, &this->_name);
        copyString(type, &this->_type);};
    Produkt(int ID, std::string& name, std::string& type) : Produkt(ID, name.c_str(), type.c_str()) {};
    Produkt(const Produkt &p) : Produkt(p._ID, p._name, p._type) { };

    virtual ~Produkt() { delete[] _name; };
};


#endif //SZYMANEKPAULINA_ETAP2_PRODUKT_H
