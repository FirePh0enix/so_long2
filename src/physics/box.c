/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:37:54 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 22:22:18 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "physics.h"
#include <stdio.h>

t_box	box_from_entity(t_entity *entity)
{
	t_box	box;
	float	h;

	box = entity->hitbox;
	h = box.max.y;
	box.min.x += entity->x;
	box.max.x += entity->x;
	box.min.y += entity->y - h;
	box.max.y += entity->y - h;
	return (box);
}

t_box	box_offset_for_entity(t_box box, t_entity *entity)
{
	box.min.x += entity->x;
	box.min.y += entity->y;
	return (box);
}

int	box_collide_with_box(t_box *a, t_box *b)
{
	return (a->min.x < b->max.x && a->max.x > b->min.x && a->min.y < b->max.y
		&& a->max.y > b->min.y);
}

int	box_collide_with_ground(t_box *box, t_map *map)
{
	int		i;
	t_box	tile_box;
	t_tile	*tile;

	i = 0;
	while (i < map->width * map->height)
	{
		tile = &map->tiles[i];
		if (!tile->img)
		{
			i++;
			continue ;
		}
		tile_box.min.x = tile->x;
		tile_box.max.x = tile->x + tile->img->width;
		tile_box.min.y = tile->y - tile->img->height;
		tile_box.max.y = tile->y;
		if (box_collide_with_box(box, &tile_box))
			return (1);
		i++;
	}
	return (0);
}
