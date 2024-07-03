#include "so_long.h"

int	ft_handle_input(int keysym, t_game *game)
{
	if (keysym == KEY_UP || keysym == KEY_W)
		ft_move_player(game, game->player.y - 1, game->player.x, BACK);
	if (keysym == KEY_LEFT || keysym == KEY_A)
		ft_move_player(game, game->player.y, game->player.x - 1, LEFT);
	if (keysym == KEY_RIGHT || keysym == KEY_D)
		ft_move_player(game, game->player.y, game->player.x + 1, RIGHT);
	if (keysym == KEY_DOWN || keysym == KEY_S)
		ft_move_player(game, game->player.y + 1, game->player.x, FRONT);
	if (keysym == KEY_Q || keysym == KEY_ESC)
	{
		game->close_game = 1;
		ft_close_game(game);
	}
	return (0);
}

static void	ft_number_coins(t_game *game)
{
	game->num_coins++;
	game->coins--;
}

void	ft_move_player(t_game *game, int new_y, int new_x, int player_side)
{
	int	last_x;
	int	last_y;

	game->player_side =  player_side;
	last_x = game->player.x;
	last_y = game->player.y;
	if (game->map[new_y][new_x] == 'L')
		ft_loss(game);
	if (game->map[new_y][new_x] == EXIT && game->coins == 0)
		ft_victory(game);
	else if ((game->map[new_y][new_x] == GRASS)
	|| (game->map[new_y][new_x] == COINS))
	{
		game->map[last_y][last_x] = GRASS;
		if (game->map[new_y][new_x] == COINS)
			ft_number_coins(game);
		game->player.x = new_x;
		game->player.y = new_y;
		game->map[new_y][new_x] = PLAYER;
		game->movements++;
		printf("Movements: %d\n", game->movements);
		ft_render_game(game);
	}
}
