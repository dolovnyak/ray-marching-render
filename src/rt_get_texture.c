
#include "rt.h"
#define STB_IMAGE_IMPLEMENTATION
# include "stb_image.h"


void
find_textures_size(t_rt_main *rt, char **texture_file, int number_of_texture)
{
	unsigned char	*tex_data;
	int 			bpp;
	int 			texture_w;
	int 			texture_h;
	int				i;

	i = -1;
	rt->texture.texture_size = 0;
	while (++i < number_of_texture)
	{
		if (!(tex_data = stbi_load(texture_file[i], &texture_w,
								   &texture_h, &bpp, 4)))
			return ;
		rt->texture.texture_w[i] = texture_w;
		rt->texture.texture_h[i] = texture_h - 1;
		rt->texture.texture_size += (texture_w * texture_h);
		free(tex_data);
	}
}

void		get_textures(t_rt_main *rt, char **texture_file, int number_of_texture)
{
	unsigned char	*tex_data;
	int 			x;
	int 			y;
	int 			total_texture_size;
	int 			i;

	i = -1;
	total_texture_size = 0;
	rt->texture.prev_texture_size[0] = 0;
	while (++i < number_of_texture)
	{
		if (!(tex_data = stbi_load(texture_file[i], &rt->texture.w,
								   &rt->texture.h, &rt->texture.bpp, 4)))
			return;
		y = -1;
		while (++y < rt->texture.h)
		{
			x = -1;
			while (++x < rt->texture.w)
			{
				rt->texture.texture[(x + (y * rt->texture.w)) + total_texture_size] =
						*((int *) tex_data + x + y * rt->texture.w);
			}
		}
		rt->texture.prev_texture_size[i] = total_texture_size;
		total_texture_size += rt->texture.w * (rt->texture.h - 1);
		free(tex_data);
	}
}
