#include "ffc.hpp"
#include "scales.hpp"

// FNV-1a hash, 32-bit 
inline constexpr std::uint32_t fnv1a(const char* str, std::uint32_t hash = 2166136261UL) {
    return *str ? fnv1a(str + 1, (hash ^ *str) * 16777619ULL) : hash;
}

const std::string romanmaj[7] = {"I", "II", "III", "IV", "V", "VI", "VII"};
const std::string romanmin[7] = {"i", "ii", "iii", "iv", "v", "vi", "vii"};

int modeToOffset(const std::string& mode) {
    switch (fnv1a(mode.data())) {
        case fnv1a("Lyd"):     return 0;
        case fnv1a("Ion"):     return 1;
        case fnv1a("Mixolyd"): return 2;
        case fnv1a("Dor"):     return 3;
        case fnv1a("Aeo"):     return 4;
        case fnv1a("Phy"):     return 5;
        case fnv1a("Loc"):     return 6;
        default: return 0;
    }
}

std::vector<int> scaleSteps(int offset) {
    const std::vector<int> d = {1, 5, 2, 6, 3, 7, 4};
    auto t = std::vector<int>(d.begin() + 7 - offset, d.end());
    for (int i = 0; i < 7 - offset; i++) {
        t.push_back(d[i]);
    }
    return t;
}

std::vector<std::string> getRomanScale(const Note &tonic, const std::string &mode)
{
    auto r = std::vector<std::string>(7);

    auto ss = scaleSteps(modeToOffset(mode));
    for (int i = 0; i < 7; i++) {
        if (i < 3) r[i] = romanmaj[ss[i]-1];
        else if (i > 2 && i < 6) r[i] = romanmin[ss[i]-1];
        else r[i] = romanmin[ss[i]-1] + "d";
    }
    return r;
}
