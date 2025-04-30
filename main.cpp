#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <sstream>
#include <vector>

// Function to read the content of a file
std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();

    // Debug: Log the content of the file
    std::cout << "File content:\n" << buffer.str() << "\n";

    return buffer.str();
}


// Function to escape special regex characters in a string
std::string escapeRegex(const std::string& str) {
    static const std::regex specialChars(R"([-[\]{}()*+?.,\^$|#\s])");
    return std::regex_replace(str, specialChars, R"(\$&)");
}

bool parseCppClass(const std::string& content, const std::string& className, std::string& output) {
    // Validate className
    if (className.empty()) {
        throw std::invalid_argument("Class name cannot be empty.");
    }

    // Escape the class name to handle special characters
    std::string escapedClassName = escapeRegex(className);

    // Simplified regex to match the class declaration and public:
    std::string regexPattern = R"(class\s+)" + escapedClassName + R"((?:\s+\w+)*\s*:\s*public\s+\w+\s*{)";
    std::regex classRegex(regexPattern);

    // Debug: Log the constructed regex
    std::cout << "Constructed regex: " << regexPattern << "\n";

    std::smatch match;

    if (std::regex_search(content, match, classRegex)) {
        std::string classBody = match.suffix().str();

        // Debug: Log the matched class body
        std::cout << "Matched class body: " << classBody.substr(0, 200) << "...\n"; // Log first 200 characters

        // Regex to match fields
        std::regex fieldRegex(R"(([\w\s:<>\*]+)\s+(\w+);.*//\s*0x([0-9a-fA-F]+))");
        std::smatch fieldMatch;

        std::stringstream structOutput;
        structOutput << "public struct " << className << "\n{\n";

        auto begin = classBody.cbegin();
        auto end = classBody.cend();
        while (std::regex_search(begin, end, fieldMatch, fieldRegex)) {
            std::string fieldType = fieldMatch[1].str();
            std::string fieldName = fieldMatch[2].str();
            std::string offset = fieldMatch[3].str();
            structOutput << "    public const uint " << fieldName << " = 0x" << offset << "; // " << fieldType << "\n";
            begin = fieldMatch.suffix().first;
        }

        structOutput << "}\n";
        output = structOutput.str();
        return true;
    }

    // Debug: Log if no match is found
    std::cerr << "No match found for class: " << className << "\n";
    return false;
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

    // Parse command-line arguments
    std::string inputFilePath = argv[1];
    std::string className = "FSQSwayData";
    std::string outputFilePath = argv[2];

    try {
        // Read the C++ file content
        std::string cppContent = readFile(inputFilePath);

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
