#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>

// Assuming Token struct definition
struct Token {
    TokenType type;
    std::string term; // Changed from lexeme to term per your code
    int line;
    bool lexed;
    std::vector<std::string> extracted_lines; // To store lines between public: and };
};

void register_terms(std::string s, Token* token_array) {
    std::string token;
    int i = 0; // line num
    int j = 0; // array index
    std::stringstream stream(s);
    bool searching = true;
    
    while (searching && std::getline(stream, token)) {
        // Skip comment lines
        if (token.find("//") == 0) {
            ++i;
            continue;
        }
        
        if (!token.empty() && j < MAX_REGISTERED_TERMS) {
            auto class_pos = token.find("class ");
            auto struct_pos = token.find("struct ");
            std::string testTerm;
            bool term_found = false;
            size_t end_pos = 0;
            
            // Check for "class term : public superclass" pattern
            if (class_pos != std::string::npos) {
                auto inheritance_pos = token.find(" : public ", class_pos);
                if (inheritance_pos != std::string::npos) {
                    testTerm = token.substr(class_pos + 6, inheritance_pos - (class_pos + 6));
                    term_found = true;
                    end_pos = inheritance_pos;
                }
            }
            // Check for "struct term final" pattern
            else if (struct_pos != std::string::npos) {
                auto final_pos = token.find(" final", struct_pos);
                if (final_pos != std::string::npos) {
                    testTerm = token.substr(struct_pos + 7, final_pos - (struct_pos + 7));
                    term_found = true;
                    end_pos = final_pos;
                }
            }
            
            if (term_found) {
                // Clean term: remove whitespace
                testTerm.erase(std::remove_if(testTerm.begin(), testTerm.end(), ::isspace), testTerm.end());
                
                // Validate term
                if (!testTerm.empty() && std::all_of(testTerm.begin(), testTerm.end(),
                    [](char c) { return std::isalnum(c) || c == '_'; })) {
                    
                    // Search token array for matching term
                    for (int k = 0; k < MAX_REGISTERED_TERMS * 8 && !token_array[k].lexed; ++k) {
                        if (testTerm == token_array[k].term) {
                            token_array[k].lexed = true;
                            bool in_public_section = false;
                            std::vector<std::string> extracted_lines;
                            
                            // Process lines starting from the NEXT line
                            while (std::getline(stream, token)) {
                                ++i;
                                
                                // Check for public: to start extraction
                                if (!in_public_section && token.find("public:") != std::string::npos) {
                                    in_public_section = true;
                                    continue;
                                }
                                
                                // Extract lines if in public section
                                if (in_public_section) {
                                    // Check for end of struct/class
                                    if (token.find("};") != std::string::npos) {
                                        break;
                                    }
                                    // Store non-empty, non-comment lines
                                    if (!token.empty() && token.find("//") != 0) {
                                        extracted_lines.push_back(token);
                                    }
                                }
                            }
                            
                            // Store extracted lines in token
                            token_array[k].extracted_lines = extracted_lines;
                            break; // Exit token array loop
                        }
                    }
                } else {
                    std::cerr << "Invalid term format: " << testTerm << std::endl;
                }
            }
        } else {
            break;
        }
        ++i;
    }
    
    // Print results
    for (int k = 0; k < MAX_REGISTERED_TERMS; ++k) {
        if (token_array[k].term.empty()) {
            std::cout << "end of array\n";
            break;
        }
        std::cout << tkntype_str(token_array[k].type) << "  " << token_array[k].term;
        if (token_array[k].lexed) {
            std::cout << " [lexed, lines: " << token_array[k].extracted_lines.size() << "]";
            for (const auto& line : token_array[k].extracted_lines) {
                std::cout << "\n  - " << line;
            }
        }
        std::cout << std::endl;
    }
}