/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhirvone <jhirvone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:29:35 by jhirvone          #+#    #+#             */
/*   Updated: 2025/01/20 13:40:54 by jhirvone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_array(char **array, int n)
{
	int	i;

	i = 0;
	while (i <= n)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}

static int	count_words(const char *str, char sepa)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] != sepa && (str[i + 1] == sepa || str[i + 1] == 0))
			words++;
		else if (i == 0 && str[i] == sepa)
			words++;
		else if (str[i] == sepa && (str[i + 1] == sepa || str[i + 1] == 0))
			words++;
		i++;
	}
	return (words);
}

static int	ft_process_word(char **strs, const char *str, char sepa, int *state)
{
	int	j;

	j = 0;
	while (str[state[0] + j] != sepa && str[state[0] + j])
		j++;
	strs[state[1]] = ft_substr(str, state[0], j);
	if (!(strs[state[1]]))
		return (0);
	state[0] += j;
	state[1]++;
	return (1);
}

// state[0] = i, state[1] = n
static char	**ft_merge(char **strs, const char *str, char sepa, int words)
{
	int	state[2];

	state[0] = 0;
	state[1] = 0;
	while (str[state[0]] && state[1] < words)
	{
		if (str[state[0]] == sepa)
		{
			if (state[0] == 0 || str[state[0] - 1] == sepa)
			{
				strs[state[1]] = ft_strdup("");
				if (!(strs[state[1]]))
					return (free_array(strs, state[1]));
				state[1]++;
			}
			state[0]++;
			continue ;
		}
		if (!ft_process_word(strs, str, sepa, state))
			return (free_array(strs, state[1]));
	}
	strs[state[1]] = 0;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		words;

	words = count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (0);
	strs = ft_merge(strs, s, c, words);
	return (strs);
}
