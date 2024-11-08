/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:34:40 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 12:55:28 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "../sprite.h"
#include "graph.h"
#include "libft.h"
#include "light.h"
#include "mlx.h"
#include "render.h"
#include <stdio.h>

static int	mul_color(int color, float scalar)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * scalar;
	g = ((color >> 8) & 0xFF) * scalar;
	b = (color & 0xFF) * scalar;
	return ((((color >> 24) & 0xFF) << 24) | (r << 16) | (g << 8) | b);
}

// The formula for each channel of color `pixel + (light - pixel) * intensity`,
// then to clamp the value: `new > original ? original : new`
static int	apply_light(int pixel, int og_pixel, int light_color,
	float intensity)
{
	int	modified_red;
	int	modified_green;
	int	modified_blue;

	modified_red = (int)((double)((pixel >> 16) & 0xFF)
			+ ((double)((light_color >> 16) & 0xFF)
				- (double)((pixel >> 16) & 0xFF)) * intensity);
	modified_green = (int)((double)((pixel >> 8) & 0xFF)
			+ ((double)((light_color >> 8) & 0xFF)
				- (double)((pixel >> 8) & 0xFF)) * intensity);
	modified_blue = (int)((double)(pixel & 0xFF)
			+ ((double)(light_color & 0xFF)
				- (double)(pixel & 0xFF)) * intensity);
	if (modified_red > ((og_pixel >> 16) & 0xFF))
		modified_red = (og_pixel >> 16) & 0xFF;
	if (modified_green > ((og_pixel >> 8) & 0xFF))
		modified_green = (og_pixel >> 8) & 0xFF;
	if (modified_blue > (og_pixel & 0xFF))
		modified_blue = og_pixel & 0xFF;
	return ((modified_red << 16) | (modified_green << 8) | modified_blue);
}

static int	apply_lights(t_game *game, int x, int y, int pixel)
{
	int		i;
	t_light	*light;
	float	intensity;
	int		color;

	i = 0;
	color = mul_color(pixel, game->map->default_intensity);
	x -= game->canvas->width / 2 - (int)game->camera_x;
	y -= game->canvas->height / 2 - (int)game->camera_y;
	while (i < game->map->light_count)
	{
		light = game->map->lights[i];
		if (light->disabled)
		{
			i++;
			continue ;
		}
		intensity = light_intensity(light, x, y);
		if (intensity > 0)
			color = apply_light(color, pixel, light->color, intensity);
		i++;
	}
	return (color);
}

void	apply_lighting(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->canvas->width)
	{
		y = 0;
		while (y < game->canvas->height)
		{
			set_pixel_color(
				game->canvas, x, y,
				apply_lights(game, x, y, get_pixel_color(game->canvas, x, y)));
			y++;
		}
		x++;
	}
}

void	draw_ui(t_game *game, t_sprite *sprite, t_vec2 pos, t_effect effect)
{
	int				ix;
	int				iy;
	unsigned int	color;

	ix = 0;
	while (ix < sprite->width)
	{
		iy = 0;
		while (iy < sprite->height)
		{
			if ((ix + pos.x < 0 || iy + pos.y < 0
					|| ix + pos.x >= game->canvas->width
					|| iy + pos.y >= game->canvas->height) && ++iy)
				continue ;
			color = get_pixel_color(sprite->img, ix, iy);
			if (effect.apply)
				color = effect.apply(color, ix,
						iy, effect.user_data);
			if (color == 0xff000000 && ++iy)
				continue ;
			set_pixel_color(game->canvas, pos.x + ix, pos.y + iy, color);
			iy++;
		}
		ix++;
	}
}

void	present(t_game *game)
{
	apply_lighting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas, 0, 0);
}

void	clear_screen(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->canvas->width)
	{
		y = 0;
		while (y < game->canvas->height)
		{
			set_pixel_color(game->canvas, x, y, 0x00000000);
			y++;
		}
		x++;
	}
}

unsigned int	blend_colors(unsigned int a, unsigned int b, float ratio)
{
	const unsigned char	c1[] = {(a >> 16) & 0xFF, (a >> 8) & 0xFF, a & 0xFF};
	const unsigned char	c2[] = {(b >> 16) & 0xFF, (b >> 8) & 0xFF, b & 0xFF};

	return (((unsigned int)(c1[0] * (1 - ratio) + c2[0] * ratio) << 16)
		| ((unsigned int)(c1[1] * (1 - ratio) + c2[1] * ratio) << 8)
		| ((unsigned int)(c1[2] * (1 - ratio) + c2[2] * ratio)));
}

t_vec2	camera_offset(t_game *game)
{
	return ((t_vec2){(float)game->canvas->width / 2 - (int)game->camera_x,
		(float)game->canvas->width / 2 - (int)game->camera_x});
}
