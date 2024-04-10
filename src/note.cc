#include "note.hpp"

const std::string chromatic[13] {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B", "C"};

Note::Note(int n) {
    _i = (n + 48) % 12;
    _s = chromatic[_i];
    if (_s.length() > 1) state = 1;
}

Note::Note(const std::string &s) {
    _s = s;
    if (s.length() > 3 || s.length() == 0) _s = "";

    int o = 0;
    switch(s[0]) {
        case 'C': o = 0;  break;
        case 'D': o = 2;  break;
        case 'E': o = 4;  break;
        case 'F': o = 5;  break;
        case 'G': o = 7;  break;
        case 'A': o = 9;  break;
        case 'B': o = 11; break;
        default: break;
    }
    auto q = s.substr(1);

    if (q != "") {
        if (q == "b") state = -1;
        else if (q == "bb") state = -2;
        else if (q == "#") state = 1;
        else if (q == "##") state = 2;
        else _s = "";
    }

    o += state;

    _i = (o + 12) % 12;
}

int Note::getnum() const
{
    return _i;
}

std::string Note::get() const
{
    return _s;
}

Note Note::flattened() const
{
    const std::string r[12] = { "", "Db", "", "Eb",
                   "Fb", "", "Gb", "",
                   "Ab", "", "Bb", "Cb" };
    return r[_i] == "" ? _s : r[_i];
}

Note Note::dflattened() const
{
    const std::string r[12] = { "Dbb", "", "Ebb", "Fbb",
                   "", "Gbb", "", "Abb",
                   "", "Bbb", "Cbb", "" };
    return r[_i] == "" ? _s : r[_i];
}

Note Note::sharpened() const
{
    const std::string r[12] = { "B#", "C#", "", "D#",
                   "", "E#", "F#", "",
                   "G#", "", "A#", "" };
    return r[_i] == "" ? _s : r[_i];
}

Note Note::dsharpened() const
{
   const std::string r[12] = { "", "B##", "C##", "",
                   "D##", "", "E##", "F##",
                   "", "G##", "", "A##" };
    return r[_i] == "" ? _s : r[_i];
}

Note Note::flat() const
{
    auto t = Note(_i - 1);
    switch(state) {
        case -2: return t.dflattened();
        case -1: return t.dflattened();
        case 0: return t.flattened();
        case 1: return t;
        case 2: return t.sharpened();
        default: return t;
    }
}

Note Note::dflat() const
{
    return Note(_i - 2).dflattened();
}

Note Note::sharp() const
{
    auto t = Note(_i + 1);
    switch(state) {
        case -2: return t.flattened();
        case -1: return t;
        case 0: return t.sharpened();
        case 1: return t.dsharpened();
        case 2: return t.dsharpened();
        default: return t;
    }
}

Note Note::dsharp() const
{
    return Note(_i + 2).dsharpened();
}

int Note::interval(Note to) const
{
    return (to.getnum() - _i + 12) % 12;
}

Note Note::add(int interval) const
{
    return Note(_i + interval);
}
