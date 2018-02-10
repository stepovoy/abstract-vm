#ifndef OPERAND_H
#define OPERAND_H

#include <iostream>
#include <string>
#include <iomanip>
#include <float.h>
#include <limits.h>
#include <sstream>
#include <math.h>
#include "OperandFactory.hpp"
#include "AvmException.hpp"
#include "IOperand.hpp"

template <typename T> class Operand : public IOperand {

public:

	int getPrecision( void ) const {
		return _precision;
	}

	eOperandType getType( void ) const {
		return _type;
	}

	IOperand const * operator+( IOperand const & rhs ) const {
		eOperandType type = ( _type >= rhs.getType() ) ? _type : rhs.getType();
		int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
		try {
			std::stringstream ss (std::stringstream::out);
			if (type < Float) {
				long long r = std::stoll(_str) + std::stoll(rhs.toString());
				if (hasOverflow<long long>(r, type))
					throw OperandException("Overflow Exception!");
				ss << r;
			}
			else {
				long double r = std::stold(_str) + std::stold(rhs.toString());
				if (hasOverflow<long double>(r, type))
					throw OperandException("Overflow Exception!");
				ss << std::setprecision(precision) << r;
			}
			return (_factory->createOperand(type, ss.str()));
		}
		catch(const std::out_of_range& oor) {
			oor.what();
		}
		return (0);
	}

	IOperand const * operator-( IOperand const & rhs ) const {
		eOperandType type = (_type >= rhs.getType()) ? _type : rhs.getType();
		int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
		try {
			std::stringstream ss (std::stringstream::out);
			if (type < Float) {
				long long r = std::stoll(_str) - std::stoll(rhs.toString());
				if (hasOverflow<long long>(r, type))
					throw OperandException("Overflow Exception!");
				ss << r;
			}
			else {
				long double r = std::stold(_str) - std::stold(rhs.toString());
				if (hasOverflow<long double>(r, type))
					throw OperandException("Overflow Exception!");
				ss << std::setprecision(precision) << r;
			}
			return (_factory->createOperand(type, ss.str()));
		}
		catch(const std::out_of_range& oor) {
			oor.what();
		}
		return (0);
	}

	IOperand const * operator*( IOperand const & rhs ) const {
		eOperandType type = (_type >= rhs.getType()) ? _type : rhs.getType();
		int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();

		try {
			std::stringstream ss(std::stringstream::out);
			if (type < Float) {
				long long r = std::stoll(_str) * std::stoll(rhs.toString());
				if (hasOverflow<long long>(r, type)) {
					throw OperandException("Overflow Exception!");
				}
				ss << r;
			}
			else {
				long double r = std::stold(_str) * std::stold(rhs.toString());
				if (hasOverflow<long double>(r, type)) {
					throw OperandException("Overflow Exception!");
				}
				ss << std::setprecision(precision) << r;
			}
			return (_factory->createOperand(type, ss.str()));
		}
		catch(const std::out_of_range& oor) {
			oor.what();
		}
		return (0);
	}

	IOperand const * operator/( IOperand const & rhs ) const {
		eOperandType type = (_type >= rhs.getType()) ? _type : rhs.getType();
		int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
		try {
			if (std::stold(rhs.toString()) == 0) {
				throw OperandException("Division by zero !");
			}
			std::stringstream ss(std::stringstream::out);
			if (type < Float) {
				long long r = std::stoll(_str) / std::stoll(rhs.toString());
				if (hasOverflow<long long>(r, type)) {
					throw OperandException("Overflow Exception!");
				}
				ss << r;
			}
			else {
				long double r = std::stold(_str) / std::stold(rhs.toString());
				if (hasOverflow<long double>(r, type)) {
					throw OperandException("Overflow Exception!");
				}
				ss << std::setprecision(precision) << r;
			}
			return (_factory->createOperand(type, ss.str()));
		}
		catch(const std::out_of_range& oor) {
			oor.what();
		}
		return (0);
	}

	IOperand const * operator%( IOperand const & rhs ) const {
		eOperandType type = (_type >= rhs.getType()) ? _type : rhs.getType();
		int precision = ( _precision >= rhs.getPrecision() ) ? _precision: rhs.getPrecision();
		try {
			if (std::stold(rhs.toString()) == 0) {
				throw OperandException("Modulo by zero !");
			}
			std::stringstream ss(std::stringstream::out);
			if (type < Float) {
				long long r = std::stoll(_str) % std::stoll(rhs.toString());
				if (hasOverflow<long long>(r, type)) {
					throw OperandException("Overflow Exception!");
				}
				ss << r;
			}
			else {
				long double r = fmod(std::stold(_str), std::stold(rhs.toString()));
				if (hasOverflow<long double>(r, type)) {
					throw OperandException("Overflow Exception!");
				}
				ss << std::setprecision(precision) << r;
			}
			return (_factory->createOperand(type, ss.str()));
		}
		catch(const std::out_of_range& oor) {
			oor.what();
		}
		return (0);
	}

	std::string const & toString( void ) const {
		return (_str);
	}

	std::string	removeTrailingZeros(std::string s) const {
		for(int i = s.length() - 1; i >= 0; i--) {
			if (s[i] == '0') {
				s.erase(s.end() - 1);
			}
			else {
				break;
			}
		}
		return s;
	}

	template <typename U> bool	hasOverflow(U r, eOperandType type) const {
		switch (type) {
			case (Int8):
				return (r > SCHAR_MAX || r < SCHAR_MIN);
			case (Int16):
				return  (r > SHRT_MAX || r < SHRT_MIN);
			case (Int32):
				return (r > INT_MAX || r < INT_MIN);
			case (Float):
				return (r > FLT_MAX || r < -FLT_MAX);
			case (Double):
				return (r > DBL_MAX || r < -DBL_MAX);
			break;
		}
		return (true);
	}

	Operand();
	Operand(const Operand&);
	const Operand& operator=(const Operand&);
	Operand(std::string const & value, eOperandType type, int precision, const OperandFactory* factory) : _factory(factory), _type(type), _precision(precision) {
		try {
			if (type < Float) {
				long long v = std::stoll(value);
				
				if (hasOverflow<long long>(v, type)) {
					throw OperandException("Overflow Exception!");
				}
				_value = static_cast<T>(v);
				std::stringstream ss(std::stringstream::out);
				ss << std::setprecision(precision) << v;
				_str = ss.str();
			}
			else {
				long double	v = std::stold(value);

				if (hasOverflow<long double>(v, type)) {
					throw OperandException("Overflow Exception!");
				}
				_value = static_cast<T>(v);
				std::stringstream ss(std::stringstream::out);
				ss << std::setprecision(precision) << v;
				_str = ss.str();
			}
		}
		catch(const std::out_of_range& oor) {
			oor.what();
		}
	}
	~Operand( void ) {
	}

private:

	class OperandException : public AvmException {

	public:

		OperandException(const std::string& message) : AvmException(), _msg(message){
		}
	
	  	virtual const char* what() const throw () {
   			return _msg.c_str();
		}

		virtual ~OperandException() throw (){
		}

	private:

		std::string			_msg;

	};

	T						_value;
	const OperandFactory*	_factory;
	std::string				_str;
	eOperandType			_type;
	int						_precision;
};

#endif