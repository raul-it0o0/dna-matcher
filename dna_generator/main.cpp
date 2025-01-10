#include <iostream>
#include <string>
#include <getopt.h>
#include "dna_generator.hpp"

int main(int argc, char* argv[]) {

    // Argument validation
    if (argc != 3 && argc != 2) {
        std::cerr << "Usage: <executable> [-p] <output file name>" << std::endl;
        std::cerr << "-p : Generate patterns along with the DNA sequence." << std::endl;
        return 1;
    }

    bool generatePatterns = false;

    // Parse optional argument -p
    int opt;
    while ((opt = getopt(argc, argv, "p")) != -1) {
        switch (opt) {
            case 'p':
                generatePatterns = true;
                break;
            case '?':  // Handle unknown options
                std::cerr << "Unknown option: " << optopt << std::endl;
                std::cerr << "Usage: <executable> [-p] <output file name>" << std::endl;
                std::cerr << "-p : Generate patterns along with the DNA sequence." << std::endl;
                return 1;
        }
    }

    if (generatePatterns) {
        std::string fileName = std::string(argv[2]);
        generateAndWriteDNASequence(fileName, true);
    }
    else {
        std::string fileName = std::string(argv[1]);
        generateAndWriteDNASequence(fileName);
    }

}


