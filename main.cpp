#include <iostream>
#include <fstream>
#include <string>

// Function to read the content of a file
char* readOffsetFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    char* buffer[];
    buffer << file.rdbuf();

    // Debug: Log the content of the file
    std::cout << "File content:\n" << buffer.str() << "\n";

    return buffer.str()
}


// Function to display usage instructions
void displayUsage(const std::string& programName) {
    std::cout << "Usage: " << programName << " <input_file> <output_file>\n";
    std::cout << "  <input_file>  - Path to the C++ header file (e.g., example.hpp)\n";
    //std::cout << "  <class_name>  - Name of the class to parse (e.g., AActor)\n";
    std::cout << "  <output_file> - Path to the output C# file (e.g., Offsets.cs)\n";
}

int main(int argc, char* argv[]) {

    if (argc > 1 && (std::string(argv[1]) == "help" || std::string(argv[1]) == "Help") || argc < 2) {
		displayUsage(argv[0]);
		return 0;
    }

    if (argc > 3) {
		std::cout << "Too many arguments provided.\n";
		displayUsage(argv[0]);
        return 0;
    }

    // Parse command-line arguments
    std::string inputFilePath = argv[1];
    std::string className = "FSQSwayData";
    std::string outputFilePath = argv[2];

    try {
        // Read the C++ file content
        char* buffered_OUT = readOffsetFile(inputFilePath);

        // Parse the class and generate the C# output
        std::string csharpOutput;
        if (parseCppClass(cppContent, className, csharpOutput)) {
            // Write the output to the specified file
            std::ofstream outFile(outputFilePath);
            if (!outFile.is_open()) {
                throw std::runtime_error("Failed to open output file: " + outputFilePath);
            }
            outFile << "namespace Offsets\n{\n" << csharpOutput << "}\n";
            outFile.close();

            std::cout << "Successfully generated C# struct for " << className << " in " << outputFilePath << "\n";
        }
        else {
            std::cerr << "Class " << className << " not found in the C++ file.\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
