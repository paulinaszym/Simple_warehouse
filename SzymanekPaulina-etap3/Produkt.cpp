#include "Produkt.h"
#include "cstring"
using namespace std;

void Produkt::copyString(const char *s1, char **s2)
{
    if(s1)
    {
        delete *s2;
        *s2 = new char[strlen(s1) + 1];
        strcpy(*s2, s1);
    }
    else *s2=nullptr;
}
