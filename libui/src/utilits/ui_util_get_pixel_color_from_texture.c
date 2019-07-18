/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_util_get_pixel_color_from_texture.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 08:48:48 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/12 08:48:57 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

Uint32	ui_util_get_pixel_color_from_texture(SDL_Renderer *renderer,
		SDL_Texture *texture, t_vec2 coord)
{
	Uint32		res;
	SDL_Surface	*surf;
	Uint8		*p;

	surf = SDL_CreateRGBSurfaceWithFormat(0, 1, 1, 24,
			SDL_PIXELFORMAT_RGBA8888);
	res = 0;
	SDL_SetRenderTarget(renderer, texture);
	SDL_RenderReadPixels(renderer, &((t_rect){coord.x, coord.y, 1, 1}), 0,
			surf->pixels, surf->pitch);
	SDL_SetRenderTarget(renderer, NULL);
	p = (Uint8 *)surf->pixels;
	res = (p[2] << 16 & 0xFF0000) + (p[1] << 8 & 0x00FF00) + (p[0] & 0x0000FF);
	SDL_FreeSurface(surf);
	return (res);
}
