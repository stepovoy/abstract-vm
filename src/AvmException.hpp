#ifndef AVM_EXCEPTION_H
# define AVM_EXCEPTION_H

class AvmException : public std::exception {

public:

    virtual const char* what() const throw () {
        return _msg.c_str();
    }

    AvmException() {};
    AvmException(const AvmException&);
    const AvmException& operator=(const AvmException &);
    virtual ~AvmException() throw (){}

private:

	std::string         _msg;

};

#endif