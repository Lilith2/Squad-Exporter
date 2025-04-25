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
    log << message << L"\n"; \
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
    std::regex structPattern(R"(public\s+struct\s+(\w+)\s*[\n\r\s]*\{)");
    auto begin = content.cbegin();
    auto end = content.cend();
    std::smatch matches;

    while (std::regex_search(begin, end, matches, structPattern)) {
        structNames.insert(matches[1].str());
        begin = matches.suffix().first;
    }

    log_message(L"Parsed structs from Offsets.cs: " + stringToWstring(std::to_string(structNames.size())) + L" found");
    return structNames;
}

bool parseHPPForStruct(const std::string& content, const std::string& structName, std::string& structOutput, const std::wstring& filePath) {
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> fields;
    enum class ParseState { SEARCHING, PARSING };
    ParseState state = ParseState::SEARCHING;

    // Regex patterns
    const std::regex structStartRegex(R"(\b(?:struct|class)\s+" + structName + R"\s*(?::\s*public\s+\w+)?\s*\{)");
    const std::regex fieldRegex(R"(\s*([\w\s:<>\*]+(?:<\s*[\w\s\*,<>]+\s*>)?)\s+(\w+)\s*;\s*//\s*0x([0-9a-fA-F]+)(?:\s*\(([^)]*)\))?\s*)");
    const std::regex bitfieldRegex(R"(\s*(uint\d+|bool)\s+(\w+)\s*:\s*\d+\s*;\s*//\s*0x([0-9a-fA-F]+)(?:\s*\(([^)]*)\))?\s*)");
    const std::regex methodRegex(R"(\s*(?:[\w:<>\*]+\s*(?:<\s*[\w\s\*,<>]+\s*>)?\s+)?\w+\s*\([^)]*\)\s*(?:const)?\s*;)");
    const std::regex accessSpecifierRegex(R"(\s*(public|private|protected):\s*)");
    const std::regex paddingRegex(R"(\s*uint8\s+(Pad_\w+|BitPad_\w+)\s*(?:\[\d+\]|\s*:\s*\d+);\s*//\s*0x[0-9a-fA-F]+)");
    const std::regex endStructRegex(R"(^\s*\};)");

    if (content.empty()) {
        log_message(L"Error: Empty content for struct " + stringToWstring(structName) + L" in " + filePath);
        return false;
    }

    log_message(L"Starting parseHPPForStruct for " + stringToWstring(structName) + L" in " + filePath);

    std::stringstream ss(content);
    std::string line;
    int lineNumber = 0;

    while (std::getline(ss, line)) {
        lineNumber++;
        std::smatch match;

        if (line.empty() || std::all_of(line.begin(), line.end(), isspace)) {
            log_message(L"Line " + std::to_wstring(lineNumber) + L" in " + filePath + L": [Empty]");
            continue;
        }

        log_message(L"Line " + std::to_wstring(lineNumber) + L" in " + filePath + L": " + stringToWstring(line));

        switch (state) {
        case ParseState::SEARCHING:
            if (std::regex_search(line, match, structStartRegex)) {
                state = ParseState::PARSING;
                log_message(L"Found struct " + stringToWstring(structName) + L" at line " + std::to_wstring(lineNumber) + L" in " + filePath);
            }
            else {
                log_message(L"Searching for struct " + stringToWstring(structName) + L" at line " + std::to_wstring(lineNumber) + L" in " + filePath);
            }
            break;

        case ParseState::PARSING:
            if (std::regex_search(line, match, fieldRegex) && !std::regex_search(line, match, paddingRegex)) {
                std::string type = match[1].str();
                std::string name = match[2].str();
                std::string offset = match[3].str();
                std::string comment = match[4].matched ? match[4].str() : "";
                fields.emplace_back(type, name, offset, comment);
                log_message(L"Matched field: " + stringToWstring(name) + L" at 0x" + stringToWstring(offset) + L", Type: " + stringToWstring(type) + L" in " + filePath);
            }
            else if (std::regex_search(line, match, bitfieldRegex)) {
                std::string type = match[1].str();
                std::string name = match[2].str();
                std::string offset = match[3].str();
                std::string comment = match[4].matched ? match[4].str() : "";
                fields.emplace_back(type, name, offset, comment);
                log_message(L"Matched bitfield: " + stringToWstring(name) + L" at 0x" + stringToWstring(offset) + L", Type: " + stringToWstring(type) + L" in " + filePath);
            }
            else if (std::regex_search(line, match, methodRegex) || std::regex_search(line, match, accessSpecifierRegex)) {
                log_message(L"Stopping field parsing at line " + std::to_wstring(lineNumber) + L" (method or access specifier) in " + filePath);
                if (!fields.empty()) {
                    std::stringstream ss;
                    ss << "    public struct " << structName << "\n    {\n";
                    for (const auto& [type, name, offset, comment] : fields) {
                        ss << "        public const uint " << name << " = 0x" << offset << "; // " << type;
                        if (!comment.empty()) {
                            ss << " (" << comment << ")";
                        }
                        ss << "\n";
                    }
                    ss << "    }\n\n";
                    structOutput = ss.str();
                    log_message(L"Generated output for " + stringToWstring(structName) + L" in " + filePath + L":\n" + stringToWstring(structOutput));
                    return true;
                }
                log_message(L"No fields found before methods or access specifier in " + filePath);
                return false;
            }
            else if (std::regex_search(line, match, endStructRegex)) {
                log_message(L"End of struct at line " + std::to_wstring(lineNumber) + L" in " + filePath);
                if (!fields.empty()) {
                    std::stringstream ss;
                    ss << "    public struct " << structName << "\n    {\n";
                    for (const auto& [type, name, offset, comment] : fields) {
                        ss << "        public const uint " << name << " = 0x" << offset << "; // " << type;
                        if (!comment.empty()) {
                            ss << " (" << comment << ")";
                        }
                        ss << "\n";
                    }
                    ss << "    }\n\n";
                    structOutput = ss.str();
                    log_message(L"Generated output for " + stringToWstring(structName) + L" in " + filePath + L":\n" + stringToWstring(structOutput));
                    return true;
                }
                log_message(L"No fields found before end of struct in " + filePath);
                return false;
            }
            else {
                log_message(L"Unmatched line for " + stringToWstring(structName) + L" at line " + std::to_wstring(lineNumber) + L" in " + filePath);
            }
            break;
        }
    }

    log_message(L"Reached end of file for " + stringToWstring(structName) + L" in " + filePath);
    if (state == ParseState::PARSING && !fields.empty()) {
        std::stringstream ss;
        ss << "    public struct " << structName << "\n    {\n";
        for (const auto& [type, name, offset, comment] : fields) {
            ss << "        public const uint " << name << " = 0x" << offset << "; // " << type;
            if (!comment.empty()) {
                ss << " (" << comment << ")";
            }
            ss << "\n";
        }
        ss << "    }\n\n";
        structOutput = ss.str();
        log_message(L"Generated output for " + stringToWstring(structName) + L" in " + filePath + L":\n" + stringToWstring(structOutput));
        return true;
    }

    log_message(L"Failed to find struct " + stringToWstring(structName) + L" or parse fields in " + filePath);
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

        // Generate new Offsets.cs content
        std::stringstream newOffsetsContent;
        newOffsetsContent << "namespace Offsets\n{\n";
        std::set<std::string> processedStructs;

        for (const auto& structName : structNames) {
            std::string structOutput;
            if (parseHPPForStruct(hppContent, structName, structOutput, hppFilePath)) {
                newOffsetsContent << structOutput;
                processedStructs.insert(structName);
            }
            else {
                newOffsetsContent << "    public struct " << structName << "\n    {\n    }\n\n";
                processedStructs.insert(structName);
                log_message(L"Warning: No fields found for struct " + stringToWstring(structName));
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
        log_message(L"Success: Populated " + stringToWstring(std::to_string(processedStructs.size())) + L" structs in Offsets.cs");
    }
    catch (...) {
        log_message(L"Error: Unexpected exception in populateOffsetsFromHPP");
    }
}