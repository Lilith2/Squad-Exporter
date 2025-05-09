# Lexer
## What is the Token?
```
typedef struct {
    TokenType type;
    std::string term;
    std::string* fields; //set array size with calloc later
    int field_count;// array size
    bool lexed = false;

    ~Token() {
        if (fields) {
            for (int i = 0; i < field_count; ++i) {
                fields[i].~std::string();
            }
            free(fields);
        }
    }
} Token;
```
Token uses std::string[] for the fields of each definition. TokenType is not fully relevant yet. Reference JAI's lexer for the proper use. I also understand that just using strings isn't the "correct lexer way" but everyone starts somewhere.
- C++ Tokenizer, catches class and struct definitions without the methods. 
- C# Tokenizer, identifies empty structs within input file.

# Parser
### Handles the output of C# struct fields determined by tokens created by Lexer.
- The word term is used to describe the struct or class requested by input file.
- boolean lexed is used to avoid overriding in use tokens when doing passes on new files. All tokens are stored in a single array.
- Token is analyzed for the offset value in the comment, the type of either built-in or custom, and the variable name
- Data is arranged in order and saved to a new array of tokens ready for output
- Output tokens are parsed further to ensure the term is correctly correlated with the fields in the C# output
