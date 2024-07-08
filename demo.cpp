#include <stdio.h>

class Demo {
    private:
        int one = 1;
        int two = 2;
    public:
        void Dump() {
            printf("one=%d, two=%d\n", one, two);
        }
};

template<typename Class, typename Member, Member Class::* Address>
struct AccessGenerator {
    friend Member &Access(Class &inst) {
        return inst.*Address;
    }
};

template
struct AccessGenerator<Demo, int, &Demo::two>;

int &Access(Demo &);

int main() {
    Demo d;
    d.Dump();

    Access(d) = 99999;

    d.Dump();

    return 0;
}

