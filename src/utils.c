/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:29:40 by ivautrav          #+#    #+#             */
/*   Updated: 2023/05/10 15:02:31 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bashmaster.h>

char	*append_char(char *str, char c)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(tmp, str, ft_strlen(str) + 2);
	ft_strlcat(str, &c, ft_strlen(str) + 2);
	free(tmp);
	return (str);
}
