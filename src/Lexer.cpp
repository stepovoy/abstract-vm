#include "Lexer.hpp"

extern int      yylex(void);
extern FILE*    yyin;
extern char*    yytext;
extern int      yyleng;

void Lexer::run() {
    int tok;

    while ((tok = yylex())) {
        if (tok == ERROR) {
            throw LexerException("Lexer Exception. Unknown instruction!");
        }
        if (tok == END) {
            break;
        }
        const std::string value = yytext;
        _lexemes.push_back({static_cast<token>(tok), value});
    }
}

std::list<Lexeme>& Lexer::lexemes() {
    return _lexemes;
}

Lexer::Lexer(int argc, char** argv) : _lexemes(0) {
    if (argc > 2)
        throw LexerException("Lexer Exception. Too many arguments!");
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            throw LexerException("Lexer Exception. File is not readable!");
        }
    }
}

Lexer::~Lexer() {
}