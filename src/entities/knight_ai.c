/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   knight_ai.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:41:33 by ledelbec          #+#    #+#             */
/*   Updated: 2024/02/27 16:45:21 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../entity.h"
#include "../so_long.h"
#include "../data/vector.h"
#include "../math/a_star.h"

/*
 * Find a random position in the map for the knight to go to.
 */
static t_vec2i	_find_random_pos(t_level *map)
{
	int	x;
	int	y;

	while (1)
	{
		x = rand() % map->width;
		y = rand() % map->height;
		if (map->data[x + y * map->width] == TILE_EMPTY)
			return ((t_vec2i){x, y});
	}
	return ((t_vec2i){});
}

static void	_invalidate_path(t_knight *ext)
{
	if (ext->path)
	{
		vector_free(ext->path);
		ext->path = NULL;
	}
}

static void	_pick_chase(t_entity *entity, t_knight *ext, t_level *map,
	t_entity *player)
{
	_invalidate_path(ext);
	ext->path = astar_search(&ext->arena, map, (t_vec2i){entity->pos.x / 64,
			entity->pos.y / 64},
			(t_vec2i){(player->pos.x + 32) / 64, (player->pos.y + 56) / 64});
	if (!ext->path)
	{
		ext->state = STATE_IDLE;
		return ;
	}
	ext->target_pos = (t_vec2){ext->path[0].x * 64, ext->path[0].y * 64};
	ext->current_path = vector_size(ext->path) - 2;
	ext->state = STATE_CHASING;
}

static void	_pick_patrol(t_entity *entity, t_knight *ext, t_level *map)
{
	_invalidate_path(ext);
	ext->path = astar_search(&ext->arena, map, (t_vec2i){entity->pos.x / 64,
			entity->pos.y / 64}, _find_random_pos(map));
	if (!ext->path)
		return ;
	ext->target_pos = (t_vec2){ext->path[0].x * 64, ext->path[0].y * 64};
	ext->current_path = vector_size(ext->path) - 2;
	ext->state = STATE_PATROLING;
}

void	knight_pick_action(t_entity *entity, t_knight *ext, t_level *map)
{
	t_entity	*player;

	if (entity->game->player2
		&& vec2_length(vec2_sub(entity->pos, entity->game->player->pos)) >
			vec2_length(vec2_sub(entity->pos, entity->game->player2->pos)))
		player = entity->game->player2;
	else
		player = entity->game->player;
	if (!player)
		return ;
	if (vec2_length(vec2_sub(entity->pos, player->pos)) < 1.0 * TILE_SIZE
		&& player->level == entity->level)
	{
		ext->path = NULL;
		ext->state = STATE_ATTACKING;
	}
	else if (vec2_length(vec2_sub(entity->pos, player->pos)) < 3.5 * TILE_SIZE
		&& player->level == entity->level)
		_pick_chase(entity, ext, map, player);
	else if (ext->state == STATE_IDLE && getms() >= ext->action_end)
		_pick_patrol(entity, ext, map);
	else if (ext->state != STATE_IDLE
		&& vec2_equals(entity->pos, ext->target_pos, 16))
	{
		ext->state = STATE_IDLE;
		ext->action_end = getms() + 700;
		_invalidate_path(ext);
	}
}
