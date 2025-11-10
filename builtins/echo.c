/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzannis <lzannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:59:56 by leazannis         #+#    #+#             */
/*   Updated: 2025/09/28 20:44:22 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}

static int	skip_n_flags(int argc, char **argv, int *newl)
{
	int	i;
	int	j;

	i = 1;
	*newl = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		j = 1;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0')
			break ;
		*newl = 0;
		i++;
	}
	return (i);
}

int	ft_echo(int argc, char **argv, t_set_fd *set_fd)
{
	int	i;
	int	newl;

	(void)set_fd;
	i = skip_n_flags(argc, argv, &newl);
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	if (newl)
		printf("\n");
	return (0);
}
