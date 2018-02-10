#include <iostream>
#include "Parser.hpp"

void Parser::run() {
    for (std::list<Lexeme>::iterator it = _lexemes.begin() ; it != _lexemes.end() ; it++) {
        if (it->type > END) {
            continue;
        }
        (this->*_operations.at(it->type - PUSH))(it);
    }
    throw ParserException("No exit at the end of the file!");
}

void Parser::push(std::list<Lexeme>::iterator& it) {
    std::list<Lexeme>::iterator next = ++it;
    _stack.push_front(_factory.createOperand(static_cast<eOperandType>(next->type - INT8), next->value));
}

void Parser::pop(std::list<Lexeme>::iterator& it) {
    (void)it;
    if (_stack.size() == 0) {
        throw ParserException("Cannot pop on empty stack!");
    }
    _stack.pop_front();
}

void Parser::dump(std::list<Lexeme>::iterator& it) {
    (void)it;
    if (_stack.size() == 0) {
        throw ParserException("Cannot dump on empty stack!");
    }
    std::list<const IOperand*>::iterator itr;

    for (itr = _stack.begin(); itr != _stack.end(); ++itr) {
        std::cout << (*itr)->toString() << std::endl;
    }
}

void Parser::assert(std::list<Lexeme>::iterator& it) {
    if (_stack.size() == 0) {
        throw ParserException("Cannot assert on empty stack!");
    }
    std::list<Lexeme>::iterator next = ++it;
    const IOperand* op = *(_stack.begin());
    if (op->toString() != next->value) {
        throw ParserException("Wrong value in assert!");
    }
    if (op->getType() != next->type - INT8) {
        throw ParserException("Wrong type in assert!");
    }
}

void Parser::add(std::list<Lexeme>::iterator& it) {
    (void)it;
    if (_stack.size() < 2) {
        throw ParserException("Insufficient values to use add!");
    }
    const IOperand* op1 = *(_stack.begin());
    _stack.pop_front();
    const IOperand* op2 = *(_stack.begin());
    _stack.pop_front();
    const IOperand* r  = *op1 + *op2;
    delete op1;
    delete op2;
    _stack.push_front(r);
}

void Parser::sub(std::list<Lexeme>::iterator& it) {
    (void)it;
    if (_stack.size() < 2) {
        throw ParserException("Insufficient values to use sub!");
    }
    const IOperand* op1 = *(_stack.begin());
    _stack.pop_front();
    const IOperand* op2 = *(_stack.begin());
    _stack.pop_front();
    const IOperand* r  = *op2 - *op1;
    delete op1;
    delete op2;
    _stack.push_front(r);
}

void Parser::mul(std::list<Lexeme>::iterator& it) {
    (void)it;
    if (_stack.size() < 2) {
        throw ParserException("Insufficient values to use mul!");
    }
    const IOperand* op1 = *(_stack.begin());
    _stack.pop_front();
    const IOperand* op2 = *(_stack.begin());
    _stack.pop_front();
    const IOperand* r  = *op1 * *op2;
    delete op1;
    delete op2;
    _stack.push_front(r);
}

void Parser::div(std::list<Lexeme>::iterator& it) {
    (void)it;
    if (_stack.size() < 2) {
        throw ParserException("Insufficient values to use div!");
    }
    const IOperand* op1 = *(_stack.begin());
    _stack.pop_front();
    const IOperand* op2 = *(_stack.begin());
    _stack.pop_front();
    const IOperand* r  = *op2 / *op1;
    delete op1;
    delete op2;
    _stack.push_front(r);
}

void Parser::mod(std::list<Lexeme>::iterator& it) {
    (void)it;
    if (_stack.size() < 2) {
        throw ParserException("Insufficient values to use mod!");
    }
    const IOperand* op1 = *(_stack.begin());
    _stack.pop_front();
    const IOperand* op2 = *(_stack.begin());
    _stack.pop_front();
    const IOperand* r  = *op2 % *op1;
    delete op1;
    delete op2;
    _stack.push_front(r);
}

void Parser::print(std::list<Lexeme>::iterator& it) {
    (void)it;
    if (_stack.size() == 0) {
        throw ParserException("Cannot print empty stack!");
    }
    const IOperand* op1 = *(_stack.begin());
    if (op1->getType() != Int8) {
        throw ParserException("Only 8-bit integer can be printed!");
    }
    std::cout << static_cast<char>(std::stoi(op1->toString())) << std::endl;
}

void Parser::exit(std::list<Lexeme>::iterator& it) {
    (void)it;
    std::exit(0);
}

Parser::Parser(std::list<Lexeme>& lexemes) : _lexemes(lexemes) {
    _operations[0] = &Parser::push;
    _operations[1] = &Parser::pop;
    _operations[2] = &Parser::dump;
    _operations[3] = &Parser::assert;
    _operations[4] = &Parser::add;
    _operations[5] = &Parser::sub;
    _operations[6] = &Parser::mul;
    _operations[7] = &Parser::div;
    _operations[8] = &Parser::mod;
    _operations[9] = &Parser::print;
    _operations[10] = &Parser::exit;
}

Parser::~Parser() {
}