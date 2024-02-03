#include "cub3d.h"

#define KEY_PRESS 2
#define KEY_RELEASE 3

int handleKeyPress(int keycode, void *param) {
    printf("Key pressed: %d\n", keycode);
    // Add your key press handling logic here
    return 0;
}

int handleKeyRelease(int keycode, void *param) {
    printf("Key released: %d\n", keycode);
    // Add your key release handling logic here
    return 0;
}

int main() {
    void *mlx_ptr;
    void *win_ptr;

    // Initialize MiniLibX
    mlx_ptr = mlx_init();
    if (!mlx_ptr) {
        fprintf(stderr, "Error: Couldn't initialize MiniLibX\n");
        return 1;
    }

    // Create a window
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "MiniLibX Key Events");

    // Set up event hooks for key press and key release events
    mlx_hook(win_ptr, KEY_PRESS, 0, &handleKeyPress, NULL);
    mlx_hook(win_ptr, KEY_RELEASE, 0, &handleKeyRelease, NULL);

    // Loop to keep the window open and handle events
    mlx_loop(mlx_ptr);

    return 0;
}