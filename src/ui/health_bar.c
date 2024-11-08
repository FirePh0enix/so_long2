/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:40:54 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:18:52 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "ui.h"

void	health_bar_update(t_game *game, t_ui *ui)
{
}

int	health_bar_effect(int color, int x, int y, t_ui *ui)
{
	const int	max_width = ui->sprite->width
		* ((float)ui->game->map->player->health
			/ (float)ui->game->map->player->max_health);

	if (x > max_width)
		return (0xff000000);
	return (color);
}
