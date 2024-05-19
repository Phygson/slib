#include "scales.hpp"
#include <cstdint>
// FNV-1a hash, 32-bit 
inline constexpr std::uint32_t fnv1a(const char* str, std::uint32_t hash = 2166136261UL) {
    return *str ? fnv1a(str + 1, (hash ^ *str) * 16777619ULL) : hash;
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

std::vector<std::string> chordsInScale(const Note &tonic, const std::string &mode)
{
    std::vector<std::string> r {7};

    auto qq = notesInScale(Note(tonic), mode);
    qq.push_back(qq[0]);
    qq.push_back(qq[1]);
    qq.push_back(qq[2]);
    qq.push_back(qq[3]);

    for (int i = 0; i < 7; i++) {
        r[i] += qq[i].get();
        if (qq[i].interval(qq[i+4]) == 6) { r[i] += "dim"; continue; }
        if (qq[i].interval(qq[i+2])==3) r[i] += "m";
        
    };

    return r;
}
