/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:04:12 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/18 17:04:12 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**dup_arr(char **arr)
{
	char	**dup;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
		{
			free_array(dup);
			return (NULL);
		}
		i++;
	}
	return (dup);
}

bool	only_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]))
			i++;
		else
			break ;
	}
	if (!str[i])
		return (true);
	return (false);
}

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

void	skip_spaces(char **line)
{
	while (**line && is_whitespace(**line))
		(*line)++;
}

bool valid_quotes(char *str)
{
	int	i;

	ms()->quote[0] = false;
	ms()->quote[1] = false;
	i = 0;
	while (str[i])
		in_quotes(str[i++]);
	if (ms()->quote[0] || ms()->quote[1])
	{
		g_exit_code = 2;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("unexpected EOF while looking for matching `", 2);
		if (ms()->quote[0])
			ft_putchar_fd('\'', STDERR_FILENO);
		else
			ft_putchar_fd('\"', STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (false);
	}
	return (true);
}
