#include "utils.h"

#include <SDL_image.h>

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