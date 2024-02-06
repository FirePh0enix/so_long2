/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:37:47 by ledelbec          #+#    #+#             */
/*   Updated: 2024/02/06 11:13:06 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "render/render.h"
#include "entity.h"
#include "data/vector.h"

static void	_free_anim(t_game *game, t_img **sprites, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		mlx_destroy_image(game->mlx, sprites[i]);
		i++;
	}
	free(sprites);
}

static void	_free_images(t_game *game)
{
	mlx_destroy_image(game->mlx, game->solid);
	mlx_destroy_image(game->mlx, game->gem);
	mlx_destroy_image(game->mlx, game->door);
	_free_anim(game, game->goblin_idle, 6);
	_free_anim(game, game->goblin_walk, 6);
	_free_anim(game, game->goblin_atk_side, 6);
	_free_anim(game, game->warrior_idle, 6);
	_free_anim(game, game->warrior_walk, 6);
	_free_anim(game, game->warrior_atk_side, 6);
	_free_anim(game, game->money_spawn, 7);
	mlx_destroy_image(game->mlx, game->ground_mid);
	mlx_destroy_image(game->mlx, game->ground_top);
	mlx_destroy_image(game->mlx, game->ground_topleft);
	mlx_destroy_image(game->mlx, game->ground_topright);
	mlx_destroy_image(game->mlx, game->ground_left);
	mlx_destroy_image(game->mlx, game->ground_right);
	mlx_destroy_image(game->mlx, game->ground_bot);
	mlx_destroy_image(game->mlx, game->ground_botleft);
	mlx_destroy_image(game->mlx, game->ground_botright);
	mlx_destroy_image(game->mlx, game->ground_toplr);
	mlx_destroy_image(game->mlx, game->ground_lr);
	mlx_destroy_image(game->mlx, game->ground_botlr);
	mlx_destroy_image(game->mlx, game->ground_leftbt);
	mlx_destroy_image(game->mlx, game->ground_bt);
	mlx_destroy_image(game->mlx, game->ground_rightbt);
	mlx_destroy_image(game->mlx, game->ground_all);
	_free_anim(game, game->foam, 8);
	free(game->foam_anim);
	mlx_destroy_image(game->mlx, game->btn_left);
	mlx_destroy_image(game->mlx, game->btn_mid);
	mlx_destroy_image(game->mlx, game->btn_right);
	mlx_destroy_image(game->mlx, game->hl_tl);
	mlx_destroy_image(game->mlx, game->hl_tr);
	mlx_destroy_image(game->mlx, game->hl_bl);
	mlx_destroy_image(game->mlx, game->hl_br);
	mlx_destroy_image(game->mlx, game->bnr_topleft);
	mlx_destroy_image(game->mlx, game->bnr_top);
	mlx_destroy_image(game->mlx, game->bnr_topright);
	mlx_destroy_image(game->mlx, game->bnr_left);
	mlx_destroy_image(game->mlx, game->bnr_mid);
	mlx_destroy_image(game->mlx, game->bnr_right);
	mlx_destroy_image(game->mlx, game->bnr_botleft);
	mlx_destroy_image(game->mlx, game->bnr_bot);
	mlx_destroy_image(game->mlx, game->bnr_botright);
	mlx_destroy_image(game->mlx, game->plus);
}

void	game_free(t_game *game)
{
	unsigned int	i;

	rdr_free(game->rdr);
	_free_images(game);
	free(game->keys);
	i = 0;
	while (i < vector_size(game->entities))
	{
		if (game->entities[i]->free)
			game->entities[i]->free(game->entities[i]);
		free(game->entities[i]);
		i++;
	}
	vector_free(game->entities);
	map_free(game->map);
	free(game->menu);
	mlx_destroy_image(game->mlx, game->canvas);
}
