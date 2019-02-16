#include <unistd.h>
#include "game.h"
#include "window.h"

void gameloop(void)
{
    SDL_Surface *surf = SDL_GetWindowSurface(window);
    SDL_Rect rect;
    struct timespec before, after;
    int loopCount = 0;
    size_t x, y, i, num_alive;
    Uint32 color = 0;
    while (1)
    {
    	if(clock_gettime(CLOCK_MONOTONIC, &before) == -1)
	{
	    exit(-1);
	}
	//usleep(5000);
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                break;
            }
        }
        SDL_FillRect(surf,
                     NULL,
                     0x000000);

	// update window surface
	
	SDL_UpdateWindowSurface(window);

	if(clock_gettime(CLOCK_MONOTONIC, &after) == -1)
	{
	    exit(-1);
	}

	if(after.tv_sec > before.tv_sec)
	{
	    printf("%d frames this second\n", loopCount);
	    loopCount=0;
	}
	else
	{
	    loopCount++;
	}
    }	
}
