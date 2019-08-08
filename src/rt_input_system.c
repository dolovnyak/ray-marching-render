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

#include "rt_input_system.h"

static float	get_axis(const Uint8 *state, SDL_Scancode low, SDL_Scancode high)
{
	if (!(state[low] ^ state[high]))
		return (0);
	if (state[high])
		return (1);
	if (state[low])
		return (-1);
	return (0);
}

void	rotate_active(t_input_system *s)
{
	t_rb		*active;

	active = s->active;

	/// Arrows mode

	active->rot.raw_vel = (cl_float3){{
		get_axis(s->state, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN),
		get_axis(s->state, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT),
		0
	}};
	/// End of arrows mode

//	/// Mouse mode
//	int x, y;
//	SDL_GetMouseState(&x, &y);
//	if (!raw_rot_velocity.y)
//		raw_rot_velocity.y = (x - cam->mx) / 1440.f * 300;
//	if (!raw_rot_velocity.x)
//		raw_rot_velocity.x = (y - cam->my) / 810.f * 300;
//	/// End of mouse mode

	active->rot.vel.x = ft_lerp(active->rot.vel.x, active->rot.raw_vel.x, active->rot.acc);
	active->rot.vel.y = ft_lerp(active->rot.vel.y, active->rot.raw_vel.y, active->rot.acc);

	float rot_matrix[9];
//	SDL_LockMutex(s->system.mutex);

	fill_rotation_matrix(&rot_matrix[0], active->transform->right, active->rot.vel.x * active->rot.speed * s->system.delta_time);
//	get_x_rot_matrix(&rot_matrix[0], &active->transform->right, active->rot.vel.x * active->rot.speed * s->system.delta_time);
	mult(&rot_matrix[0], &active->transform->right);
	mult(&rot_matrix[0], &active->transform->up);
	mult(&rot_matrix[0], &active->transform->forward);

	fill_rotation_matrix(&rot_matrix[0], (cl_float3){{0, 1, 0}}, active->rot.vel.y * active->rot.speed * s->system.delta_time);
	mult(&rot_matrix[0], &active->transform->right);
	mult(&rot_matrix[0], &active->transform->up);
	mult(&rot_matrix[0], &active->transform->forward);

//	SDL_UnlockMutex(s->system.mutex);

//	cam->mx = x;
//	cam->my = y;
}

void	move_active(t_input_system *s)
{
//	SDL_LockMutex(s->system.mutex);
	s->active->move.raw_vel = (cl_float3){{
		get_axis(s->state, SDL_SCANCODE_A, SDL_SCANCODE_D),
		get_axis(s->state, SDL_SCANCODE_Q, SDL_SCANCODE_E),
		get_axis(s->state, SDL_SCANCODE_S, SDL_SCANCODE_W)
	}};
	if (s->state[SDL_SCANCODE_LSHIFT])
		s->active->move.raw_vel.v4 *= s->active->move.speed_mult;

	// ТЕСТ
	if (!ft_strcmp(s->active->transform->id, "camera"))
	{
		t_camera *cam = (t_camera *)s->active->transform;
		float d = get_axis(s->state, SDL_SCANCODE_T, SDL_SCANCODE_Y);
		if (d != 0)
			cam->fov += d * 0.1f;
	}
}

int					is_func(void *isv)
{
	t_input_system	*is;

	is = (t_input_system *)isv;
	is->system.now = SDL_GetPerformanceCounter();
	is->system.last = 0;
	while (is)
	{
		is->system.delta_time = (is->system.now - is->system.last) / (double)SDL_GetPerformanceFrequency();
		move_active(is);
		rotate_active(is);
		SDL_Delay(is->system.delay);
		is->system.last = is->system.now;
		is->system.now = SDL_GetPerformanceCounter();
	}
	return (0);
}