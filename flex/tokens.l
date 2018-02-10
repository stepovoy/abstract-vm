%{
#include "Lexer.hpp"

%}


%option noyywrap
%option noinput
%option nounput

%x BEGIN_INT8 BEGIN_INT16 BEGIN_INT32 BEGIN_FLOAT BEGIN_DOUBLE END_TYPE

%%

[ \t]										;
"\n"										{ return EOL; }
"int8("										{ BEGIN(BEGIN_INT8); }
"int16("									{ BEGIN(BEGIN_INT16); }
"int32("									{ BEGIN(BEGIN_INT32); }
"float("									{ BEGIN(BEGIN_FLOAT); }
"double("									{ BEGIN(BEGIN_DOUBLE); }

<BEGIN_INT8>[+-]?[0-9]+						{ BEGIN(END_TYPE); return INT8; }
<BEGIN_INT8>.								{ return ERROR; }
<BEGIN_INT16>[+-]?[0-9]+					{ BEGIN(END_TYPE); return INT16; }
<BEGIN_INT16>.								{ return ERROR; }
<BEGIN_INT32>[+-]?[0-9]+					{ BEGIN(END_TYPE); return INT32; }
<BEGIN_INT32>.								{ return ERROR; }
<BEGIN_FLOAT>[+-]?[0-9]+(\.[0-9]+)?			{ BEGIN(END_TYPE); return FLOAT; }
<BEGIN_FLOAT>.								{ return ERROR; }
<BEGIN_DOUBLE>[+-]?[0-9]+(\.[0-9]+)?		{ BEGIN(END_TYPE); return DOUBLE; }
<BEGIN_DOUBLE>.								{ return ERROR; }
<END_TYPE>"\n"								{ return ERROR; }
<END_TYPE>[ \t]+							;
<END_TYPE>\)								{ BEGIN(INITIAL); }
<END_TYPE>. 								{ return (ERROR); }

push										{ return PUSH; }
pop											{ return POP; }
dump										{ return DUMP; }
assert										{ return ASSERT; }
add											{ return ADD; }
sub											{ return SUB; }
mul											{ return MUL; }
div											{ return DIV; }
mod											{ return MOD; }
print										{ return PRINT; }
exit										{ return EXIT; }
^;;$										{ return END; }
;.*											;
.											{ return ERROR; }

%%
