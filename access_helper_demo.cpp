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
        const int three = 3;
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
    private:
        int AddOne(int v1, int v2) {
            one += v1;
            one += v2;
            return one;
        }

        int Sum(const char *x, double y) const {
            printf("Sum input: %s %f\n", x, y);
            return one + two + three;
        }
};

namespace DemoAccess {

GenerateFieldAccessor(AccessOne, Demo, one, int);
GenerateFieldAccessor(AccessTwo, Demo, two, int);
GenerateFieldAccessor(AccessThree, Demo, two, const int);

GenerateFieldConstAccessor(AccessConstOne, Demo, one, const int);
GenerateFieldConstAccessor(AccessConstTwo, Demo, two, const int);
GenerateFieldConstAccessor(AccessConstThree, Demo, three, const int);

GenerateFieldAccessor(AccessSvector, Demo, svector, std::vector<std::string>);

GenerateMethodCaller(CallAddOne, Demo, AddOne, int, int, int);
GenerateMethodConstCaller(CallSumConst, Demo, Sum, int, const char *, double);

}

int main() {
    Demo d;
    d.Dump();
    d.DumpSvector();

    DemoAccess::AccessOne(d) = 88888;
    DemoAccess::AccessTwo(d) = 99999;
    
    d.Dump();

    DemoAccess::AccessSvector(d).emplace_back("first_string");
    DemoAccess::AccessSvector(d).emplace_back("second_string");

    int ret = DemoAccess::CallAddOne(d, 88, 99);
    printf("ret=%d\n", ret);

    d.Dump();
    d.DumpSvector();

    printf("non-const: %d %d %d\n", DemoAccess::AccessConstOne(d),
            DemoAccess::AccessConstTwo(d), DemoAccess::AccessConstThree(d));

    printf("sum: %d\n", DemoAccess::CallSumConst(d, "this_is_a_string", 9.99));

    const Demo e;
    printf("const: %d %d %d\n", DemoAccess::AccessConstOne(e),
            DemoAccess::AccessConstTwo(e), DemoAccess::AccessConstThree(e));
    
    printf("sum: %d\n", DemoAccess::CallSumConst(e, "this_is_a_string", 9.99));

    return 0;
}


