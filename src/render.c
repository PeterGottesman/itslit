#include "render.h"
#include "defs.h"
#include "ray.h"

void render_placeable(SDL_Renderer *renderer, int x, int y);
void render_light_source(SDL_Renderer *renderer, int x, int y);

void render_level(SDL_Renderer *renderer, level_t *level)
{
    int x, y;
    for (int i = 0; i < level->num_light_sources; ++i)
    {
	x = level->light_sources[i].x;
	y = level->light_sources[i].y;
	render_light_source(renderer, x, y);
	// render_ray(renderer, level->light_sources[i].x, level->light_sources[i].y, 0, 0);
	// render_ray(renderer, level->light_sources[i].x, level->light_sources[i].y, 0, HEIGHT);
	// render_ray(renderer, level->light_sources[i].x, level->light_sources[i].y, WIDTH, 0);
	// render_ray(renderer, level->light_sources[i].x, level->light_sources[i].y, WIDTH, HEIGHT);
	/* render_placeable(renderer, 50, 50); */
    }

    for (int i = 0; i < level->num_placeables; ++i)
    {
	x = level->placeables[i].x;
	y = level->placeables[i].y;
	if (x >= 0 && y >= 0)
	{
	    render_placeable(renderer, x, y);
	}
	/* else */
	/* { */
	/*     render_in_inventory(renderer, i); */
	/* } */
    }
}

void render_light_source(SDL_Renderer *renderer, int x, int y)
{
    filledCircleRGBA(renderer, x, y, 5, 0xd9, 0xf4, 0x0e, 0xff);
}

void render_placeable(SDL_Renderer *renderer, int x, int y)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = RENDERABLE_SIZE;
    rect.h = RENDERABLE_SIZE;
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderFillRect(renderer, &rect);
}

void render_shadows(SDL_Renderer *renderer, level_t *level)
{
    // render lines
    for (int l = 0; l < level->num_light_sources; ++l)
    {
	light_source_t *ls = &level->light_sources[l];
	int npts = level->num_placeables*4 + 4;
	point_t *poly_points = malloc(sizeof(point_t) * npts);
	int pp = 0;
	for (int i = 0; i < level->num_placeables; ++i) {
	    int plx = level->placeables[i].x;
	    int ply = level->placeables[i].y;

	    // four corners of shape
	    poly_points[pp] = compile_point(level, ls, plx, ply);
	    pp++;
	    poly_points[pp] = compile_point(level, ls, plx + RENDERABLE_SIZE, ply);
	    pp++;
	    poly_points[pp] = compile_point(level, ls, plx + RENDERABLE_SIZE, ply + RENDERABLE_SIZE);
	    pp++;
	    poly_points[pp] = compile_point(level, ls, plx, ply + RENDERABLE_SIZE);
	    pp++;
	}

	poly_points[npts-4] = compile_point(level, ls, 0, 0);
	poly_points[npts-3] = compile_point(level, ls, WIDTH, 0);
	poly_points[npts-2] = compile_point(level, ls,
					    WIDTH,
					    GAME_HEIGHT);
	poly_points[npts-1] = compile_point(level, ls, 0, GAME_HEIGHT);

	sort_points(poly_points, npts);
	Sint16 ys[3];
	Sint16 xs[3];
	int i = 0;
	while (i < npts)
	{
	    xs[0] = poly_points[i].x;
	    ys[0] = poly_points[i].y;
	    i++;
	    xs[1] = poly_points[i].x;
	    ys[1] = poly_points[i].y;
//	i++;
	    xs[2] = ls->x;
	    ys[2] = ls->y;
	
	    filledPolygonRGBA(renderer, xs, ys, 3, 0xd9, 0xf4, 0x0e, 0x10);
	}
    }
}

/* void render_ray(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int trx, int try) */
/* { */
/*     SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); */
/*     point_t dest_point = cast_ray(x1, y1, x2, y2, trx, try); */
/*     SDL_RenderDrawLine(renderer, x1, y1, dest_point.x, dest_point.y); */
/*     SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); */

/* } */
