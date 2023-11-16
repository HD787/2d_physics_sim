#include <SDL.h>
#include <stdio.h>


#include "player.h"
#include "background.h"
#include "projectile.h"


int main() {

    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    Uint32 LastFrameTime = 0;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    //best practices says you should check to ensure this is properly instantiated
    window = SDL_CreateWindow("My SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );

    screenSurface = SDL_GetWindowSurface( window );

    
    projectile* ball = spawnBall();
    playerCharacter* player = CreatePlayerCharacter();
    SDL_FillRect(screenSurface, &ball->rect, SDL_MapRGB(screenSurface->format,0x00, 0x00, 0xFF));
    Drawbackground(screenSurface, window);
    DrawPlayer(player, screenSurface, window);

    enum DIRECTIONS {
    UP, DOWN, LEFT, RIGHT
    };
    int PlayerDirections[4] = {0, 0, 0, 0};
    
    int quit = 0;
    SDL_Event e;
    while (!quit) {
        Uint32 CurrentFrameTime = SDL_GetTicks();
        float deltaTime = (CurrentFrameTime - LastFrameTime) / 1000.0f;
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }                         
        }

        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if(keystate[SDL_SCANCODE_W]){
            PlayerDirections[UP] = 1;
            player->directionY = -1;
        }
        else {PlayerDirections[UP] = 0;}

        if(keystate[SDL_SCANCODE_A]){
            PlayerDirections[LEFT] = 1; 
            player->directionX = -1;
        }
        else {PlayerDirections[LEFT] = 0;}

        if(keystate[SDL_SCANCODE_S]){
            PlayerDirections[DOWN] = 1;
            player->directionY = 1;
        }
        else {PlayerDirections[DOWN] = 0;}

        if(keystate[SDL_SCANCODE_D]){
            PlayerDirections[RIGHT] = 1;
            player->directionX = 1; 
        }
        else {PlayerDirections[RIGHT] = 0;}

        // check if directions cancel out thisll be important
        if(PlayerDirections[RIGHT] && PlayerDirections[LEFT]) player->directionX = 0;
        if(PlayerDirections[DOWN] && PlayerDirections[UP]) player->directionY = 0;
        //set momentum this will eventually determine the angle of refelction
        if(player->directionX || player->directionY) player->momentum = 1;
        else player->momentum = 0;

        //call our movement functions
        if(PlayerDirections[UP]){ playerup(player, deltaTime); }
        if(PlayerDirections[LEFT]){ playerleft(player, deltaTime); }
        if(PlayerDirections[DOWN]){ playerdown(player, deltaTime); }
        if(PlayerDirections[RIGHT]){ playerright(player, deltaTime); }

        Drawbackground(screenSurface, window);
        SDL_FillRect(screenSurface, &ball->rect, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0xFF));
        move(ball, deltaTime, player);
        SDL_FillRect(screenSurface, &player->rect, SDL_MapRGB(screenSurface->format, 0x00, 0xFF, 0x00));           
        SDL_UpdateWindowSurface(window); 
        LastFrameTime = CurrentFrameTime;
        SDL_Delay(33);
    }
    free(player);
    free(ball);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}