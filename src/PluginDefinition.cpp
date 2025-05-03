#include "PluginDefinition.h"
#include "menuCmdID.h"
#include "lexertk.hpp"
#include <string>
#include <regex>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <set>
#include <vector>
#include <windows.h>
#include <tchar.h>
#include <algorithm>
#include <iostream>
#ifndef SCI_GETTEXT
#define SCI_GETTEXT 2182
#endif
#ifndef SCI_GETLENGTH
#define SCI_GETLENGTH 2006
#endif
#ifndef L_CS
#define L_CS 3
#endif

// File-based debug logging
#define log_message(message) { \
    std::wofstream log("debug.log", std::ios::app); \
    log << (message) << L"\n"; \
    log.close(); \
}


FuncItem funcItem[nbFunc];
NppData nppData;

// Helper function to convert std::string to std::wstring  
std::wstring stringToWstring(const std::string& str) {
    if (str.empty()) return std::wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), NULL, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), &wstr[0], size_needed);
    return wstr;
}

void pluginInit(HANDLE /*hModule*/) {}
void pluginCleanUp() {}

bool commandMenuInit() {
    TCHAR* populateOffsets = _tcsdup(TEXT("Populate Offsets from HPP Files"));
    setCommand(0, populateOffsets, populateOffsetsFromHPP, NULL, false);
    return true;
}

void commandMenuCleanUp() {}

bool setCommand(size_t index, TCHAR* cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey* sk, bool check0nInit) {
    if (index >= nbFunc || !pFunc) return false;
    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;
    return true;
}

std::string getFileContent(const std::wstring& filePath) {
    if (!::SendMessage(nppData._nppHandle, NPPM_SWITCHTOFILE, 0, (LPARAM)filePath.c_str())) {
        log_message(L"Error: Failed to switch to file: " + filePath);
        return "";
    }

    HWND curScintilla;
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    curScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

    size_t textLength = ::SendMessage(curScintilla, SCI_GETLENGTH, 0, 0);
    if (textLength == 0) {
        log_message(L"Error: File is empty: " + filePath);
        return "";
    }

    std::vector<char> buffer(textLength + 1);
    ::SendMessage(curScintilla, SCI_GETTEXT, textLength + 1, (LPARAM)buffer.data());
    std::string content(buffer.data(), textLength);

    // Log first few lines for verification
    std::stringstream ss(content);
    std::string line;
    int lineCount = 0;
    log_message(L"Loaded file: " + filePath + L", Size: " + std::to_wstring(textLength) + L" bytes");
    while (std::getline(ss, line) && lineCount < 5) {
        log_message(L"File " + filePath + L" line " + std::to_wstring(lineCount + 1) + L": " + stringToWstring(line));
        lineCount++;
    }

    return content;
}

// Function to get the path of "Engine_classes.hpp" if open in Notepad++
std::wstring getOpenHPPFile() {
    std::wstring targetFile = L"Engine_classes.hpp";
    int nbOpenFiles = ::SendMessage(nppData._nppHandle, NPPM_GETNBOPENFILES, 0, ALL_OPEN_FILES);
    if (nbOpenFiles <= 0) {
        return L"";
    }

    std::vector<TCHAR*> filePaths(nbOpenFiles);
    for (int i = 0; i < nbOpenFiles; ++i) {
        filePaths[i] = new TCHAR[MAX_PATH];
    }

    BOOL result = ::SendMessage(nppData._nppHandle, NPPM_GETOPENFILENAMES, (WPARAM)filePaths.data(), nbOpenFiles);
    if (!result) {
        for (int i = 0; i < nbOpenFiles; ++i) {
            delete[] filePaths[i];
        }
        return L"";
    }

    for (int i = 0; i < nbOpenFiles; ++i) {
        std::wstring path(filePaths[i]);
        std::wstring::size_type lastSep = path.find_last_of(L"\\/");
        std::wstring fileName = (lastSep != std::wstring::npos) ? path.substr(lastSep + 1) : path;
        if (_wcsicmp(fileName.c_str(), targetFile.c_str()) == 0) {
            for (int j = 0; j < nbOpenFiles; ++j) {
                delete[] filePaths[j];
            }
            return path;
        }
    }

    for (int i = 0; i < nbOpenFiles; ++i) {
        delete[] filePaths[i];
    }
    return L"";
}

