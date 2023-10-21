/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:59:28 by ecaruso           #+#    #+#             */
/*   Updated: 2023/10/21 22:11:21 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_char_input(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
			{
				printf("ERROR:\nAlphabetical input is not valid\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_negative_input(char **argv)
{
	int	i;
	
	i = 1;
	while (argv[i] && i++)
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("ERROR:\nNegative input is not valid\n");
			return (1);
		}
	}
	return (0);
}