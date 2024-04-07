#include "chshape.hpp"
#include "note.hpp"

#include <string>
#include <vector>

constexpr int frets = 12;
constexpr int width = 4;

const std::vector<std::vector<int>> grf = { {4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4}, 
                                            {11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                                            {7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7},
                                            {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2},
                                            {9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
                                            {4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4} };

std::string impl(std::vector<Note>& notes) {
    if (notes.size() > 6) return "idk";
    std::vector<int> qq;
    qq.reserve(notes.size());
    for (auto& u : notes) qq.push_back(u.getnum());
    std::vector<std::vector<std::pair<int, int>>> pp(6);
    for (int i = 0; i < grf.size(); i++) {
        for (int j = 0; j < grf[i].size(); j++) {
            if (std::find(qq.begin(), qq.end(), grf[i][j]) != qq.end()) pp[i].push_back(std::make_pair(grf[i][j], j));
        }
    }

    auto res = std::string();
    for (int tt = 0; tt < frets - width + 1; tt++) {
gtend:
        res += "Frets " + std::to_string(tt) + " to " + std::to_string(tt+width-1) + ": ";
        std::vector<std::vector<std::pair<int, int>>> filt(6);
        std::string mtst = "x";
        int sw = 0;
        for (int i = 0; i < pp.size(); i++) {
            std::vector<int> nna;
            for (int j = 0; j < pp[i].size(); j++) {
                if (pp[i][j].second == 0 || (pp[i][j].second >= tt && pp[i][j].second < tt+width)) {
                    filt[i].push_back(pp[i][j]);
                }
            }
            if (filt[i].empty()) {
                if (mtst.back() == '+') sw++;
                mtst += "x";
            }
            if (!filt[i].empty()) {
                if (mtst.back() == 'x') sw++;
                mtst += "+";
            }
        }
        if (sw > 2) { res += "\n"; tt++; goto gtend; }

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

        for (auto a : qq) {
            int cc = 0;
            for (auto& b : filt) {
                for (auto& c : b) {
                    if (c.first == a) cc += 1;
                }
            }
            if (cc == 0) { res += "\n"; tt++; goto gtend; }
        }

        for (auto& a : filt) {
            if (a.empty()) res += "X";
            for (auto& b : a) {
                if (b.first == -1) { res += "X"; break; }
                else {
                    res += Note(b.first).get() + "("; 
                    res += std::to_string(b.second)+")";
                    res += " ";
                }
            }
            res += "\t\t";
        }
        res += "\n";
    }

    return res;
}

std::string getChordShape(const std::string &name)
{
    return impl(std::vector<Note>({Note("C"), Note("E"), Note("G"), Note("Bb")}));
}
