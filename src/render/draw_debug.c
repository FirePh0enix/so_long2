/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 01:47:40 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 12:41:04 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "render.h"
#include <stdio.h>

void	draw_debug_box(t_game *game, t_box *box, int color)
{
	const int	x = box->min.x
		+ game->canvas->width / 2.0 - (int)game->camera_x;
	const int	y = box->min.y
		+ game->canvas->height / 2.0 - (int)game->camera_y;
	int			ix;
	int			iy;

	ix = 0;
	while (ix < (int)(box->max.x - box->min.x))
	{
		iy = 0;
		while (iy < (int)(-box->min.y))
		{
			if (ix + x < 0 || iy + y < 0 || ix + x >= game->canvas->width
				|| iy + y >= game->canvas->height)
			{
				iy++;
				continue ;
			}
			set_pixel_color(game->canvas, x + ix, y + iy, color);
			iy++;
		}
		ix++;
	}
}
