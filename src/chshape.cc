#include "chshape.hpp"
#include "note.hpp"

#include <string>
#include <vector>
#include <algorithm>
#include <set>

constexpr int frets = 8;
constexpr int width = 4;
constexpr int returnFirstN = 1;

const std::vector<std::vector<int>> grf = { {4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4}, 
                                            {11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                                            {7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7},
                                            {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2},
                                            {9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
                                            {4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4} };

bool areAllNotesPresent(const std::vector<int>& notes, const std::vector<std::pair<int,int>>& chord) {
    for (auto a : notes) {
            int cc = 0;
            for (auto c : chord) {
                //for (auto& c : b) {
                    if (c.first == a) cc += 1;
                //}
            }
            if (cc == 0) { return false; }
        }
    return true;
}

bool noMidMute(const std::vector<std::pair<int,int>>& chord) {
    int sw = 0;
    char lat = 'x';
    for (auto& a : chord) {
        if (a.first == -1 && lat == '+') sw++;
        if (a.first != -1 && lat == 'x') sw++;
        lat = (a.first == -1 ? 'x' : '+');
    }
    return sw <= 2;
}

inline int countMuted(const std::vector<std::pair<int, int>>& a) {
    int c = 0;
    for (auto& b : a) {
        if (b.first < 0 || b.second < 0) c++;
    }
    return c;
}

inline int countZeroed(const std::vector<std::pair<int, int>>& a) {
    int c = 0;
    for (auto& b : a) {
        if (b.second == 0 && b.first >= 0) c++;
    }
    return c;
}

bool poss(const std::vector<std::pair<int, int>>& chord) {
    auto cz = countZeroed(chord);
    auto cm = countMuted(chord);
    if (countMuted(chord) >= 2) return true;
    if (cz != 0) {
        if (6 - cz - cm <= 4) return true;
        else return false;
    } else {
        auto cop = chord;
        while (countZeroed(cop) == 0) {
            for (auto& c : cop) c.second -= 1;
        }
        if (6 - countZeroed(cop) - cm <= 3) return true;
        else return false;
    }
}

void getAllCombinations(const std::vector<int>& notes, const std::vector<std::vector<std::pair<int,int>>>& filt, std::vector<std::vector<std::pair<int, int>>>& sk) {
    for (auto& a : filt[0]) {
        for (auto& b : filt[1]) {
            for (auto& c : filt[2]) {
                for (auto& d : filt[3]) {
                    for (auto& e : filt[4]) {
                        for (auto& f : filt[5]) {
                            std::vector<std::pair<int,int>> chord {a, b, c, d, e, f};
                            if (areAllNotesPresent(notes, chord) && noMidMute(chord) && poss(chord)) sk.push_back(chord);
                        }
                    }                
                }
            }      
        }
    }
}

std::vector<std::vector<int>> impl(std::vector<Note>& notes) {
    if (notes.size() > 6) return {};
    std::vector<int> qq;
    qq.reserve(notes.size());
    for (auto& u : notes) qq.push_back(u.getnum());
    std::vector<std::vector<std::pair<int, int>>> pp(6);
    for (int i = 0; i < grf.size(); i++) {
        for (int j = 0; j < grf[i].size(); j++) {
            if (std::find(qq.begin(), qq.end(), grf[i][j]) != qq.end() || j == 0) pp[i].push_back(std::make_pair(grf[i][j], j));
        }
    }

    std::vector<std::vector<std::pair<int, int>>> sk;
    for (int tt = 0; tt < frets - width + 1; tt++) {
        std::vector<std::vector<std::pair<int, int>>> filt(6);
        for (int i = 0; i < pp.size(); i++) {
            for (int j = 0; j < pp[i].size(); j++) {
                if (pp[i][j].second == 0 || (pp[i][j].second >= tt && pp[i][j].second < tt+width)) {
                    if (std::find(qq.begin(), qq.end(), pp[i][j].first) != qq.end()) filt[i].push_back(pp[i][j]);
                    else filt[i].push_back(std::make_pair(-1, -1));
                }
            }
        }

        {
            bool dmetB = true;
            for (int i = 5; i != 0; i--) {
                for (auto& a : filt[i]) {
                    if (a.first == notes[0].getnum()) { 
                        dmetB = false;
                        filt[i] = std::vector<std::pair<int, int>>({a});
                        break; 
                        }
                    else { a.first = -1; a.second = -1; }
                }
                if (!dmetB) break;
            }
        }
        getAllCombinations(qq, filt, sk);
    }
    
    std::sort(sk.begin(), sk.end(), [](const std::vector<std::pair<int, int>> &a, const std::vector<std::pair<int, int>> &b)
    { 
        if (countMuted(a) < countMuted(b)) {
            return true;
        } else if (countMuted(a) == countMuted(b)) {
            return countZeroed(a) < countZeroed(b);
        } else {
            return false;
        }
    });

    std::vector<std::vector<int>> sk2;
    for (auto& a : sk) {
        std::vector<int> t;
        for (auto& b : a) {
            t.push_back(b.second);
        }
        sk2.push_back(t);
    }

    sk2.erase( unique( sk2.begin(), sk2.end() ), sk2.end() );

    auto zem = std::find_if(sk2.begin(), sk2.end(), [&](const std::vector<int> &a)
    { 
        return std::count(a.begin(), a.end(), -1) == 0;
    });
    auto onm = std::find_if(sk2.begin(), sk2.end(), [&](const std::vector<int> &a)
    { 
        return std::count(a.begin(), a.end(), -1) == 1 && a[5] == -1;
    });
    auto twm = std::find_if(sk2.begin(), sk2.end(), [&](const std::vector<int> &a)
    { 
        return std::count(a.begin(), a.end(), -1) == 2 && a[5] == -1 && a[4] == -1;
    });
    auto thm = std::find_if(sk2.begin(), sk2.end(), [&](const std::vector<int> &a)
    { 
        return std::count(a.begin(), a.end(), -1) == 3 && a[5] == -1 && a[4] == -1 && a[3] == -1;
    });

    decltype(sk2) ret;
    if (zem != sk2.end()) ret.push_back(*zem);
    if (onm != sk2.end()) ret.push_back(*onm);
    if (twm != sk2.end()) ret.push_back(*twm);
    if (thm != sk2.end()) ret.push_back(*thm);

    return ret;
}

std::string getChordShape(const std::string &name)
{
    std::string res = "";
    auto tt = impl(std::vector<Note>({Note("C"), Note("E"), Note("G"), Note("Bb")}));
    for (auto& a : tt) {
        for (auto&b : a) {
            res += (b != -1 ? std::to_string(b) + " " : "x ");
        }
        res.pop_back();
        res += "\n";
    }
    res.pop_back();
    return res;
}
