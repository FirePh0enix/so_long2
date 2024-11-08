/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:41:51 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:35:45 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "render.h"

// const int	xo = game->canvas->width / 2.0 - (int)game->camera_x + pos.x
// 	- sprite->width / 2.0;
// const int	yo = game->canvas->height / 2.0 - (int)game->camera_y + pos.y
// 	- sprite->height;

static void	_draw_flipped_sprite(
	t_game *g,
	t_sprite *sprite,
	t_vec2i pos,
	t_draw_opts opts)
{
	const int	p[] = {g->canvas->width / 2.0 - (int)g->camera_x + pos.x
		- sprite->width / 2.0, g->canvas->height / 2.0 - (int)g->camera_y
		+ pos.y - sprite->height};
	int			x;
	int			y;
	int			c;

	x = 0;
	while (x < sprite->width)
	{
		y = 0;
		while (y < sprite->height)
		{
			if ((x + p[0] < 0 || x + p[0] >= g->canvas->width
					|| y + p[1] < 0 || y + p[1] >= g->canvas->height) && ++y)
				continue ;
			c = get_pixel_color(sprite->img, x, y);
			if (c == (int)0xff000000 && ++y)
				continue ;
			if (opts.effect.apply)
				c = opts.effect.apply(c, x, y, opts.effect.user_data);
			set_pixel_color(g->canvas, p[0] - x + sprite->width, y + p[1], c);
			y++;
		}
		x++;
	}
}

static void	_draw_sprite(
	t_game *game,
	t_sprite *sprite,
	t_vec2i pos,
	t_draw_opts opts)
{
	const int	p[] = {game->canvas->width / 2.0 - (int)game->camera_x + pos.x
		- sprite->width / 2.0, game->canvas->height / 2.0 - (int)game->camera_y
		+ pos.y - sprite->height};
	int			x;
	int			y;
	int			col;

	x = 0;
	while (x < sprite->width)
	{
		y = 0;
		while (y < sprite->height)
		{
			if ((x + p[0] < 0 || x + p[0] >= game->canvas->width
					|| y + p[1] < 0 || y + p[1] >= game->canvas->height) && ++y)
				continue ;
			col = get_pixel_color(sprite->img, x, y);
			if (col == (int)0xff000000 && ++y)
				continue ;
			if (opts.effect.apply)
				col = opts.effect.apply(col, x, y, opts.effect.user_data);
			set_pixel_color(game->canvas, x + p[0], y + p[1], col);
			y++;
		}
		x++;
	}
}

void	draw_sprite(
	t_game *game,
	t_sprite *sprite,
	t_vec2i pos,
	t_draw_opts opts)
{
	if (opts.flipped)
		_draw_flipped_sprite(game, sprite, pos, opts);
	else
		_draw_sprite(game, sprite, pos, opts);
}
