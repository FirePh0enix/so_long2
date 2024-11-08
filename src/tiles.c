/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:40:48 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 21:40:50 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include "sprite.h"

static void	load_sides(t_game *g, t_tiles *t)
{
	t->sides[LEFT] = new_sprite(g, "textures/gen/left.xpm");
	t->sides[RIGHT] = new_sprite(g, "textures/gen/right.xpm");
	t->sides[TOP] = new_sprite(g, "textures/gen/top.xpm");
	t->sides[BOTTOM] = new_sprite(g, "textures/gen/bottom.xpm");
	t->sides[LEFT_TOP] = new_sprite(g, "textures/gen/lt_side.xpm");
	t->sides[LEFT_BOTTOM] = new_sprite(g, "textures/gen/lb_side.xpm");
	t->sides[RIGHT_TOP] = new_sprite(g, "textures/gen/rt_side.xpm");
	t->sides[RIGHT_BOTTOM] = new_sprite(g, "textures/gen/rb_side.xpm");
	t->sides[ALL] = new_sprite(g, "textures/gen/all_sides.xpm");
	t->sides[NONE] = new_sprite(g, "textures/gen/mid.xpm");
	t->sides[LEFT_TOP_BOTTOM] = new_sprite(g, "textures/gen/ltb_side.xpm");
	t->sides[TOP_BOTTOM] = new_sprite(g, "textures/gen/tb_side.xpm");
	t->sides[RIGHT_TOP_BOTTOM] = new_sprite(g, "textures/gen/rtb_side.xpm");
	t->sides[LEFT_RIGHT_TOP] = new_sprite(g, "textures/gen/lrt_side.xpm");
	t->sides[LEFT_RIGHT] = new_sprite(g, "textures/gen/lr_side.xpm");
	t->sides[LEFT_RIGHT_BOTTOM] = new_sprite(g, "textures/gen/lrb_side.xpm");
}

static void	load_corners(t_game *g, t_tiles *t)
{
	t->sides[ALL_COR] = new_sprite(g, "textures/gen/all_corners.xpm");
	t->sides[RIGHT_BOTTOM_COR] = new_sprite(g, "textures/gen/rb_corner.xpm");
	t->sides[LEFT_BOTTOM_COR] = new_sprite(g, "textures/gen/lb_corner.xpm");
	t->sides[RIGHT_TOP_COR] = new_sprite(g, "textures/gen/rt_corner.xpm");
	t->sides[LEFT_TOP_COR] = new_sprite(g, "textures/gen/lt_corner.xpm");
	t->sides[LRT_COR] = new_sprite(g, "textures/gen/lrt_corner.xpm");
	t->sides[LRB_COR] = new_sprite(g, "textures/gen/lrb_corner.xpm");
	t->sides[RTB_COR] = new_sprite(g, "textures/gen/rtb_corner.xpm");
	t->sides[LTB_COR] = new_sprite(g, "textures/gen/ltb_corner.xpm");
	t->sides[LRT_COR_B_SIDE] = new_sprite(g, "textures/gen/lrt_cor_b_side.xpm");
	t->sides[LRB_COR_T_SIDE] = new_sprite(g, "textures/gen/lrb_cor_t_side.xpm");
	t->sides[RTB_COR_L_SIDE] = new_sprite(g, "textures/gen/rtb_cor_l_side.xpm");
	t->sides[LTB_COR_R_SIDE] = new_sprite(g, "textures/gen/ltb_cor_r_side.xpm");
	t->sides[RB_COR_LT_SIDE] = new_sprite(g, "textures/gen/rb_cor_lt_side.xpm");
	t->sides[LB_COR_RT_SIDE] = new_sprite(g, "textures/gen/lb_cor_rt_side.xpm");
	t->sides[RT_COR_LB_SIDE] = new_sprite(g, "textures/gen/rt_cor_lb_side.xpm");
	t->sides[LT_COR_RB_SIDE] = new_sprite(g, "textures/gen/lt_cor_rb_side.xpm");
	t->sides[LT_COR_B_SIDE] = new_sprite(g, "textures/gen/lt_cor_b_side.xpm");
	t->sides[LB_COR_T_SIDE] = new_sprite(g, "textures/gen/lb_cor_t_side.xpm");
	t->sides[RT_COR_L_SIDE] = new_sprite(g, "textures/gen/rt_cor_l_side.xpm");
	t->sides[LT_COR_R_SIDE] = new_sprite(g, "textures/gen/lt_cor_r_side.xpm");
	t->sides[RT_COR_B_SIDE] = new_sprite(g, "textures/gen/rt_cor_b_side.xpm");
	t->sides[RB_COR_T_SIDE] = new_sprite(g, "textures/gen/rb_cor_t_side.xpm");
	t->sides[RB_COR_L_SIDE] = new_sprite(g, "textures/gen/rb_cor_l_side.xpm");
	t->sides[LB_COR_R_SIDE] = new_sprite(g, "textures/gen/lb_cor_r_side.xpm");
}

static void	load_props(t_game *game, t_tiles *tiles)
{
	tiles->grass = new_sprite(game, "textures/gen/grass.xpm");
	tiles->red_flower = new_sprite(game, "textures/gen/red_flower.xpm");
	tiles->yellow_flower = new_sprite(game, "textures/gen/yellow_flower.xpm");
	tiles->glowing_tree = new_sprite(game, "textures/gen/glowing_tree.xpm");
	tiles->door[0] = new_sprite(game, "textures/exit_door/exit_door1.xpm");
	tiles->door[1] = new_sprite(game, "textures/exit_door/exit_door2.xpm");
	tiles->door[2] = new_sprite(game, "textures/exit_door/exit_door3.xpm");
	tiles->door[3] = new_sprite(game, "textures/exit_door/exit_door4.xpm");
	tiles->door[4] = new_sprite(game, "textures/exit_door/exit_door5.xpm");
	tiles->door[5] = new_sprite(game, "textures/exit_door/exit_door6.xpm");
	tiles->gem[0] = new_sprite(game, "textures/gem/gem1.xpm");
	tiles->gem[1] = new_sprite(game, "textures/gem/gem2.xpm");
	tiles->gem[2] = new_sprite(game, "textures/gem/gem3.xpm");
	tiles->gem[3] = new_sprite(game, "textures/gem/gem4.xpm");
	tiles->gem[4] = new_sprite(game, "textures/gem/gem5.xpm");
	tiles->gem[5] = new_sprite(game, "textures/gem/gem6.xpm");
	tiles->player = new_sprite(game, "textures/player/player.xpm");
	tiles->projectile = new_sprite(game, "textures/projectile.xpm");
	tiles->golem = new_sprite(game, "textures/golem.xpm");
	tiles->wall = new_sprite(game, "textures/ice_wall.xpm");
	tiles->ui = new_sprite(game, "textures/ui/ui.xpm");
	tiles->health_bar = new_sprite(game, "textures/ui/HealthBar.xpm");
}

void	load_tiles(t_game *game)
{
	load_sides(game, &game->tiles);
	load_corners(game, &game->tiles);
	load_props(game, &game->tiles);
}
