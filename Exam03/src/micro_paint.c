/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 14:34:54 by najlee            #+#    #+#             */
/*   Updated: 2021/07/09 14:34:54 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct drawing {
    int width;
    int height;
    char *map;
} drawing;


typedef struct rect {
    char type;
    float x;
    float y;
    float width;
    float height;
    char color;
} rect;

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int get_info(FILE *file, drawing *draw)
{
	char 	*tmp;
	int 	i;
	char	background;

	if (fscanf(file, "%d %d %c\n", &draw->width, &draw->height, &background) == 3)
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

int draw_rect(rect *rect, drawing *draw)
{
	int j;
	int i;

	if (((rect->width <= 0.00000000) || (rect->height <= 0.00000000)) || ((rect->type != 'R' && (rect->type != 'r'))))
		return (1);
	i = -1;
	while (++i < draw->width)
	{
		j = -1;
		while (++j < draw->height)
		{
			int is_in = 1; // Inside
			float x = (float)i;
			float y = (float)j;

			if ((((x < rect->x) || (rect->x + rect->width < x)) || (y < rect->y)) || (rect->y + rect->height < y))
				is_in = 0;
			else if (((x - rect->x < 1.00000000) || ((rect->x + rect->width) - x < 1.00000000)) ||
				((y - rect->y < 1.00000000 || ((rect->y + rect->height) - y < 1.00000000))))
				is_in = 2; // Border
			if ((is_in == 2) || ((is_in == 1 && (rect->type == 'R'))))
				draw->map[i + j * draw->width] = rect->color;
		}
	}
	return (0);
}

int execute(FILE *file)
{
	int 		len;
	rect	rect;
	drawing		draw;

	if (!get_info(file, &draw))
	{
		len = fscanf(file,"%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y, &rect.width, &rect.height, &rect.color);
		while (len == 6)
		{
			if (draw_rect(&rect, &draw))
				return (1);
			len = fscanf(file,"%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y, &rect.width, &rect.height, &rect.color);
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
