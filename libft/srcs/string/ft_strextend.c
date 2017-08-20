/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strextend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:03:05 by gudemare          #+#    #+#             */
/*   Updated: 2017/04/13 17:14:02 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strextend(char *str, int extension)
{
	char	*new;

	if (!(new = ft_strnew(ft_strlen(str) + extension)))
		return (0);
	ft_strcpy(new, str);
	free(str);
	return (new);
}
