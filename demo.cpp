#include <stdio.h>

#include <utility>

class Demo {
    private: int one = 1;
        int two = 2;
    public:
        void Dump() {
            printf("one=%d, two=%d\n", one, two);
        }
    private:
        int AddOne(int v1, int v2) {
            one += v1;
            one += v2;
            return one;
        }
};

template<int Demo::* Address>
struct AccessGenerator {
    friend int &Access(Demo &inst) {
        return inst.*Address;
    }
};
template
struct AccessGenerator<&Demo::two>;
int &Access(Demo &);


template<int (Demo::*Address)(int, int)>
struct MethodGenerator {
    template<typename ... Args>
    friend int Method(Demo &inst, Args && ... args) {
        return (inst.*Address)(std::forward<Args>(args)...);
    }
};
template
struct MethodGenerator<&Demo::AddOne>;
template<typename ... Args>
int Method(Demo &, Args && ... args);


int main() {
    Demo d;
    d.Dump();

    Access(d) = 99999;

    d.Dump();

    int ret = Method(d, 222, 333);
    printf("ret=%d\n", ret);

    d.Dump();

    return 0;
}

