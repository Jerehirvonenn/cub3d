/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhirvone <jhirvone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:51:40 by jhirvone          #+#    #+#             */
/*   Updated: 2025/01/20 12:51:44 by jhirvone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*normalize_row(t_parsing *pars, char *row, int longest)
{
	char	*norm_row;
	int		j;

	j = 0;
	norm_row = (char *)malloc(sizeof(char) * (longest + 1));
	if (!norm_row)
		parse_clean_exit(pars, 1, "Error\nMalloc failure\n");
	while (row[j])
	{
		norm_row[j] = row[j];
		j++;
	}
	while (j < longest)
	{
		norm_row[j] = ' ';
		j++;
	}
	norm_row[j] = 0;
	return (norm_row);
}

char	**normalize_map(t_parsing *pars, char **map)
{
	int		i;
	int		longest;
	int		rows;
	char	**norm_map;

	rows = count_rows(map);
	longest = find_longest(map);
	norm_map = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!norm_map)
		parse_clean_exit(pars, 1, "Error\nMalloc failure\n");
	norm_map[rows] = NULL;
	i = 0;
	while (i < rows)
	{
		norm_map[i] = NULL;
		norm_map[i] = normalize_row(pars, map[i], longest);
		i++;
	}
	return (norm_map);
}
