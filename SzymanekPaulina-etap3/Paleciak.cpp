#include "Paleciak.h"
using namespace std;

void Paleciak::addItemP(Produkt* p)
{
    unique_ptr<Produkt> x(p);
    if(emptyP() || !isItem(p)) _paleciak.push_back(move(x));
    else {
        int ix=getIndex(p->getID());
        _paleciak[ix]->addI(p->getAmountI());
    }
    _capacity+= p->getWeight();
}

void Paleciak::deleteItemP(Magazyn* magazyn, int ID, double amount) {
    if(amount>getAmount(ID)) throw AmountError();
    auto p = _paleciak[getIndex(ID)]->divideI(amount);
    _capacity-= p->getWeight();
    magazyn->acceptM(p);
}
bool Paleciak::isItem(Produkt* p) {
    int ix=getIndex(p->getID());
    for(auto &x : _paleciak)
        if(x->getID()==_paleciak[ix]->getID()) return true;
    return false;
}
void Paleciak::printP() const {
    cout << "Obecny udzwig paleciaka: " << _capacity << endl;
    cout << "Zawartosc paleciaka: " << endl;
    int i=0;
    for( auto &x : _paleciak){
        cout << "Nr." << i << " | ";
        x->printItem();
        i++;
    }
    std::cout << "\n";
}
int Paleciak::getIndex(int ID) const {
    if(ID>realSize()) throw IndexError();
    for(int i=0; i<_paleciak.size(); i++)
        if(_paleciak[i]->getID()==_paleciak[ID]->getID()) return i;
    throw IndexError();
}
