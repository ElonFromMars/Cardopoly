#pragma once

#include <cstdint>
#include <iostream>
using namespace std;

template <typename T>
class unique_id {
    static char type_id;
public:
    static uintptr_t get_ID() { return reinterpret_cast<uintptr_t>(&type_id); }
};

template <typename T>
char unique_id<T>::type_id;