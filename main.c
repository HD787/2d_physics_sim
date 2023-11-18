#include <SDL.h>
#include <stdio.h>


#include "player.h"
#include "background.h"
#include "projectile.h"
#include "collision.h"

int main() {

    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    Uint32 LastFrameTime = 0;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    //best practices says you should check to ensure this is properly instantiated, im not doing this
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
        //IMPUT HANDLING
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


        //PLAYER MOVEMENT
        // check if directions cancel out thisll be important
        if(PlayerDirections[RIGHT] && PlayerDirections[LEFT]) player->directionX = 0;
        if(PlayerDirections[DOWN] && PlayerDirections[UP]) player->directionY = 0;
        //set momentum this will eventually determine the angle of refelction
        if(player->directionX || player->directionY) player->momentum = 1;
        else player->momentum = 0;

        //Scalars are the amount of pixels an entity will move, precalculated to avoind rounding errors
        int scalarX = 100 * player->directionX * deltaTime;
        int scalarY = 100 * player->directionY * deltaTime ;
        SDL_Rect playerTemp = player->rect;
        SDL_Rect projectileTemp = ball->rect;

        //UP
        if(PlayerDirections[UP]){ playerTemp = playerMove(player, deltaTime, 'u', playerTemp); }
        if(checkCollisionBoundary(playerTemp)) playerTemp = player->rect;
        if(checkCollisionRects(playerTemp, projectileTemp)){
            projectileTemp.y += scalarY;
            if(!checkCollisionBoundary(projectileTemp)){
                ball->rect = projectileTemp;
                player->rect = playerTemp;
            }
            else playerTemp = player->rect;
        }
        else player->rect = playerTemp;

        //LEFT
        if(PlayerDirections[LEFT]){ playerTemp = playerMove(player, deltaTime, 'l', playerTemp); }
        if(checkCollisionBoundary(playerTemp)) playerTemp = player->rect;
        if(checkCollisionRects(playerTemp, projectileTemp)){
            projectileTemp.x += scalarX;
            if(!checkCollisionBoundary(projectileTemp)){
                ball->rect = projectileTemp;
                player->rect = playerTemp;
            }
            else {playerTemp = player->rect; }
        }
        else {player->rect = playerTemp; }

        //DOWN
        if(PlayerDirections[DOWN]){ playerTemp = playerMove(player, deltaTime, 'd', playerTemp); }
        if(checkCollisionBoundary(playerTemp)) playerTemp = player->rect;
        if(checkCollisionRects(playerTemp, projectileTemp)){
            projectileTemp.y += scalarY;
            if(!checkCollisionBoundary(projectileTemp)){
                ball->rect = projectileTemp;
                player->rect = playerTemp;
            }
            else playerTemp = player->rect;
        }
        else player->rect = playerTemp;

        //RIGHT
        if(PlayerDirections[RIGHT]){ playerTemp = playerMove(player, deltaTime, 'r', playerTemp); }
        if(checkCollisionBoundary(playerTemp)) playerTemp = player->rect;
        if(checkCollisionRects(playerTemp, projectileTemp)){
            projectileTemp.x += scalarX;
            if(!checkCollisionBoundary(projectileTemp)){
                ball->rect = projectileTemp;
                player->rect = playerTemp;
            }
            else playerTemp = player->rect;
        }
        else player->rect = playerTemp;

        //PROJECTILE MOVEMENT
        
        projectileTemp = move(projectileTemp, ball, deltaTime);
        SDL_Rect projectileTempX = {projectileTemp.x, ball->rect.y, 10, 10};
        SDL_Rect projectileTempY = {ball->rect.x, projectileTemp.y, 10, 10};
        if(checkCollisionRects(projectileTempX, player->rect)) ball->directionX *= -1;
        if(checkCollisionRects(projectileTempY, player->rect)) ball->directionX *= -1;  
        if(checkCollisionHorizontal(projectileTemp)) ball->directionY *= -1;
        if(checkCollisionVertical(projectileTemp)) ball->directionX *= -1;
        ball->rect = move(projectileTemp, ball, deltaTime);




        // here are my update screen functions
        Drawbackground(screenSurface, window);
        SDL_FillRect(screenSurface, &ball->rect, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0xFF));
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