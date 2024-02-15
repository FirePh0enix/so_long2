/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:42:35 by ledelbec          #+#    #+#             */
/*   Updated: 2024/02/15 15:39:02 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../math/box.h"
#include "../so_long.h"

/*
 * Stairs have no collison when going through the front, but must have
 * collisions on the three other sides.
 * sides - Collision with only sides, not up
 */
static bool	_collide_with_stair(t_box box, int x, int y, bool sides)
{
	const t_vec2i	pos = (t_vec2i){x * 64, y * 64};
	t_box			up;
	t_box			left;
	t_box			right;

	up = (t_box){{pos.x, pos.y}, {pos.x + 64, pos.y}};
	left = (t_box){{pos.x, pos.y}, {pos.x, pos.y + 64}};
	right = (t_box){{pos.x + 64, pos.y}, {pos.x + 64, pos.y + 64}};
	return ((!sides && box_collide_with_box(box, up))
		|| box_collide_with_box(box, left)
		|| box_collide_with_box(box, right));
}

static bool	_collide_with_upper_layer(t_box box, int index, t_map2 *map)
{
	int		x;
	int		y;
	t_level	*level;

	if (index >= map->level_count - 1)
		return (false);
	level = &map->levels[index + 1];
	x = -1;
	while (++x < map->width)
	{
		y = -1;
		while (++y < map->height)
		{
			if (level->data[x + y * level->width] == TILE_EMPTY
				&& (map->levels[index].data[x
						+ (y + 1) * level->width] != TILE_STAIR))
			{
				if (box_collide_with_box(box, box_for_position((t_box){
							{0, 0}, {64, 64}}, (t_vec2){x * 64, (y + 1) * 64})))
					return (true);
			}
		}
	}
	return (false);
}

bool	box_collide_with_map2(t_box box, int index, t_map2 *map)
{
	const t_level	*level = &map->levels[index];
	int				x;
	int				y;
	t_box			tbox;

	x = -1;
	while (++x < map->width)
	{
		y = -1;
		while (++y < map->height)
		{
			tbox = (t_box){{0, 0}, {64, 64}};
			if (index > 0
				&& map->levels[index - 1].data[x + y * map->width] == TILE_STAIR
				&& _collide_with_stair(box, x, y, true))
				return (true);
			else if (level->data[x + y * level->width] == TILE_SOLID
				&& box_collide_with_box(box, box_for_position(tbox, (t_vec2){
						x * 64, y * 64}))
				&& (index == 0
					|| map->levels[index
						- 1].data[x + y * map->width] != TILE_STAIR))
			{
				return (true);
			}
			else if (level->data[x + y * level->width] == TILE_STAIR
				&& _collide_with_stair(box, x, y, false))
				return (true);
			else if (level->data[x + y * level->width] == TILE_DOOR)
			{
				if (box_collide_with_box(box, box_for_position(tbox, (t_vec2){
							(x - 1) * 64, y * 64})))
					return (true);
				if (_collide_with_stair(box, x, y, false))
					return (true);
				if (box_collide_with_box(box, box_for_position(tbox, (t_vec2){
							(x + 1) * 64, y * 64})))
					return (true);
			}
		}
	}
	if (_collide_with_upper_layer(box, index, map))
		return (true);
	return (false);
}
