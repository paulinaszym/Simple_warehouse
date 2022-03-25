#include "Magazyn.h"
using namespace std;
#include <stdexcept>

int Magazyn::Id=-1;

void Magazyn::addItem(unique_ptr<Produkt>& p)
{
    _magazyn.push_back(move(p));
}
void Magazyn::deleteItem()
{
    _magazyn.pop_back();
}
void Magazyn::addM(int ID, double amount)
{
    auto wsk = _magazyn[getIndex(ID)].get();
    wsk->addI(amount);
}
void Magazyn::removeM(int ID, double amount)
{
    if(amount>getAmount(ID)) throw AmountError();
    auto wsk = _magazyn[getIndex(ID)].get();
    wsk->removeI(amount);
}
void Magazyn::printM() const
{
    cout << "Zawartosc magazynu " << _magazynID << ":" << endl;
    int i=0;
    for(auto &x : _magazyn) {
        cout << "Nr." << i << " | ";
        x->printItem();
        i++;
    }
    cout << "\n";
}
void Magazyn::deliveryM(Paleciak& paleciak, int ID, double amount)
{
    if(amount>getAmount(ID)) throw AmountError();
    auto p = _magazyn[getIndex(ID)]->divideI(amount);
    paleciak.addItemP(p);
}
void Magazyn::acceptM(Produkt* p)
{
    unique_ptr<Produkt> x(p);
    if(!isItem(p)) _magazyn.push_back(move(x));
    else { int ix=getIndex(p->getID());
        _magazyn[ix]->addI(p->getAmountI());
    }
}
double Magazyn::getAmount(int ID) const {
    return _magazyn[getIndex(ID)]->getAmountI();
}

int Magazyn::getIndex(int ID) const
{
    if(ID>realSize()) throw IndexError();
    for(int i=0; i<_magazyn.size(); i++)
        if(_magazyn[i]->getID()==_magazyn[ID]->getID()) return i;
    throw IndexError();
}

bool Magazyn::isItem(Produkt* p) {
    int ix=getIndex(p->getID());
    for(auto &x : _magazyn)
        if(x->getID()==_magazyn[ix]->getID()) return true;
    return false;
}
