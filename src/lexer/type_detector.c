/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_detector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:15:59 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/19 10:06:08 by ndiamant         ###   ########.fr       */
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

int	ft_sep_or_doll(char *str, int i)
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
	else if (str[i] == '$')
		return (6);
	return (0);
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
