#include "chshape.hpp"
#include "note.hpp"

#include <iostream>

#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

const std::vector<std::vector<int>> grf = { {4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4}, 
                                            {11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
                                            {7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7},
                                            {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2},
                                            {9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
                                            {4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4} };

std::string impl(std::vector<Note>& notes) {
    if (notes.size() > 6) return "idk";
    auto qq = std::vector<int>(notes.size());
    for (auto& u : notes) qq.push_back(u.getnum());
    std::vector<std::vector<std::pair<int, int>>> pp(6);
    for (int i = 0; i < grf.size(); i++) {
        for (int j = 0; j < grf[i].size(); j++) {
            if (std::find(qq.begin(), qq.end(), grf[i][j]) != qq.end()) pp[i].push_back(std::make_pair(grf[i][j], j));
        }
    }

    auto res = std::string();

    for (int tt = 0; tt < 9; tt++) {
        std::vector<std::vector<std::pair<int, int>>> filt(6);
        for (int i = 0; i < pp.size(); i++) {
            for (int j = 0; j < pp[i].size(); j++) {
                if (pp[i][j].second == 0 || (pp[i][j].second >= tt && pp[i][j].second < tt+4)) filt[i].push_back(pp[i][j]);
            }
        }
        for (auto& a : filt) {
            for (auto& b : a) {
                res += Note(b.first).get() + "("; 
                res += std::to_string(b.second)+")";
                res += " ";
            }
            res += "\t";
        }
        res += "\n";
    }

    return res;
}

std::string getChordShape(const std::string &name)
{
    return impl(std::vector<Note>({Note("C"), Note("E"), Note("G")}));
}
