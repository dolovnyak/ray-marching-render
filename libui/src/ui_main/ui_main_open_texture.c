/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_open_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 16:35:28 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/06 20:19:52 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_main_open_texture(SDL_Renderer *r, t_ui_el *e, const char *path)
{
	SDL_Texture	*t;

	SDL_SetRenderTarget(r, (SDL_Texture *)e->sdl_textures->content);
	SDL_RenderClear(r);
	if (ui_el_load_surface_from(e, path) ||
		!(t = ui_el_create_texture(e)))
	{
		SDL_SetRenderTarget(r, NULL);
		return ;
	}
	SDL_RenderCopy(r, t, NULL, NULL);
	SDL_SetRenderTarget(r, NULL);
}
