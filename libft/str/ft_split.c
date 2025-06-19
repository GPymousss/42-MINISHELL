/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 00:40:10 by miniklar          #+#    #+#             */
/*   Updated: 2025/05/27 00:14:46 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	word_counter(const char *s, char c)
{
	int	counter;

	counter = 0;
	while (*s)
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s)
			counter++;
		while (*s != '\0' && *s != c)
			s++;
	}
	return (counter);
}

static void	ft_free(char **array, size_t i)
{
	while (i-- > 0)
	{
		free (array[i]);
	}
	free (array);
}

static char	*fill_word(const char *s, char c)
{
	char	*word;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**array;
	size_t	i;

	array = malloc((sizeof(char *) * (word_counter(s, c) + 1)));
	if (!array)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			array[i] = fill_word(s, c);
			if (!array[i])
				return (ft_free(array, i), NULL);
			i++;
		}
		while (*s != c && *s != '\0')
			s++;
	}
	array[i] = NULL;
	return (array);
}
