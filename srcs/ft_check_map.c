#include "so_long.h"

void    ft_check_map(t_game *game, char *av)
{
    int fd;

    ft_check_sorrounders(game);
    ft_check_characters(game);
    ft_check_map_shape(game);
    fd = open(av, O_RDONLY);
    if (fd < 0)
        ft_error_game("Couldn't open the fd", game);
    ft_check_valid_path(game, fd);
}

void    ft_check_sorrounders(t_game *game)
{
    int col;
    int row;
    int y;
    int x;
    
    col = game->columns - 1;
    row = game->rows - 1;
    y = 0;
    while (y <= row)
    {
        x = 0;
        while (x <= col)
        {
            if (game->map[0][x] != WALL || game->map[row][x] != WALL)
                ft_error_game("The map should be surrounder by walls!", game);
            if (game->map[y][0] != WALL || game->map[y][col] != WALL)
                ft_error_game("The map should be surrounder by walls!", game);
            x++;
        }
        y++;
    }
}

void    ft_check_chr(t_game *game, char letter, int y, int x)
{
    if (!ft_strchr("LECP01", letter))
        ft_error_game("Invalid characters", game);
    else if (letter == COINS)
        game->coins++;
    else if (letter == EXIT)
        game->exits++;
    else if (letter == PLAYER)
    {
        game->players++;
        game->player.y = y;
        game->player.x = x;
    }
}

void    ft_check_characters(t_game *game)
{
    int y;
    int x;

    y = 0;
    while (y < game->rows)
    {
        x = 0;
        while (x < game->columns)
        {
            ft_check_chr(game, game->map[y][x], y, x);
            x++;
        }
        y++;
    }
    if (game->coins == 0)
        ft_error_game("There are no coins in the map", game);
    if (game->exits != 1)
        ft_error_game("There should be one exit door", game);
    if (game->players != 1)
        ft_error_game("There should be one player", game);
}

void    ft_check_map_shape(t_game *game)
{
    int len_line;
    int num_col;
    int i;

    num_col = game->columns;
    i = 0;
    if (game->columns == game->rows)
        ft_error_game("The shape of the map should be rectangular", game);
    while (game->map[i])
    {
        len_line = ft_strlen(game->map[i]) - 1;
        if (!game->map[i + 1])
            len_line += 1;
        if (len_line != num_col)
            ft_error_game("Invalid shape of the map", game);
        i++;
    }
}
