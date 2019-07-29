/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_physics_system.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 03:01:47 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 19:48:39 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_physics.h"

int					ps_func(void *psv)
{
	t_rb	**rbs;
	size_t	rbs_count;
	size_t	i;

	rbs = ((t_physics_system *)psv)->rbs;
	rbs_count = ((t_physics_system *)psv)->rbs_count;
	while (rbs)
	{
		i = -1;
		while (++i < rbs_count)
		{
			if (rbs[i]->move_vel.x != rbs[i]->raw_move_vel.x)
				rbs[i]->move_vel.x = ft_lerp(
					rbs[i]->move_vel.x,
					rbs[i]->raw_move_vel.x * rbs[i]->move_speed_mult,
					ft_fmin(1, rbs[i]->move_acc / fabs(rbs[i]->move_vel.x -
					rbs[i]->raw_move_vel.x)));
			if (rbs[i]->move_vel.y != rbs[i]->raw_move_vel.y)
				rbs[i]->move_vel.y = ft_lerp(
					rbs[i]->move_vel.y,
					rbs[i]->raw_move_vel.y * rbs[i]->move_speed_mult,
					ft_fmin(1, rbs[i]->move_acc / fabs(rbs[i]->move_vel.y -
					rbs[i]->raw_move_vel.y)));
			if (rbs[i]->move_vel.z != rbs[i]->raw_move_vel.z)
				rbs[i]->move_vel.z = ft_lerp(
					rbs[i]->move_vel.z,
					rbs[i]->raw_move_vel.z * rbs[i]->move_speed_mult,
					ft_fmin(1, rbs[i]->move_acc / fabs(rbs[i]->move_vel.z -
					rbs[i]->raw_move_vel.z)));

			rbs[i]->transform->pos.v4 += rbs[i]->transform->local.forward.v4 *
					rbs[i]->move_speed;
			rbs[i]->transform->pos.v4 += rbs[i]->transform->local.right *
					rbs[i]->move_speed;
			rbs[i]->transform->pos.v4 += rbs[i]->transform->local.up.v4 *
					rbs[i]->move_speed;
		}
		SDL_Delay(5);
	}
	return (0);
}

/// PHYSICS SYSTEM

t_physics_system	*ps_init(t_phys_func *f)
{
	t_physics_system	*ps;

	if (!(ps = ft_memalloc(sizeof(t_physics_system))) ||
		!(ps->thread = SDL_CreateThread(f, "physics", ps)))
		return (NULL);
	return (ps);
}

int					ps_start(t_physics_system *p)
{
	if (!p)
		return (-1);
	SDL_DetachThread(p->thread);
	return (0);
}