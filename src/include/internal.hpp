#pragma once
#include <iostream>
#include <string>

const std::string chromatic[13] {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B", "C"};

constexpr int maj[15] {0, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1};
constexpr int dor[15] {0, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 2};
constexpr int phy[15] {0, 1, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 2};
constexpr int lyd[15] {0, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1};
constexpr int mix[15] {0, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2};
constexpr int min[15] {0, 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 2};
constexpr int loc[15] {0, 1, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2};

int nnn(const std::string& t);
std::string nnote(int n);