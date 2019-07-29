#ifndef RT_H
# define RT_H

#include "math_vec.h"

typedef struct			s_object3d
{
	int					type;
	t_vector3d			center;
	float				radius;
}						t_object3d;

#endif
