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

#ifndef SCI_GETTEXT
#define SCI_GETTEXT 2182
#endif

#ifndef SCI_GETLENGTH
#define SCI_GETLENGTH 2006
#endif

#ifndef L_CS
#define L_CS 3
#endif

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

std::string getFileContent(const std::wstring& /*filePath*/) {
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

// Get all open .hpp files and validate required files
bool getOpenHPPFiles(std::vector<std::wstring>& hppFiles, std::wstring& missingFiles) {
    std::vector<std::wstring> requiredFiles = {
        L"Engine_classes.hpp",
        L"Engine_structs.hpp",
        L"Squad_classes.hpp",
        L"Squad_structs.hpp"
    };
    std::set<std::wstring, std::less<>> foundFiles; // std::less<> is case-sensitive, but we'll handle case below
    TCHAR filePath[MAX_PATH];

    // Temporary debug string to see what files are detected
    std::wstring debugMsg = L"Detected .hpp files:\n";

    for (int i = 0; ; i++) {
        for (int i = 0; ; i++) {
for (int i = 0; ; i++) {
    LRESULT result = ::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID, i, (LPARAM)filePath);
    if (result == -1) {
        if (i == 0) { // Only show the error message once for ID 0
            std::wstring debugMsg = L"SendMessage returned -1 for buffer ID: " + std::to_wstring(i) + L"\n";
            ::MessageBox(nppData._nppHandle, debugMsg.c_str(), TEXT("Debug: Buffer ID Failure"), MB_OK | MB_ICONINFORMATION);
        }
        break; // Exit the loop
    }
    std::wstring path(filePath);
    if (path.length() >= 4 && _wcsicmp(path.substr(path.length() - 4).c_str(), L".hpp") == 0) {
        // Process .hpp file
    }
}
            LRESULT result = ::SendMessage(nppData._nppHandle, NPPM_GETFULLPATHFROMBUFFERID, i, (LPARAM)filePath);
            if (result == -1) {
                std::wstring debugMsg = L"SendMessage returned -1 for buffer ID: " + std::to_wstring(i) + L"\n";
                ::MessageBox(nppData._nppHandle, debugMsg.c_str(), TEXT("Debug: Buffer ID Failure"), MB_OK | MB_ICONINFORMATION);
                break;
            }
            std::wstring path(filePath);
            if (path.length() >= 4 && _wcsicmp(path.substr(path.length() - 4).c_str(), L".hpp") == 0) {
                // Process .hpp file
            }
        }
        std::wstring path(filePath);
        if (path.length() >= 4 && _wcsicmp(path.substr(path.length() - 4).c_str(), L".hpp") == 0) {
            std::wstring::size_type lastSep = path.find_last_of(L"\\/");
            std::wstring fileName = (lastSep != std::wstring::npos) ? path.substr(lastSep + 1) : path;

            // Add to debug message
            debugMsg += fileName + L"\n";

            // Case-insensitive comparison for required files
            for (const auto& reqFile : requiredFiles) {
                if (_wcsicmp(fileName.c_str(), reqFile.c_str()) == 0) {
                    hppFiles.push_back(path);
                    foundFiles.insert(fileName);
                    break;
                }
            }
        }
    }

    // Show debug message (remove this after confirming the issue)
    ::MessageBox(nppData._nppHandle, debugMsg.c_str(), TEXT("Debug: Detected .hpp Files"), MB_OK | MB_ICONINFORMATION);

    // Check for missing required files
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

// Parse .hpp file for a specific struct and extract fields
bool parseHPPForStruct(const std::string& content, const std::string& structName, std::string& output) {
    std::stringstream result;
    std::istringstream iss(content);
    std::string line;
    bool insideStruct = false;
    bool foundStruct = false;

    // Regex for struct start, allowing for 'final' keyword and 'class' or 'struct'
    std::regex structStartPattern(R"((?:struct|class)\s+" + structName + R"\s*(?:final)?\s*\{)");
    // Regex for fields, e.g., "float UnclampedTotalSway; // 0x0074 (metadata)"
    std::regex fieldPattern(R"(\s*(?:struct\s+)?(\w+)\s+(\w+)\s*;\s*//\s*0x([0-9A-Fa-f]+)\s*(?:\([^\)]*\))?(?:.*))");
    // Regex to skip padding fields like "uint8 Pad_60[0x14];"
    std::regex paddingPattern(R"(\s*uint8\s+Pad_\w+\[\w+\]\s*;\s*//\s*0x[0-9A-Fa-f]+\s*(?:.*))");

    while (std::getline(iss, line)) {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (!insideStruct) {
            std::smatch matches;
            if (std::regex_search(line, matches, structStartPattern)) {
                insideStruct = true;
                foundStruct = true;
                result << "    public struct " << structName << "\n    {\n";
                continue;
            }
        }
        else {
            // Skip padding fields
            if (std::regex_match(line, paddingPattern)) {
                continue;
            }

            std::smatch matches;
            if (std::regex_search(line, matches, fieldPattern)) {
                std::string fieldType = matches[1].str();
                std::string fieldName = matches[2].str();
                std::string offset = matches[3].str();
                // Convert offset to lowercase
                std::transform(offset.begin(), offset.end(), offset.begin(), ::tolower);

                // All fields use uint in C#
                result << "        public const uint " << fieldName << " = 0x" << offset << "; // " << fieldType << "\n";
            }
            if (line.find("};") != std::string::npos) {
                insideStruct = false;
                result << "    }\n\n";
                output = result.str();
                return true;
            }
        }
    }
    return foundStruct;
}

void populateOffsetsFromHPP()
{
    try {
        // Get current file path (should be Offsets.cs)
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

        // Read Offsets.cs content
        std::string offsetsContent = getFileContent(currentFilePath);
        if (offsetsContent.empty()) {
            showError(TEXT("Offsets.cs is empty."));
            return;
        }

        // Parse struct names from Offsets.cs
        std::set<std::string> structNames = parseOffsetsStructs(offsetsContent);
        if (structNames.empty()) {
            showError(TEXT("No structs found in Offsets.cs."));
            return;
        }

        // Get all open .hpp files and validate required files
        std::vector<std::wstring> hppFiles;
        std::wstring missingFiles;
        if (!getOpenHPPFiles(hppFiles, missingFiles)) {
            std::wstring errorMsg = missingFiles + L"\nPlease open all required .hpp files (Engine_classes.hpp, Engine_structs.hpp, Squad_classes.hpp, Squad_structs.hpp) and try again.";
            showError(errorMsg.c_str());
            return;
        }

        // Process each struct
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
                    break; // Stop searching other .hpp files once found
                }
            }
            if (!found) {
                TCHAR msg[256];
                std::wstring wStructName(structName.begin(), structName.end());
                _stprintf_s(msg, TEXT("Struct or class '%s' not found in any open .hpp file (Engine_classes.hpp, Engine_structs.hpp, Squad_classes.hpp, Squad_structs.hpp)."), wStructName.c_str());
                showError(msg);
                return;
            }
        }

        newOffsetsContent << "}\n";

        // Write updated Offsets.cs
        std::wofstream outFile(currentFilePath, std::ios::out | std::ios::trunc);
        if (!outFile.is_open()) {
            showError(TEXT("Failed to write to Offsets.cs."));
            return;
        }
        outFile << stringToWstring(newOffsetsContent.str());
        outFile.close();

        // Reload Offsets.cs in Notepad++
        ::SendMessage(nppData._nppHandle, NPPM_DOOPEN, 0, (LPARAM)currentFilePath.c_str());
        ::SendMessage(nppData._nppHandle, NPPM_SETCURRENTLANGTYPE, 0, L_CS);

        TCHAR msg[256];
        _stprintf_s(msg, TEXT("Successfully populated %zu structs in Offsets.cs."), processedStructs.size());
        ::MessageBox(nppData._nppHandle, msg, TEXT("HPP to C# Offset Populator"), MB_OK | MB_ICONINFORMATION);
    }
    catch (...) {
        showError(TEXT("An unexpected error occurred while processing."));
    }
}