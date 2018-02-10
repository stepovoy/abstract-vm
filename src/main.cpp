#include <iostream>
#include "AvmException.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"

int main(int argc, char **argv) {
	try {
    	Lexer   lexer(argc, argv);
    	lexer.run();
        Parser  parser(lexer.lexemes());
    	parser.run();
    } catch (AvmException& e) {
    	std::cout << e.what() << std::endl;
    }
}    