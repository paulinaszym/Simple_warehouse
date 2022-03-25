#ifndef REJESTR_MAGAZYNU_MAGAZYN_H
#define REJESTR_MAGAZYNU_MAGAZYN_H
#include "Produkt.h"
#include "Paleciak.h"
#include <vector>
#include <memory>

struct AmountError : std::exception {
    std::string message;
    explicit AmountError(std::string msg="AmountError!") : message(std::move(msg)) {}
};
struct IndexError : std::exception {
    std::string message;
    explicit IndexError(std::string msg="IndexError!") : message(std::move(msg)) {}
};

class Paleciak;
class Magazyn {
    std::vector<std::unique_ptr<Produkt>> _magazyn;
    int _magazynID;

public:
    static int Id;
    void addItem(std::unique_ptr<Produkt>& p);
    void deleteItem();
    void addM(int ID, double amount); //przyjecie
    void removeM(int ID, double amount); //odbior
    void printM() const;
    void deliveryM(Paleciak& paleciak, int ID, double amount); //wydaj
    void acceptM(Produkt* p); //przyjmij
    int getIndex(int ID) const;
    bool emptyM() const { return _magazyn.empty(); };
    int realSize() const {
        int s = _magazyn.size();
        if(!s) return 0;
        else return  --s;
    }
    double getAmount(int ID) const;
    bool isItem(Produkt* p);
    Magazyn(int magazynID) : _magazynID(magazynID) {};
};

#endif //REJESTR_MAGAZYNU_MAGAZYN_H
