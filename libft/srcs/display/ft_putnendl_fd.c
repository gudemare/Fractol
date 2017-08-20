/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnendl_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 14:26:43 by gudemare          #+#    #+#             */
/*   Updated: 2017/07/11 10:59:47 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnendl_fd(char const *s, int fd, size_t n)
{
	write(fd, s, ft_min(ft_strlen(s), n));
	write(fd, "\n", 1);
}
