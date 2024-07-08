#include <stdio.h>

#include "access_helper.h"

class Demo {
    private:
        int one = 1;
        int two = 2;
    public:
        void Dump() {
            printf("one=%d, two=%d\n", one, two);
        }
};

GenerateAccessor(AccessOne, Demo, one, int);
GenerateAccessor(AccessTwo, Demo, two, int);

GenerateConstAccessor(AccessConstOne, Demo, one, int);
GenerateConstAccessor(AccessConstTwo, Demo, two, int);


int main() {
    Demo d;
    d.Dump();

    AccessOne(d) = 88888;
    AccessTwo(d) = 99999;

    d.Dump();

    const Demo e;
    printf("const: %d %d\n", AccessConstOne(e), AccessConstTwo(e));

    // AccessConstOne(e) = 777;

    return 0;
}


