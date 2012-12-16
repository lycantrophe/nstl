#include "nstl-comparison.h"

unsigned short int_lt( void* lhs, void* rhs ) {
    return *(int*)lhs < *(int*)rhs;
}

unsigned short int_lt( void* lhs, void* rhs ) {
    return *(unsigned int*)lhs < *(unsigned int*)rhs;
}

unsigned short int_lt( void* lhs, void* rhs ) {
    return *(long*)lhs < *(long*)rhs;
}

unsigned short int_lt( void* lhs, void* rhs ) {
    return *(long long*)lhs < *(long long*)rhs;
}

unsigned short int_lt( void* lhs, void* rhs ) {
    return *(char*)lhs < *(char*)rhs;
}

unsigned short int_lt( void* lhs, void* rhs ) {
    return *(double*)lhs < *(double*)rhs;
}

unsigned short int_lt( void* lhs, void* rhs ) {
    return *(unsigned double*)lhs < *(unsigned double*)rhs;
}

unsigned short int_lt( void* lhs, void* rhs ) {
    return *(float*)lhs < *(float*)rhs;
}
