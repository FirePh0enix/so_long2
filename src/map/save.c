/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:36:59 by ledelbec          #+#    #+#             */
/*   Updated: 2024/02/10 11:58:23 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "../entity.h"
#include "../data/vector.h"

static	t_tile	_etype_to_tile(t_etype etype)
{
	if (etype == ETYPE_GEM)
		return (TILE_COLLECT);
	else if (etype == ETYPE_PLAYER)
		return (TILE_PLAYER);
	else if (etype == ETYPE_ENEMY)
		return (TILE_ENEMY);
	return (TILE_EMPTY);
}

static void	_save_entities(t_map *map, t_entity **entities)
{
	unsigned int	i;
	t_entity		*entity;

	i = 0;
	while (i < vector_size(entities))
	{
		entity = entities[i];
		map->data[((int)entity->pos.x / SCALED_SIZE)
			+ ((int)entity->pos.y / SCALED_SIZE) * map->width]
			= _etype_to_tile(entity->type);
		i++;
	}
}

static char	*_get_tile_str(t_tile tile)
{
	if (tile == TILE_SOLID)
		return ("1");
	else if (tile == TILE_EMPTY)
		return ("0");
	else if (tile == TILE_DOOR)
		return ("E");
	else if (tile == TILE_COLLECT)
		return ("C");
	else if (tile == TILE_PLAYER)
		return ("P");
	else if (tile == TILE_ENEMY)
		return ("E");
	return ("@");
}

static void	_write_to_string(t_map *map)
{
	int	x;
	int	y;
	const int	width = map->width + 1;

	free(map->string);
	map->string = malloc(width * map->height);
	x = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			map->string[x + y * width] = _get_tile_str(
				map->data[x + y * map->width])[0];
			y++;
		}
		map->string[map->width * y * map->width] = '\n';
		x++;
	}
}

void	map_save(t_map *map, t_game *game, char *filename)
{
	int			x;
	int			y;
	t_tile		tile;
	const int	fd = open(filename, O_WRONLY);

	_save_entities(map, game->entities);
	if (fd == -1)
		return ;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			tile = map->data[x + y * map->width];
			write(fd, _get_tile_str(tile), 1);
			x++;
		}
		write(fd, "\n", 1);
		y++;
	}
	close(fd);
	_write_to_string(map);
	ft_printf("Map saved to %s\n", filename);
}
