/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:02:32 by chustei           #+#    #+#             */
/*   Updated: 2023/12/01 15:59:05 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_draw_pixel(uint8_t *pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void	ft_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t	*pixelstart;

	pixelstart = &image->pixels[(y * image->width + x) * sizeof(uint32_t)];
	ft_draw_pixel(pixelstart, color);
}
