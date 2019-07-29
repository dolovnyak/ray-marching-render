/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_CAMERA_H
# define RT_CAMERA_H

//# include "libui.h"
# include "math_vec.h"
# include "rt_physics.h"

typedef struct			s_camera
{
	t_transform			transform;
	t_rb				rb;
	/// Rendering
	float 				aspect_ratio;
	float				min_distance;
	float				max_distance;
	/// Physics
	float				pos_acc;
	float				speed;
	t_vector3d			pos;
	t_vector3d			velocity;
	t_vector3d			rot_velocity;
	float				rot_speed;
	float				rot_acc;
	t_vector3d			local_x;
	t_vector3d			local_y;
	t_vector3d			local_z;
	/// Temp
	int					mx;
	int					my;
}						t_camera;

//void	move_camera(t_ui_main *m);
//void	rotate_camera(t_ui_main *m);

#endif
