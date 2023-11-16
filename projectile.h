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
    ball->directionX = 0;
    ball->directionY = 0;
    //do something with this
    ball->momentum = 1;
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

void move(projectile* ball, float deltaTime, playerCharacter* player){
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

    if(ball->rect.x + ball->directionX * scalar > 630 || 
    ball ->rect.x + ball->directionX * scalar < 0 || 
    playerCollide(ball->rect.x + ball->directionX * scalar, ball->rect.y, ball, player)){
       xadder *= -1;
       ball->directionX *=-1;
    }

    if(ball->rect.y + ball->directionY * scalar > 470 ||
    ball->rect.y + ball->directionY * scalar < 0 ||
    playerCollide(ball->rect.x, ball->rect.y + ball->directionY * scalar, ball, player)){
       yadder *= -1;
       ball->directionY *= -1;
    }

    ball->rect.x += xadder;
    ball->rect.y += yadder;
}
