#include "utils.h"

#include <SDL_image.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_gfxPrimitives_font.h>

void initPNG()
{
    IMG_Init(IMG_INIT_PNG);
}

void initFont()
{
    gfxPrimitivesSetFont(gfxPrimitivesFontdata, 8, 8);
}

SDL_Surface* loadPNG(const char* path)
{
    SDL_Surface* loaded = IMG_Load(path);
    if(loaded != NULL)
    {
        SDL_Surface* converted = SDL_DisplayFormatAlpha(loaded);
        SDL_FreeSurface(loaded);
        if(converted != NULL)
        {
            return converted;
        }
    }
    printf("PNG loading failed for \"%s\".\n", path);
    return NULL;
}