/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:42:56 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:20:45 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOX_H
# define BOX_H

# include "vec2.h"

typedef struct s_entity	t_entity;

typedef struct s_box
{
	t_vec2	min;
	t_vec2	max;
}	t_box;

t_box	box_from_entity(t_entity *entity);

#endif
