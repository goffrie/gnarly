#include "object.h"
#include "util.h"

using namespace std;

string Object::name(Article a) const {
    string r = basicName();
    switch (a) {
        case Definite: return "the " + r;
        case Indefinite:
            if (r.size() > 0 && isVowel(r[0])) {
                return "an " + r;
            } else {
                return "a " + r;
            }
        default:
            return r;
    }
}
