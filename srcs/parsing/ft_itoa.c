/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:24:59 by alvina            #+#    #+#             */
/*   Updated: 2023/04/21 00:59:35 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_length(long n)
{
	long	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_making_str(char *str, long nb, int i)
{
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[i--] = (nb % 10) + 48;
		nb /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nb;

	nb = n;
	str = (char *)malloc(sizeof(char) * ft_length(nb) + 1);
	if (!str)
		return (NULL);
	i = ft_length(nb) - 1;
	str[ft_length(nb)] = '\0';
	return (ft_making_str(str, nb, i));
}
