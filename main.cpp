#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "utils.hpp"

int main(int argc, char* argv[]) {

    // Seed random number generator
    srand(time(nullptr));

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <child DNA source text file> ";
        std::cerr << " <potential parent DNA source text file> " << std::endl;
        return 1;
    }

    std::string childDNA;
    std::string parentDNA;
    std::string line;

    // Attempt to open the child DNA file
    std::ifstream childFile(argv[1]);
    if (childFile.is_open()) {
        // Read the child DNA file and store it in childDNA
        while (getline(childFile, line)) {
            childDNA += line;
        }
        childFile.close();

        // NOTE: DEBUG
        std::cout << "Finished reading child DNA file. " << std::endl;

    }
    else {
        std::cerr << "Unable to open child DNA file. " << std::endl;
        return 1;
    }

    // Attempt to open the parent DNA file
    std::ifstream parentFile(argv[2]);
    if (parentFile.is_open()) {
        // Read the parent DNA file and store it in parentDNA
        while (getline(parentFile, line)) {
            parentDNA += line;
        }
        parentFile.close();

        // NOTE: DEBUG
        std::cout << "Finished reading parent DNA file. " << std::endl;

    }
    else {
        std::cerr << "Unable to open parent DNA file. " << std::endl;
        return 1;
    }

    // Randomly choose patterns from the child DNA to search for in the parent DNA

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    // Define the distribution (range) for the number of patterns to search for
    std::uniform_int_distribution<int> patternNumberDistribution(1, childDNA.length());
    // Randomly decide how many patterns to search for
    int numPatterns = patternNumberDistribution(generator);

    // Get the patterns from the child DNA to search for in the parent DNA
    std::vector<std::string> patterns = getNSubstrings(childDNA, numPatterns);

    // TODO: Make Algo-Corasick function return int (number of matches)
    // (matches/numPatterns) * 100 = % of child DNA found in parent DNA
    // If % > 50, print "The child DNA is likely to be the parent DNA"
    // Else, print "The child DNA is unlikely to be the parent DNA"

    std::vector<std::string> DNApatterns;
    for (int i = 0; i < 5; i++) {
        int start = rand() % childDNA.length();
        int length = rand() % (childDNA.length() - start) + 1;
        DNApatterns.push_back(childDNA.substr(start, length));
    }



}
