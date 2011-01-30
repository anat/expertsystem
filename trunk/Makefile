# Makefile for Expert system

# Fact :

NAME	=	expert_system

SRC		=	./src/main.cpp		\
			./src/Fact.cpp		\
			./src/Parserv2.cpp	\
			./src/And.cpp		\
			./src/Xor.cpp

OBJ		=	$(SRC:.cpp=.o)

RM		=	rm -f

CC		=	g++

INCLUDE		=	./inc

CPPFLAGS	+=	-g3 -W -Wall -I $(INCLUDE)

# Rules :

$(OBJ)		:	$(SRC)

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

clean		:
			$(RM) ./src/*.o

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all
