#include <unistd.h>
#include "game.h"
#include "window.h"

void gameloop(void)
{
    SDL_Surface *surf = SDL_GetWindowSurface(window);
    struct timespec before, after;
    int loopCount = 0;
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
            if (e.type == SDL_QUIT ||
		(e.type == SDL_KEYDOWN && SDL_GetKeyFromScancode(SDLK_q)))
            {
                break;
            }
        }
        SDL_FillRect(surf,
                     NULL,
                     BACKGROUND_COLOR);

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
