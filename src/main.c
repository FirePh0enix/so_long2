/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 00:50:52 by ledelbec          #+#    #+#             */
/*   Updated: 2024/02/03 00:31:27 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data/vector.h"
#include "entity.h"
#include "graph.h"
#include "libft.h"
#include "math/vec2.h"
#include "mlx.h"
#include "so_long.h"
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

void	game_deinit(t_game *game)
{
	free(game->keys);
}

static t_sprite	**_load_frames(t_game *game, char *name, int size)
{
	char		buf[128];
	int			i;
	t_sprite	**sprites;

	i = 0;
	sprites = malloc(sizeof(t_sprite) * size);
	while (i < size)
	{
		sprintf(buf, name, i);
		sprites[i] = sprite(game, buf);
		i++;
	}
	return (sprites);
}

static void	_setup_game(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "so_long");
	game->keys = ft_calloc(0xFFFF, sizeof(bool));
	game->canvas = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->entities = vector_new(sizeof(t_entity *), 0);
	game->graph = new_graph();
	game->ground = sprite(game, "textures/gen/Mid.xpm");
	game->solid = sprite(game, "textures/gen/Water.xpm");
	game->gem = sprite(game, "textures/gen/Mid.xpm");
	game->door = sprite(game, "textures/gen/Water.xpm");
	game->player_s = sprite(game, "textures/gen/Goblin_Idle/0.xpm");
	game->player_idle = _load_frames(game, "textures/gen/Goblin_Idle/%d.xpm", 6);
	game->player_walk = _load_frames(game, "textures/gen/Goblin_Walk/%d.xpm", 6);
	game->money = sprite(game, "textures/gen/Gold.xpm");
	game->money_spawn = _load_frames(game, "textures/gen/Gold_Spawn/%d.xpm", 7);

	game->ground_mid = sprite(game, "textures/gen/Mid.xpm");
	game->ground_top = sprite(game, "textures/gen/Top.xpm");
	game->ground_topleft = sprite(game, "textures/gen/TopLeft.xpm");
	game->ground_topright = sprite(game, "textures/gen/TopRight.xpm");
	game->ground_left = sprite(game, "textures/gen/Left.xpm");
	game->ground_right = sprite(game, "textures/gen/Right.xpm");
	game->ground_bot = sprite(game, "textures/gen/Bot.xpm");
	game->ground_botleft = sprite(game, "textures/gen/BotLeft.xpm");
	game->ground_botright = sprite(game, "textures/gen/BotRight.xpm");
	game->ground_toplr = sprite(game, "textures/gen/TopLR.xpm");
	game->ground_lr = sprite(game, "textures/gen/LR.xpm");
	game->ground_botlr = sprite(game, "textures/gen/BotLR.xpm");
	game->ground_leftbt = sprite(game, "textures/gen/LeftBT.xpm");
	game->ground_bt = sprite(game, "textures/gen/BT.xpm");
	game->ground_rightbt = sprite(game, "textures/gen/RightBT.xpm");
	game->ground_all = sprite(game, "textures/gen/All.xpm");

	game->btn_left = sprite(game, "textures/gen/Btn_Left.xpm");
	game->btn_mid = sprite(game, "textures/gen/Btn_Mid.xpm");
	game->btn_right = sprite(game, "textures/gen/Btn_Right.xpm");

	game->hl_tl = sprite(game, "textures/gen/hl_tl.xpm");
	game->hl_tr = sprite(game, "textures/gen/hl_tr.xpm");
	game->hl_bl = sprite(game, "textures/gen/hl_bl.xpm");
	game->hl_br = sprite(game, "textures/gen/hl_br.xpm");
}

static int	_edit_main(int argc, char *argv[])
{
	t_game	game;
	char	*filename;

	(void) argc;
	_setup_game(&game);
	filename = argv[1];
	game.map = map_load(&game, filename, true);
	if (!game.map)
		return (ft_printf("Error\nInvalid map\n"), 1);
	mlx_do_key_autorepeatoff(game.mlx);
	mlx_hook(game.win, KeyPress, KeyPressMask, key_pressed_hook, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, key_released_hook, &game);
	mlx_hook(game.win, 17, 0, close_hook, &game);
	mlx_mouse_hook(game.win, edit_mouse_hook, &game);
	mlx_loop_hook(game.mlx, edit_update_hook, &game);
	mlx_loop(game.mlx);
	map_save(game.map, &game, filename);
	game_deinit(&game);
	mlx_do_key_autorepeaton(game.mlx);
	mlx_destroy_display(game.mlx);
	return (0);
}

static int	_normal_main(int argc, char *argv[])
{
	t_game	game;

	(void) argc;
	_setup_game(&game);
	game.map = map_load(&game, argv[1], false);
	if (!game.map)
		return (ft_printf("Error\nInvalid map\n"), 1);
	game.menu = menu_new();
	game.menu_opened = true;
	mlx_do_key_autorepeatoff(game.mlx);
	mlx_hook(game.win, KeyPress, KeyPressMask, key_pressed_hook, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, key_released_hook, &game);
	mlx_hook(game.win, 17, 0, close_hook, &game);
	mlx_mouse_hook(game.win, mouse_hook, &game);
	mlx_loop_hook(game.mlx, update_hook, &game);
	mlx_loop(game.mlx);
	game_deinit(&game);
	mlx_do_key_autorepeaton(game.mlx);
	mlx_destroy_display(game.mlx);
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (1);
	else if (argc == 3 && strcmp(argv[2], "--edit") == 0)
		return (_edit_main(argc, argv));
	else
		return (_normal_main(argc, argv));
}
