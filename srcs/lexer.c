/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:42:58 by nicolasdiam       #+#    #+#             */
/*   Updated: 2023/05/10 11:44:09 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sort_tokens(char	**tmp, t_vars *vars)
{
	int		i;
	int		temoin;

	i = 0;
	temoin = 0;
	while (tmp[i])
	{
		if (ft_is_separator(tmp[i], 0))
			ft_sort_separators(tmp, i, vars);
		else if (tmp[i][0] == '$')
			ft_sort_dollar(tmp, i, vars);
		else
			ft_sort_cmd_arg(tmp, &i, &temoin, vars);
		if (temoin == 0)
			i++;
		temoin = 0;
	}
	ft_print_tokens(vars);
}

int	ft_is_builtin(char **tmp, int i)
{
	if (!ft_strncmp(tmp[i], "echo", 4))
		return (1);
	if (!ft_strncmp(tmp[i], "cd", 2))
		return (1);
	if (!ft_strncmp(tmp[i], "pwd", 3))
		return (1);
	if (!ft_strncmp(tmp[i], "export", 6))
		return (1);
	if (!ft_strncmp(tmp[i], "unset", 5))
		return (1);
	if (!ft_strncmp(tmp[i], "env", 3))
		return (1);
	if (!ft_strncmp(tmp[i], "exit", 4))
		return (1);
	return (0);
}

void	ft_sort_cmd_arg(char **tmp, int *i, int *temoin, t_vars *vars)
{
	int		j;
	char	**args;
	int		start;
	t_token	*token;
	int		id;

	id = 0;
	args = malloc(sizeof(char *) * (10 + 1));
	start = *i;
	if (ft_is_builtin(tmp, *i))
	{
		id = BUILTIN_TOKEN;
		printf("%s is a builtin\n", tmp[*i]);
	}
	else
	{
		if (ft_check_cmd(tmp[*i], vars) == 0)
		{
			id = CMD_TOKEN;
			printf("%s is a cmd\n", tmp[*i]);
		}
		else
		{
			id = NOT_CMD_TOKEN;
			printf("%s, is not a cmd\n", tmp[*i]);
		}
	}
	(*i)++;
	*temoin = 1;
	j = 0;
	while (!ft_is_separator(tmp[*i], 0) && tmp[*i][0] != '$')
	{
		args[j] = tmp[*i];
		j++;
		printf("%s is an arg\n", tmp[*i]);
		(*i)++;
	}
	token = ft_create_cmd_token(tmp[start], id, args);
	ft_add_token(vars, token);
}

void	ft_sort_dollar(char **tmp, int i, t_vars *vars)
{
	int		id;
	t_token	*token;

	id = 0;
	if (tmp[i][1] == '?')
	{
		id = ERR_DOLLAR_TOKEN;
		printf("%s is $?\n", tmp[i]);
	}
	else
	{
		id = ENV_VAR_TOKEN;
		printf("%s is an env var\n", tmp[i]);
	}
	token = ft_create_dollar_token(tmp[i], id);
	ft_add_token(vars, token);
}

void	ft_sort_separators(char **tmp, int i, t_vars *vars)
{
	t_token	*token;
	int		id;

	id = 0;
	if (tmp[i][0] == '|')
	{
		id = PIPE_TOKEN;
		printf("%s is a pipe\n", tmp[i]);
	}
	else if (tmp[i][0] == '<' && tmp[i][1] != '<')
	{
		id = RED_ENTRY_TOKEN;
		printf("%s is an entry redirect\n", tmp[i]);
	}
	else if (tmp[i][0] == '<' && tmp[i][1] == '<')
	{
		id = HERE_DOC_TOKEN;
		printf("%s is an here-doc\n", tmp[i]);
	}
	else if (tmp[i][0] == '>' && tmp[i][1] != '>')
	{
		id = RED_EXIT_TOKEN;
		printf("%s redirect the exit\n", tmp[i]);
	}
	else if (tmp[i][0] == '>' && tmp[i][1] == '>')
	{
		id = APPEND_TOKEN;
		printf("%s redirect the exit append mode\n", tmp[i]);
	}
	token = ft_create_redir_token(tmp[i], id);
	ft_add_token(vars, token);
}
