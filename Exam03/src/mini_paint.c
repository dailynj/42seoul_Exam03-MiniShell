/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 14:34:49 by najlee            #+#    #+#             */
/*   Updated: 2021/07/09 14:34:50 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

typedef struct drawing
{
    int		width;
    int		height;
    char	*map;
} drawing;

typedef struct circle
{
    char	type;
    float	x;
    float	y;
    float	radius;
    char	color;
} circle;

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	get_info(FILE *file, drawing *draw)

{
	char	*tmp;
	int		i;
	char	background;

	if (fscanf(file,"%d %d %c\n", &draw->width, &draw->height, &background) == 3)
	{
		if ((((draw->width < 1) || (300 < draw->width)) || (draw->height < 1)) || (300 < draw->height))
			return (1);
		tmp = (char *)malloc(draw->width * draw->height);
		draw->map = tmp;
		if (!draw->map)
			return (1);
		i = 0;
		while (i < draw->width * draw->height)
			draw->map[i++] = background;
		return (0);
	}
	return (1);
}

float sq_dist(float x1, float y1, float x2, float y2)
{
	float dist_x;
	float dist_y;

	dist_x = powf(x1 - x2, 2);
	dist_y = powf(y1 - y2, 2);
	return (sqrtf(dist_x + dist_y));
}

int draw_circle(circle *circle, drawing *draw)
{
	int j;
	int i;

	if ((circle->radius <= 0.00000000) || ((circle->type != 'C' && (circle->type != 'c'))))
		return (1);
	i = -1;
	while (++i < draw->width)
	{
		j = -1;
		while (++j < draw->height)
		{
			int		is_in = 0;
			float	x = (float)i;
			float	y = (float)j;
			float	distance;

			distance = sq_dist(x, y, circle->x, circle->y) - circle->radius;
			if (distance <= 0.00000000)
			{
				if (distance <= -1.00000000)
					is_in = 1; // Inside
				is_in = 2; // Border
			}
			if ((is_in == 2) || ((is_in == 1 && (circle->type == 'C'))))
				draw->map[i + j * draw->width] = circle->color;
		}
	}
	return (0);
}

int execute(FILE *file)
{
	int 	len;
	circle 	circle;
	drawing	draw;

	if (!get_info(file, &draw))
	{
		len = fscanf(file,"%c %f %f %f %c\n", &circle.type, &circle.x, &circle.y, &circle.radius, &circle.color);
		while (len == 5)
		{
			if (draw_circle(&circle, &draw))
				return (1);
			len = fscanf(file,"%c %f %f %f %c\n", &circle.type, &circle.x, &circle.y, &circle.radius, &circle.color);
		}
		if (len == -1)
		{
			int i = -1;
			while (++i < draw.height)
			{
				int j = -1;
				char tmp[draw.width + 1];
				while (++j < draw.width)
					tmp[j] = draw.map[i * draw.width + j];
				tmp[j] = 0;
				write(1, tmp, draw.width + 1);
				write(1, "\n", 1);
			}
			return (0);
		}
		return (1);
	}
	return (1);
}

int	main(int argc,char **argv)
{
	FILE *file;
	char *error1 = "Error: argument\n";
	char *error2 = "Error: Operation file corrupted\n";

	file = fopen(argv[1], "r");
	if (argc == 2)
	{
		if (file && !execute(file))
			return (0);
		write(1, error2, ft_strlen(error2));
	}
	else
		write(1, error1, ft_strlen(error1));
	return (0);
}
