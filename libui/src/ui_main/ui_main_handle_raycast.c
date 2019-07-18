/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_handle_raycast.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 00:43:05 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/11 22:52:13 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_main_handle_raycast(t_ui_main *m)
{
	t_ui_el *prev;
	t_ui_el *cur;

	prev = m->raycaster->selected;
	cur = ui_raycast(m, m->raycaster->focused_win);
	if (prev != NULL && cur != NULL && prev->id != cur->id)
	{
		ui_event_invoke(prev->events->onPointerLeftButtonReleased, m, prev);
		ui_event_invoke(prev->events->onPointerRightButtonReleased, m, prev);
		ui_event_invoke(prev->events->onPointerExit, m, prev);
		ui_event_invoke(cur->events->onPointerEnter, m, cur);
		m->raycaster->selected = cur;
	}
	else if (prev == NULL && cur != NULL)
	{
		ui_event_invoke(cur->events->onPointerEnter, m, cur);
		m->raycaster->selected = cur;
	}
	else if (cur == NULL && prev != NULL)
	{
		ui_event_invoke(prev->events->onPointerLeftButtonReleased, m, prev);
		ui_event_invoke(prev->events->onPointerRightButtonReleased, m, prev);
		ui_event_invoke(prev->events->onPointerExit, m, prev);
		m->raycaster->selected = NULL;
	}

	if (cur != NULL)
	{
		if (cur->params & EL_IS_SCROLLABLE && m->params & (MAIN_SCROLL_DOWN | MAIN_SCROLL_UP))
		{
			if (m->params & MAIN_SCROLL_DOWN)
				ui_event_invoke(cur->events->onScrollDown, m, cur);
			if (m->params & MAIN_SCROLL_UP)
				ui_event_invoke(cur->events->onScrollUp, m, cur);
			m->params &= ~(MAIN_SCROLL_DOWN | MAIN_SCROLL_UP);
		}
		else if (m->params & MAIN_LMB_PRESSED)
		{
			if ((cur->params & EL_IS_TEXT) && (cur->text_area->params & TEXT_IS_INPUTTING))
				m->focused_el = cur;
			ui_event_invoke(cur->events->onPointerLeftButtonPressed, m, cur);
			m->params &= ~MAIN_LMB_PRESSED;
		}
		else if (m->params & MAIN_LMB_RELEASED)
		{
			ui_event_invoke(cur->events->onPointerLeftButtonReleased, m, cur);
			m->params &= ~MAIN_LMB_RELEASED;
		}
		else if (m->params & MAIN_RMB_PRESSED)
		{
			ui_event_invoke(cur->events->onPointerRightButtonPressed, m, cur);
			m->params &= ~MAIN_RMB_PRESSED;
		}
		else if (m->params & MAIN_RMB_RELEASED)
		{
			ui_event_invoke(cur->events->onPointerRightButtonReleased, m, cur);
			m->params &= ~MAIN_RMB_RELEASED;
		}
	}
	ui_main_handle_continious_event(m, cur);
}
