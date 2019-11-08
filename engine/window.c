/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:59:23 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/08 15:43:42 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include "engine.h"

int
	destroy_window(t_window *win)
{
	if (win->screen.img)
		mlx_destroy_image(win->ptr, win->screen.img);
	if (win->ui.img)
		mlx_destroy_image(win->ptr, win->ui.img);
	if (win->ptr && win->win)
		mlx_destroy_window(win->ptr, win->win);
	return (0);
}

int
	clear_window(t_window *window)
{
	return (mlx_clear_window(window->ptr, window->win));
}

int
	init_window(t_window *window, t_config *config)
{
	set_pos(&window->size, config->requested_width, config->requested_height);
	if (window->size.x > 1920)
		window->size.x = 1920;
	if (window->size.y > 1080)
		window->size.y = 1080;
	window->ptr = NULL;
	window->win = NULL;
	if (!(window->ptr = mlx_init())
		|| !(window->win = mlx_new_window(
			window->ptr,
			window->size.x,
			window->size.y,
			"cub3d")))
		return (destroy_window(window));
	set_pos(&window->half, window->size.x / 2, window->size.y / 2);
	window->screen.img = NULL;
	init_image(window, &window->screen);
	window->ui.img = NULL;
	init_image(window, &window->ui);
	return (1);
}

void
	update_window(t_game *game)
{
	t_window	*w;

	w = &game->window;
	mlx_put_image_to_window(w->ptr, w->win, w->screen.img, 0, 0);
	if (game->options & 0x00000001)
	{
		mlx_put_image_to_window(w->ptr, w->win, w->ui.img, 0, 0);
		write_ui_text(game);
	}
}
