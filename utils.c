/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:59:28 by ecaruso           #+#    #+#             */
/*   Updated: 2023/10/22 00:04:27 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
			{
				printf("ERROR:\nInput is not valid\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
