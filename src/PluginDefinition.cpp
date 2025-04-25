#include "PluginDefinition.h"
#include "menuCmdID.h"
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

//#define verbose_debug

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

bool commandMenuInit()
{
    TCHAR* populateOffsets = _tcsdup(TEXT("Populate Offsets from HPP Files"));
    setCommand(0, populateOffsets, populateOffsetsFromHPP, NULL, false);
    return true;
}

void commandMenuCleanUp() {}

bool setCommand(size_t index, TCHAR* cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey* sk, bool check0nInit)
{
    if (index >= nbFunc || !pFunc) return false;
    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;
    return true;
}

void showError(const TCHAR* message) {
    ::MessageBox(nppData._nppHandle, message, TEXT("HPP to C# Offset Populator Error"), MB_OK | MB_ICONERROR);
}

//it always grabs the content of whatever document is currently active in Notepad++.
std::string getFileContent(const std::wstring& filePath) {
    // Switch to the specified file in Notepad++
    if (!::SendMessage(nppData._nppHandle, NPPM_SWITCHTOFILE, 0, (LPARAM)filePath.c_str())) {
        std::wstring errorMsg = L"Failed to switch to file: " + filePath;
        ::MessageBox(nppData._nppHandle, errorMsg.c_str(), TEXT("Debug: File Switch Error"), MB_OK | MB_ICONERROR);
        return "";
    }

    // Get the current Scintilla editor handle
    HWND curScintilla;
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    curScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

    size_t textLength = ::SendMessage(curScintilla, SCI_GETLENGTH, 0, 0);
    if (textLength == 0) return "";

    std::vector<char> buffer(textLength + 1);
    ::SendMessage(curScintilla, SCI_GETTEXT, textLength + 1, (LPARAM)buffer.data());
    return std::string(buffer.data(), textLength);
}

