#pragma once
#include <iostream>
#include <string>
#include <vector>

const std::string chromatic[13] {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B", "C"};

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

std::vector<Note> notesInScale(const Note& tonic, const std::string& mode);
