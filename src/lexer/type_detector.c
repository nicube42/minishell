/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_detector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:15:59 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/14 19:33:11 by ndiamant         ###   ########.fr       */
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
	if (str[i] == '>' && str[i + 1] == '>')
		return (1);
	else if (str[i] == '>')
		return (2);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (3);
	else if (str[i] == '<')
		return (4);
	else if (str[i] == '|')
		return (5);
	return (0);
}

int	ft_check_cmd(char *tok, t_vars *vars)
{
	int		i;
	char	*cmd;

	i = -1;
	vars->tmp_path = NULL;
	while (vars->splitted_path[++i])
	{
		cmd = ft_strjoin(vars->splitted_path[i], tok);
		if (access(cmd, F_OK) == 0)
		{
			vars->tmp_path = ft_strdup(cmd);
			printf("%s", vars->tmp_path);
			free(cmd);
			return (0);
		}
		free(cmd);
	}
	return (1);
}

int	ft_is_builtin(char **tmp, int i)
{
	if (!ft_strncmp(tmp[i], "echo", 5))
		return (1);
	if (!ft_strncmp(tmp[i], "cd", 3))
		return (1);
	if (!ft_strncmp(tmp[i], "pwd", 4))
		return (1);
	if (!ft_strncmp(tmp[i], "export", 5))
		return (1);
	if (!ft_strncmp(tmp[i], "unset", 6))
		return (1);
	if (!ft_strncmp(tmp[i], "env", 4))
		return (1);
	if (!ft_strncmp(tmp[i], "exit", 5))
		return (1);
	return (0);
}
