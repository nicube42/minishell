/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasdiamantis <nicolasdiamantis@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:42:58 by nicolasdiam       #+#    #+#             */
/*   Updated: 2023/05/09 21:15:56 by nicolasdiam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sort_tokens(char	**tmp, char **splitted_path)
{
	int		i;
	int		temoin;

	i = 0;
	temoin = 0;
	while (tmp[i])
	{
		if (ft_is_separator(tmp[i], 0))
			ft_sort_separators(tmp, i);
		else if (tmp[i][0] == '$')
			ft_sort_dollar(tmp, i);
		else
			ft_sort_cmd_arg(tmp, &i, &temoin, splitted_path);
		if (temoin == 0)
			i++;
		temoin = 0;
	}
}

void	ft_sort_cmd_arg(char **tmp, int *i, int *temoin, char **splitted_path)
{
	if (ft_check_cmd(tmp[*i], splitted_path) == 0)
	{
		printf("%s is a cmd\n", tmp[*i]);
	}
	else
		printf("%s, is not a cmd\n", tmp[*i]);
	(*i)++;
	*temoin = 1;
	while (!ft_is_separator(tmp[*i], 0) && tmp[*i][0] != '$')
	{
		printf("%s is an arg\n", tmp[*i]);
		(*i)++;
	}
}

void	ft_sort_dollar(char **tmp, int i)
{
	if (tmp[i][1] == '?')
		printf("%s is $?\n", tmp[i]);
	else
		printf("%s is an env var\n", tmp[i]);
}

void	ft_sort_separators(char **tmp, int i)
{
	if (tmp[i][0] == '|')
	{
		printf("%s is a pipe\n", tmp[i]);
	}
	if (tmp[i][0] == '<' && tmp[i][1] != '<')
	{
		printf("%s is an entry redirect\n", tmp[i]);
	}
	if (tmp[i][0] == '<' && tmp[i][1] == '<')
	{
		printf("%s is an here-doc\n", tmp[i]);
	}
	if (tmp[i][0] == '>' && tmp[i][1] != '>')
	{
		printf("%s redirect the exit\n", tmp[i]);
	}
	if (tmp[i][0] == '>' && tmp[i][1] == '>')
	{
		printf("%s redirect the exit append mode\n", tmp[i]);
	}
}
