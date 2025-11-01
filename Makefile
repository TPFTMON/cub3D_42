# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/22 13:52:33 by abaryshe          #+#    #+#              #
#    Updated: 2025/11/01 08:09:41 by abaryshe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Variables for names and directiories ---
NAME = cub3D

TEST_NAME = test_cub3D

LIBFT = ${LIBFT_DIR}/libft.a
MLX = ${MLX_DIR}/libmlx.a

INC_DIR = build/includes
LIBFT_DIR = libft
MLX_DIR = mlx_linux

OBJ_DIR = objects

PARS_DIR = build/sources/parsing
ENGINE_DIR = build/sources/engine
CORE_DIR = build/sources

# --- Tools ---
FREM = rm -f
CC = cc
CMPFLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = ${CMPFLAGS} -g -fsanitize=address
INCLUDES = -I ${INC_DIR} -I ${LIBFT_DIR}/includes -I ${MLX_DIR}

LIBS_WITH_FLAGS = ${LIBFT} ${MLX} -lXext -lX11 -lm

# --- Sources ---
# The files to compile in parsing directory go HERE
# || || || || || ||
# \/ \/ \/ \/ \/ \/
PARS_FILES = parsing.c
ENGINE_FILES = engine.c hooks.c game_loop.c
CORE_FILES = cub3D.c init.c cleanup.c

PARS_SRCS = $(addprefix ${PARS_DIR}/, ${PARS_FILES})
ENGINE_SRCS = $(addprefix ${ENGINE_DIR}/, ${ENGINE_FILES})
CORE_SRCS = $(addprefix ${CORE_DIR}/, ${CORE_FILES})

SRCS = ${CORE_SRCS} ${PARS_SRCS} ${ENGINE_SRCS}

# --- Object Files ---
OBJS = $(addprefix ${OBJ_DIR}/, $(notdir $(SRCS:.c=.o)))

# Tell Make where to find .c files
vpath %.c ${CORE_DIR} ${PARS_DIR} ${ENGINE_DIR}

all: ${NAME}

${NAME}: ${OBJS} ${LIBS_WITH_FLAGS}
	${CC} ${CMPFLAGS} ${INCLUDES} ${OBJS} ${LIBS_WITH_FLAGS} -o ${NAME}

test: ${OBJS} ${LIBS_WITH_FLAGS}
	${CC} ${DEBUG_FLAGS} ${INCLUDES} ${OBJS} ${LIBS_WITH_FLAGS} -o ${TEST_NAME}

# Compile .c files to .o files in the objects/ directory
${OBJ_DIR}/%.o: %.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

${MLX}:
	$(MAKE) -C ${MLX_DIR}

${LIBFT}:
	$(MAKE) -C ${LIBFT_DIR}

clean:
	${FREM} ${OBJS}
	${FREM} -d ${OBJ_DIR}
	${MAKE} -C ${LIBFT_DIR} clean
	${MAKE} -C ${MLX_DIR} clean

fclean: clean
	${FREM} ${NAME}
	${FREM} ${TEST_NAME}
	${FREM} ${MSLIB}
	${FREM} ${TESTING}
	${MAKE} -C ${LIBFT_DIR} fclean

re: fclean all

.PHONY: all clean fclean re test
