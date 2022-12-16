# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 12:15:15 by mlarra            #+#    #+#              #
#    Updated: 2022/12/16 14:41:49 by wcollen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	webserv

DIR			=	./src/

SRC			=	${addprefix ${DIR}, Client.cpp\
									Config.cpp\
									Location.cpp\
									main.cpp\
									Response.cpp\
									Server.cpp\
									utils.cpp\
									}

#									Handler.cpp\
#									Request.cpp
DIR_HEADERS	=	./includes/

HEADERS		=	${DIR_HEADERS}webserv.hpp

OBJ			=	${SRC:%.cpp=%.o}

FLAGS		=	-Wall -Wextra -Werror -std=c++98 #-g

CC			=	c++

RM			=	rm -f

.PHONY	:	all clean fclean re

%.o		:	%.cpp ${HEADERS}
	${CC} ${FLAGS} -c $< -o $@

${NAME}	:	${OBJ}
	${CC} ${FLAGS} -I ${HEADERS} ${SRC} -o $@

all		:	${NAME}

clean	:
	${RM} ${OBJ}

fclean	:	clean
	${RM} ${NAME}

re		:	fclean all
