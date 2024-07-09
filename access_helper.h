#ifndef __ACCESS_HELPER_H__
#define __ACCESS_HELPER_H__


#define GenerateFieldAccessor(AccessName, ClassName, MemberName, MemberType) \
template<typename Class, typename Member, Member Class::* Address> \
struct AccessName##_FieldAccessGenerator { \
    friend Member & AccessName (Class &inst) { \
        return inst.*Address; \
    } \
}; \
template \
struct AccessName##_FieldAccessGenerator<ClassName, MemberType, &ClassName::MemberName>; \
MemberType & AccessName (ClassName &inst);


#define GenerateFieldConstAccessor(AccessName, ClassName, MemberName, MemberType) \
template<typename Class, typename Member, Member Class::* Address> \
struct AccessName##_FieldConstAccessGenerator { \
    friend const Member & AccessName (const Class &inst) { \
        return inst.*Address; \
    } \
}; \
template \
struct AccessName##_FieldConstAccessGenerator<ClassName, MemberType, &ClassName::MemberName>; \
const MemberType & AccessName (const ClassName &inst);


#endif
