/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 14:40:12 by nlowe             #+#    #+#             */
/*   Updated: 2017/06/06 14:59:50 by nlowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_seg	parallel(t_env *env, int x, int y, int direction)
{
	t_seg	ret;

	if (direction == 1)
	{
		ret.x_0 = env->map[y][x].x * XS + XM + env->map[y][x].z * ZS;
		ret.y_0 = env->map[y][x].y * YS + YM + env->map[y][x].z * ZS;
		ret.x_1 = env->map[y + 1][x].x * XS + XM + env->map[y + 1][x].z * ZS;
		ret.y_1 = env->map[y + 1][x].y * YS + YM + env->map[y + 1][x].z * ZS;
	}
	else
	{
		ret.x_0 = env->map[y][x].x * XS + XM + env->map[y][x].z * ZS;
		ret.y_0 = env->map[y][x].y * YS + YM + env->map[y][x].z * ZS;
		ret.x_1 = env->map[y][x + 1].x * XS + XM + env->map[y][x + 1].z * ZS;
		ret.y_1 = env->map[y][x + 1].y * YS + YM + env->map[y][x + 1].z * ZS;
	}
	return (ret);
}

t_seg	isometric(t_env *env, int x, int y, int direction)
{
	t_seg	ret;

	if (direction == 1)
	{
		ret.x_0 = (env->map[y][x].x * XS) -
			(env->map[y][x].y * YS) + XM;
		ret.y_0 = (((env->map[y][x].x * XS) +
			(env->map[y][x].y * YS)) / 2) - (env->map[y][x].z * ZS) + YM;
		ret.x_1 = (env->map[y + 1][x].x * XS) -
			(env->map[y + 1][x].y * YS) + XM;
		ret.y_1 = (((env->map[y + 1][x].x * XS) + (env->map[y + 1][x].y *
			YS)) / 2) - (env->map[y + 1][x].z * ZS) + YM;
	}
	else
	{
		ret.x_0 = (env->map[y][x].x * XS) - (env->map[y][x].y * YS) + XM;
		ret.y_0 = (((env->map[y][x].x * XS) + (env->map[y][x].y * YS)) / 2) -
			(env->map[y][x].z * ZS) + YM;
		ret.x_1 = (env->map[y][x + 1].x * XS) -
			(env->map[y][x + 1].y * YS) + XM;
		ret.y_1 = (((env->map[y][x + 1].x * XS) + (env->map[y][x + 1].y *
			YS)) / 2) - (env->map[y][x + 1].z * ZS) + YM;
	}
	return (ret);
}

void	put_pixel(t_env *env, int x, int y, int color)
{
	int		pos;
	int		i;

	if (x > IMG_WIDTH || y > IMG_HEIGHT || x < 0 || y < 0)
		return ;
	pos = (y * env->ls) + (x * 4);
	i = 0;
	while (i < 3)
	{
		env->data[pos + i] = (color >> (8 * i)) & 0xff;
		i++;
	}
}

void	put_segment(t_env *env, t_seg seg, int color)
{
	seg.d_x = abs(seg.x_1 - seg.x_0);
	seg.d_y = abs(seg.y_1 - seg.y_0);
	seg.s_x = (seg.x_0 < seg.x_1 ? 1 : -1);
	seg.s_y = (seg.y_0 < seg.y_1 ? 1 : -1);
	seg.err1 = (seg.d_x > seg.d_y ? seg.d_x : -seg.d_y) / 2;
	while (1)
	{
		put_pixel(env, seg.x_0, seg.y_0, color);
		if (seg.x_0 == seg.x_1 && seg.y_0 == seg.y_1)
			break ;
		seg.err2 = seg.err1;
		if (seg.err2 > -seg.d_x)
		{
			seg.err1 -= seg.d_y;
			seg.x_0 += seg.s_x;
		}
		if (seg.err2 < seg.d_y)
		{
			seg.err1 += seg.d_x;
			seg.y_0 += seg.s_y;
		}
	}
}

void	add_to_image(t_env *env, int x, int y)
{
	t_seg	seg;

	if (x + 1 < env->x_max)
	{
		seg = (env->projection)(env, x, y, 0);
		put_segment(env, seg, (env->map[y][x]).color);
	}
	if (y + 1 < env->y_max)
	{
		seg = (env->projection)(env, x, y, 1);
		put_segment(env, seg, (env->map[y][x]).color);
	}
}
