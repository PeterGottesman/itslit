#include <unistd.h>
#include "defs.h"
#include "ui.h"
#include "game.h"
#include "render.h"

void init_game(struct gamestate *state)
{
    // Create window and renderer
    (*state).playing = 1;
    int window_flags = SDL_WINDOW_OPENGL;// | SDL_WINDOW_RESIZABLE;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, window_flags,
				&(*state).window, &(*state).renderer);
    SDL_SetWindowTitle(state->window, "It's Lit");
}

void gameloop(struct gamestate state)
{
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
	SDL_SetRenderDrawColor(state.renderer,
			       BACKGROUND_R,
			       BACKGROUND_G,
			       BACKGROUND_B,
			       BACKGROUND_A);
	SDL_RenderClear(state.renderer);

	// update window surface
	draw_ui(state.renderer);

	render_level(state.renderer, state.cur_level);
	
	SDL_RenderPresent(state.renderer);

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
