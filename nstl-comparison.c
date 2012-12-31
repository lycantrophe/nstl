#include "nstl-comparison.h"

unsigned short int_lt( void* lhs, void* rhs ) {
    return *(int*)lhs < *(int*)rhs;
}

unsigned short uint_lt( void* lhs, void* rhs ) {
    return *(unsigned int*)lhs < *(unsigned int*)rhs;
}

unsigned short long_lt( void* lhs, void* rhs ) {
    return *(long*)lhs < *(long*)rhs;
}

unsigned short longlong_lt( void* lhs, void* rhs ) {
    return *(long long*)lhs < *(long long*)rhs;
}

unsigned short char_lt( void* lhs, void* rhs ) {
    return *(char*)lhs < *(char*)rhs;
}

unsigned short double_lt( void* lhs, void* rhs ) {
    return *(double*)lhs < *(double*)rhs;
}

unsigned short float_lt( void* lhs, void* rhs ) {
    return *(float*)lhs < *(float*)rhs;
}
