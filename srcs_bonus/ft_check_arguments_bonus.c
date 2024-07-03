#include "so_long.h"

void    ft_check_arguments(int ac, char **av, t_game *game)
{
    game->map_alloc = 0;
    if (ac != 2)
        ft_error_game("Incorrect number of arguments\n", game);
    if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".ber", 4))
        ft_error_game("File must be of type \".ber\"\n", game);
}

void ft_init_map(t_game *game, char *av)
{
    char *map_line;
    char *line;
    char *temp;
    int fd;

    fd = open(av, O_RDONLY);
    if (fd == -1)
        ft_error_game("Couldn't open the file\n", game);
    map_line = ft_strdup("");
    game->rows = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        temp = map_line;
        map_line = ft_strjoin(map_line, line);
        free(temp);
        free(line);
        game->rows++;
    }
    close(fd);
    ft_check_empty_lines(game, map_line);
    game->map = ft_split(map_line, '\n');
    game->map_alloc = 1;
    free(map_line);
    ft_init_vars(game);
}

void ft_check_empty_lines(t_game *game, char *map_line)
{
    int i = 0;
    if (map_line[0] == '\n')
    {
        free(map_line);
        ft_error_game("There's an empty line in the first row", game);
    }
    else if (map_line[ft_strlen(map_line) - 1] == '\n')
    {
        free(map_line);
        ft_error_game("There's an empty line in the last row", game);
    }
    while (map_line[i + 1])
    {
        if (map_line[i] == '\n' && map_line[i + 1] == '\n')
        {
            free(map_line);
            ft_error_game("There's an empty line in the map", game);
        }
        i++;
    }
}

void    ft_init_vars(t_game *game)
{
    game->coins = 0;
    game->players = 0;
    game->exits = 0;
    game->columns = ft_strlen(game->map[0]) - 1;
    game->player_side = FRONT;
    game->movements = 0;
    game->close_game = 0;
    game->num_coins = 0;
}
