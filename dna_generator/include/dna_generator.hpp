#include <iostream>
#include <fstream>
#include <random>
#include <filesystem>
#define MIN_SEQUENCE_LENGTH 500
#define MIN_PATTERN_LENGTH 3
#define MAX_SEQUENCE_LENGTH 1000

/**
 * Returns a random boolean value.
 *
 * @param generator The generator to use for random generation
 */
bool getTrueOrFalse(std::mt19937& generator);

/**
 * Returns a random nucleotide (A, C, G, or T).
 * @param generator The generator to use for random generation
 * @return
 */
char getRandomNucleotide(std::mt19937& generator);

/**
 * Processes the user-given <b>fileName</b> to get the paths to the files to write to.
 * @param fileName The user-given file name to use for the files
 * @return An <b>std::pair</b> of <b>std::filesystem::path</b> objects,
 * one being the path to file to write the DNA sequence to,
 * and the other being the path to the file to write the patterns to.
 */
inline std::pair<std::filesystem::path, std::filesystem::path>
getFilePaths(std::string& fileName);

/**
 * Generates a random DNA sequence and writes it to a file.
 * @param fileName The name of the file to write the DNA sequence to.
 */
void generateAndWriteDNASequence(std::string &fileName, bool generatePatterns = false);