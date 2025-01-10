#include "dna_generator.hpp"

bool getTrueOrFalse(std::mt19937& generator) {
    std::bernoulli_distribution boolDistribution(0.5);
    return boolDistribution(generator);
}

char getRandomNucleotide(std::mt19937& generator) {
    std::uniform_int_distribution<int> nucleotideDistribution(0, 3);
    int nucleotide = nucleotideDistribution(generator);
    switch (nucleotide) {
        case 0:
            return 'A';
        case 1:
            return 'C';
        case 2:
            return 'G';
        case 3:
            return 'T';
    }
}

inline std::pair<std::filesystem::path, std::filesystem::path>
getFilePaths(std::string& fileName) {

    // The generated sequence itself will be stored in data/fileName.txt
    std::filesystem::path fileDir = std::filesystem::current_path().parent_path() / "data";

    if (!std::filesystem::exists(fileDir)) {
        std::filesystem::create_directory(fileDir);
    }

    std::string patternFileName = fileName;

    if (std::filesystem::path(fileName).extension().string() != ".txt") {
        fileName.append(".txt");
        patternFileName.append("_patterns.txt");
    }
    else {
        patternFileName = fileName.substr(0, fileName.length() - 4) + "_patterns.txt";
    }

    return std::make_pair(fileDir / fileName, fileDir / patternFileName);
}

void generateAndWriteDNASequence(std::string &fileName, bool generatePatterns) {

    // Open files to write in
    std::pair<std::filesystem::path, std::filesystem::path> filePaths = getFilePaths(fileName);
    std::ofstream sequenceFile(filePaths.first);
    // Make sure the file is open
    if (!sequenceFile.is_open()) {
        std::cerr << "Unable to open file to write DNA sequence to." << std::endl;
        return;
    }

    // If the user has chosen to generate patterns along with the DNA sequence,
    // open the file to write the patterns to.
    std::ofstream patternFile;
    if (generatePatterns) {
        patternFile.open(filePaths.second);
        // Make sure the file is open
        if (!patternFile.is_open()) {
            std::cerr << "Unable to open file to write patterns to." << std::endl;
            return;
        }
    }

    // Setup random number generators and distributions
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<int> sequenceLengthDistribution(MIN_SEQUENCE_LENGTH, MAX_SEQUENCE_LENGTH);
    std::uniform_int_distribution<int> nucleotideDistribution(0, 3);

    // Generate random sequence length
    int sequenceLength = sequenceLengthDistribution(generator);

    std::string subsequence;

    // Generate random nucleotide sequence
    for (int i = 0; i < sequenceLength; i++) {

        char nucleotide = getRandomNucleotide(generator);
        sequenceFile << nucleotide;

        // If user has not chosen to generate patterns along with the DNA sequence,
        // continue purely with the nucleotide generation and writing.
        if (!generatePatterns) continue;

        // Pattern generation logic from this point on
        if (subsequence.length() == 0) {
            // Decide if this will be the beginning of a subsequence/pattern
            if(getTrueOrFalse(generator) == true) {
                // Start subsequence/pattern
                subsequence += nucleotide;
            }
        }
        else {
            // Already in a subsequence/pattern
            // If subsequence/pattern meets minimum length,
            if (subsequence.length() >= MIN_PATTERN_LENGTH) {
                // Decide if this will be the end of the subsequence
                if (getTrueOrFalse(generator) == true) {
                    // Write subsequence/pattern to the file
                    patternFile << subsequence << std::endl;
                    // Empty the substring storing the current subsequence/pattern
                    subsequence.clear();
                }
                else {
                    // Continue subsequence
                    subsequence += nucleotide;
                }
            }
            else {
                // Subsequence/pattern has not met minimum length
                // Continue subsequence
                subsequence += nucleotide;
            }
        }
    }

    sequenceFile.close();

    // Close the pattern file if it was opened
    if (generatePatterns)
        patternFile.close();

}
