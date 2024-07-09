#include <stdio.h>

#include <vector>
#include <sstream>

#include "access_helper.h"

template<typename Iterator>
std::ostringstream &StringJoin(std::ostringstream &ss, Iterator begin, Iterator end, const char *separator) {
    while(begin != end) {
        ss << *begin;

        ++begin;

        if(begin != end) {
            ss << separator;
        }
    }

    return ss;
}

class Demo {
    private:
        int one = 1;
        int two = 2;
        std::vector<std::string> svector;

    public:
        void Dump() {
            printf("one=%d, two=%d\n", one, two);
        }

        void DumpSvector() {
            std::ostringstream ss;
            StringJoin(ss, svector.begin(), svector.end(), ",");
            printf("svector=[%s]\n", ss.str().c_str());
        }
};

namespace DemoAccess {

GenerateFieldAccessor(AccessOne, Demo, one, int);
GenerateFieldAccessor(AccessTwo, Demo, two, int);

GenerateFieldConstAccessor(AccessConstOne, Demo, one, int);
GenerateFieldConstAccessor(AccessConstTwo, Demo, two, int);

GenerateFieldAccessor(AccessSvector, Demo, svector, std::vector<std::string>);

}

int main() {
    Demo d;
    d.Dump();
    d.DumpSvector();

    DemoAccess::AccessOne(d) = 88888;
    DemoAccess::AccessTwo(d) = 99999;

    DemoAccess::AccessSvector(d).emplace_back("first_string");
    DemoAccess::AccessSvector(d).emplace_back("second_string");

    d.Dump();
    d.DumpSvector();

    const Demo e;
    printf("const: %d %d\n", DemoAccess::AccessConstOne(e), DemoAccess::AccessConstTwo(e));

    return 0;
}


