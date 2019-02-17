#include <unistd.h>
#include "defs.h"
#include "ui.h"
#include "game.h"
#include "render.h"
#include "ray.h"

void init_game(struct gamestate *state)
{
    // Create window and renderer
    (*state).playing = 1;
    (*state).selected = NULL;
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
	    else if (e.type == SDL_MOUSEBUTTONDOWN && state.selected == NULL)
	    {
		SDL_Point point = {.x = e.button.x, .y = e.button.y};
		for (int i = 0; i < state.cur_level->num_placeables; ++i)
		{
		    SDL_Rect rect = {.x = state.cur_level->placeables[i].x,
				.y = state.cur_level->placeables[i].y,
				RENDERABLE_SIZE, RENDERABLE_SIZE};
		    if (SDL_PointInRect(&point, &rect))
		    {
			state.selected = &state.cur_level->placeables[i];
			break;
		    }
		}
	    }
	    else if (e.type == SDL_MOUSEBUTTONUP && state.selected != NULL)
	    {
		state.selected = NULL;
	    }
	    else if (e.type == SDL_MOUSEMOTION && state.selected != NULL)
	    {
		state.selected->x = e.motion.x;
		state.selected->y = e.motion.y;
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

	for (int i = 0; i < state.cur_level->num_placeables; ++i) {
		// render lines
		int lsx = state.cur_level->light_sources[0].x;
		int lsy = state.cur_level->light_sources[0].y;

		int plx = state.cur_level->placeables[i].x;
		int ply = state.cur_level->placeables[i].y;

		render_ray(state.renderer, lsx, lsy, plx + RENDERABLE_SIZE, ply, plx, ply);
		render_ray(state.renderer, lsx, lsy, plx + RENDERABLE_SIZE, ply + RENDERABLE_SIZE, plx, ply);		
		render_ray(state.renderer, lsx, lsy, plx, ply + RENDERABLE_SIZE, plx, ply);		
		render_ray(state.renderer, lsx, lsy, plx, ply, plx, ply);

		point_t* tl = compile_point(&state.cur_level->light_sources[0], lsx, lsy);
		point_t* tr = compile_point(&state.cur_level->light_sources[0], lsx + RENDERABLE_SIZE, lsy);
		point_t* br = compile_point(&state.cur_level->light_sources[0], lsx + RENDERABLE_SIZE, lsy + RENDERABLE_SIZE);
		point_t* bl = compile_point(&state.cur_level->light_sources[0], lsx, lsy + RENDERABLE_SIZE);

		// render_ray(state.renderer, lsx, lsy, tl[0].x, tl[0].y);
		// render_ray(state.renderer, lsx, lsy, tl[1].x, tl[1].y);

		// render_ray(state.renderer, lsx, lsy, tr[0].x, tr[0].y);
		// render_ray(state.renderer, lsx, lsy, tr[1].x, tr[1].y);

		// render_ray(state.renderer, lsx, lsy, br[0].x, br[0].y);
		// render_ray(state.renderer, lsx, lsy, br[1].x, br[1].y);

		// render_ray(state.renderer, lsx, lsy, bl[0].x, bl[0].y);
		// render_ray(state.renderer, lsx, lsy, bl[1].x, bl[1].y);
	}
	
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
