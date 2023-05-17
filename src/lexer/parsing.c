/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 08:59:14 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/17 10:43:48 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_skip_blank(char *line, int i)
{
	while (ft_is_blank(line[i]) && line[i])
		i++;
	return (i);
}

int	ft_handle_quote(char *line, t_vars *vars, int i)
{
	while (ft_is_quote(line[i]))
	{
		if (ft_is_quote(line[i]) == 2)
		{
			vars->quote = !vars->quote;
			i++;
		}
		if (ft_is_quote(line[i]) == 1)
		{
			vars->dquote = !vars->dquote;
			i++;
		}
	}
	return (i);
}

int	ft_red_entry_to_string(char *line, t_vars *vars, int i)
{
	int	count;

	count = 0;
	i++;
	i = ft_skip_blank(line, i);
	while (!ft_is_blank(line[i]) && line[i] && !ft_is_separator(line, i) && line[i] != '$')
	{
		count++;
		i++;
	}
	i -= count;
	vars->tmp_tok[vars->j] = ft_calloc((count + 2), sizeof(char));
	count = 0;
	vars->tmp_tok[vars->j][count] = '<';
	count++;
	while (!ft_is_blank(line[i]) && line[i] && !ft_is_separator(line, i) && line[i] != '$')
	{
		vars->tmp_tok[vars->j][count] = line[i];
		count++;
		i++;
	}
	i = ft_skip_blank(line, i);
	vars->j++;
	return (i);
}

void	ft_parsing(char *line, t_vars *vars)
{
	int		i;

	vars->tmp_tok = ft_calloc(ft_token_qty(line) + 2, sizeof(char *));
	i = 0;
	vars->j = 0;
	vars->quote = 0;
	vars->dquote = 0;
	i = ft_skip_blank(line, i);
	while (line[i])
	{
		i = ft_handle_quote(line, vars, i);
		if (ft_is_separator(line, i) == 4 && !vars->quote && !vars->dquote)
			i = ft_red_entry_to_string(line, vars, i);
		else if (ft_is_separator(line, i) == 2 && !vars->quote && !vars->dquote)
			i = ft_red_exit_to_string(line, vars, i);
		else if (ft_is_separator(line, i) == 1 && !vars->quote && !vars->dquote)
			i = ft_append_to_string(line, vars, i);
		else if (ft_is_separator(line, i) == 5 && !vars->quote && !vars->dquote)
			i = ft_pipe_to_string(line, vars, i);
		else if (line[i] == '$')
			i = ft_dollard_to_string(line, vars, i);
		else if (vars->quote || vars->dquote)
			i = ft_parse_inside_quote(line, vars, i);
		else
			i = ft_cmd_to_string(line, vars, i);
		i = ft_skip_blank(line, i);
	}
	ft_sort_tokens(vars->tmp_tok, vars);
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
