#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <list>
#include "AvmException.hpp"

enum token {
    PUSH = 258,
    POP = 259,
    DUMP = 260,
    ASSERT = 261,
    ADD = 262,
    SUB = 263,
    MUL = 264,
    DIV = 265,
    MOD = 266,
    PRINT = 267,
    EXIT = 268,
    END = 269,
    COMMENT = 270,
    EOL = 271,
    INT8 = 272,
    INT16 = 273,
    INT32 = 274,
    FLOAT = 275,
    DOUBLE = 276,
    ERROR = 278
};

struct Lexeme {
    token type;
    const std::string value;
};

class Lexer {

public:

    void run();
    std::list<Lexeme>& lexemes();
    
    Lexer();
    Lexer(int argc, char** argv);
    Lexer(const Lexer&);
    const Lexer& operator=(const Lexer&);
    ~Lexer();

private:

    class LexerException : public AvmException {

    public:

        LexerException(const std::string& message) : AvmException() , _msg(message) {
        }
    
        virtual const char* what() const throw () {
            return _msg.c_str();
        }

        virtual ~LexerException() throw (){
        }

    private:

        std::string _msg;

    };
    std::list<Lexeme> _lexemes;
};

#endif