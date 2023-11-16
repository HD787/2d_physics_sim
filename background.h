#include <SDL.h>
#include <stdio.h>


void Drawbackground(SDL_Surface* screenSurface, SDL_Window* window){
    SDL_Rect rrect = {640/2, 0, 640/2, 480};
    SDL_Rect lrect = {0, 0, 640/2, 480};
    SDL_FillRect(screenSurface, &lrect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_FillRect(screenSurface, &rrect, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));
}