/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_detector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:15:59 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/09 11:49:30 by ndiamant         ###   ########.fr       */
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

void	ft_sort_tokens(char	**tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (ft_is_separator(tmp[i], 0))
			printf("%s is a separator\n", tmp[i]);
		else if (tmp[i][j] == '$')
			printf("%s is an env var or $?\n", tmp[i]);
		else
			printf("%s is a word\n", tmp[i]);
		i++;
	}
}
