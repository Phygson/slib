#pragma once
#include "note.hpp"

std::vector<Note> notesInScale(const Note& tonic, const std::string& mode);
std::vector<std::string> chordsInScale(const Note& tonic, const std::string& mode);