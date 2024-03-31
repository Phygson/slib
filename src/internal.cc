#include "internal.hpp"

int nnn(const std::string& t) {

    if (t.length() > 3 || t.length() == 0) return -2;

    int o = 0;
    switch(t[0]) {
        case 'C': o = 0;  break;
        case 'D': o = 2;  break;
        case 'E': o = 4;  break;
        case 'F': o = 5;  break;
        case 'G': o = 7;  break;
        case 'A': o = 9;  break;
        case 'B': o = 11; break;
        default:  return -1; break;
    }
    for (auto& x : t) {
        if (x == '#') o += 1;
        else if (x == 'b') o -= 1;
    }

    o = (o + 12) % 12;
    return o;
}

std::string nnote(int n) {
    n = (n+24) % 12;
    return chromatic[n];
}