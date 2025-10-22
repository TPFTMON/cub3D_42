# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/22 13:52:33 by abaryshe          #+#    #+#              #
#    Updated: 2025/10/22 14:40:29 by abaryshe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Variables for names and directiories ---
NAME = cub3D

INC_DIR = build/includes
LIBFT_DIR = libft
LIBFT = ${LIBFT_DIR}/libft.a
OBJ_DIR = objects

PARS_DIR = build/sources/parsing
PLAY_DIR = build/sources/player

# --- Tools ---
FREM = rm -f
CC = cc
CMPFLAGS = -Wall -Wextra -Werror
DBUG_FLAGS = ${CMPFLAGS} -g -fsanitize=address
INCLUDES = -I ${INC_DIR} -I ${LIBFT_DIR}/includes
LINK_FLAGS = -lm

# --- Sources ---
PARS_FILES = parsing.c
PLAY_FILES = player.c

PARS_SRCS = $(addprefix ${PARS_DIR}/, ${PARS_FILES}) #!!!
PLAY_SRCS = $(addprefix ${PLAY_DIR}/, ${PLAY_FILES})

SRCS = build/sources/cub3D.c ${PARS_SRCS} ${PLAY_SRCS}

# --- Object Files ---
OBJS = $(addprefix ${OBJ_DIR}/, $(notdir $(SRCS:.c=.o)))

# Tell Make where to find .c files
vpath %.c build/sources ${PARS_DIR} ${PLAY_DIR}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CMPFLAGS} ${INCLUDES} ${OBJS} -o ${NAME}

test: ${OBJS}
	${CC} ${DBUG_FLAGS} ${INCLUDES} ${OBJS} -o ${NAME}

# Compile .c files to .o files in the objects/ directory
${OBJ_DIR}/%.o: %.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

clean:
	${FREM} ${OBJS}
	${FREM} -d ${OBJ_DIR}
	${MAKE} -C ${LIBFT_DIR} clean

fclean: clean
	${FREM} ${NAME}
	${FREM} ${MSLIB}
	${FREM} ${TESTING}
	${MAKE} -C ${LIBFT_DIR} fclean

re: fclean all

.PHONY: all clean fclean re test
