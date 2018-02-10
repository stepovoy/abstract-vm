NAME = avm

VPATH = src

CC = clang++

FLAGS = -std=c++11 -Wall -Wextra -Werror -Wno-sign-compare -Wno-deprecated-register -g

SRCS = main.cpp	\
	   Lexer.cpp \
	   Parser.cpp \
	   OperandFactory.cpp \
	   tokens.cpp

BIN_DIR = bin/

BINS = $(addprefix $(BIN_DIR), $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(BINS)
	$(CC) $(FLAGS) $(BINS) -o $(NAME)

$(BIN_DIR)%.o: %.cpp
	@mkdir -p $(shell dirname $@)
	$(CC) $(FLAGS) -c -o $@ $<

src/tokens.cpp: flex/tokens.l
	flex -o $@ $<

clean:
	/bin/rm -rf $(BIN_DIR)
	/bin/rm -f src/tokens.cpp

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

tests:
	make -C test/ re
