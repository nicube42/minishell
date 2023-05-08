/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 08:59:14 by ndiamant          #+#    #+#             */
/*   Updated: 2023/05/08 15:30:34 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

int	ft_is_parenthesis(char c)
{
	if (c == '(')
		return (1);
	return (0);
}

/*int	ft_is_separator(char c)
{
	if (c == '>' || c == '<' || c == '>>' || c == '|' || c == '&&' || c == '||')
		return (1);
	return (0);
}

int	ft_is_variable(char c)
{
	//check if env variable
}*/

int	ft_is_word(char *str, int i)
{
	if (!ft_is_quote(str[i]) && !ft_is_blank(str[i])
		&& !ft_is_parenthesis(str[i])/* && !ft_is_separator(str[i])
		&& !ft_is_variable(str[i])*/ && str[i] != '$')
		return (1);
	return (0);
}

int	ft_extract_word(char *str, int i)
{
	int	quote;

	quote = 0;
	while (str[i])
	{
		if (ft_is_quote(str[i]))
			quote++;
		if (!ft_is_blank(str[i]) || quote % 2 == 1)
			printf("%c", str[i]);
		else
		{
			printf("\n");
			return (i);
		}
		i++;
	}
	return (i);
}

/*void	ft_parsing(char *line)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (line[i])
	{
		if (ft_is_word(line, i) && index == 0)
		{
			index = 1;
			ft_extract_word(line, i);
			while (ft_is_word(line, i))
				i++;
		}
		else
		{
			index = 0;
			i++;
			if (!ft_is_word(line, i))
			{
				i++;
				while (ft_is_word(line, i) && line[i])
					i++;
			}
		}
	}
}*/

void	ft_parsing(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (ft_is_blank(line[i]))
			i++;
		ft_extract_word(line, i);
		while (!ft_is_blank(line[i]) && line[i])
			i++;
	}
}

int	main(void)
{
	//ft_parsing("echo test $test \' \" \" ( ");
	ft_parsing("ARG=\"4 67 3 87 23\"; ./push_swap $ARG | ./checker_OS $ARG");
	return (0);
}
