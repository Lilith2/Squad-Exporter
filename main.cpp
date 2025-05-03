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
    int col;
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


#define MAX_REGISTERED_TERMS 1024

// Function to read the content of a file
std::string readOffsetFile(const std::string& filePath) {
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

void register_terms(std::stringstream s, std::string* str_arr){
    
}


// Function to display usage instructions
void displayUsage(const std::string& programName) {
    std::cout << "Usage: " << programName << " <input_file> <output_file>\n";
    std::cout << "  <input_file>  - Path to the C++ header file (e.g., example.hpp)\n";
    //std::cout << "  <class_name>  - Name of the class to parse (e.g., AActor)\n";
    std::cout << "  <output_file> - Path to the output C# file (e.g., Offsets.cs)\n";
}

int main(int argc, char* argv[]) {
    std::string inputFilePath = argv[1];
    try {
        // Read the C++ file content
        std::string buffered_OUT = readOffsetFile(inputFilePath);
        if(!buffered_OUT.compare(std::string("error"))){
            throw 2;
        }
        std::string search_terms[MAX_REGISTERED_TERMS];
        register_terms(std::stringstream(buffered_OUT), search_terms);
        return 0;
        
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
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
