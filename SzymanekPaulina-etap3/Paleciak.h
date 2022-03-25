#ifndef SZYMANEKPAULINA_ETAP2_PALECIAK_H
#define SZYMANEKPAULINA_ETAP2_PALECIAK_H
#include "Produkt.h"
#include "Magazyn.h"
#include <vector>
#include <memory>

class Magazyn;
class Paleciak {
    std::vector<std::unique_ptr<Produkt>> _paleciak ;
    double _capacity{};

public:
    void addItemP(Produkt* p);
    bool isItem(Produkt* p);
    void deleteItemP(Magazyn* magazyn, int ID, double amount);
    void printP() const;

    int getIndex(int ID) const;
    bool emptyP() const { return _paleciak.empty(); };
    int realSize() const {
        int s = _paleciak.size();
        if(!s) return 0;
        else return  --s;
    }
    double getAmount(int ID) const { return _paleciak[getIndex(ID)]->getAmountI(); };

    Paleciak(double capacity=0) : _capacity(capacity) {};
    ~Paleciak()=default;
};

#endif //SZYMANEKPAULINA_ETAP2_PALECIAK_H

