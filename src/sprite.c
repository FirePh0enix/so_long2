/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:07:17 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 22:55:19 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite.h"
#include "libft.h"
#include "so_long.h"

int get_pixel_color(t_img *image, int x, int y)
{
	char	*addr = image->data;
	int		bits_per_pixel = image->bpp;
	int		size_line = image->size_line;
	int		pixel_offset = (y * size_line) + (x * (bits_per_pixel / 8));
	int		color = *((int *)(addr + pixel_offset));

	return color;
}

void set_pixel_color(t_img *image, int x, int y, int color)
{
	char	*addr = image->data;
	int		bits_per_pixel = image->bpp;
	int		size_line = image->size_line;
	int		pixel_offset = (y * size_line) + (x * (bits_per_pixel / 8));

	*((int *)(addr + pixel_offset)) = color;
}

static void	*scale_image(t_game *game, t_img *img, int scale)
{
	const int	width = img->width * scale;
	const int	height = img->height * scale;
	t_img		*new_img;
	int			x;
	int			y;

	new_img = mlx_new_image(game->mlx, width, height);
	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			set_pixel_color(new_img, x, y,
				get_pixel_color(img, x / scale, y / scale));
			y++;
		}
		x++;
	}
	mlx_destroy_image(game->mlx, img);
	return (new_img);
}

t_sprite	*new_sprite(t_game *game, char *data)
{
	void		*img;
	t_sprite	*sprite;
	int			width;
	int			height;

	img = mlx_xpm_file_to_image(game->mlx, data, &width, &height);
	if (!img)
	{
		ft_printf("ERROR WHILE LOADING TEXTURE %s\n", data);
		return (NULL);
	}
	img = scale_image(game, img, PIXEL_SCALE);
	sprite = ft_calloc(sizeof(t_sprite), 1);
	sprite->img = img;
	sprite->width = width * PIXEL_SCALE;
	sprite->height = height * PIXEL_SCALE;
	return (sprite);
}
