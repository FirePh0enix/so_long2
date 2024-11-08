/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ground_tile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:43:01 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 22:16:46 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "libft.h"
#include "map.h"

static int	isg(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	return (map->str[x + y * (map->width + 1)] == '1');
}

// Take a pattern like this:
// 111
//  x
//  1
// x is the current tile, 1 is a ground tile and a space is a
// empty space.
static int	pattern(t_map *map, char *p, int x, int y)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if ((isg(map, x + i - 1, y - 1) && p[i + 0 * 3] != '1')
			|| (!isg(map, x + i - 1, y - 1) && p[i + 0 * 3] == '1'))
			return (0);
		if ((isg(map, x + i - 1, y - 1 + 2) && p[i + 2 * 3] != '1')
			|| (!isg(map, x + i - 1, y - 1 + 2) && p[i + 2 * 3] == '1'))
			return (0);
		i++;
	}
	if ((isg(map, x - 1, y - 1 + 1) && p[0 + 1 * 3] != '1')
		|| (!isg(map, x - 1, y - 1 + 1) && p[0 + 1 * 3] == '1'))
		return (0);
	if ((isg(map, x - 1 + 2, y - 1 + 1) && p[2 + 1 * 3] != '1')
		|| (!isg(map, x - 1 + 2, y - 1 + 1) && p[2 + 1 * 3] == '1'))
		return (0);
	return (1);
}

t_sprite	*map_get_ground_sprite(t_game *game, t_map *m, int x, int y)
{
	if (pattern(m, "   1x1   ", x, y))
		return (game->tiles.sides[TOP_BOTTOM]);
	else if (pattern(m, "    x1   ", x, y))
		return (game->tiles.sides[LEFT_TOP_BOTTOM]);
	else if (pattern(m, "   1x    ", x, y))
		return (game->tiles.sides[RIGHT_TOP_BOTTOM]);
	else if (pattern(m, " 1  x  1 ", x, y))
		return (game->tiles.sides[LEFT_RIGHT]);
	return (game->tiles.sides[ALL]);
}