bool getOpenHPPFiles(std::vector<std::wstring>& hppFiles, std::wstring& missingFiles) {
    std::vector<std::wstring> requiredFiles = {
        L"Engine_classes.hpp",
        L"Engine_structs.hpp",
        L"Squad_classes.hpp",
        L"Squad_structs.hpp"
    };
    std::set<std::wstring, std::less<>> foundFiles;

    int nbOpenFiles = ::SendMessage(nppData._nppHandle, NPPM_GETNBOPENFILES, 0, ALL_OPEN_FILES);
    if (nbOpenFiles <= 0) {
        missingFiles = L"No open files found.";
        return false;
    }

    std::vector<TCHAR*> filePaths(nbOpenFiles);
    for (int i = 0; i < nbOpenFiles; ++i) {
        filePaths[i] = new TCHAR[MAX_PATH];
    }

    BOOL result = ::SendMessage(nppData._nppHandle, NPPM_GETOPENFILENAMES, (WPARAM)filePaths.data(), nbOpenFiles);
    if (!result) {
        missingFiles = L"Failed to retrieve open file names.";
        for (int i = 0; i < nbOpenFiles; ++i) {
            delete[] filePaths[i];
        }
        return false;
    }

    std::vector<std::pair<std::wstring, bool>> fileList; // Pair of (file path, isStructsFile)
    std::wstring debugMsg = L"Detected open files:\n";
    for (int i = 0; i < nbOpenFiles; ++i) {
        std::wstring path(filePaths[i]);
        debugMsg += path + L"\n";

        if (path.length() >= 4 && _wcsicmp(path.substr(path.length() - 4).c_str(), L".hpp") == 0) {
            std::wstring::size_type lastSep = path.find_last_of(L"\\/");
            std::wstring fileName = (lastSep != std::wstring::npos) ? path.substr(lastSep + 1) : path;

            bool isStructsFile = (fileName.find(L"_structs.hpp") != std::wstring::npos);
            fileList.emplace_back(path, isStructsFile);

            for (const auto& reqFile : requiredFiles) {
                if (_wcsicmp(fileName.c_str(), reqFile.c_str()) == 0) {
                    foundFiles.insert(fileName);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < nbOpenFiles; ++i) {
        delete[] filePaths[i];
    }

    ::MessageBox(nppData._nppHandle, debugMsg.c_str(), TEXT("Debug: Detected Open Files"), MB_OK | MB_ICONINFORMATION);

    std::vector<std::wstring> missing;
    for (const auto& reqFile : requiredFiles) {
        bool found = false;
        for (const auto& foundFile : foundFiles) {
            if (_wcsicmp(foundFile.c_str(), reqFile.c_str()) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            missing.push_back(reqFile);
        }
    }

    if (!missing.empty()) {
        missingFiles = L"Missing required .hpp files: ";
        for (size_t i = 0; i < missing.size(); ++i) {
            missingFiles += missing[i];
            if (i < missing.size() - 1) missingFiles += L", ";
        }
        return false;
    }

    // Sort files: prioritize *_structs.hpp files
    std::sort(fileList.begin(), fileList.end(), [](const auto& a, const auto& b) {
        // If a is a structs file and b is not, a comes first
        if (a.second && !b.second) return true;
        // If b is a structs file and a is not, b comes first
        if (!a.second && b.second) return false;
        // Otherwise, sort alphabetically
        return a.first < b.first;
        });

    // Extract just the file paths
    for (const auto& file : fileList) {
        hppFiles.push_back(file.first);
    }

    return true;
}

std::set<std::string> parseOffsetsStructs(const std::string& content) {
    std::set<std::string> structNames;
    // Updated regex to allow for optional whitespace (including newlines) before the opening brace
    std::regex structPattern(R"(public\s+struct\s+(\w+)\s*[\n\r\s]*\{)");

    // Use regex_search to find all matches in the entire content
    auto begin = content.cbegin();
    auto end = content.cend();
    std::smatch matches;

    while (std::regex_search(begin, end, matches, structPattern)) {
        structNames.insert(matches[1].str());
        begin = matches.suffix().first; // Move to the end of the current match
    }

    return structNames;
}

bool parseHPPForStruct(const std::string& content, const std::string& structName, std::string& output) {
    std::stringstream result;
    std::istringstream iss(content);
    std::string line;
    bool insideStruct = false;
    bool foundStruct = false;
    bool awaitingBrace = false;
    bool seenFieldsSection = false; // Track if we've seen the first "public:"
    bool parsingFields = true;      // Track if we're still parsing fields
    int accessSpecifierCount = 0;   // Count "public:", "private:", "protected:"

    try {
        std::regex structStartPattern(R"((?:struct|class)\s+)" + structName + R"(\s*(?:final)?)");
        std::regex bracePattern(R"(\s*\{)");
        std::regex fieldPattern(R"(\s*(?:struct\s+|class\s+|TArray\s*<[^>]+>|TWeakObjectPtr\s*<[^>]+>|FMulticastSparseDelegateProperty_\s*)?(\w+)\s+(\w+)\s*;\s*//\s*0x([0-9A-Fa-f]+)(?:\([^()]*\)?)?(?:.*[^,]))");
        std::regex bitfieldPattern(R"(\s*uint8\s+(\w+)\s*:\s*1\s*;\s*//\s*0x([0-9A-Fa-f]+)(?:\([^()]*\)?)?(?:.*))");
        std::regex paddingPattern(R"(\s*uint8\s+Pad_\w+\[\w+\]\s*;\s*//\s*0x[0-9A-Fa-f]+\s*(?:.*))");
        std::regex bitPaddingPattern(R"(\s*uint8\s+BitPad_\w+\s*:\s*\d+\s*;\s*(?:.*))");
        std::regex memberPattern(R"(\s*(?:struct|class)\s+)" + structName + R"(\s+\w+\s*;\s*//\s*0x[0-9A-Fa-f]+)");
        std::regex accessSpecifierPattern(R"(\s*(public|private|protected)\s*:)");
        // Enhanced method pattern to catch more method signatures
        std::regex methodPattern(R"(\s*(?:virtual\s+)?(?:void|bool|float|int32|uint8|uint32|int64|uint64|double|class\s+\w+\*|struct\s+\w+\*|TArray\s*<[^>]+>|F[A-Za-z]+|U[A-Za-z]+|[A-Z]\w*)\s+\w+\s*\([^()]*\)\s*(?:const\s*)?(?:override\s*)?(?:;\s*)?)");
        std::regex constructorPattern(R"(\s*)" + structName + R"(\s*\([^()]*\)\s*;)");
        std::regex destructorPattern(R"(\s*~\s*)" + structName + R"(\s*\([^()]*\)\s*;)");

        result << "    public struct " << structName << "\n    {\n";

        while (std::getline(iss, line)) {
            // Trim whitespace
            size_t start = 0;
            while (start < line.length() && std::isspace(static_cast<unsigned char>(line[start]))) start++;
            line.erase(0, start);
            size_t end = line.length();
            while (end > 0 && std::isspace(static_cast<unsigned char>(line[end - 1]))) end--;
            line.erase(end);

            if (!insideStruct && !awaitingBrace) {
                std::smatch matches;
                if (std::regex_search(line, matches, structStartPattern)) {
                    if (std::regex_search(line, memberPattern)) {
                        continue;
                    }
                    awaitingBrace = true;
                    foundStruct = true;
#ifdef verbose_debug
                    std::wstring debugMsg = L"Found struct/class: " + stringToWstring(structName);
                    ::MessageBox(nppData._nppHandle, debugMsg.c_str(), TEXT("Debug: Struct Start"), MB_OK | MB_ICONINFORMATION);
#endif
                    continue;
                }
            }
            else if (awaitingBrace) {
                if (std::regex_search(line, bracePattern)) {
                    awaitingBrace = false;
                    insideStruct = true;
                }
                continue;
            }
            else {
                // Check for access specifiers
                std::smatch accessMatches;
                if (std::regex_search(line, accessMatches, accessSpecifierPattern)) {
                    accessSpecifierCount++;
                    if (accessSpecifierCount == 1) {
                        seenFieldsSection = true; // First access specifier before fields
                    }
                    else if (accessSpecifierCount >= 2) {
                        parsingFields = false; // Second access specifier, stop parsing fields
#ifdef verbose_debug
                        std::wstring debugMsg = L"Stopping field parsing for " + stringToWstring(structName) + L" after second access specifier";
                        ::MessageBox(nppData._nppHandle, debugMsg.c_str(), TEXT("Debug: Access Specifier"), MB_OK | MB_ICONINFORMATION);
#endif
                    }
                    continue;
                }

                // Stop parsing if we're past the fields section or if the line is a method, constructor, or destructor
                if (!parsingFields ||
                    std::regex_match(line, methodPattern) ||
                    std::regex_match(line, constructorPattern) ||
                    std::regex_match(line, destructorPattern)) {
                    if (line.find("};") != std::string::npos) {
                        insideStruct = false;
                        result << "    }\n\n";
                        output = result.str();
                        return true;
                    }
#ifdef verbose_debug
                    if (std::regex_match(line, methodPattern)) {
                        std::wstring debugMsg = L"Skipped method in " + stringToWstring(structName) + L": " + stringToWstring(line);
                        ::MessageBox(nppData._nppHandle, debugMsg.c_str(), TEXT("Debug: Method Skipped"), MB_OK | MB_ICONINFORMATION);
                    }
#endif
                    continue;
                }

#ifdef verbose_debug
                // Debug: Log the line being processed
                std::wstring debugMsg = L"Processing line inside struct " + stringToWstring(structName) + L": " + stringToWstring(line);
                ::MessageBox(nppData._nppHandle, debugMsg.c_str(), TEXT("Debug: Inside Struct"), MB_OK | MB_ICONINFORMATION);
#endif

                // Skip padding fields
                if (std::regex_match(line, paddingPattern) || std::regex_match(line, bitPaddingPattern)) {
                    continue;
                }

                // Match bitfields
                std::smatch matches;
                if (std::regex_search(line, matches, bitfieldPattern)) {
                    std::string fieldName = matches[1].str();
                    std::string offset = matches[2].str();
                    std::transform(offset.begin(), offset.end(), offset.begin(), ::tolower);
                    result << "        public const uint " << fieldName << " = 0x" << offset << "; // uint8\n";
#ifdef verbose_debug
                    std::wstring debugMsg = L"Matched bitfield in " + stringToWstring(structName) + L": " + stringToWstring(fieldName) + L" at offset 0x" + stringToWstring(offset);
                    ::MessageBox(nppData._nppHandle, debugMsg.c_str(), TEXT("Debug: Bitfield Match"), MB_OK | MB_ICONINFORMATION);
#endif
                }
                // Match regular fields
                else if (std::regex_search(line, matches, fieldPattern)) {
                    std::string fieldType = matches[1].str();
                    if (fieldType.empty()) {
                        fieldType = matches[0].str();
                        fieldType = fieldType.substr(0, fieldType.find(matches[2].str()));
                        fieldType = fieldType.substr(0, fieldType.find(';'));
                        fieldType.erase(std::remove_if(fieldType.begin(), fieldType.end(), ::isspace), fieldType.end());
                    }
                    std::string fieldName = matches[2].str();
                    std::string offset = matches[3].str();
                    std::transform(offset.begin(), offset.end(), offset.begin(), ::tolower);
                    result << "        public const uint " << fieldName << " = 0x" << offset << "; // " << fieldType << "\n";
#ifdef verbose_debug
                    std::wstring debugMsg = L"Matched field in " + stringToWstring(structName) + L": " + stringToWstring(fieldName) + L" at offset 0x" + stringToWstring(offset);
                    ::MessageBox(nppData._nppHandle, debugMsg.c_str(), TEXT("Debug: Field Match"), MB_OK | MB_ICONINFORMATION);
#endif
                }
            }
        }

        // Close the struct if we reach the end of the file
        if (foundStruct) {
            result << "    }\n\n";
            output = result.str();
        }
    }
    catch (const std::regex_error& e) {
        std::wstring errorMsg = L"Regex error in parseHPPForStruct: " + stringToWstring(e.what()) + L" (code: " + stringToWstring(std::to_string(e.code())) + L")";
        showError(errorMsg.c_str());
        return false;
    }

    return foundStruct && !output.empty();
}


void populateOffsetsFromHPP()
{
    try {
        TCHAR currentFile[MAX_PATH];
        if (::SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, MAX_PATH, (LPARAM)currentFile) == 0) {
            showError(TEXT("Failed to get current file path."));
            return;
        }
        std::wstring currentFilePath(currentFile);
        if (currentFilePath.length() < 3 || _wcsicmp(currentFilePath.substr(currentFilePath.length() - 3).c_str(), L".cs") != 0) {
            showError(TEXT("The current file must be Offsets.cs."));
            return;
        }
        std::wstring::size_type lastSep = currentFilePath.find_last_of(L"\\/");
        std::wstring currentFileName = (lastSep != std::wstring::npos) ? currentFilePath.substr(lastSep + 1) : currentFilePath;
        if (_wcsicmp(currentFileName.c_str(), L"Offsets.cs") != 0) {
            showError(TEXT("The current file must be named Offsets.cs."));
            return;
        }

        std::string offsetsContent = getFileContent(currentFilePath);
        if (offsetsContent.empty()) {
            showError(TEXT("Offsets.cs is empty."));
            return;
        }

        std::set<std::string> structNames = parseOffsetsStructs(offsetsContent);
        if (structNames.empty()) {
            showError(TEXT("No structs found in Offsets.cs."));
            return;
        }

        std::vector<std::wstring> hppFiles;
        std::wstring missingFiles;
        if (!getOpenHPPFiles(hppFiles, missingFiles)) {
            std::wstring errorMsg = missingFiles + L"\nPlease open all required .hpp files (Engine_classes.hpp, Engine_structs.hpp, Squad_classes.hpp, Squad_structs.hpp) and try again.";
            showError(errorMsg.c_str());
            return;
        }

        std::stringstream newOffsetsContent;
        newOffsetsContent << "namespace Offsets\n{\n";
        std::set<std::string> processedStructs;

        for (const auto& structName : structNames) {
            bool found = false;
            for (const auto& hppFile : hppFiles) {
                std::string hppContent = getFileContent(hppFile);
                if (hppContent.empty()) continue;

                std::string structOutput;
                if (parseHPPForStruct(hppContent, structName, structOutput)) {
                    newOffsetsContent << structOutput;
                    processedStructs.insert(structName);
                    found = true;
                    break;
                }
            }
            if (!found) {
                newOffsetsContent << "    public struct " << structName << "\n    {\n    }\n\n";
                processedStructs.insert(structName);
            }
        }

        newOffsetsContent << "}\n";

        std::wofstream outFile(currentFilePath, std::ios::out | std::ios::trunc);
        if (!outFile.is_open()) {
            showError(TEXT("Failed to write to Offsets.cs."));
            return;
        }
        outFile << stringToWstring(newOffsetsContent.str());
        outFile.close();

        ::SendMessage(nppData._nppHandle, NPPM_SWITCHTOFILE, 0, (LPARAM)currentFilePath.c_str());
        ::SendMessage(nppData._nppHandle, NPPM_DOOPEN, 0, (LPARAM)currentFilePath.c_str());
        ::SendMessage(nppData._nppHandle, NPPM_SETCURRENTLANGTYPE, 0, L_CS);
#ifdef verbose_debug
        TCHAR msg[256];
        _stprintf_s(msg, TEXT("Successfully populated %zu structs in Offsets.cs."), processedStructs.size());
        ::MessageBox(nppData._nppHandle, msg, TEXT("HPP to C# Offset Populator"), MB_OK | MB_ICONINFORMATION);
#endif
    }
    catch (...) {
        showError(TEXT("An unexpected error occurred while processing."));
    }
}