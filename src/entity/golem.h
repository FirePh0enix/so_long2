/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   golem.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:27:58 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:28:09 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GOLEM_H
# define GOLEM_H

# include "../entity.h"

typedef struct s_game	t_game;

typedef struct s_golem_ext
{
}	t_golem_ext;

void	golem_spawn(t_game *game, t_entity *entity, t_golem_ext *ext);
void	golem_update(t_game *game, t_entity *entity, t_golem_ext *ext);

#endif
