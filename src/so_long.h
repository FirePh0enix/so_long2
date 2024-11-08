/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:36:47 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 20:56:51 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <libft.h>
# include <mlx.h>
# include <mlx_int.h>
# include <sys/select.h>

# include "entity.h"
# include "render/graph.h"
# include "render/light.h"
# include "render/render.h"
# include "sprite.h"
# include "ui/ui.h"

# define PIXEL_SCALE 2
# define TILE_SIZE 16

typedef struct s_map t_map;

enum
{
	// Regular sides
	LEFT = 0,
	RIGHT = 1,
	TOP = 2,
	BOTTOM = 3,
	LEFT_TOP = 4,
	LEFT_BOTTOM = 5,
	RIGHT_TOP = 6,
	RIGHT_BOTTOM = 7,
	ALL = 8,
	NONE = 9,
	LEFT_TOP_BOTTOM = 10,
	TOP_BOTTOM = 11,
	RIGHT_TOP_BOTTOM = 12,
	LEFT_RIGHT_TOP = 13,
	LEFT_RIGHT = 14,
	LEFT_RIGHT_BOTTOM = 15,

	// Corners
	ALL_COR = 16,
	RIGHT_BOTTOM_COR = 17,
	LEFT_BOTTOM_COR = 18,
	RIGHT_TOP_COR = 19,
	LEFT_TOP_COR = 20,

	// Mix
	RB_COR_LT_SIDE = 21,
	LB_COR_RT_SIDE = 22,
	RT_COR_LB_SIDE = 23,
	LT_COR_RB_SIDE = 24,

	LRT_COR = 25,
	LRB_COR = 26,
	RTB_COR = 27,
	LTB_COR = 28,

	LRT_COR_B_SIDE = 29,
	LRB_COR_T_SIDE = 30,
	RTB_COR_L_SIDE = 31,
	LTB_COR_R_SIDE = 32,

	LT_COR_B_SIDE = 33,
	LB_COR_T_SIDE = 34,
	RT_COR_L_SIDE = 35,
	LT_COR_R_SIDE = 36,

	RT_COR_B_SIDE = 37,
	RB_COR_T_SIDE = 38,
	RB_COR_L_SIDE = 39,
	LB_COR_R_SIDE = 40,

	TILE_MAX,
};

typedef struct s_tiles
{
	t_sprite *door[6];
	t_sprite *gem[6];
	t_sprite *sides[TILE_MAX];
	t_sprite *grass;
	t_sprite *red_flower;
	t_sprite *yellow_flower;
	t_sprite *glowing_tree;
	t_sprite *player;
	t_sprite *projectile;
	t_sprite *golem;
	t_sprite *wall;
	t_sprite *ui;
	t_sprite *health_bar;
} t_tiles;

# define TIME_BETWEEN_FRAMES 16
# define FRAME_TIME 0.01666666666

typedef struct s_game
{
	t_xvar *mlx;
	void   *win;
	t_img  *canvas;

	suseconds_t		last_update_millis;
	t_render_graph *graph;

	float	camera_x;
	float	camera_y;
	t_map  *map;
	t_tiles tiles;
	int		collectibles;
	int		total_collectibles;
	int		mouvements;
	int		player_start_present;
	int		exit_present;

	t_ui **ui;

	t_entity_type *player_type;
	t_entity_type *collectible_type;
	t_entity_type *door_type;
	t_entity_type *projectile_type;
	t_entity_type *golem_type;
	t_entity_type *wall_type;

	int key_up;
	int key_down;
	int key_left;
	int key_right;
	int key_q;
	int key_w;
	int key_e;
	int key_r;
	int key_space;
} t_game;

enum
{
	GROUND,
	EMPTY,
	GRASS,
};

typedef struct s_tile
{
	int		  x;
	int		  y;
	int		  type;
	t_sprite *img;
} t_tile;

typedef struct s_map
{
	char	  *str;
	int		   width;
	int		   height;
	int		   start_x;
	int		   start_y;
	t_entity  *player;
	t_tile	  *tiles;
	t_entity **entities;
	float	   default_intensity;
	t_light	 **lights;
	int		   light_count;
} t_map;

int on_expose(t_game *game);

t_map *create_map(t_game *game, char *filename);
void   load_tiles(t_game *game);

void add_light(t_game *game, t_light *light);
void add_entity(t_game *game, t_entity *entity);

suseconds_t getms();

#endif
