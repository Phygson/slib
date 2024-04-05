#include "internal.hpp"

// FNV-1a hash, 32-bit 
inline constexpr std::uint32_t fnv1a(const char* str, std::uint32_t hash = 2166136261UL) {
    return *str ? fnv1a(str + 1, (hash ^ *str) * 16777619ULL) : hash;
}


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
    std::string r[12] = { "", "Db", "", "Eb",
                   "Fb", "", "Gb", "",
                   "Ab", "", "Bb", "Cb" };
    return r[_i] == "" ? _s : r[_i];
}

Note Note::dflattened() const
{
    std::string r[12] = { "Dbb", "", "Ebb", "Fbb",
                   "", "Gbb", "", "Abb",
                   "", "Bbb", "Cbb", "" };
    return r[_i] == "" ? _s : r[_i];
}

Note Note::sharpened() const
{
    std::string r[12] = { "B#", "C#", "", "D#",
                   "", "E#", "F#", "",
                   "G#", "", "A#", "" };
    return r[_i] == "" ? _s : r[_i];
}

Note Note::dsharpened() const
{
   std::string r[12] = { "", "B##", "C##", "",
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

std::vector<Note> notesInScale(const Note& tonic, const std::string &mode)
{
    std::vector<Note> qq {7};
    auto tt = tonic.get();
    if (tt.length() == 3) return {};
    switch(tt[0]) {
        case 'C': qq = {Note("C"), Note("D"),  Note("E"),  Note("F"),  Note("G"),  Note("A"),  Note("B")}; break;
        case 'D': qq = {Note("D"), Note("E"),  Note("F#"), Note("G"),  Note("A"),  Note("B"),  Note("C#")}; break;
        case 'E': qq = {Note("E"), Note("F#"), Note("G#"), Note("A"),  Note("B"),  Note("C#"), Note("D#")}; break;
        case 'F': qq = {Note("F"), Note("G"),  Note("A"),  Note("Bb"), Note("C"),  Note("D"),  Note("E")}; break;
        case 'G': qq = {Note("G"), Note("A"),  Note("B"),  Note("C"),  Note("D"),  Note("E"),  Note("F#")}; break;
        case 'A': qq = {Note("A"), Note("B"),  Note("C#"), Note("D"),  Note("E"),  Note("F#"), Note("G#")}; break;
        case 'B': qq = {Note("B"), Note("C#"), Note("D#"), Note("E"),  Note("F#"), Note("G#"), Note("A#")}; break;
    };
    if (tt.length() == 2) switch(tt[1]) {
        case '#': for (auto& a : qq) a = a.sharp(); break;
        case 'b': for (auto& a : qq) a = a.flat();  break;
    };
    switch (fnv1a(mode.data())) {
        case fnv1a("Lyd"): qq[3] = qq[3].sharp(); return qq;
        case fnv1a("Ion"): return qq;
        case fnv1a("Mixolyd"): qq[6] = qq[6].flat(); return qq;
        case fnv1a("Dor"): qq[2] = qq[2].flat(); qq[6] = qq[6].flat(); return qq;
        case fnv1a("Aeo"): qq[2] = qq[2].flat(); qq[5] = qq[5].flat(); qq[6] = qq[6].flat(); return qq;
        case fnv1a("Phy"): qq[1] = qq[1].flat(); qq[2] = qq[2].flat(); qq[5] = qq[5].flat(); qq[6] = qq[6].flat(); return qq;
        case fnv1a("Loc"): qq[1] = qq[1].flat(); qq[2] = qq[2].flat(); qq[4] = qq[4].flat(); qq[5] = qq[5].flat(); qq[6] = qq[6].flat(); return qq;
        default: return {};
    }
}
