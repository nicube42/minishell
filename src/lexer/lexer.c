/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:42:58 by nicolasdiam       #+#    #+#             */
/*   Updated: 2023/05/16 21:47:38 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
}

void	ft_sort_cmd_arg(char **tmp, int *i, int *temoin, t_vars *vars)
{
	char	**args;
	int		start;
	t_token	*token;
	int		id;

	id = 0;
	start = *i;
	if (ft_is_builtin(tmp, *i))
		id = BUILTIN_TOKEN;
	else
	{
		if (ft_check_cmd(tmp[*i], vars) == 0)
			id = CMD_TOKEN;
		else
			id = NOT_CMD_TOKEN;
	}
	(*i)++;
	*temoin = 1;
	args = NULL;
	args = ft_sort_args(tmp, i);
	token = ft_create_cmd_token(tmp[start], id, args, vars);
	ft_add_token(vars, token);
	vars->tmp_path = NULL;
}

char	**ft_sort_args(char **tmp, int	*i)
{
	char	**args;
	int		j;

	j = 0;
	while (tmp[*i] && !ft_is_separator(tmp[*i], 0) && tmp[*i][0] != '$')
	{
		j++;
		(*i)++;
	}
	args = calloc(j + 1, sizeof(char *));
	*i -= j;
	j = 0;
	while (tmp[*i] && !ft_is_separator(tmp[*i], 0) && tmp[*i][0] != '$')
	{
		args[j] = ft_strdup(tmp[*i]);
		j++;
		(*i)++;
	}
	/*args[j] = 0;
	if (j > 0)
	{
		args[j] = ft_strdup(args[j - 1]);
		args[j + 1] = 0;
	}*/
	return (args);
}

void	ft_sort_dollar(char **tmp, int i, t_vars *vars)
{
	int		id;
	t_token	*token;

	id = 0;
	if (tmp[i][1] == '?')
		id = ERR_DOLLAR_TOKEN;
	else
		id = ENV_VAR_TOKEN;
	token = ft_create_dollar_token(tmp[i], id);
	ft_add_token(vars, token);
}

void	ft_sort_separators(char **tmp, int i, t_vars *vars)
{
	t_token	*token;
	int		id;

	id = 0;
	if (tmp[i][0] == '|')
		id = PIPE_TOKEN;
	else if (tmp[i][0] == '<' && tmp[i][1] != '<')
		id = RED_ENTRY_TOKEN;
	else if (tmp[i][0] == '<' && tmp[i][1] == '<')
		id = HERE_DOC_TOKEN;
	else if (tmp[i][0] == '>' && tmp[i][1] != '>')
		id = RED_EXIT_TOKEN;
	else if (tmp[i][0] == '>' && tmp[i][1] == '>')
		id = APPEND_TOKEN;
	token = ft_create_redir_token(tmp[i], id);
	ft_add_token(vars, token);
}
