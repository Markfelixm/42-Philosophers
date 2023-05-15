/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:24:42 by marmulle          #+#    #+#             */
/*   Updated: 2023/05/11 17:17:11 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_atoi(const char *str)
{
	long	res;
	char	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t'
		|| *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		++str;
	if (*str == '-')
			sign = -1;
	if (*str == '+' || *str == '-')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*(str++) - '0');
		if (res > INT_MAX)
			return (INT_MAX);
		else if (res < INT_MIN)
			return (INT_MIN);
	}
	return (sign * res);
}
