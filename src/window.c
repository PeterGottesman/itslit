#include "window.h"

int CreateWindow(void)
{
    int flags_window;
    int flags_renderer;

    title = strdup("Testing Some SDL Shit");
    flags_window = SDL_WINDOW_OPENGL;// | SDL_WINDOW_RESIZABLE;

    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WIDTH,
                              HEIGHT,
                              flags_window);

    flags_renderer = 0; //SDL_RENDERER_ACCELERATED;

    renderer = SDL_CreateRenderer(window,
                                  -1,
                                  flags_renderer);
    return 0;

}
