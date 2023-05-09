/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:17:26 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/09 11:22:49 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	j;

	i = 0;
	j = 0;
	quote = 0;
	dquote = 0;
	while (str[i])
	{
		if (ft_is_quote(str[i]) == 1)
			quote = !quote;
		if (ft_is_quote(str[i]) == 2)
			dquote = !dquote;
		if (ft_is_blank(str[i]) && !quote && !dquote)
			j++;
		i++;
	}
	return (j);
}