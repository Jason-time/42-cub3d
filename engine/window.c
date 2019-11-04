/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:53:02 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/04 17:56:39 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include "engine.h"

t_window
	*new_window(t_config *config)
{
	t_window	*window;

	if (!(window = (t_window*)malloc(sizeof(*window))))
		return (NULL);
	window->width = config->requested_width;
	window->height = config->requested_height;
	if (!(window->ptr = mlx_init())
		|| !(window->win =	mlx_new_window(
			window->ptr,
			window->width,
			window->height,
			"cub3d"))
		)
	{
		free(window);
		return (NULL);
	}
	set_pos(&window->size, window->width, window->height);
	set_pos(&window->half, window->width / 2, window->height / 2);
	return (window);
}

int
	clear_window(t_window *window)
{
	return (mlx_clear_window(window->ptr, window->win));
}

/*int
	shade_color(int color, double divide)
{
	int	new;

	if (divide <= 1.)
		return (color);
	new = ((int)(((0xFF0000 & color) >> 16) / divide) << 16)
		+ ((int)(((0x00FF00 & color) >> 8) / divide) << 8)
		+ ((int)((0x0000FF & color) / divide));
	return (new);
}*/

/*
** TODO: Window is rendered on the wrong side, the left is on the right
*/
void
	update_window(t_game *game)
{
	t_window	*w;
	int			i;
	int			height;
	t_pos		line;
	t_raysult	ray;
	double		camera_x;

	w = game->window;
	clear_window(w);
	i = 0;
	while (i < w->width)
	{
		// test
			//clock_t begin = clock();
		// test
		camera_x = ((2. * (double)i) / (double)game->window->width) - 1.; // TODO: set_camera_x
		ray_cast(game, &ray, camera_x);
		height = fabs((double)w->height / ray.distance);
		// test
			/*clock_t end = clock();
			double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			if (time_spent > 0.0001)
				printf("{calculate:%lf}\n", time_spent);
			begin = clock();*/
		// test
		set_pos(&line, i, 0);
		draw_vertical_line(w, &line, w->half.y - height / 2, game->config->sky_color);
		set_pos(&line, i, w->half.y - (height / 2));
		draw_vertical_line(w, &line, height, (ray.side) ? 0xFFFFFF : 0xCCCCCC);
		set_pos(&line, i, w->half.y + (height / 2));
		draw_vertical_line(w, &line, w->half.y - height / 2, game->config->floor_color);
		// test
			/*end = clock();
			time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			if (time_spent > 0.0001)
				printf("{draw:%lf}\n", time_spent);*/
		// test
		i++;
	}
	printf("{done}\n");
}
