#pragma once
#include <iostream>
#include <string>
#include <vector>

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
    Note add(int interval) const;
private:
    int _i = 0;
    std::string _s = "";
    int state = 0;
};
