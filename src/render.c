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
    filledCircleColor(renderer, x, y, 2, 0xffffffff);
}

void render_placeable(SDL_Renderer *renderer, int x, int y)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = RENDERABLE_SIZE;
    rect.h = RENDERABLE_SIZE;
    SDL_RenderFillRect(renderer, &rect);
}

void render_shadows(SDL_Renderer *renderer, level_t *level)
{
    // render lines
    light_source_t *ls = &level->light_sources[0];
    int npts = level->num_placeables*4 + 4;
    point_t *poly_points = malloc(sizeof(point_t) * npts);
    int pp = 0;
    for (int i = 0; i < level->num_placeables; ++i) {
	int plx = level->placeables[i].x;
	int ply = level->placeables[i].y;

	// four corners of shape
	poly_points[pp] = compile_point(ls, plx, ply);
	pp++;
	poly_points[pp] = compile_point(ls, plx + RENDERABLE_SIZE, ply);
	pp++;
	poly_points[pp] = compile_point(ls, plx + RENDERABLE_SIZE, ply + RENDERABLE_SIZE);
	pp++;
	poly_points[pp] = compile_point(ls, plx, ply + RENDERABLE_SIZE);
	pp++;
    }

    poly_points[npts-4] = compile_point(ls, 0, 0);
    poly_points[npts-3] = compile_point(ls, WIDTH, 0);
    poly_points[npts-2] = compile_point(ls,
					WIDTH,
					GAME_HEIGHT);
    poly_points[npts-1] = compile_point(ls, 0, GAME_HEIGHT);

    sort_points(poly_points, npts);
    Sint16 ys[npts];
    Sint16 xs[npts];
    for (int i = 0; i < npts; ++i)
    {
	xs[i] = poly_points[i].x;
	ys[i] = poly_points[i].y;
    }
    filledPolygonColor(renderer, xs, ys, npts, 0x55555510);
}

void render_ray(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int trx, int try)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    point_t dest_point = cast_ray(x1, y1, x2, y2, trx, try);
    SDL_RenderDrawLine(renderer, x1, y1, dest_point.x, dest_point.y);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

}
