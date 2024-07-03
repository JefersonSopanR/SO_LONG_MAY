#include "so_long.h"

static void    map_alloc_path(t_game *game, int fd)
{
    char    *line;
    int     i;
    int     y;

    i = 0;
    y = game->rows + 1;
    game->map_floodfill = (char **)malloc(sizeof(char *) * y);
    if (!game->map_floodfill)
        ft_error_game("Invalid map because of memory", game);
    while (i < game->rows)
    {
        line = get_next_line(fd);
        game->map_floodfill[i] = ft_strtrim(line, "\n");
        free(line);
        i++;
    }
    game->map_floodfill[i] = NULL;
    
}

static void ft_fill(t_game *game, int row, int col, t_state *state)
{
    if (row < 0 || col < 0 || row >= game->rows || col >= game->columns)
        return;
    else if (game->map_floodfill[row][col] == 'X')
        return;
    else if (game->map_floodfill[row][col] == WALL)
        return;
    else if (game->map_floodfill[row][col] == LAVA)
        return;
    if (game->map_floodfill[row][col] == EXIT)
        state->exit = true;
    else if (game->map_floodfill[row][col] == COINS)
        state->coins++;

    game->map_floodfill[row][col] = 'X';

    ft_fill(game, row + 1, col, state);
    ft_fill(game, row, col + 1, state);
    ft_fill(game, row - 1, col, state);
    ft_fill(game, row, col - 1, state);
}


static bool ft_floodfill(t_game *game)
{
    t_state state;
    int row;
    int col;

    state.exit = false;
    state.coins = 0;
    row = game->player.y;
    col = game->player.x;
    ft_fill(game, row, col, &state);
    return (state.coins == game->coins && state.exit);
}


void    ft_check_valid_path(t_game *game, int fd)
{
    map_alloc_path(game, fd);
    if (!ft_floodfill(game))
    {
        free_floodfill(game);
        close(fd);
        ft_error_game("Invalid path. There's no way out!", game);
    }
    close(fd);
    free_floodfill(game);
}

void	free_floodfill(t_game *game)
{
	int	i;

	i = 0;
	while (game->map_floodfill[i])
	{
		free(game->map_floodfill[i]);
		i++;
	}
	free(game->map_floodfill);
}