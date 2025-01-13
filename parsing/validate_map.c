#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * 0 .normalize map so each row is max length
 * 1. check the map for only 1, 0, one spawn or spaces
 * 2. floodfill from 0 and starting points to see its walled
 */

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return i;
}

int count_rows(char **map)
{
	int rows;

	rows = 0;
	while (map[rows])
		rows++;
	return (rows);
}

int find_longest(char **map)
{
	int i;
	int longest;
	int current;

	i = 0;
	longest = 0;
	current = 0;
	while (map[i])
	{
		current = ft_strlen(map[i]);
		if (current > longest)
			longest = current;
		i++;
	}
	return (longest);
}

/*
 * 1.find the longest row
 * 2.normalize the others to same size with ' ' padding.
 * */
char **normalize_map(char **map)
{
	int	   i;
	int	   j;
	int	   longest;
	int	   rows;
	char **norm_map;

	rows = count_rows(map);
	longest = find_longest(map);
	norm_map = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!norm_map)
		exit(1); // need protection
	norm_map[rows] = NULL;
	i = 0;
	while (i < rows)
	{
		norm_map[i] = (char *)malloc(sizeof(char) * (longest + 1));
		if (!norm_map[i])
			exit(1); // need protection
		j = 0;
		while (map[i][j])
		{
			norm_map[i][j] = map[i][j];
			j++;
		}
		while (j < longest)
		{
			norm_map[i][j] = ' ';
			j++;
		}
		norm_map[i][j] = 0;
		i++;
	}
	return (norm_map);
}

bool validate_characters(char **map)
{
	int	 i;
	int	 j;
	int	 spawn;
	bool result;

	result = true;
	i = 0;
	spawn = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			char c = map[i][j];
			if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' &&
				c != 'W' && c != ' ')
			{
				printf("Invalid character '%c' found in %d %d\n", c, i, j);
				result = false;
			}
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				spawn++;
			j++;
		}
		i++;
	}
	if (spawn != 1 || !result)
		return false;
	return true;
}

bool flood_fill(char **map, int x, int y, int rows, int col)
{
	if (x < 0 || x >= rows || y < 0 || y >= col || map[x][y] == ' ')
	{
		printf("Escaped to %d %d\n", x, y);
		return false;
	}
	if (map[x][y] == '.' || map[x][y] == '1')
		return true;
	if (map[x][y] == '0')
		map[x][y] = '.';
	return (flood_fill(map, x + 1, y, rows, col) &&
			flood_fill(map, x - 1, y, rows, col) &&
			flood_fill(map, x, y + 1, rows, col) &&
			flood_fill(map, x, y - 1, rows, col));
}

bool check_walls(char **norm_map, int rows, int col)
{
	int i;
	int j;

	i = 0;
	while (norm_map[i])
	{
		j = 0;
		while (norm_map[i][j])
		{
			if (norm_map[i][j] == '0' || norm_map[i][j] == 'N' ||
				norm_map[i][j] == 'S' || norm_map[i][j] == 'E' ||
				norm_map[i][j] == 'W')
				if (!flood_fill(norm_map, i, j, rows, col))
					return false;
			j++;
		}
		i++;
	}
	return true;
}
