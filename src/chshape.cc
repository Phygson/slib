#include "chshape.hpp"
#include "note.hpp"

#include <string>
#include <vector>
#include <algorithm>

constexpr int frets = 13;
constexpr int width = 4;

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
        if (b.first == -1) c++;
    }
    return c;
}

inline int countZeroed(const std::vector<std::pair<int, int>>& a) {
    int c = 0;
    for (auto& b : a) {
        if (b.second == 0 && b.first != -1) c++;
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

std::string impl(std::vector<Note>& notes) {
    if (notes.size() > 6) return "idk";
    std::vector<int> qq;
    qq.reserve(notes.size());
    for (auto& u : notes) qq.push_back(u.getnum());
    std::vector<std::vector<std::pair<int, int>>> pp(6);
    for (int i = 0; i < grf.size(); i++) {
        for (int j = 0; j < grf[i].size(); j++) {
            if (std::find(qq.begin(), qq.end(), grf[i][j]) != qq.end() || j == 0) pp[i].push_back(std::make_pair(grf[i][j], j));
        }
    }

    auto res = std::string();
    std::vector<std::vector<std::pair<int, int>>> sk;
    for (int tt = 0; tt < frets - width + 1; tt++) {
        std::vector<std::vector<std::pair<int, int>>> filt(6);
        for (int i = 0; i < pp.size(); i++) {
            for (int j = 0; j < pp[i].size(); j++) {
                if (pp[i][j].second == 0 || (pp[i][j].second >= tt && pp[i][j].second < tt+width)) {
                    if (std::find(qq.begin(), qq.end(), pp[i][j].first) != qq.end()) filt[i].push_back(pp[i][j]);
                    else filt[i].push_back(std::make_pair(-1, 0));
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
                    else a.first = -1;
                }
                if (!dmetB) break;
            }
        }

        getAllCombinations(qq, filt, sk);
    }
    std::sort(sk.begin(), sk.end(), [](const std::vector<std::pair<int, int>> &a, const std::vector<std::pair<int, int>> &b)
    { 
    return countMuted(a) < countMuted(b); 
    });
    sk.erase( unique( sk.begin(), sk.end() ), sk.end() );

    for (auto& a : sk) {
            for (auto& b : a) {
                if (b.first == -1) { res += "X ";}
                else {
                    res += std::to_string(b.second) + " "; 
                }
            }
            res += "\n";
        }

    return res;
}

std::string getChordShape(const std::string &name)
{
    return impl(std::vector<Note>({Note("G"), Note("A#"), Note("D")}));
}
