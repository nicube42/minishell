/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_detector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasdiamantis <nicolasdiamantis@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:15:59 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/11 09:32:31 by nicolasdiam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	ft_check_cmd(char *tok, t_vars *vars)
{
	int		i;
	char	*cmd;

	i = -1;
	while (vars->splitted_path[++i])
	{
		cmd = ft_strjoin(vars->splitted_path[i], tok);
		if (access(cmd, F_OK) == 0)
		{
			vars->tmp_path = cmd;
			free(cmd);
			return (0);
		}
		free(cmd);
	}
	return (1);
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
