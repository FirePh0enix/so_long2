/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:17:08 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 22:25:02 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../entity.h"
#include "../so_long.h"
#include "box.h"
#include "physics.h"
#include "vec2.h"
#include <stdio.h>
#include "../vector.h"

int	physx_box_collision(t_box a, t_box b)
{
	return (a.min.x < b.max.x && a.max.x > b.min.x && a.min.y < b.max.y
		&& a.max.y > b.min.y);
}

int	physx_collide_with_terrain(t_box box, t_map *map)
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
		if (physx_box_collision(box, tile_box))
			return (1);
		i++;
	}
	return (0);
}

t_entity	*physx_collide_with_entities(t_box box, t_map *map, int mask)
{
	t_entity		*entity;
	unsigned int	i;

	i = 0;
	while (i < vector_size(map->entities))
	{
		entity = map->entities[i];
		if (entity->state == 0)
		{
			i++;
			continue ;
		}
		if (entity->collision_mask & mask
			&& physx_box_collision(box, box_from_entity(entity)))
			return (entity);
		i++;
	}
	return (NULL);
}

int	physx_is_on_ground(t_entity *entity)
{
	t_box	box;
	float	h;

	box = box_from_entity(entity);
	h = box.max.y - box.min.y;
	box.min.y += h;
	box.max.y += 2;
	return (physx_collide_with_terrain(box, entity->game->map));
}

void	physx_move_entity(t_entity *entity)
{
	const t_vec2	cor = vec2_scale(entity->velocity, 0.1);
	t_box			box;

	while (1)
	{
		box = box_from_entity(entity);
		box.min.x += entity->velocity.x;
		box.max.x += entity->velocity.x;
		if (!physx_collide_with_terrain(box, entity->game->map))
			break ;
		entity->velocity.x -= cor.x;
	}
	while (1)
	{
		box = box_from_entity(entity);
		box.min.y += entity->velocity.y;
		box.max.y += entity->velocity.y;
		if (!physx_collide_with_terrain(box, entity->game->map))
			break ;
		entity->velocity.y -= cor.y;
	}
	entity->x += entity->velocity.x;
	entity->y += entity->velocity.y;
}
