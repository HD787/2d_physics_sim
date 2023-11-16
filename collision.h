#include <SDL.h>
#include <stdio.h>

int checkCollisionRects(SDL_Rect rect1, SDL_Rect rect){
    return 0;
}

// this guy is gonne be hardcoded for now, is that okay?
int checkCollisionBoundary(SDL_Rect rect){
    if(
    rect.x > 630 || 
    rect.x < 0 ||
    rect.y < 0 || 
    rect.y > 470
    )
    return 1;
    return 0;
}

int checkCollisionHorizontal(SDL_Rect rect){
   if(
    rect.y < 0 || 
    rect.y > 470
    )
    return 1;
    return 0; 
}

int checkCollisionVertical(SDL_Rect rect){
   if(
    rect.x > 630 || 
    rect.x < 0
    )
    return 1;
    return 0; 
}