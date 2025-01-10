#include <iostream>
#include <vector>
#include "TrieTree.hpp"

/**
 * Search for matches from <b>patterns</b> in <b>text</b>
 * @param text The text to search in
 * @param patterns The patterns to search for
 * @return The number of patterns matched (found in the file)
 */
int pattern_matches(const std::string &text, const std::set<std::string> &patterns);