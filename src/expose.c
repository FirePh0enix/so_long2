/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:37:41 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 12:55:19 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entity.h"
#include "libft.h"
#include "render/graph.h"
#include "render/render.h"
#include "so_long.h"
#include "vector.h"
#include <mlx.h>
#include <stdio.h>

static void	draw_map(t_game *game, t_map *map)
{
	t_tile		*tile;
	t_entity	*entity;
	int			i;

	i = 0;
	while (i < map->width * map->height)
	{
		if (!map->tiles[i].img)
		{
			i++;
			continue ;
		}
		tile = &map->tiles[i];
		graph_add_sprite(game->graph, tile->img, (t_vec2){tile->x, tile->y}, -5,
			(t_effect){NULL, NULL});
		i++;
	}
	i = 0;
	while (i < (int)vector_size(map->entities))
	{
		entity = map->entities[i];
		if (entity->state == 0)
		{
			i++;
			continue ;
		}
		graph_add_sprite(game->graph, entity->sprite,
			(t_vec2){entity->x, entity->y}, entity->type->render_order,
			(t_effect){(void *)entity_effect, entity});
		i++;
	}
}

static void	draw_hud(t_game *game, t_map *map)
{
	char			buffer[64];
	t_ui			*ui;
	unsigned int	i;

	i = 0;
	while (i < vector_size(game->ui))
	{
		ui = game->ui[i];
		graph_add_ui(game->graph, ui->sprite, (t_vec2){ui->x, ui->y}, ui->order,
			(t_effect){(void *)ui->effect, ui});
		i++;
	}
	sprintf(buffer, "Collectibles %d/%d", game->collectibles,
		game->total_collectibles);
	mlx_string_put(game->mlx, game->win, 30, 30, 0xffffff, buffer);
	sprintf(buffer, "Movements: %d", game->mouvements);
	mlx_string_put(game->mlx, game->win, 30, 50, 0xffffff, buffer);
}

int	on_expose(t_game *game)
{
	clear_screen(game);
	draw_map(game, game->map);
	present(game);
	draw_hud(game, game->map);
	graph_draw(game->graph, game);
	graph_reset(game->graph);
	return (0);
}
