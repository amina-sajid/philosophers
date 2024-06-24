/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:50:10 by asajid            #+#    #+#             */
/*   Updated: 2023/10/16 17:22:50 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_overflow(long result, int sign, int current_digit)
{
	if (result > (INT_MAX - current_digit) / 10)
	{
		if (sign == 1)
			return (-1);
		else
			return (0);
	}
	return (1);
}

int	check_sign(const char *str, unsigned int *i, int *sign)
{
	if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	return (1);
}

int	skip_whitespace(const char *str, unsigned int *i)
{
	while (str[*i] != '\0' && ((str[*i] >= 9 && str[*i] <= 13)
			|| str[*i] == 32))
		(*i)++;
	return (1);
}

int	ft_atoi(const char *str)
{
	long			result;
	int				sign;
	unsigned int	i;
	int				current_digit;
	int				overflow_check;

	result = 0;
	sign = 1;
	i = 0;
	skip_whitespace(str, &i);
	check_sign(str, &i, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		current_digit = str[i] - '0';
		overflow_check = ft_check_overflow(result, sign, current_digit);
		if (overflow_check != 1)
			return (overflow_check);
		result = result * 10 + current_digit;
		i++;
	}
	if (result * sign < 0)
		return (0);
	else if (result * sign > INT_MAX)
		return (-1);
	return ((int)(result * sign));
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;
	size_t	n;

	i = 0;
	n = size * count;
	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	ptr = (malloc(n));
	if (!ptr)
		return (0);
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
