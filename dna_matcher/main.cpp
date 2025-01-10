#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "dna_matcher.hpp"
#include <iomanip>

int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <text file DNA patterns>.txt ";
        std::cerr << " <file containing target DNA sequence>.txt " << std::endl;
        return 1;
    }

    std::set<std::string> patterns;
    std::string targetDNASequence;
    std::string line;

    // Attempt to open the DNA patterns file
    // If the file does not contain patterns,
    //  the behaviour is undefined

    std::ifstream patternFile(argv[1]);
    if (patternFile.is_open()) {
        // Read the patterns and store them in a vector
        while (getline(patternFile, line)) {
            patterns.insert(line);
        }
        patternFile.close();


    }
    else {
        std::cerr << "Unable to open patterns file. " << std::endl;
        return 1;
    }

    // Attempt to open the subject DNA file
    std::ifstream subjectFile(argv[2]);
    if (subjectFile.is_open()) {
        // Read the parent DNA file and store it in parentDNA
        while (getline(subjectFile, line)) {
            targetDNASequence += line;
        }
        subjectFile.close();

    }
    else {
        std::cerr << "Unable to open target DNA file. " << std::endl;
        return 1;
    }

    int matches = pattern_matches(targetDNASequence, patterns);
    int numPatterns = patterns.size();

    // Output the match percentage
    std::cout << argv[2] << " matched " << matches << " patterns out of " << numPatterns << std::endl;
    std::cout << std::setprecision(2) << ((float)matches / numPatterns) * 100 << "% match." << std::endl;

    return 0;
}
