/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:30:33 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/06/26 14:25:20 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == 32 || (s[i] >= 9 && s[i] <= 13)))
			i++;
		if (s[i])
			count++;
		while (s[i] && !(s[i] == 32 || (s[i] >= 9 && s[i] <= 13)))
			i++;
	}
	return (count);
}

static char	*ft_create_word(char const *str)
{
	char	*dest;
	int		i;

	i = 0;
	while (str[i] && !(str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	dest = (char *)malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] && !(str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	*ft_free(char **split, int i)
{
	while (--i)
		free(split[i]);
	free(split);
	return (NULL);
}

char	**ft_split(char const *s)
{
	char	**dest;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	dest = (char **)malloc(sizeof(char *) * (count_word(s) + 1));
	if (!dest)
		return (NULL);
	while (*s)
	{
		while (*s == 32 || (*s >= 9 && *s <= 13))
			s++;
		if (*s && !(*s == 32 || (*s >= 9 && *s <= 13)))
		{
			dest[i++] = ft_create_word(s);
			if (dest[i - 1] == NULL)
				return (ft_free(dest, i));
			while (*s && !(*s == 32 || (*s >= 9 && *s <= 13)))
				s++;
		}
	}
	dest[i] = NULL;
	return (dest);
}
