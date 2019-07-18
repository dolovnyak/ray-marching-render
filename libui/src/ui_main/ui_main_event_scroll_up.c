/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_event_scroll_up.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 05:09:10 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/13 09:23:59 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_main_event_scroll_up(t_ui_main *m, void *a)
{
	(void)a;
	m->params |= MAIN_SCROLL_UP;
	return (1);
}
