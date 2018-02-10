#ifndef OPERAND_FACTORY_H
#define OPERAND_FACTORY_H

#include <string>
#include <map>
#include "IOperand.hpp"

class OperandFactory {

public:

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	OperandFactory();
	OperandFactory(const OperandFactory&);
	const OperandFactory& operator=(const OperandFactory&);
	~OperandFactory();

private:

	std::map<eOperandType, IOperand const* (OperandFactory::*)(std::string const & value) const> create;
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
	
};

#endif