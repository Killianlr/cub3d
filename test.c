#include "include/cub3d.h"

#define KEY_PRESS 2
#define KEY_RELEASE 3
#define KEY_PRESS_EVENT 2
#define KEY_RELEASE_EVENT 3
#define ESC_KEY 53

int key_press_hook(int keycode, void *param)
{
    printf("Key pressed: %d\n", keycode);
    return (0);
}

int key_release_hook(int keycode, void *param)
{
    printf("    Key released: %d\n", keycode);
    return (0);
}

int main()
{
    void *mlx_ptr;
    void *win_ptr;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 500, 500, "MiniLibX Key Events");

    // Set up event hooks for key presses and releases
    mlx_hook(win_ptr, KEY_PRESS, KEY_PRESS_EVENT, key_press_hook, NULL);
    mlx_hook(win_ptr, KEY_RELEASE, KEY_RELEASE_EVENT, key_release_hook, NULL);

    // Start the event loop
    mlx_loop(mlx_ptr);

    return 0;
}