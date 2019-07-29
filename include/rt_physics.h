/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_physics.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 03:01:47 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 19:48:39 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PHYSICS_H
# define RT_PHYSICS_H

# define CL_SILENCE_DEPRECATION
# ifndef CONFIG_CL_H
#  include <OpenCL/opencl.h>
#  include <SDL.h>
#  include <opencl-c.h>
#  include "libft.h"
# endif

typedef	int			(t_phys_func)(void *);

typedef	struct		s_local
{
	float3			right;
	float3			up;
	float3			forward;
}					t_local;

typedef struct		s_transform
{
	cl_float3		pos;
	t_local			local;
}					t_transform;

typedef struct		s_rb
{
	cl_float3		move_vel;
	cl_float3		raw_move_vel;
	float			move_acc;
	float			move_speed;
	float			move_speed_mult;
	cl_float3		rot_vel;
	cl_float3		raw_rot_vel;
	float			rot_acc;
	float			rot_speed;
	float			rot_speed_mult;
	t_transform		*transform;
}					t_rb;

typedef struct		s_physics_system
{
	SDL_Thread		*thread;
	t_rb			**rbs;
	size_t			rbs_count;
}					t_physics_system;

int					ps_start(t_physics_system *p);
t_physics_system	*ps_init(t_phys_func *f);

int					ps_func(void *psv);

#endif
