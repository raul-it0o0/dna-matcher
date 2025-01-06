#include <random>
#include "utils.hpp"
#define MAX_ATTEMPTS 100

std::vector<std::string> getNSubstrings(const std::string& string, int count) {

    // Ensure that the count is not greater than the length of the string
    if (count > string.length()) {
        throw std::invalid_argument("Cannot generate more substrings than the length of the string.\n");
    }

    // Set up random number generator
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    // Define ranges for the random number generator
    // Since minimum length is 1, the maximum starting index is string.length() - 2
    std::uniform_int_distribution<int> substringStartIndexDistribution(0, (string.length() - 2));
    std::uniform_int_distribution<int> substringLengthDistribution(1, (string.length() / count));

    // Store substrings
    std::vector<std::string> substrings;
    // Keep track of used indices (used to avoid overlapping substrings). Set all to false initially
    std::vector<bool> isUsed(string.length(), false);

    int attempts = 0;
    while (substrings.size() < count && attempts < MAX_ATTEMPTS) {
        attempts++;

        // Generate random starting index and length
        int start = substringStartIndexDistribution(generator);
        int length = substringLengthDistribution(generator);
        int end = start + length;

        // If substring exceeds bounds, try again
        if (end > string.length()) continue;

        for (int i = start; i < end; i++) {
            // If index is part of another substring, try again
            if (isUsed[i]) continue;
        }

        // At this point,
        // the generated substring is of valid length
        // and all its indices are not part of another substring

        // Mark indices as used
        for (int i = start; i < end; i++) {
            isUsed[i] = true;
        }

        // Add substring to list
        substrings.push_back(string.substr(start, length));

    }

    if (attempts > MAX_ATTEMPTS) {
        throw std::runtime_error(
                "Generated only" + std::to_string(substrings.size()) + " substrings out of " + std::to_string(count) + " after " + std::to_string(MAX_ATTEMPTS) + " attempts.\n");
    }

    return substrings;
}
