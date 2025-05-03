#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>

enum TokenType {
    UNKNOWN                     ,
    WHITESPACE                  ,

    LITERAL_INTEGER             ,   // 1
    LITERAL_FLOATING_POINT      ,   // 1.0
    LITERAL_CHARACTER           ,   // 'j'
    LITERAL_STRING              ,   // "hello"

    PAREN_LEFT                  ,   // (
    PAREN_RIGHT                 ,   // )
    BRACKET_LEFT                ,   // {
    BRACKET_RIGHT               ,   // }
    SQUARE_BRACKET_LEFT         ,   // [
    SQUARE_BRACKET_RIGHT        ,   // ]
    ANGLE_BRACKET_LEFT          ,   // <
    ANGLE_BRACKET_RIGHT         ,   // >

    COMMA                       ,   // ,
    SEMICOLON                   ,   // ;
    IDENTIFIER                  ,   // var/const/func/type name

    OP_PTR                      ,   // *

    KW_BREAK                    ,
    KW_CASE                     ,
    KW_CAST                     ,
    KW_CONST                    ,
    KW_CONTINUE                 ,
    KW_DEFAULT                  ,
    KW_DELETE                   ,
    KW_ELSE                     ,
    KW_ENUM                     ,   // var
    KW_FALSE                    ,
    KW_FOR                      ,
    KW_IF                       ,
    KW_NEW                      ,
    KW_NULL                     ,
    KW_RETURN                   ,
    KW_SIZEOF                   ,
    KW_STRUCT                   ,   // var
    KW_SWITCH                   ,
    KW_TRUE                     ,
    KW_WHILE                    ,

    // Builtin types
    BT_INT8                     ,   // i8,  byte
    BT_INT16                    ,   // i16, short
    BT_INT32                    ,   // i32, int
    BT_INT64                    ,   // i64, long

    BT_UINT8                    ,   // u8
    BT_UINT16                   ,   // u16
    BT_UINT32                   ,   // u32
    BT_UINT64                   ,   // u64

    BT_FLOAT                    ,   // float
    BT_DOUBLE                   ,   // double

    BT_BOOL                     ,   // bool
    BT_CHAR                     ,   // char
    BT_STRING                   ,   // string
    BT_VOID                        // void
};

typedef struct {
    TokenType type;
    std::string lexeme;
    int line;
} Token;

bool isNewline(char c) {
    return c == '\n' || c =='\r';
}

bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool isNumeric(char c) {
    return c >= '0' && c <= '9';
}

