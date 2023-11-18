#include <SDL.h>
#include <stdio.h>



typedef struct playerCharacter{
    SDL_Rect rect;
    int directionX;
    int directionY;
    int momentum;
}playerCharacter;

playerCharacter* CreatePlayerCharacter(){
    playerCharacter* player = (playerCharacter*) malloc(sizeof(playerCharacter));
    player->rect.x = 300;
    player->rect.y = 220;
    player->rect.w = 40;
    player->rect.h = 40;
    player->directionX = 0;
    player->directionY = 0;
    player->momentum = 0;

    return player;
}

void DrawPlayer(playerCharacter* player, SDL_Surface* screenSurface, SDL_Window* window){
    SDL_FillRect(screenSurface, &player->rect, SDL_MapRGB(screenSurface->format,0x00, 0xFF, 0x00));
    SDL_UpdateWindowSurface(window);
}


SDL_Rect playerMove(playerCharacter* player, float deltaTime, char direction, SDL_Rect new){
    int scalar = 100 * deltaTime * player->momentum;
    if(direction == 'u'){
        new.y -= scalar;
    }
    if(direction == 'd'){
        new.y += scalar;
    }
    if(direction == 'l'){
        new.x -= scalar;
    }
    if(direction == 'r'){
        new.x += scalar;
    }
    return new;

}

void playerUpdate(playerCharacter* player, SDL_Rect new){
    player->rect = new;
}
