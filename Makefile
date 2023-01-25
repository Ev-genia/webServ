# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 12:15:15 by mlarra            #+#    #+#              #
#    Updated: 2023/01/25 15:20:59 by mlarra           ###   ########.fr        #
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
									}

#									Response.cpp\

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
