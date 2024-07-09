#ifndef __ACCESS_HELPER_H__
#define __ACCESS_HELPER_H__


#define GenerateFieldAccessor(AccessorName, ClassName, MemberName, MemberType) \
template<MemberType ClassName::* Address> \
struct AccessorName##_FieldAccessorGenerator { \
    friend MemberType & AccessorName (ClassName &inst) { \
        return inst.*Address; \
    } \
}; \
template \
struct AccessorName##_FieldAccessorGenerator<&ClassName::MemberName>; \
MemberType & AccessorName (ClassName &);


#define GenerateFieldConstAccessor(AccessorName, ClassName, MemberName, MemberType) \
template<MemberType ClassName::* Address> \
struct AccessorName##_FieldConstAccessorGenerator { \
    friend MemberType & AccessorName (const ClassName &inst) { \
        return inst.*Address; \
    } \
}; \
template \
struct AccessorName##_FieldConstAccessorGenerator<&ClassName::MemberName>; \
MemberType & AccessorName (const ClassName &);


#define GenerateMethodCaller(CallerName, ClassName, MethodName, ReturnType, ...) \
template<ReturnType (ClassName::*Address)( __VA_ARGS__ )> \
struct CallerName##_MethodCallerGenerator { \
    template<typename ... Args> \
    friend ReturnType CallerName (ClassName &inst, Args && ... args) { \
        return (inst.*Address)(std::forward<Args>(args)...); \
    } \
}; \
template \
struct CallerName##_MethodCallerGenerator<&ClassName::MethodName>; \
template<typename ... Args> \
ReturnType CallerName (ClassName &inst, Args && ... args);


#define GenerateMethodConstCaller(CallerName, ClassName, MethodName, ReturnType, ...) \
template<ReturnType (ClassName::*Address)( __VA_ARGS__ ) const> \
struct CallerName##_MethodConstCallerGenerator { \
    template<typename ... Args> \
    friend ReturnType CallerName (const ClassName &inst, Args && ... args) { \
        return (inst.*Address)(std::forward<Args>(args)...); \
    } \
}; \
template \
struct CallerName##_MethodConstCallerGenerator<&ClassName::MethodName>; \
template<typename ... Args> \
ReturnType CallerName (const ClassName &inst, Args && ... args);


#endif
