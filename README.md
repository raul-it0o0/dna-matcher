
# DNA Matcher

DNA Matcher is a small command-line application written in C++, which allows determining the similarity of two DNA sequences (i.e. sequences of nucleotides).

It also features a small tool to generate the DNA sequences (and optionally, the patterns that will be used during the matching process) that will be compared.


## Features

- Generating a DNA sequence, of length customizable within the source code
- Generating patterns (i.e. subsequences) of a DNA sequence, which will be used to match it with another DNA sequence (to determine similarity)
- Comparing two DNA sequences, using the **Aho-Corasick** string matching algorithm, and determining their similarity based on the number of pattern matches.


## Usage/Examples
### Building the code
This project uses [CMake](https://cmake.org/) to generate build files for various build systems. It must be installed on your machine. Ensure it is added as an environment variable (PATH) so it can be executed globally in the terminal.

Additionally, a build system, such as [Ninja](https://ninja-build.org/) or [GNU Make](https://www.gnu.org/software/make/) is required to actually build the source code and create an executable.
1. Clone the repository (`git` must be installed on your machine.) by running the following command:

    ```
    git clone https://github.com/raul-it0o0/dna-matcher
    cd dna-matcher
    ```

2. In the project's directory, create a directory (folder) named `build` and navigate inside it.

3. Build the project inside the current directory (`build`) using the `CMakeLists` in the project's root directory.

    ```
    cmake ..
    ```

4. Now that the build files have been generated in the `build` folder, compile/assemble the code using your preferred build system. For example, if you use Ninja, you simply run:

    ```
    ninja
    ```

5. The executables have been created in the `bin` directory of the project's root directory. 
6. Navigate to the `bin` directory, either through your file explorer, or using the command

    ```
    cd ../bin
    ```
7. Using a terminal, you can now run executables.

### Using the DNA sequence generator
```
./dna_generator [-p] <file_name>
```
- Where `<file_name>` will be the name of the `.txt` file containing the generated DNA sequence, and
- `-p` is an option which must be specified if you wish to generate a text file with the patterns that will be used to match that sequence with another. The text file containing the patterns will be named `<file_name>_patterns.txt`.

#### Example
```
./dna_generator -p crime_scene_dna_sample
```
- Generates two text files, `crime_scene_dna_sample.txt` and `crime_scene_dna_sample_patterns.txt`, in a `data` directory inside the project's root directory.
```
./dna_generator suspect_dna_sample
```
- Generates a text file `suspect_dna_sample.txt` inside the aforementioned `data` directory
### Using the DNA matcher
```
./dna_matcher <DNA_patterns>.txt <target_DNA_sequence>.txt
```
-  Where `<DNA_patterns>.txt` contains the patterns of a DNA sequence, and
- `<target_DNA_sequence>.txt` contains the DNA sequence on which the patterns will be matched to determine similarity.
#### Example
```
./dna_matcher ../data/crime_scene_dna_sample_patterns.txt ../data/suspect_dna_sample.txt
```
- Matches the patterns of the previously generated `crime_scene_dna_sample` to `suspect_dna_sample` and displays the percentage of matches.


## Lessons Learned

- This project features two executables (`dna_generator` and `dna_matcher`) therefore they act as separate modules of the application. Each one of them has their own `CMakeLists.txt` configuration. A top-level `CMakeLists.txt` must exist to unify the two submodules.
- I experimented with the `<random>` header of C++, for the multiple random value generations within the application. I have learned a bit about distributions used for random value generations, including the [Bernoulli distribution](https://en.wikipedia.org/wiki/Bernoulli_distribution). 


## Possible improvements
- A GUI, that allows users to input the files required and that will make the application  way more intuitive
- Using specialized file formats to store the DNA sequences, such as the [FASTA file format](https://en.wikipedia.org/wiki/FASTA_format).
- Storing DNA sequences in an embedded database, for faster retrieval and to not require the user to manually input the files each time.

## Known issues
- If compiled on a Windows machine, the executables cannot be ran in UNIX-based terminals (e.g. Git Bash). 
  The executables must be ran in the Windows Command Prompt or PowerShell. 
  - The application **should** work on a Linux-based machine. It has been tested on WSL (Windows Subsystem for Linux) and it works as expected.