bool isAlphabetical(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Function to convert TokenType enum to string
std::string tkntype_str(TokenType type) {
    switch (type) {
        case UNKNOWN:                   return "UNKNOWN";
        case WHITESPACE:                return "WHITESPACE";
        case LITERAL_INTEGER:           return "LITERAL_INTEGER";
        case LITERAL_FLOATING_POINT:    return "LITERAL_FLOATING_POINT";
        case LITERAL_CHARACTER:         return "LITERAL_CHARACTER";
        case LITERAL_STRING:            return "LITERAL_STRING";
        case PAREN_LEFT:                return "PAREN_LEFT";
        case PAREN_RIGHT:               return "PAREN_RIGHT";
        case BRACKET_LEFT:              return "BRACKET_LEFT";
        case BRACKET_RIGHT:             return "BRACKET_RIGHT";
        case SQUARE_BRACKET_LEFT:       return "SQUARE_BRACKET_LEFT";
        case SQUARE_BRACKET_RIGHT:      return "SQUARE_BRACKET_RIGHT";
        case ANGLE_BRACKET_LEFT:        return "ANGLE_BRACKET_LEFT";
        case ANGLE_BRACKET_RIGHT:       return "ANGLE_BRACKET_RIGHT";
        case COMMA:                     return "COMMA";
        case SEMICOLON:                 return "SEMICOLON";
        case IDENTIFIER:                return "IDENTIFIER";
        case OP_PTR:                    return "OP_PTR";
        case KW_BREAK:                  return "KW_BREAK";
        case KW_CASE:                   return "KW_CASE";
        case KW_CAST:                   return "KW_CAST";
        case KW_CONST:                  return "KW_CONST";
        case KW_CONTINUE:               return "KW_CONTINUE";
        case KW_DEFAULT:                return "KW_DEFAULT";
        case KW_DELETE:                 return "KW_DELETE";
        case KW_ELSE:                   return "KW_ELSE";
        case KW_ENUM:                   return "KW_ENUM";
        case KW_FALSE:                  return "KW_FALSE";
        case KW_FOR:                    return "KW_FOR";
        case KW_IF:                     return "KW_IF";
        case KW_NEW:                    return "KW_NEW";
        case KW_NULL:                   return "KW_NULL";
        case KW_RETURN:                 return "KW_RETURN";
        case KW_SIZEOF:                 return "KW_SIZEOF";
        case KW_STRUCT:                 return "KW_STRUCT";
        case KW_SWITCH:                 return "KW_SWITCH";
        case KW_TRUE:                   return "KW_TRUE";
        case KW_WHILE:                  return "KW_WHILE";
        case BT_INT8:                   return "BT_INT8";
        case BT_INT16:                  return "BT_INT16";
        case BT_INT32:                  return "BT_INT32";
        case BT_INT64:                  return "BT_INT64";
        case BT_UINT8:                  return "BT_UINT8";
        case BT_UINT16:                 return "BT_UINT16";
        case BT_UINT32:                 return "BT_UINT32";
        case BT_UINT64:                 return "BT_UINT64";
        case BT_FLOAT:                  return "BT_FLOAT";
        case BT_DOUBLE:                 return "BT_DOUBLE";
        case BT_BOOL:                   return "BT_BOOL";
        case BT_CHAR:                   return "BT_CHAR";
        case BT_STRING:                 return "BT_STRING";
        case BT_VOID:                   return "BT_VOID";
        default:                        return "UNKNOWN"; // Should not happen if all enums are covered
    }
}


#define MAX_REGISTERED_TERMS 1024

// Function to read the content of a file
std::string readFile2String(const std::string& filePath) {
    FILE* f = fopen(filePath.c_str(), "rb");//binary mode prevents ascii code mode
    if(f){
         fseek(f, 0, SEEK_END);
         auto len = ftell(f);
         rewind(f);
         std::string data;
         data.resize(static_cast<size_t>(len));
         fread(&data[0], sizeof(char), len, f);
         fclose(f);
         return data;
    }
    return std::string("error");
}

//read the wanted terms from the stream and save them in array
//https://en.cppreference.com/w/cpp/io/basic_stringstream
//https://en.cppreference.com/w/cpp/string/basic_string/rfind
void register_terms(std::string s, Token* token_array){
    std::string token;
    int i = 0;//line num
    int j = 0;//array index
    std::stringstream stream(s);
    while(std::getline(stream, token, '{')){
        if(!token.empty() && j < MAX_REGISTERED_TERMS)
        {
            auto n = token.rfind("struct "); //+ 7 positions to reach search term in token
            if (n != std::string::npos){
                //https://cplusplus.com/reference/string/basic_string/npos/  defined as -1
                std::string term = token.substr(n+7,std::string::npos);
                while(term.back() == '\n'){
                    term.pop_back();
                }
                while(term.find(" ") != std::string::npos){
                    auto pos = term.find(" ");
                    term.erase(pos);
                }
                Token newToken = {TokenType::BT_STRING, term, -1};
                token_array[j] = newToken;
                ++j; //index num
            } 
        }else{break;}
        ++i;//line num  
    }
    for(int i = 0; i < MAX_REGISTERED_TERMS; ++i){
        if(token_array[i].lexeme.empty()){
            std::cout << "end of array\n";
            return;
        }
        std::cout << tkntype_str(token_array[i].type) << "  " << token_array[i].lexeme;
    }
}


// Function to display usage instructions
void displayUsage(const std::string& programName) {
    std::cout << "Usage: " << programName << " <input_file> <output_file>\n";
    std::cout << "  <input_file>  - Path to the C++ header file (e.g., example.hpp)\n";
    //std::cout << "  <class_name>  - Name of the class to parse (e.g., AActor)\n";
    //std::cout << "  <output_file> - Path to the output C# file (e.g., Offsets.cs)\n";
}

int main(int argc, char* argv[]) {
    if(argc > 1){
        std::string inputFilePath = argv[1];
        try {
            // Read the C++ file content
            std::string buffered_OUT = readFile2String(inputFilePath);
            if(!buffered_OUT.compare(std::string("error"))){
                throw "no file path";
            }
            Token search_terms[MAX_REGISTERED_TERMS];
            register_terms(buffered_OUT, search_terms);
            return 0;
            
        }
        catch (const std::exception& e) {
            // This catch block handles exceptions derived from std::exception
            std::cerr << "Caught std::exception: " << e.what() << "\n";
            return 3;
        }
        // Add a catch block for other types of exceptions, like C-style strings
        catch (const char* msg) {
            // This catch block handles C-style string literals thrown
            std::cerr << "Caught C-style string exception: " << msg << "\n";
            return 4;
        }
        catch (...) {
            // This catch block handles any other type of exception
            std::cerr << "Caught unknown exception\n";
            return 5;
        }
    }else{displayUsage(argv[0]); return 1;}
}



    // if (argc > 1 && (std::string(argv[1]) == "help" || std::string(argv[1]) == "Help") || argc < 2) {
	// 	displayUsage(argv[0]);
	// 	return 0;
    // }

    // if (argc > 3) {
	// 	std::cout << "Too many arguments provided.\n";
	// 	displayUsage(argv[0]);
    //     return 0;
    // }

    // // Parse command-line arguments
    // std::string inputFilePath = argv[1];
    // std::string className = "FSQSwayData";
    // std::string outputFilePath = argv[2];

    

    // return 0;
//}
