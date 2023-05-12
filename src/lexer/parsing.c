/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 08:59:14 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/12 14:59:33 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_parsing(char *line, t_vars *vars)
{
	int		i;
	int		j;
	int		k;
	int		quote;
	int		dquote;
	char	**tmp;

	j = 0;
	k = 0;
	tmp = malloc(sizeof(char *) * (ft_token_qty(line) + 1));
	tmp[k] = malloc(sizeof(char) * (ft_token_len(line, 0) + 1));
	if (!tmp)
		exit(1);
	vars->quote_error = 0;
	quote = 0;
	dquote = 0;
	i = 0;
	while (ft_is_blank(line[i]))
			i++;
	while (line[i])
	{
		if (ft_is_quote(line[i]) == 2)
		{
			quote = !quote;
			i++;
		}
		if (ft_is_quote(line[i]) == 1)
		{
			dquote = !dquote;
			i++;
		}
		if (line[i - 1] != '>' && line[i - 1] != '<')
		{
			if (ft_is_blank(line[i]) && !quote && !dquote)
			{
				k++;
				tmp[k] = malloc(sizeof(char) * (ft_token_len(line, 0) + 1));
				j = 0;
				i++;
			}
		}
		if (!ft_is_blank(line[i]) || quote || dquote)
		{
			tmp[k][j] = line[i];
			tmp[k][j + 1] = '\0';
			j++;
		}
		if (line[i + 1] == '|' && !quote && !dquote)
		{
			k++;
			tmp[k] = malloc(sizeof(char) * (ft_token_len(line, 0) + 1));
			j = 0;
		}
		if (line[i] == '|' && !quote && !dquote)
		{
			k++;
			tmp[k] = malloc(sizeof(char) * (ft_token_len(line, 0) + 1));
			j = 0;
			if (ft_is_blank(line[i + 1]))
				i++;
		}
		if (ft_is_blank(line[i]) && !quote && !dquote)
		{
			while (ft_is_blank(line[i]) || quote || dquote)
				i++;
		}
		else
			i++;
	}
	if (dquote || quote)
		vars->quote_error = !vars->quote_error;
	tmp[k + 1] = 0;
	ft_sort_tokens(tmp, vars);
}

char	**ft_parsing_execve(char **envp)
{
	int		i;
	char	*full_path;
	char	**splitted_path;

	i = 0;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			full_path = envp[i] + 5;
	}
	splitted_path = ft_split(full_path, ':');
	i = -1;
	while (splitted_path[++i])
		splitted_path[i] = ft_strjoin(splitted_path[i], "/");
	return (splitted_path);
}
