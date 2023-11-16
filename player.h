#include <SDL.h>
#include <stdio.h>

typedef struct projectile projectile;

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


void playerMove(playerCharacter* player, float deltaTime, projectile* ball, char direction){
    int scalar = 100 * deltaTime;
    if(direction == 'u'){
        if (player->rect.y - scalar < 0){
        ;//player cant move out of bounds
            }
        else{
            player->rect.y -= scalar;
        }
    }
    if(direction == 'd'){
        if (player->rect.y + scalar > 440){
            ;//player cant move out of bounds
        }
        else{
            player->rect.y += scalar;
        }
    }
    if(direction == 'l'){
        if (player->rect.x - scalar < 0){
            ;//player cant move out of bounds
        }
        else{
            player->rect.x -= scalar;
        }
    }
    if(direction == 'r'){
        if (player->rect.x + scalar > 600){
            ;//player cant move out of bounds
        }
        else{
            player->rect.x += scalar;
        }
    }

}

void playerup(playerCharacter* player, float deltaTime){
    int scalar = 100 * deltaTime;
    if (player->rect.y - scalar < 0){
        ;//player cant move out of bounds
    }
    else{
        player->rect.y -= scalar;
    }
}
void playerdown(playerCharacter* player, float deltaTime){
    int scalar = 100 * deltaTime;
    if (player->rect.y + scalar > 440){
        ;//player cant move out of bounds
    }
    else{
        player->rect.y += scalar;
    }
}
void playerleft(playerCharacter* player, float deltaTime){
    int scalar = 100 * deltaTime;
    if (player->rect.x - scalar < 0){
        ;//player cant move out of bounds
    }
    else{
        player->rect.x -= scalar;
    }
}
void playerright(playerCharacter* player, float deltaTime){
    int scalar = 100 * deltaTime;
    if (player->rect.x + scalar > 600){
        ;//player cant move out of bounds
    }
    else{
        player->rect.x += scalar;
    }
}
