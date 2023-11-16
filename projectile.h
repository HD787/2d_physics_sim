#include <SDL.h>
#include <stdio.h>



typedef struct{
    SDL_Rect rect;
    double directionX;
    double directionY;
    float momentum;
}projectile;


projectile* spawnBall(){
    projectile* ball = (projectile*) malloc(sizeof(projectile));
    ball->rect.x = 100;
    ball->rect.y = 100;
    ball->rect.w = 10;
    ball->rect.h = 10;
    ball->directionX = 1;
    ball->directionY = -1;
    ball->momentum = .5;
    return ball;
}



void hitWallHorizontal(projectile* ball){
    ball->directionY *= -1;
}
void hitWallVertical(projectile* ball){
    ball->directionX *= -1;
}

int playerCollide(int x, int y, projectile* ball, playerCharacter* player){
    if(x + ball->rect.w < player->rect.x ||
    x > player->rect.x + player->rect.w ||
    y + ball->rect.h < player->rect.y ||
    y > player->rect.y + player->rect.h){
       return 0; 
    }
    else return 1;
}

SDL_Rect move(SDL_Rect new, projectile* ball, float deltaTime){
    float scalar = 100 * deltaTime * ball->momentum;
    float xadder = 0;
    float yadder = 0;
    if(ball->directionX == 0){
        xadder = 0;
    }
    else xadder = ball->directionX * scalar; 

    if(ball->directionY == 0){
        yadder = 0;
    }
    else yadder = ball->directionY * scalar;
    new.x += xadder;
    new.y += yadder;
    return new;
}
