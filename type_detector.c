/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_detector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:15:59 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/09 14:34:17 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_quote(char c)
{
	if (c == '"')
		return (1);
	if (c == '\'')
		return (2);
	return (0);
}

int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

int	ft_is_separator(char *str, int i)
{
	if (str[i] == '>' || (str[i] == '>' && str[i + 1] == '>') || str[i] == '<'
		|| (str[i] == '<' && str[i + 1] == '<') || str[i] == '|')
		return (1);
	return (0);
}

void	ft_sort_tokens(char	**tmp, char **splitted_path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (ft_is_separator(tmp[i], 0))
		{
			if (ft_check_separator(tmp[i]) == 1)
				printf("%s is a pipe\n", tmp[i]);
			if (ft_check_separator(tmp[i]) == 2)
				printf("%s is an entry redirect\n", tmp[i]);
			if (ft_check_separator(tmp[i]) == 3)
				printf("%s is an here-doc\n", tmp[i]);
			if (ft_check_separator(tmp[i]) == 4)
				printf("%s redirect the exit\n", tmp[i]);
			if (ft_check_separator(tmp[i]) == 5)
				printf("%s redirect the exit append mode\n", tmp[i]);
		}
		else if (tmp[i][j] == '$')
			printf("%s is an env var or $?\n", tmp[i]);
		else
		{
			if (ft_check_cmd(tmp[i], splitted_path) == 0)
				printf("%s is a cmd\n", tmp[i]);
			else
				printf("%s, is not a cmd\n", tmp[i]);
		}
		i++;
	}
}

int	ft_check_separator(char *tok)
{
	if (tok[0] == '|')
		return (1);
	if (tok[0] == '<' && tok[1] != '<')
		return (2);
	if (tok[0] == '<' && tok[1] == '<')
		return (3);
	if (tok[0] == '>' && tok[1] != '>')
		return (4);
	if (tok[0] == '>' && tok[1] == '>')
		return (5);
	return (0);
}

int	ft_check_cmd(char *tok, char **splitted_path)
{
	int		i;
	char	*cmd;
	int		j;

	j = -1;
	i = -1;
	while (splitted_path[++i])
	{
		cmd = ft_strjoin(splitted_path[i], tok);
		if (access(cmd, F_OK) == 0)
		{
			free(cmd);
			return (0);
		}
		free(cmd);
	}
	return (1);
}