/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:37:22 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 22:53:01 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entity.h"
#include "entity/collectible.h"
#include "entity/door.h"
#include "entity/golem.h"
#include "entity/projectile.h"
#include "entity/wall.h"
#include "libft.h"
#include "mlx.h"
#include "player/player.h"
#include "render/graph.h"
#include "so_long.h"
#include "vector.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>

static int	key_pressed_hook(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
	{
		// FIXME: For some reason the escape key is pressed continuously when
		// starting the game, this goes away after touching a key
		// ft_printf("ESCAPE pressed!\n");
		// mlx_loop_end(game->mlx);
	}
	else if (keycode == XK_Up)
	{
		game->mouvements++;
		game->key_up = 1;
	}
	else if (keycode == XK_Down)
	{
		game->mouvements++;
		game->key_down = 1;
	}
	else if (keycode == XK_Left)
	{
		game->mouvements++;
		game->key_left = 1;
	}
	else if (keycode == XK_Right)
	{
		game->mouvements++;
		game->key_right = 1;
	}
	else if (keycode == 113)
		game->key_q = 1;
	else if (keycode == 119)
		game->key_w = 1;
	else if (keycode == 101)
		game->key_e = 1;
	else if (keycode == 114)
		game->key_r = 1;
	else if (keycode == 32)
		game->key_space = 1;
	return (0);
}

static int	key_release_hook(int keycode, t_game *game)
{
	if (keycode == XK_Up)
		game->key_up = 0;
	else if (keycode == XK_Down)
		game->key_down = 0;
	else if (keycode == XK_Left)
		game->key_left = 0;
	else if (keycode == XK_Right)
		game->key_right = 0;
	else if (keycode == 113)
		game->key_q = 0;
	else if (keycode == 119)
		game->key_w = 0;
	else if (keycode == 101)
		game->key_e = 0;
	else if (keycode == 114)
		game->key_r = 0;
	else if (keycode == 32)
		game->key_space = 0;
	return (0);
}

static int	close_hook(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}

static int	on_update(t_game *game)
{
	unsigned int	i;
	t_entity		*entity;
	suseconds_t		time;

	time = getms();
	if (time - game->last_update_millis < TIME_BETWEEN_FRAMES)
		return (0);
	game->last_update_millis = time;
	i = 0;
	while (i < vector_size(game->map->entities))
	{
		entity = game->map->entities[i];
		if (entity->state == 0)
		{
			i++;
			continue ;
		}
		entity->type->update_hook(game, entity, entity->extension);
		i++;
	}
	on_expose(game);
	return (0);
}

static void	map_init(t_game *game, t_map *map)
{
	t_ui	*ui;

	map->player = new_entity(game, game->map->start_x, game->map->start_y,
			game->player_type);
	add_entity(game, map->player);
	ui = malloc(sizeof(t_ui));
	ui->game = game;
	ui->x = 0;
	ui->y = 0;
	ui->order = 100;
	ui->sprite = game->tiles.ui;
	ui->update_hook = base_ui_update;
	ui->effect = base_ui_effect;
	vector_add((void *)&game->ui, &ui);
	ui = malloc(sizeof(t_ui));
	ui->game = game;
	ui->x = 49 * PIXEL_SCALE;
	ui->y = 335 * PIXEL_SCALE;
	ui->order = 101;
	ui->sprite = game->tiles.health_bar;
	ui->update_hook = health_bar_update;
	ui->effect = health_bar_effect;
	vector_add((void *)&game->ui, &ui);
}

static void	init_entity_types(t_game *game)
{
	game->player_type = ft_calloc(sizeof(t_entity_type), 1);
	game->player_type->extension_size = sizeof(t_player_ext);
	game->player_type->sprite = game->tiles.player;
	game->player_type->spawn_hook = (void *)player_spawn;
	game->player_type->update_hook = (void *)player_update;
	game->player_type->render_order = 0;
	game->collectible_type = ft_calloc(sizeof(t_entity_type), 1);
	game->collectible_type->extension_size = sizeof(t_collectible_ext);
	game->collectible_type->sprite = game->tiles.gem[0];
	game->collectible_type->spawn_hook = (void *)collectible_spawn;
	game->collectible_type->update_hook = (void *)collectible_update;
	game->collectible_type->render_order = -1;
	game->door_type = ft_calloc(sizeof(t_entity_type), 1);
	game->door_type->extension_size = sizeof(t_door_ext);
	game->door_type->sprite = game->tiles.door[0];
	game->door_type->spawn_hook = (void *)door_spawn;
	game->door_type->update_hook = (void *)door_update;
	game->door_type->render_order = -10;
	game->projectile_type = ft_calloc(sizeof(t_entity_type), 1);
	game->projectile_type->extension_size = sizeof(t_projectile_ext);
	game->projectile_type->sprite = game->tiles.projectile;
	game->projectile_type->spawn_hook = (void *)projectile_spawn;
	game->projectile_type->update_hook = (void *)projectile_update;
	game->projectile_type->render_order = 2;
	game->golem_type = ft_calloc(sizeof(t_entity_type), 1);
	game->golem_type->extension_size = sizeof(t_golem_ext);
	game->golem_type->sprite = game->tiles.golem;
	game->golem_type->spawn_hook = (void *)golem_spawn;
	game->golem_type->update_hook = (void *)golem_update;
	game->golem_type->render_order = -1;
	game->wall_type = ft_calloc(sizeof(t_entity_type), 1);
	game->wall_type->extension_size = sizeof(t_wall_ext);
	game->wall_type->sprite = game->tiles.wall;
	game->wall_type->spawn_hook = (void *)wall_spawn;
	game->wall_type->update_hook = (void *)wall_update;
	game->wall_type->render_order = 1;
}

suseconds_t	getms(void)
{
	struct timeval	val;

	gettimeofday(&val, NULL);
	return ((val.tv_sec * 1000000 + val.tv_usec) / 1000);
}

int	main(int argc, char *argv[])
{
	void	*mlx;
	void	*window;
	t_game	game;

	(void)argc;
	(void)argv;
	ft_bzero(&game, sizeof(t_game));
	mlx = mlx_init();
	window = mlx_new_window(mlx, 1280, 720, "so_long");
	game.mlx = mlx;
	game.win = window;
	game.camera_x = 0;
	game.camera_y = 0;
	game.canvas = mlx_new_image(mlx, 1280, 720);
	game.graph = new_graph();
	game.mouvements = 0;
	game.ui = vector_new(sizeof(t_ui *), 0);
	load_tiles(&game);
	init_entity_types(&game);
	game.map = create_map(&game, argv[1]);
	if (!game.map)
		return (1);
	game.last_update_millis = 0;
	map_init(&game, game.map);
	mlx_do_key_autorepeatoff(mlx);
	mlx_hook(window, KeyPress, KeyPressMask, key_pressed_hook, &game);
	mlx_hook(window, KeyRelease, KeyReleaseMask, key_release_hook, &game);
	mlx_hook(window, 17, 0, close_hook, &game);
	mlx_loop_hook(mlx, on_update, &game);
	mlx_expose_hook(window, on_expose, &game);
	mlx_loop(mlx);
	mlx_do_key_autorepeaton(mlx);
	mlx_destroy_display(mlx);
}
