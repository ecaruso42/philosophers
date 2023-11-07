/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:23:39 by ecaruso           #+#    #+#             */
/*   Updated: 2023/11/07 19:50:53 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	message(t_philo *philo, char *str)
{
	u_int64_t	time;

	time = get_time() - philo->env->start_time;
	if (philo->is_alive || philo->env->number_of_philosophers == 1)
		printf("%lu %d %s\n", time, philo->id + 1, str);
}

void	case_one(t_env *env)
{
	message(&env->philo, FORK);
	my_usleep(env->time_to_die);
	env->philo.is_alive = 0;
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	num;
	int	i;

	neg = 1;
	num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10;
		num += (str[i] - 48);
		i++;
	}
	num *= neg;
	return (num);
}

void	kill_process(t_env *env)
{
	int	i;

	i = 0;
	while(i < env->number_of_philosophers)
	{
		kill(env->pid[i], SIGKILL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_env	env;
	int		i;
	int		status;
	
	i = -1;
	if (argc < 5 || argc > 6)
	{
		printf("ERROR: Argoument count not valid\n");
		return (1);
	}
	if (check_input(argv))
		return (1);
	init(&env, argc, argv);
	while(++i < env.number_of_philosophers)
		play(&env, i);
	i = -1;
	while(++i < env.number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		if(WIFEXITED(status))
			if(WEXITSTATUS(status) == 2)
			{
				printf("ciao\n");
				kill_process(&env);
			}
	}
	return (0);
}
