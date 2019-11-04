/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:24:41 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/04 17:55:29 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "engine.h"

static void
	find_start_pos_angle(t_config *config, t_camera *camera)
{
	int	stop;

	stop = 0;
	camera->pos.y = 0;
	while (!stop && camera->pos.y < config->rows)
	{
		camera->pos.x = 0;
		while (!stop && camera->pos.x < config->columns)
		{
			if (ft_in_set(MAP(camera->pos, config), DIRECTIONS))
			{
				stop = 1;
				break ;
			}
			(camera->pos.x)++;
		}
		if (!stop)
			(camera->pos.y)++;
	}
	camera->pos.x += .5;
	camera->pos.y += .5;
	if (MAP(camera->pos, config) == 'N')
	{
		set_pos(&camera->dir, 0, -1);
		set_pos(&camera->plane, -.66, 0);
	}
	else if (MAP(camera->pos, config) == 'E')
	{
		set_pos(&camera->dir, 1, 0);
		set_pos(&camera->plane, 0, -.66);
	}
	else if (MAP(camera->pos, config) == 'S')
	{
		set_pos(&camera->dir, 0, 1);
		set_pos(&camera->plane, .66, 0);
	}
	else if (MAP(camera->pos, config) == 'W')
	{
		set_pos(&camera->dir, -1, 0);
		set_pos(&camera->plane, 0, .66);
	}
	MAP(camera->pos, config) = '0';
}

t_camera
	*new_camera(t_config *config)
{
	t_camera	*camera;

	if (!(camera = (t_camera*)malloc(sizeof(*camera))))
		return (NULL);
	find_start_pos_angle(config, camera);
	return (camera);
}

/*
** TODO: Move X and Y axis independently to allow *walking* on walls
*/
int
	move_camera(t_game *game, int f_b)
{
	t_camera	*c;
	t_pos		n_pos;

	c = game->camera;
	copy_pos(&n_pos, &c->pos);
	if (!f_b)
		set_pos(&n_pos,
			n_pos.x + (c->dir.x * .4), n_pos.y + (c->dir.y * .4));
	else
		set_pos(&n_pos,
			n_pos.x - (c->dir.x * .4), n_pos.y - (c->dir.y * .4));
	if (n_pos.x >= 0 && n_pos.y >= 0
		&& n_pos.x < game->config->columns
		&& n_pos.y < game->config->rows
		&& MAP(n_pos, game->config) == '0')
	{
		copy_pos(&c->pos, &n_pos);
		return (1);
	}
	return (0);
}

int
	rotate_camera(t_game *game, int direction)
{
	t_camera	*c;
	t_pos		old;
	double		rotation;

	c = game->camera;
	rotation = (!direction) ? .2 : -.2;
	copy_pos(&old, &c->dir);
	c->dir.x = (c->dir.x * cos(-rotation)) - (c->dir.y * sin(-rotation));
	c->dir.y = (old.x * sin(-rotation)) + (c->dir.y * cos(-rotation));
	copy_pos(&old, &c->plane);
	c->plane.x = (c->plane.x * cos(-rotation)) - (c->plane.y * sin(-rotation));
	c->plane.y = (old.x * sin(-rotation)) + (c->plane.y * cos(-rotation));
	return (1);
}

/*
** TODO: Set an array of camera_x to avoid calculating it before ray_cast
*/
void
	set_camera_x(int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		i++;
	}
}

void
	debug_print_camera(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->config->rows)
	{
		if (i == 0)
			printf("   0 1 2 3 4 5 6 7 8 9101112131415161718192021222324252627282930\n 0 ");
		else
			printf("%2d ", i);
		j = 0;
		while (j < game->config->columns)
		{
			if (i == (int)game->camera->pos.y
				&& j == (int)game->camera->pos.x)
				printf("  ");
			else
				printf("%c ", MAP_XY(j, i, game->config));
			j++;
		}
		if (i == game->config->rows - 1)
			printf("\n");
		else
			printf("\n");
		i++;
	}
	printf("#CAMERA" \
		"\nx:\t%lf" \
		"\ny:\t%lf" \
		"\nplane:\t%lfx %lfy" \
		"\ndir:\t%lfx %lfy\n",
		game->camera->pos.x, game->camera->pos.y,
		game->camera->plane.x, game->camera->plane.y,
		game->camera->dir.x, game->camera->dir.y);
}
