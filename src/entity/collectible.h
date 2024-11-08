/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:23:42 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:24:22 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTIBLE_H
# define COLLECTIBLE_H

# include "../entity.h"
# include "../render/light.h"

typedef struct s_game	t_game;

typedef struct s_collectible_ext
{
	t_anim	*anim;
	t_light	*light;
}	t_collectible_ext;

void	collectible_spawn(t_game *g, t_entity *ent, t_collectible_ext *ext);
void	collectible_update(t_game *g, t_entity *ent, t_collectible_ext *ext);

#endif
