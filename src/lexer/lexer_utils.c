/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivautrav <ivautrav@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:17:26 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/10 12:19:52 by ivautrav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_token_len(char *str, int i)
{
	int	quote;
	int	dquote;

	quote = 0;
	dquote = 0;
	while (str[i])
	{
		if (ft_is_quote(str[i]) == 1)
			quote = !quote;
		if (ft_is_quote(str[i]) == 2)
			dquote = !dquote;
		if (ft_is_blank(str[i]) && !quote && !dquote)
			return (i);
		i++;
	}
	return (i);
}

int	ft_token_qty(char *str)
{
	int	quote;
	int	dquote;
	int	i;
	int	k;

	i = 0;
	k = 0;
	quote = 0;
	dquote = 0;
	while (str[i])
	{
		if (ft_is_quote(str[i]) == 1)
			quote = !quote;
		if (ft_is_quote(str[i]) == 2)
			dquote = !dquote;
		if (ft_is_blank(str[i]) && !quote && !dquote)
		{
			while (ft_is_blank(str[i]))
				i++;
			k++;
		}
		i++;
	}
	return (k);
}
