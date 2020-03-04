# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/04 22:24:52 by ehakam            #+#    #+#              #
#    Updated: 2020/03/04 22:39:49 by ehakam           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

SRC =	cub/ft_cub_main.c \
		cub/ft_cub_utils.c \
		cub/ft_cub_ray.c \
		cub/ft_cub_player.c \
		cub/ft_cub_events.c \
		cub/ft_cub_wall.c \
		cub/ft_cub_read.c \
		utils/ft_putnbr_fd.c \
		utils/ft_strnstr.c \
		utils/ft_split.c \
		utils/ft_atoi.c \
		utils/get_next_line.c \
		utils/get_next_line_utils.c
OUT = cub3d
ARG = map.cub
all: clean
	@echo "Compiling..."
	@gcc -I minilibx -lmlx -framework OpenGL -framework AppKit $(SRC) -o $(OUT) -O3
	@make exec
clean:
	@echo "Cleaning..."
	@rm -rf *.o $(OUT)

exec:
	@echo "Running..."
	@./$(OUT) $(ARG)