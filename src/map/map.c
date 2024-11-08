/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:43:05 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 22:20:27 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "../entity.h"
#include "../so_long.h"
#include "../vector.h"
#include "libft.h"
#include <unistd.h>

static size_t	get_line_size(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		i++;
	}
	return (i);
}

static size_t	get_line_count(char *s, size_t size)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 0;
	while (i < size && s[i])
	{
		if (s[i] == '\n')
			n++;
		i++;
	}
	return (n);
}

static void	setup_tiles(t_game *game, char *s, size_t size, t_map *map)
{
	const size_t	width = get_line_size(s);
	const size_t	height = get_line_count(s, size);
	size_t			x;
	size_t			y;
	t_entity		*entity;

	map->tiles = malloc(sizeof(t_tile) * width * height);
	map->width = width;
	map->height = height;
	game->total_collectibles = 0;
	game->collectibles = 0;
	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			map->tiles[x + y * width].img = NULL;
			if (s[x + y * (width + 1)] == '1')
			{
				map->tiles[x + y * width].type = GROUND;
				map->tiles[x + y * width].img = map_get_ground_sprite(game,
						map, x, y);
				map->tiles[x + y * width].x = x * TILE_SIZE * PIXEL_SCALE;
				map->tiles[x + y * width].y = y * TILE_SIZE * PIXEL_SCALE;
			}
			else if (s[x + y * (width + 1)] == 'P')
			{
				map->start_x = x * TILE_SIZE * PIXEL_SCALE;
				map->start_y = y * TILE_SIZE * PIXEL_SCALE;
				game->player_start_present = 1;
			}
			else if (s[x + y * (width + 1)] == 'C')
			{
				game->total_collectibles++;
				entity = new_entity(game, x * TILE_SIZE * PIXEL_SCALE,
						y * TILE_SIZE * PIXEL_SCALE, game->collectible_type);
				add_entity(game, entity);
			}
			else if (s[x + y * (width + 1)] == 'E')
			{
				game->exit_present = 1;
				entity = new_entity(game, x * TILE_SIZE * PIXEL_SCALE,
						y * TILE_SIZE * PIXEL_SCALE, game->door_type);
				add_entity(game, entity);
			}
			else if (s[x + y * (width + 1)] == 'G')
			{
				entity = new_entity(game, x * TILE_SIZE * PIXEL_SCALE,
						y * TILE_SIZE * PIXEL_SCALE, game->golem_type);
				add_entity(game, entity);
			}
			else
				map->tiles[x + y * width].type = EMPTY;
			y++;
		}
		x++;
	}
}

t_map	*create_map(t_game *game, char *filename)
{
	int		fd;
	char	*s;
	char	buf[4096];
	int		n;
	size_t	size;
	t_map	*map;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	s = NULL;
	n = 4096;
	size = 0;
	while (n == 4096)
	{
		n = read(fd, buf, 4096);
		s = realloc(s, size + n);
		ft_memcpy(s + size, buf, n);
		size += n;
	}
	map = malloc(sizeof(t_map));
	map->str = s;
	map->default_intensity = 0.3;
	map->lights = NULL;
	map->light_count = 0;
	map->entities = vector_new(sizeof(t_entity *), 0);
	game->map = map;
	setup_tiles(game, s, size, map);
	if (!map_verify(game, map))
	{
		free(map);
		ft_printf("Error\nInvalid map\n");
		return (NULL);
	}
	return (map);
}

void	add_entity(t_game *game, t_entity *entity)
{
	vector_add((void *)&game->map->entities, &entity);
	entity->type->spawn_hook(game, entity, entity->extension);
}

void	add_light(t_game *game, t_light *light)
{
	game->map->lights = realloc(
			game->map->lights,
			sizeof(t_light *) * (game->map->light_count + 1));
	game->map->lights[game->map->light_count] = light;
	game->map->light_count++;
}

t_tile	*map_get_tile(t_map *map, int x, int y)
{
	return (&map->tiles[x + y * map->width]);
}