std::set<std::string> parseOffsetsStructs(const std::string& content) {
    std::set<std::string> structNames;

    // Improved regex to handle various formatting scenarios
    std::regex structPattern(R"(public\s+struct\s+(\w+)(?:\s*\{|\s*[\n\r]+\s*\{))");

    auto begin = content.cbegin();
    auto end = content.cend();
    std::smatch matches;

    while (std::regex_search(begin, end, matches, structPattern)) {
        std::string structName = matches[1].str();
        structNames.insert(structName);
        log_message(L"Found struct in Offsets.cs: " + stringToWstring(structName));
        begin = matches.suffix().first;
    }

    // If we didn't find any structs with the first pattern, try a more lenient one
    if (structNames.empty()) {
        begin = content.cbegin();
        std::regex altPattern(R"(struct\s+(\w+))");

        while (std::regex_search(begin, end, matches, altPattern)) {
            std::string structName = matches[1].str();
            structNames.insert(structName);
            log_message(L"Found struct with alternative pattern: " + stringToWstring(structName));
            begin = matches.suffix().first;
        }
    }

    log_message(L"Parsed structs from Offsets.cs: " + std::to_wstring(structNames.size()) + L" found");
    
    // Debug logging of all found structs
    for (const auto& name : structNames) {
        log_message(L"  - " + stringToWstring(name));
    }

    return structNames;
}

bool parseHPPForStruct(const std::string& content, const std::string& structName, std::string& structOutput, const std::wstring& filePath) {
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> fields;
    enum class ParseState { SEARCHING, PARSING };
    ParseState state = ParseState::SEARCHING;

    // Regex patterns - improved to be more specific
    const std::regex structStartRegex(R"(\b(?:struct|class)\s+" + structName + R"\s*(?::\s*public\s+\w+)?\s*\{)");
    const std::regex fieldRegex(R"(\s*([\w\s:<>\*]+(?:<\s*[\w\s\*,<>]+\s*>)?)\s+(\w+)\s*;\s*//\s*0x([0-9a-fA-F]+)(?:\s*\(([^)]*)\))?\s*)");
    const std::regex bitfieldRegex(R"(\s*(uint\d+|bool)\s+(\w+)\s*:\s*\d+\s*;\s*//\s*0x([0-9a-fA-F]+)(?:\s*\(([^)]*)\))?\s*)");
    const std::regex methodRegex(R"(\s*(?:virtual\s+)?(?:[\w:<>\*]+\s*(?:<\s*[\w\s\*,<>]+\s*>)?\s+)?\w+\s*\([^{;]*\)\s*(?:const)?\s*(?:override)?\s*;)");
    const std::regex accessSpecifierRegex(R"(\s*(public|private|protected):\s*)");
    const std::regex paddingRegex(R"(\s*uint8\s+(Pad_\w+|BitPad_\w+)\s*(?:\[\d+\]|\s*:\s*\d+);\s*//\s*0x[0-9a-fA-F]+)");
    const std::regex endStructRegex(R"(^\s*\};)");
    const std::regex methodStartRegex(R"(\s*(?:[\w:<>\*]+\s*(?:<\s*[\w\s\*,<>]+\s*>)?\s+)?\w+\s*\()");  // Detect start of method definitions

    if (content.empty()) {
        log_message(L"Error: Empty content for struct " + stringToWstring(structName) + L" in " + filePath);
        return false;
    }

    log_message(L"Starting parseHPPForStruct for " + stringToWstring(structName) + L" in " + filePath);

    // Initial search for the struct/class
    std::size_t start_pos = content.find(structName);
    if (start_pos == std::string::npos) {
        log_message(L"Could not find struct/class " + stringToWstring(structName) + L" in " + filePath);
        return false;
    }

    // Find the opening brace for the class/struct
    std::size_t struct_start = content.find("{", start_pos);
    if (struct_start == std::string::npos) {
        log_message(L"Could not find opening brace for " + stringToWstring(structName) + L" in " + filePath);
        return false;
    }

    // Find where fields end and methods begin
    std::size_t method_section_start = content.find("public:", struct_start + 1);
    if (method_section_start == std::string::npos) {
        // If no public: section found, try to find the closing brace
        method_section_start = content.find("};", struct_start + 1);
        if (method_section_start == std::string::npos) {
            log_message(L"Could not find end of struct " + stringToWstring(structName) + L" in " + filePath);
            return false;
        }
    }

    // Extract the fields section
    std::string fields_section = content.substr(struct_start + 1, method_section_start - struct_start - 1);
    log_message(L"Found fields section for " + stringToWstring(structName) + L" in " + filePath);

    // Process the fields section line by line
    std::stringstream ss(fields_section);
    std::string line;
    int lineNumber = 0;
    bool inPublicSection = false;

    while (std::getline(ss, line)) {
        lineNumber++;
        std::smatch match;

        if (line.empty() || std::all_of(line.begin(), line.end(), isspace)) {
            continue;
        }

        // Check for access specifiers
        if (std::regex_search(line, match, accessSpecifierRegex)) {
            if (match[1].str() == "public:") {
                inPublicSection = true;
            }
            else {
                inPublicSection = false;
            }
            continue;
        }

        // Skip if not in public section or if this is a method
        if (!inPublicSection || std::regex_search(line, methodStartRegex)) {
            continue;
        }

        // Process fields
        if (std::regex_search(line, match, fieldRegex) && !std::regex_search(line, match, paddingRegex)) {
            std::string type = match[1].str();
            std::string name = match[2].str();
            std::string offset = match[3].str();
            std::string comment = match[4].matched ? match[4].str() : "";

            // Trim whitespace
            type.erase(0, type.find_first_not_of(" \t"));
            type.erase(type.find_last_not_of(" \t") + 1);

            fields.emplace_back(type, name, offset, comment);
            log_message(L"Matched field: " + stringToWstring(name) + L" at 0x" + stringToWstring(offset) + L", Type: " + stringToWstring(type));
        }
        else if (std::regex_search(line, match, bitfieldRegex)) {
            std::string type = match[1].str();
            std::string name = match[2].str();
            std::string offset = match[3].str();
            std::string comment = match[4].matched ? match[4].str() : "";

            fields.emplace_back(type, name, offset, comment);
            log_message(L"Matched bitfield: " + stringToWstring(name) + L" at 0x" + stringToWstring(offset) + L", Type: " + stringToWstring(type));
        }
    }

    // Generate the output
    if (!fields.empty()) {
        std::stringstream output;
        output << "    public struct " << structName << "\n    {\n";
        for (const auto& [type, name, offset, comment] : fields) {
            output << "        public const uint " << name << " = 0x" << offset << "; // " << type;
            if (!comment.empty()) {
                output << " (" << comment << ")";
            }
            output << "\n";
        }
        output << "    }\n\n";
        structOutput = output.str();
        log_message(L"Generated output for " + stringToWstring(structName) + L" with " + std::to_wstring(fields.size()) + L" fields");
        return true;
    }

    log_message(L"No fields found for " + stringToWstring(structName) + L" in " + filePath);
    return false;
}

