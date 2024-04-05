#pragma once
#include <iostream>
#include <string>
#include <vector>

const std::string chromatic[13] {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B", "C"};

const std::string cmaj[7] {"C", "D", "E", "F", "G", "A", "B"};
const std::string dmaj[7] {"D", "E", "F#", "G", "A", "B", "C#"};
const std::string emaj[7] {"E", "F#", "G#", "A", "B", "C#", "D#"};
const std::string fmaj[7] {"F", "G", "A", "Bb", "C", "D", "E"};
const std::string gmaj[7] {"G", "A", "B", "C", "D", "E", "F#"};
const std::string amaj[7] {"A", "B", "C#", "D", "E", "F#", "G#"};
const std::string bmaj[7] {"B", "C#", "D#", "E", "F#", "G#", "A#"};

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
