# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/05 14:39:36 by ledelbec          #+#    #+#              #
#    Updated: 2023/12/27 13:34:46 by ledelbec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# additional functions:
#
# - realloc (TODO remove)
# - sprintf (TODO remove)
# - gettimeofday (For animations)
# - srand / rand

SOURCES = \
	src/main.c \
	src/expose.c \
	src/tiles.c \
	src/sprite.c \
	src/anim.c \
	src/entity.c \
	src/entity/collectible.c \
	src/entity/door.c \
	src/entity/projectile.c \
	src/entity/golem.c \
	src/entity/wall.c \
	src/player/player.c \
	src/player/dash.c \
	src/render/draw.c \
	src/render/draw_sprite.c \
	src/render/draw_debug.c \
	src/render/light.c \
	src/render/graph.c \
	src/physics/entity.c \
	src/physics/box.c \
	src/physics/vec2_common.c \
	src/physics/vec2_calc.c \
	src/physics/vec2i.c \
	src/map/map.c \
	src/map/verif.c \
	src/map/ground_tile.c \
	src/ui/base_ui.c \
	src/ui/health_bar.c \
	src/vector.c

TEXTURES = \
	textures/exit_door/exit_door1.png \
	textures/exit_door/exit_door2.png \
	textures/exit_door/exit_door3.png \
	textures/exit_door/exit_door4.png \
	textures/exit_door/exit_door5.png \
	textures/exit_door/exit_door6.png \
	\
	$(wildcard textures/gen/*.png) \
	$(wildcard textures/gem/*.png) \
	$(wildcard textures/ui/*.png) \
	\
	textures/player/player.png \
	textures/golem.png \
	textures/projectile.png \
	textures/ice_wall.png

NAME = so_long

CFLAGS = -Wall -Wextra -Imlx -Ilibft -MMD -g3 -fPIC -O2 -fno-builtin # -Werror
LDFLAGS= -lm -lX11 -lXext

OBJECTS = $(SOURCES:.c=.o)
TEXTURES_XPM = $(TEXTURES:.png=.xpm)

all: $(NAME)

mlx/libmlx.a:
	cd mlx && make

libft/libft.a:
	cd libft && make

$(NAME): mlx/libmlx.a libft/libft.a textures/gen $(TEXTURES_XPM) $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) mlx/libmlx.a libft/libft.a $(LDFLAGS)

%.xpm: %.png
	convert $< $@

-include $(OBJECTS:.o=.d)

textures/gen:
	bash spritesheet.sh

clean:
	rm -rf $(OBJECTS) $(TEXTURES_XPM) textures/gen
	cd mlx && make clean && rm -f libmlx.a
	cd libft && make fclean

fclean: clean
	rm -f $(NAME)

re: fclean all
