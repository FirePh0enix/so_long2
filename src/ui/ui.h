/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:41:13 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:18:03 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "../sprite.h"

typedef struct s_ui	t_ui;
typedef void		(*t_ui_update)(t_game *game, t_ui *ui);

typedef struct s_ui
{
	t_game		*game;
	t_sprite	*sprite;
	int			x;
	int			y;
	int			order;
	t_ui_update	update_hook;
	int			(*effect)(int, int, int, t_ui *);
}	t_ui;

void	base_ui_update(t_game *game, t_ui *ui);
int		base_ui_effect(int color, int x, int y, t_ui *ui);

void	health_bar_update(t_game *game, t_ui *ui);
int		health_bar_effect(int color, int x, int y, t_ui *ui);

#endif
