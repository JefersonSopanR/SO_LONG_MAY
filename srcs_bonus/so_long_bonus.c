#include "so_long.h"

int main(int ac, char **av)
{
    t_game  *game;

    game = malloc(sizeof(t_game));
    if (!game)
        return (1);
    ft_check_arguments(ac, av, game);
    ft_init_map(game, av[1]);
    ft_check_map(game, av[1]);
    ft_init_mlx(game);
    mlx_hook(game->win_ptr, KeyPress, KeyPressMask, ft_handle_input, game);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, ft_close_game, game);
	mlx_hook(game->win_ptr, Expose, ExposureMask, ft_render_game, game);
	mlx_loop(game->mlx_ptr);
	ft_free_all_allocated_memory(game);
}