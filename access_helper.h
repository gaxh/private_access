#ifndef __ACCESS_HELPER_H__
#define __ACCESS_HELPER_H__


#define GenerateAccessor(AccessName, ClassName, MemberName, MemberType) \
template<typename Class, typename Member, Member Class::* Address> \
struct AccessName##_AccessGenerator { \
    friend Member & AccessName (Class &inst) { \
        return inst.*Address; \
    } \
}; \
template \
struct AccessName##_AccessGenerator<ClassName, MemberType, &ClassName::MemberName>; \
MemberType & AccessName (ClassName &inst);


#define GenerateConstAccessor(AccessName, ClassName, MemberName, MemberType) \
template<typename Class, typename Member, Member Class::* Address> \
struct AccessName##_ConstAccessGenerator { \
    friend const Member & AccessName (const Class &inst) { \
        return inst.*Address; \
    } \
}; \
template \
struct AccessName##_ConstAccessGenerator<ClassName, MemberType, &ClassName::MemberName>; \
const MemberType & AccessName (const ClassName &inst);


#endif
