/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:30:27 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:30:28 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_H
# define WALL_H

# include "../entity.h"

typedef struct s_game	t_game;

typedef struct s_wall_ext
{
	long	death_time;
}	t_wall_ext;

void	wall_spawn(t_game *game, t_entity *entity, t_wall_ext *ext);
void	wall_update(t_game *game, t_entity *entity, t_wall_ext *ext);

#endif
