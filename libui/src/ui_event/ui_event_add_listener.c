/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_event_add_listener.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 17:16:15 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/13 05:47:23 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_event_add_listener(t_ui_event *e, pred_ptr_event f)
{
	t_list	*node;
	long	ptr;

	ptr = (long)f;
	if ((node = ft_lstnew((void *)&ptr, sizeof(ptr))) == NULL)
	//if (!(node = ft_lstnew(NULL, 0)))
		ui_sdl_deinit(228);
	//node->content = (void *)&ptr;
	if (e->events == NULL)
		e->events = node;
	else
		ft_lstadd_back(&(e->events), node);
	return (FUNCTION_SUCCESS);
}
