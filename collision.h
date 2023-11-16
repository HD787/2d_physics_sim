#include <SDL.h>
#include <stdio.h>

int checkCollisionRects(SDL_Rect rect1, SDL_Rect rect2){
    if (rect1.x + rect1.w <= rect2.x || rect2.x + rect2.w <= rect1.x) return 0;
    if (rect1.y + rect1.h <= rect2.y || rect2.y + rect2.h <= rect1.y) return 0;
    return 1;
}

// this guy is gonne be hardcoded for now, is that okay?
int checkCollisionBoundary(SDL_Rect rect){
    if(
    rect.x > 640 - rect.w || 
    rect.x < 0 ||
    rect.y < 0 || 
    rect.y > 480 - rect.h
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