// Function to populate Offsets.cs with data from Engine_classes.hpp
void populateOffsetsFromHPP() {
    try {
        // Clear debug log
        std::wofstream log("debug.log", std::ios::trunc);
        log.close();

        // Verify current file is Offsets.cs
        TCHAR currentFile[MAX_PATH];
        if (::SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, MAX_PATH, (LPARAM)currentFile) == 0) {
            log_message(L"Error: Failed to get current file path");
            return;
        }
        std::wstring currentFilePath(currentFile);
        if (currentFilePath.length() < 3 || _wcsicmp(currentFilePath.substr(currentFilePath.length() - 3).c_str(), L".cs") != 0) {
            log_message(L"Error: Current file must be Offsets.cs");
            return;
        }
        std::wstring::size_type lastSep = currentFilePath.find_last_of(L"\\/");
        std::wstring currentFileName = (lastSep != std::wstring::npos) ? currentFilePath.substr(lastSep + 1) : currentFilePath;
        if (_wcsicmp(currentFileName.c_str(), L"Offsets.cs") != 0) {
            log_message(L"Error: Current file must be named Offsets.cs");
            return;
        }

        // Get content of Offsets.cs
        std::string offsetsContent = getFileContent(currentFilePath);
        if (offsetsContent.empty()) {
            log_message(L"Error: Offsets.cs is empty");
            return;
        }

        // Parse struct names from Offsets.cs
        std::set<std::string> structNames = parseOffsetsStructs(offsetsContent);
        if (structNames.empty()) {
            log_message(L"Error: No structs found in Offsets.cs");
            return;
        }

        // Get path of Engine_classes.hpp
        std::wstring hppFilePath = getOpenHPPFile();
        if (hppFilePath.empty()) {
            log_message(L"Error: Engine_classes.hpp is not open");
            return;
        }

        // Get content of Engine_classes.hpp
        std::string hppContent = getFileContent(hppFilePath);
        if (hppContent.empty()) {
            log_message(L"Error: Engine_classes.hpp is empty");
            return;
        }

        // Check all possible Engine/Game files
        std::vector<std::wstring> possibleHppFiles;
        std::vector<std::string> possibleHppContents;

        possibleHppFiles.push_back(hppFilePath);
        possibleHppContents.push_back(hppContent);

        // Check other potential HPP files
        std::vector<std::wstring> additionalFiles = {
            L"Engine_structs.hpp",
            L"Game_classes.hpp",
            L"Game_structs.hpp"
        };

        for (const auto& filename : additionalFiles) {
            // Check if file is open in Notepad++
            int nbOpenFiles = ::SendMessage(nppData._nppHandle, NPPM_GETNBOPENFILES, 0, ALL_OPEN_FILES);
            std::vector<TCHAR*> filePaths(nbOpenFiles);
            for (int i = 0; i < nbOpenFiles; ++i) {
                filePaths[i] = new TCHAR[MAX_PATH];
            }

            BOOL result = ::SendMessage(nppData._nppHandle, NPPM_GETOPENFILENAMES, (WPARAM)filePaths.data(), nbOpenFiles);
            if (result) {
                for (int i = 0; i < nbOpenFiles; ++i) {
                    std::wstring path(filePaths[i]);
                    std::wstring::size_type lastSep = path.find_last_of(L"\\/");
                    std::wstring fileName = (lastSep != std::wstring::npos) ? path.substr(lastSep + 1) : path;

                    if (_wcsicmp(fileName.c_str(), filename.c_str()) == 0) {
                        std::string content = getFileContent(path);
                        if (!content.empty()) {
                            possibleHppFiles.push_back(path);
                            possibleHppContents.push_back(content);
                            log_message(L"Found additional file: " + path);
                        }
                    }
                }
            }

            for (int i = 0; i < nbOpenFiles; ++i) {
                delete[] filePaths[i];
            }
        }

        // Generate new Offsets.cs content
        std::stringstream newOffsetsContent;
        newOffsetsContent << "namespace Offsets\n{\n";
        std::set<std::string> processedStructs;

        // Preserve existing structs and replace with updated content
        std::map<std::string, std::string> existingStructs;
        std::regex structRegex(R"(public\s+struct\s+(\w+)\s*\{[^}]*\})");
        auto begin = offsetsContent.cbegin();
        auto end = offsetsContent.cend();
        std::smatch matches;

        while (std::regex_search(begin, end, matches, structRegex)) {
            std::string structName = matches[1].str();
            std::string structContent = matches[0].str();
            existingStructs[structName] = structContent;
            begin = matches.suffix().first;
        }

        for (const auto& structName : structNames) {
            bool found = false;

            // Try to find the struct in any of the possible hpp files
            for (size_t i = 0; i < possibleHppFiles.size(); i++) {
                std::string structOutput;
                if (parseHPPForStruct(possibleHppContents[i], structName, structOutput, possibleHppFiles[i])) {
                    newOffsetsContent << structOutput;
                    processedStructs.insert(structName);
                    found = true;
                    log_message(L"Found struct " + stringToWstring(structName) + L" in " + possibleHppFiles[i]);
                    break;
                }
            }

            if (!found) {
                // If we couldn't find the struct, preserve the existing one
                if (existingStructs.find(structName) != existingStructs.end()) {
                    newOffsetsContent << "    " << existingStructs[structName] << "\n\n";
                    processedStructs.insert(structName);
                    log_message(L"Preserved existing struct " + stringToWstring(structName));
                }
                else {
                    // If it didn't exist before, add an empty struct
                    newOffsetsContent << "    public struct " << structName << "\n    {\n    }\n\n";
                    processedStructs.insert(structName);
                    log_message(L"Warning: No fields found for struct " + stringToWstring(structName));
                }
            }
        }

        newOffsetsContent << "}\n";

        // Write to Offsets.cs
        std::wofstream outFile(currentFilePath, std::ios::out | std::ios::trunc);
        if (!outFile.is_open()) {
            log_message(L"Error: Failed to write to Offsets.cs");
            return;
        }
        outFile << stringToWstring(newOffsetsContent.str());
        outFile.close();

        // Refresh and set language in Notepad++
        ::SendMessage(nppData._nppHandle, NPPM_SWITCHTOFILE, 0, (LPARAM)currentFilePath.c_str());
        ::SendMessage(nppData._nppHandle, NPPM_DOOPEN, 0, (LPARAM)currentFilePath.c_str());
        ::SendMessage(nppData._nppHandle, NPPM_SETCURRENTLANGTYPE, 0, L_CS);
        log_message(L"Success: Populated " + stringToWstring(std::to_wstring(processedStructs.size())) + L" structs in Offsets.cs");
    }
    catch (const std::exception& e) {
        log_message(L"Error: Exception in populateOffsetsFromHPP: " + stringToWstring(e.what()));
    }
    catch (...) {
        log_message(L"Error: Unexpected exception in populateOffsetsFromHPP");
    }
}