# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 12:15:15 by mlarra            #+#    #+#              #
#    Updated: 2023/02/01 16:33:05 by wcollen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	webserv

DIR			=	./src/

SRC			=	${addprefix ${DIR}, CgiHandler.cpp\
									Client.cpp\
									Config.cpp\
									Handler.cpp\
									Location.cpp\
									main.cpp\
									Request.cpp\
									ResponseConfig.cpp\
									Server.cpp\
									utils.cpp\
									Response.cpp\
									ResponseHeader.cpp\
									}
						

DIR_HEADERS	=	./includes/

HEADERS		=	${DIR_HEADERS}webserv.hpp

OBJ			=	${SRC:%.cpp=%.o}

FLAGS		=	-Wall -Wextra -std=c++98 #-g -Werror

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
