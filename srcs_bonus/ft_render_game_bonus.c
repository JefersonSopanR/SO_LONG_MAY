#include "so_long.h"

int    ft_render_game(t_game *game)
{
    char    *movements;
    char    *line;
    int     y;
    int     x;

    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            ft_identify_sprite(game, game->map[y][x], y, x);
            x++;
        }
        y++;
    }
    movements = ft_itoa(game->movements);
    line = ft_strjoin("Movements: ", movements);
    mlx_string_put(game->mlx_ptr, game->win_ptr, 40, 20, 0xFFFFFF, line);
	free(movements);
	free(line);
	return (0);
}

void	ft_identify_sprite(t_game *game, char character, int y, int x)
{	
	if (character == WALL)
		ft_render_sprite(game, game->wall, y, x);
	else if (character == GRASS)
		ft_render_sprite(game, game->grass, y, x);
	else if (character == COINS)
		ft_render_sprite(game, game->img_coins, y, x);
	else if (character == EXIT)
	{
		if (game->coins == 0)
			ft_render_sprite(game, game->exit_open, y, x);
		else
			ft_render_sprite(game, game->exit_close, y, x);
	}
	else if (character == PLAYER)
		ft_check_player_side(game, y, x);
	else if (character == LAVA)
		ft_render_sprite(game, game->lava, y, x);
}

void	ft_check_player_side(t_game *game, int y, int x)
{
	if (game->player_side == FRONT)
		ft_render_sprite(game, game->player_front, y, x);
	if (game->player_side == LEFT)
		ft_render_sprite(game, game->player_left, y, x);
	if (game->player_side == RIGHT)
		ft_render_sprite(game, game->player_right, y, x);
	if (game->player_side == BACK)
		ft_render_sprite(game, game->player_back, y, x);
}

void	ft_render_sprite(t_game *game, t_image sprite, int y, int x)
{
	int	col;
	int	row;

	col = x * sprite.x;
	row = y * sprite.y;
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, sprite.xpm_ptr, col, row);
}

