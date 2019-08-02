/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:50:06 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/23 17:50:07 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

//TODO create fps checker

void	run_render(t_conf *conf, t_ui_el *el, cl_mem *mem_img,
		cl_mem *mem_objects)
{
	int		err;
	size_t	global_size;
	cl_kernel *kernel;

	kernel = cl_get_kernel_by_name(conf->cl, "render");
	err = clSetKernelArg(*kernel, 0, sizeof(cl_mem), mem_img);
	err |= clSetKernelArg(*kernel, 1, sizeof(int), &el->rect.w);
	err |= clSetKernelArg(*kernel, 2, sizeof(int), &el->rect.h);
	err |= clSetKernelArg(*kernel, 3, sizeof(int), &conf->objects_num);
	err |= clSetKernelArg(*kernel, 4, sizeof(cl_mem), mem_objects);
	err |= clSetKernelArg(*kernel, 5, sizeof(cl_float3), &conf->camera.transform.pos);
	err |= clSetKernelArg(*kernel, 6, sizeof(cl_float3), &conf->camera.transform.local.right);
	err |= clSetKernelArg(*kernel, 7, sizeof(cl_float3), &conf->camera.transform.local.up);
	err |= clSetKernelArg(*kernel, 8, sizeof(cl_float3), &conf->camera.transform.local.forward);
	err |= clSetKernelArg(*kernel, 9, sizeof(float), &conf->camera.clipping_planes.near);
	err |= clSetKernelArg(*kernel, 10, sizeof(float), &conf->camera.clipping_planes.far);
	err |= clSetKernelArg(*kernel, 11, sizeof(float), &conf->camera.fov);
	if (err != 0)
		SDL_Log("set kernel arg - error\n");
	global_size = el->rect.w * el->rect.h;
	err = clEnqueueNDRangeKernel(*conf->cl->queue, *kernel, 1, NULL,
			&global_size, NULL, 0, NULL, NULL);
	if (err != 0)
		SDL_Log("NDR - error\n");

/////////////////////////////TODO put texture in element or make it static, not create/del any draw.
	void	*pixels;
	int		pitch = 0;
	//TODO maybe del surf, and get w and h with in other ways.
	SDL_LockTexture(conf->texture, NULL, &pixels, &pitch);
	err = clEnqueueReadBuffer(*conf->cl->queue, *mem_img, CL_TRUE, 0,
			pitch * el->rect.h, pixels, 0, NULL, NULL);
	if (err != 0)
		SDL_Log("read buffer - error\n");
	SDL_UnlockTexture(conf->texture);
	SDL_RenderCopy(el->sdl_renderer, conf->texture, 0, 0);
////////////////////////////////////////////////////////////////////////////////////////////////
}

void	get_mem_for_render(t_conf *conf, t_ui_el *el, cl_mem *mem_img,
		cl_mem *mem_objects)
{
	int	err;

	*mem_img = clCreateBuffer(*conf->cl->context, CL_MEM_READ_WRITE,
			el->rect.w * el->rect.h * sizeof(int), NULL, &err);
	if (err != 0)
		SDL_Log("create buffer - error\n");
	*mem_objects = clCreateBuffer(*conf->cl->context, CL_MEM_READ_ONLY,
			sizeof(t_object3d) * conf->objects_num, NULL, &err);
	if (err != 0)
		SDL_Log("create buffer - error\n");
	err = clEnqueueWriteBuffer(*conf->cl->queue, *mem_objects, CL_TRUE, 0,
			sizeof(t_object3d) * conf->objects_num,
			conf->objects, 0, NULL, NULL);
	if (err != 0)
		SDL_Log("create buffer - error\n");
}

int		ray_marching_render(t_ui_main *m, void *a)
{
	t_conf	*conf;
	t_ui_el	*el;

	conf = m->data;
	el = a;
	cl_mem		mem_img;
	cl_mem		mem_objects;
	get_mem_for_render(conf, el, &mem_img, &mem_objects);
	run_render(conf, el, &mem_img, &mem_objects);
	clReleaseMemObject(mem_img);
	clReleaseMemObject(mem_objects);
	return (1);
}