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
    std::vector<std::pair<int, int>> grf2;
    std::copy(grf.begin(), grf.end(), std::back_inserter(grf2));
    for (auto& u : grf2) {
        for (auto& uu : u) {
            if (std::find(qq.begin(), qq.end(), uu) == qq.end()) uu = -1;
        }
    } 

    std::stringstream result;
    std::copy(grf2[0].begin(), grf2[0].end(), std::ostream_iterator<int>(result, " "));
    result << "\n";
    std::copy(grf2[1].begin(), grf2[1].end(), std::ostream_iterator<int>(result, " "));
    result << "\n";
    std::copy(grf2[2].begin(), grf2[2].end(), std::ostream_iterator<int>(result, " "));
    result << "\n";
    std::copy(grf2[3].begin(), grf2[3].end(), std::ostream_iterator<int>(result, " "));
    result << "\n";
    std::copy(grf2[4].begin(), grf2[4].end(), std::ostream_iterator<int>(result, " "));
    result << "\n";
    std::copy(grf2[5].begin(), grf2[5].end(), std::ostream_iterator<int>(result, " "));
    result << "\n";

    return result.str();
}

std::string getChordShape(const std::string &name)
{
    return impl(std::vector<Note>({Note("C"), Note("E"), Note("G"), Note("B")}));
}
