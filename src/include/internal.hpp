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

class Note {
public:
    bool is_ok() { return _s != ""; };
    Note() = default;
    Note(const int n);
    Note(const std::string& s);



    int getnum() const;
    std::string get() const;
    Note flattened() const;
    Note dflattened() const;
    Note sharpened() const;
    Note dsharpened() const;

    Note flat() const;
    Note dflat() const;
    Note sharp() const;
    Note dsharp() const;

    int interval(Note to) const;
private:
    int _i = 0;
    std::string _s = "";
    int state = 0;
};