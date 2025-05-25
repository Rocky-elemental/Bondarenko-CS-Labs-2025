#include "factorial.h"

namespace factorial {
    int fact(int a) {
        int s = 1;
        while (a!=0){
            s*=a;
            a-=1;
        }
        return s;
    }
}
