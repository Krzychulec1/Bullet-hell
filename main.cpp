#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define PLAYER_HORIZONTAL_SIZE 100
#define PLAYER_VERTICAL_SIZE 100

//level size
#define LEVEL_WIDTH 2000
#define LEVEL_HEIGHT 1900

//screen size
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 1000

//arrays values
#define MAX_PLAYER_BULLET_AMOUNT 10000
#define ENEMY_BULLETS_AMOUNT 20
#define MAX_HP_OCCURRENCE 1000
#define ENEMY_BULLETS_TYPES 15
#define SHAPE_TYPES 2

//objects size
#define BULLET_VERTICAL_SIZE 10
#define BULLET_HORIZONTAL_SIZE 10
#define ENEMY_1_VERTICAL_SIZE 200
#define ENEMY_1_HORIZONTAL_SIZE 130
#define ENEMY_2_VERTICAL_SIZE 300
#define ENEMY_2_HORIZONTAL_SIZE 280
#define ENEMY_3_VERTICAL_SIZE 300
#define ENEMY_3_HORIZONTAL_SIZE 160
#define HP_SIZE 50
#define SHAPE_1_SIZE 220
#define SHAPE_2_VERTICAL_SIZE 160
#define SHAPE_2_HORIZONTAL_SIZE 320
#define EXPLOSION_SIZE 300

//game values
#define BULLET_SPEED 1
#define PLAYER_UNIT_BULLET_SPEED 6
#define INVISIBILITY_PLAYER 2
#define BONUS_TMIE 2;
#define ENEMY_HP 20
#define PLAYER_HP 10

//variables values
#define PLAYER_BULLET 0
#define ENEMY_BULLET 1
#define ENEMY_BULLET_2 2
#define TOP 0
#define BOTTOM 1
#define LEFT 2
#define RIGHT 3
#define NONE 4

struct Player {
    double x1, x2, y1, y2;
    int px;
    int py;
    int rel_py;
};

struct Bullet {
    int sizeVertical, sizeHorizontal;
    double x1, x2, y1, y2, delay;
    double px;
    double py;
    int id;
    int speed;
    int type;
    int move;
};

struct Health {
    int px, py, called;
};

struct Shape
{
    int px, py, called;
    double shapeDelay, shapeTime;
};

struct GameVariables {
    int t1, t2, quit, frames, rc, turn, intWorldTime, playerPoints, enemyPoints, playerBullets, level, stage, enemyHP, playerHP, score, bonusPoints, lastMove;
    double delta, worldTime, fpsTimer, fps, distance, indestructiblePlayer, explosionTime1, explosionTime2, explosion1X, explosion1Y, explosion2X, explosion2Y, delay, shootingDelay, bonusTime, HPdelay;
    char text[128];
};

struct SDLVariables {
    SDL_Surface* screen, * charset;
    SDL_Surface* eti;
    SDL_Surface* playermissile;
    SDL_Surface* missile;
    SDL_Surface* player;
    SDL_Surface* background;
    SDL_Texture* scrtex;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* explosion;
    SDL_Surface* enemy2;
    SDL_Surface* background2;
    SDL_Surface* missile2;
    SDL_Surface* enemy3;
    SDL_Surface* enemy3A;
    SDL_Surface* enemy3B;
    SDL_Surface* shapebullet;
    SDL_Surface* missile3;
    SDL_Surface* background3;
    SDL_Surface* champ1;
    SDL_Surface* champ2;
    SDL_Surface* champ3;
    SDL_Surface* champ4;
    SDL_Surface* champ6;
    SDL_Surface* champ7;
    SDL_Surface* HP;
    SDL_Surface* shape1;
    SDL_Surface* shape2;
    SDL_Surface* A;
    SDL_Surface* B;
    SDL_Surface* C;
    SDL_Surface* D;
    SDL_Surface* E;
};

struct ColorSet {
    int czarny, zielony, czerwony, niebieski;
};

struct Camera {
    int x1, x2, y1, y2;
};

struct Enemy {
    double x1, x2, y1, y2, px, py;

};

// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDLVariables* SDLData, int x, int y, const char* text);

// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);

// draw a single pixel
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);

// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDLVariables* SDLData, int x, int y, int l, int dx, int dy, Uint32 color);

// draw a rectangle of size l by k
void DrawRectangle(SDLVariables* SDLData, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

//creates single enemy bullet
void CreateEnemyBullet(Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], int type, int id, int px, int py, int speed, int sizeVertical, int sizeHorizontal, int x, int y);

//creates all enemy bullets
void CreateenemyBullets(Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT]);

//creates bullets of player
void CreatePlayerBullet(Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], int type, int id, int px, int py, int speed, int sizeVertical, int sizeHorizontal, int x, int y);

//sets beggining values of the game
void SetValues(Player* gracz, GameVariables* gameData, Camera* camera, Enemy* enemy, Health* HP, Shape shape[SHAPE_TYPES]);

//moves bullets when they run out of the map for enemies 1 and 2
void MoveMissileToStartPos(Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], int type, int id);

//moves bullets wheny they run out of the map for enemy 3
void MoveMissileToStartPos3(Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], int type, int id, Enemy* enemy);

//prints error if BMP is not loaded
int     ErrorBMP(SDLVariables* SDLData, char* name);

//shots bullets for enemies
void ShootMissiles1(Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], SDLVariables* SDLData, GameVariables* gameData, Player* gracz);

void ShootMissiles2(Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], SDLVariables* SDLData, GameVariables* gameData, Player* gracz);

void ShootMissiles3(Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], SDLVariables* SDLData, GameVariables* gameData, Player* gracz, Enemy* enemy);

//counts fps
void Fps(GameVariables* gameData);

//set colors for the game
void SetColor(ColorSet* colors, SDLVariables* SDLData);

//set values to the beggining state
void NewGame(GameVariables* gameData, Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], Player* gracz, Camera* camera, Enemy* enemy, Health* HP, Shape shape[SHAPE_TYPES]);

//loads BMPs
void LoadBMP(SDLVariables* SDLData);

//shots player bullets
void PlayerShooting(Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], SDLVariables* SDLData, GameVariables* gameData, Player* gracz);

//checks if player bullet hit enemy
int CheckCollisionPlayerBullet_enemy(GameVariables* gameData, Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], Enemy* enemy);

//checks if enemy bullet hits player
void CheckCollisionEnemyBullet_Player(GameVariables* gameData, Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], Player* gracz);

//prints top bar
void DrawTopBar(SDLVariables* SDLData, GameVariables* gameData, ColorSet* colors, Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT]);

//changes vairables in loop 
void ChangeVarialbes(GameVariables* gameData, Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], Shape shape[SHAPE_TYPES]);

//loads SDL functions
int PrepareSDLs(GameVariables* gameData, SDLVariables* SDLData);

//moves enemy 3
void MoveEnemy(Enemy* enemy, GameVariables* gameData);

//prints menu
void PrintMenu(GameVariables* gameData, SDLVariables* SDLData, ColorSet* colors);

//functions that move player
void MoveUp(Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], GameVariables* gameData, Camera* camera, Player* gracz);

void MoveDown(Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], GameVariables* gameData, Camera* camera, Player* gracz);

void MoveLeft(Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], GameVariables* gameData, Camera* camera, Player* gracz);

void MoveRight(Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], GameVariables* gameData, Camera* camera, Player* gracz);

//creates HP bonuses
void CreateHP(Health* HP, GameVariables* gameData);

//creates shapes on the ground
void CreateShape(Shape shape[SHAPE_TYPES], GameVariables* gameData);

//checks if player catch hp bonus
void CheckHP_Player(Health* HP, GameVariables* gameData, Player* gracz);

//checks if player gets damage from shape
void CheckShape_Player(Shape shape[SHAPE_TYPES], GameVariables* gameData, Player* gracz);

//show grade for the players performance
void Grade(GameVariables* gameData, SDLVariables* SDLData);

//prepares values for level
void SetLevel(SDLVariables* SDLData, Player* gracz, Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], GameVariables* gameData, Enemy* enemy, ColorSet* colors, Health* HP);

//loads choosen level
void LoadLevel(SDLVariables* SDLData, GameVariables* gameData, Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], Enemy* enemy, ColorSet* colors, Player* gracz, Health* HP, Shape shape[SHAPE_TYPES], Camera* camera);

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {
    SDL_Event event;
    Player gracz;
    GameVariables gameData;
    ColorSet colors;
    SDLVariables SDLData;
    Camera camera;
    Enemy enemy;
    Bullet ArrayOfBullets[ENEMY_BULLETS_TYPES][ENEMY_BULLETS_AMOUNT];
    Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT];
    Shape shape[SHAPE_TYPES];
    Health HP;
    SetValues(&gracz, &gameData, &camera, &enemy, &HP, shape);
    if (PrepareSDLs(&gameData, &SDLData) == 1)
        return 1;
    LoadBMP(&SDLData);
    SetColor(&colors, &SDLData);
    SDL_ShowCursor(SDL_DISABLE);
    gameData.score = 0;
    gameData.level = -1;
    while (!gameData.quit) {
        ChangeVarialbes(&gameData, ArrayOfBullets, shape);
        const Uint8* pressed = SDL_GetKeyboardState(NULL);
        LoadLevel(&SDLData, &gameData, ArrayOfBullets, ArrayOfPlayerBullets, &enemy, &colors, &gracz, &HP, shape, &camera);
        if (!pressed[SDL_SCANCODE_UP] && !pressed[SDL_SCANCODE_DOWN] && !pressed[SDL_SCANCODE_LEFT] && !pressed[SDL_SCANCODE_RIGHT])
        {
            if (gameData.level == 1 || gameData.level == 2 || gameData.level == 3)
            {
                gameData.lastMove = NONE;
                DrawSurface(SDLData.screen, SDLData.player, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            }
        }
        Fps(&gameData);
        CreateHP(&HP, &gameData);
        CreateShape(shape, &gameData);
        CheckHP_Player(&HP, &gameData, &gracz);
        CheckShape_Player(shape, &gameData, &gracz);
        if (pressed[SDL_SCANCODE_UP])
            MoveUp(ArrayOfPlayerBullets, &gameData, &camera, &gracz);
        else if (pressed[SDL_SCANCODE_DOWN])
            MoveDown(ArrayOfPlayerBullets, &gameData, &camera, &gracz);
        else if (pressed[SDL_SCANCODE_LEFT])
            MoveLeft(ArrayOfPlayerBullets, &gameData, &camera, &gracz);
        else if (pressed[SDL_SCANCODE_RIGHT])
            MoveRight(ArrayOfPlayerBullets, &gameData, &camera, &gracz);
        SDL_UpdateTexture(SDLData.scrtex, NULL, SDLData.screen->pixels, SDLData.screen->pitch);
        SDL_RenderClear(SDLData.renderer);
        SDL_RenderCopy(SDLData.renderer, SDLData.scrtex, NULL, NULL);
        SDL_RenderPresent(SDLData.renderer);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) gameData.quit = 1;
                else if (event.key.keysym.sym == SDLK_n)
                {
                    NewGame(&gameData, ArrayOfBullets, &gracz, &camera, &enemy, &HP, shape);
                }
                else if (event.key.keysym.sym == SDLK_SPACE)
                {
                    if (gameData.shootingDelay <= 0)
                    {
                        CreatePlayerBullet(ArrayOfPlayerBullets, PLAYER_BULLET, gameData.playerBullets, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, BULLET_SPEED, BULLET_VERTICAL_SIZE, BULLET_HORIZONTAL_SIZE, gracz.px, gracz.rel_py);
                        gameData.playerBullets++;
                        gameData.shootingDelay = 0.5;
                    }
                }
                else if (event.key.keysym.sym == SDLK_1)
                {
                    gameData.level = 1;
                    NewGame(&gameData, ArrayOfBullets, &gracz, &camera, &enemy, &HP, shape);
                }
                else if (event.key.keysym.sym == SDLK_2)
                {
                    gameData.level = 2;
                    NewGame(&gameData, ArrayOfBullets, &gracz, &camera, &enemy, &HP, shape);
                }
                else if (event.key.keysym.sym == SDLK_3)
                {
                    gameData.level = 3;
                    NewGame(&gameData, ArrayOfBullets, &gracz, &camera, &enemy, &HP, shape);
                }
                else if (event.key.keysym.sym == SDLK_m)
                {
                    gameData.level = -1;
                }
                break;
            case SDL_QUIT:
                gameData.quit = 1;
                break;
            };
        };
        gameData.frames++;
        gameData.turn++;
    };
    SDL_FreeSurface(SDLData.charset);
    SDL_FreeSurface(SDLData.screen);
    SDL_DestroyTexture(SDLData.scrtex);
    SDL_DestroyRenderer(SDLData.renderer);
    SDL_DestroyWindow(SDLData.window);
    SDL_Quit();
    return 0;
};

void LoadLevel(SDLVariables* SDLData, GameVariables* gameData, Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], Enemy* enemy, ColorSet* colors, Player* gracz, Health* HP, Shape shape[SHAPE_TYPES], Camera* camera)
{
    if (gameData->level == 1)
    {
        DrawSurface(SDLData->screen, SDLData->background, gracz->px, gracz->py);
        DrawSurface(SDLData->screen, SDLData->eti, gracz->px, gracz->py + LEVEL_HEIGHT / 2 - ENEMY_1_VERTICAL_SIZE / 2);
        SetLevel(SDLData, gracz, ArrayOfBullets, ArrayOfPlayerBullets, gameData, enemy, colors, HP);
        ShootMissiles1(ArrayOfBullets, SDLData, gameData, gracz);
    }
    if (gameData->level == 2)
    {
        DrawSurface(SDLData->screen, SDLData->background2, gracz->px, gracz->py);
        DrawSurface(SDLData->screen, SDLData->enemy2, gracz->px, gracz->py + LEVEL_HEIGHT / 2 - ENEMY_2_VERTICAL_SIZE / 2);
        ShootMissiles2(ArrayOfBullets, SDLData, gameData, gracz);
        SetLevel(SDLData, gracz, ArrayOfBullets, ArrayOfPlayerBullets, gameData, enemy, colors, HP);
    }
    if (gameData->level == 3)
    {
        DrawSurface(SDLData->screen, SDLData->background3, gracz->px, gracz->py);
        if (gameData->intWorldTime % 3 == 0)
            DrawSurface(SDLData->screen, SDLData->enemy3B, gracz->px + enemy->px, gracz->py + LEVEL_HEIGHT / 2 - ENEMY_3_VERTICAL_SIZE / 2);
        if (gameData->intWorldTime % 3 == 1)
            DrawSurface(SDLData->screen, SDLData->enemy3, gracz->px + enemy->px, gracz->py + LEVEL_HEIGHT / 2 - ENEMY_3_VERTICAL_SIZE / 2);
        if (gameData->intWorldTime % 3 == 2)
            DrawSurface(SDLData->screen, SDLData->enemy3A, gracz->px + enemy->px, gracz->py + LEVEL_HEIGHT / 2 - ENEMY_3_VERTICAL_SIZE / 2);
        ShootMissiles3(ArrayOfBullets, SDLData, gameData, gracz, enemy);
        SetLevel(SDLData, gracz, ArrayOfBullets, ArrayOfPlayerBullets, gameData, enemy, colors, HP);
        MoveEnemy(enemy, gameData);
        for (int i = 0; i < SHAPE_TYPES; i++)
        {
            if (shape[i].called == 1 && shape[i].shapeTime <= 0)
                shape[i].called = 0;
            if (shape[i].called == 1 && shape[i].shapeTime > 0)
            {
                if (i == 0)
                    DrawSurface(SDLData->screen, SDLData->shape1, gracz->px - shape[i].px, gracz->py - shape[i].py);
                if (i == 1)
                    DrawSurface(SDLData->screen, SDLData->shape2, gracz->px - shape[i].px, gracz->py - shape[i].py);
            }
        }
    }
    if (gameData->level == -1)
    {
        PrintMenu(gameData, SDLData, colors);
        gameData->worldTime = 0;
        gameData->delta = 0;
    }
    if (gameData->playerHP <= 0)
        gameData->level = 5;
    if (gameData->enemyHP == 0)
    {
        if (gameData->level != 3)
        {
            gameData->level++;
            PrintMenu(gameData, SDLData, colors);
            NewGame(gameData, ArrayOfBullets, gracz, camera, enemy, HP, shape);
        }
        else if (gameData->level == 3)
        {
            gameData->enemyHP = ENEMY_HP;
            gameData->level = 4;
        }
    }
    if (gameData->level == 5)
    {
        PrintMenu(gameData, SDLData, colors);
        sprintf(gameData->text, "YOU LOST");
        DrawString(SDLData, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4, gameData->text);
    }
    if (gameData->level == 4)
    {
        PrintMenu(gameData, SDLData, colors);
        sprintf(gameData->text, "YOU WON");
        DrawString(SDLData, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4, gameData->text);
    }
}

void CreateHP(Health* HP, GameVariables* gameData)
{
    if (gameData->HPdelay <= 0 && HP->called == 0 && gameData->intWorldTime % 5 == 1)
    {
        HP->px = rand() % (1000) - SCREEN_WIDTH / 2;
        HP->py = rand() % (1000) - LEVEL_HEIGHT / 3;
        gameData->HPdelay = 5.0;
        HP->called = 1;
    }
}

void CreateShape(Shape shape[SHAPE_TYPES], GameVariables* gameData)
{
    for (int i = 0; i < SHAPE_TYPES; i++)
    {
        if (shape[i].shapeDelay <= 0 && shape[i].called == 0)
        {
            if (gameData->intWorldTime % 8 == 1 && i == 0)
            {
                shape[i].px = rand() % (1000) - SCREEN_WIDTH / 2;
                shape[i].py = rand() % (1000) - LEVEL_HEIGHT / 3;
                shape[i].shapeDelay = 5.0;
                shape[i].called = 1;
                shape[i].shapeTime = 4.0;
            }
            if (gameData->intWorldTime % 8 == 5 && i == 1)
            {
                shape[i].px = rand() % (1000) - SCREEN_WIDTH / 2;
                shape[i].py = rand() % (1000) - LEVEL_HEIGHT / 3;
                shape[i].shapeDelay = 5.0;
                shape[i].called = 1;
                shape[i].shapeTime = 4.0;
            }
        }
    }
}

void CheckHP_Player(Health* HP, GameVariables* gameData, Player* gracz)
{
    if (HP->px + SCREEN_WIDTH / 2 > gracz->px - 50 && HP->px + SCREEN_WIDTH / 2 < gracz->px + 50 && HP->called == 1)
    {
        if (HP->py + SCREEN_HEIGHT / 2 > gracz->py - 70 && HP->py + SCREEN_HEIGHT / 2 < gracz->py + 50)
        {
            gameData->playerHP += 1;
            HP->called = 0;
        }
    }
}

void CheckShape_Player(Shape shape[SHAPE_TYPES], GameVariables* gameData, Player* gracz)
{
    for (int i = 0; i < SHAPE_TYPES; i++)
    {
        if (gameData->indestructiblePlayer <= 0)
        {
            if (i == 0)
            {
                if (shape[i].px + SCREEN_WIDTH / 2 > gracz->px - SHAPE_1_SIZE / 2 && shape[i].px + SCREEN_WIDTH / 2 < gracz->px + SHAPE_1_SIZE / 2 && shape[i].called == 1)
                {
                    if (shape[i].py + SCREEN_HEIGHT / 2 > gracz->py - SHAPE_1_SIZE / 2 && shape[i].py + SCREEN_HEIGHT / 2 < gracz->py + SHAPE_1_SIZE / 2)
                    {
                        gameData->playerHP -= 1;
                        gameData->indestructiblePlayer = INVISIBILITY_PLAYER / 2;
                    }
                }
            }
            if (i == 1)
            {
                if (shape[i].px + SCREEN_WIDTH / 2 > gracz->px - SHAPE_2_HORIZONTAL_SIZE / 2 && shape[i].px + SCREEN_WIDTH / 2 < gracz->px + SHAPE_2_HORIZONTAL_SIZE / 2 && shape[i].called == 1)
                {
                    if (shape[i].py + SCREEN_HEIGHT / 2 > gracz->py - SHAPE_2_VERTICAL_SIZE / 2 && shape[i].py + SCREEN_HEIGHT / 2 < gracz->py + SHAPE_2_VERTICAL_SIZE / 2)
                    {
                        gameData->playerHP -= 1;
                        gameData->indestructiblePlayer = INVISIBILITY_PLAYER / 2;
                    }
                }
            }
        }
    }
}

void MoveUp(Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], GameVariables* gameData, Camera* camera, Player* gracz)
{
    if (camera->y1 > 0)
    {
        for (int i = 0; i < gameData->playerBullets; i++)
        {
            ArrayOfPlayerBullets[i].py = ArrayOfPlayerBullets[i].py + 8;
        }
        gracz->py = gracz->py + 8;
        gracz->rel_py = gracz->rel_py - 8;
        gracz->y1 = gracz->y1 - 8;
        gracz->y2 = gracz->y2 - 8;
        camera->y1 = camera->y1 - 8;
        camera->y2 = camera->y2 - 8;
    }
    gameData->lastMove = TOP;
}

void MoveDown(Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], GameVariables* gameData, Camera* camera, Player* gracz)
{
    if (camera->y2 < LEVEL_HEIGHT) {
        for (int i = 0; i < gameData->playerBullets; i++)
        {
            ArrayOfPlayerBullets[i].py = ArrayOfPlayerBullets[i].py - 8;
        }
        gracz->py = gracz->py - 8;
        gracz->rel_py = gracz->rel_py + 8;
        gracz->y1 = gracz->y1 + 8;
        gracz->y2 = gracz->y2 + 8;
        camera->y1 = camera->y1 + 8;
        camera->y2 = camera->y2 + 8;
    }
    gameData->lastMove = BOTTOM;
}

void MoveLeft(Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], GameVariables* gameData, Camera* camera, Player* gracz)
{
    if (camera->x1 > 0) {
        for (int i = 0; i < gameData->playerBullets; i++)
        {
            ArrayOfPlayerBullets[i].px = ArrayOfPlayerBullets[i].px + 8;
        }
        camera->x1 = camera->x1 - 8;
        camera->x2 = camera->x2 - 8;
        gracz->px = gracz->px + 8;
        gracz->x1 = gracz->x1 + 8;
        gracz->x2 = gracz->x2 + 8;
    }
    gameData->lastMove = LEFT;
}

void MoveRight(Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], GameVariables* gameData, Camera* camera, Player* gracz)
{
    if (camera->x2 < LEVEL_WIDTH) {
        for (int i = 0; i < gameData->playerBullets; i++)
        {
            ArrayOfPlayerBullets[i].px = ArrayOfPlayerBullets[i].px - 8;
        }
        camera->x1 = camera->x1 + 8;
        camera->x2 = camera->x2 + 8;
        gracz->px = gracz->px - 8;
        gracz->x1 = gracz->x1 - 8;
        gracz->x2 = gracz->x2 - 8;
    }
    gameData->lastMove = RIGHT;
}

void PrintMenu(GameVariables* gameData, SDLVariables* SDLData, ColorSet* colors)
{
    DrawRectangle(SDLData, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, colors->czarny, colors->czarny);
    sprintf(gameData->text, "PRESS 1 TO RUN LEVEL 1");
    DrawString(SDLData, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4 + 20, gameData->text);
    sprintf(gameData->text, "PRESS 2 TO RUN LEVEL 2");
    DrawString(SDLData, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4 + 40, gameData->text);
    sprintf(gameData->text, "PRESS 3 TO RUN LEVEL 3");
    DrawString(SDLData, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4 + 60, gameData->text);
    sprintf(gameData->text, "PRESS ESC TO QUIT THE GAME");
    DrawString(SDLData, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4 + 80, gameData->text);
}

void CreateEnemyBullet(Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], int type, int id, int px, int py, int speed, int sizeVertical, int sizeHorizontal, int x, int y)
{
    ArrayOfBullets[type][id].sizeVertical = sizeVertical;
    ArrayOfBullets[type][id].sizeHorizontal = sizeHorizontal;
    ArrayOfBullets[type][id].x1 = x - sizeHorizontal / 2;
    ArrayOfBullets[type][id].x2 = x + sizeHorizontal / 2;
    ArrayOfBullets[type][id].y1 = y - sizeVertical / 2;
    ArrayOfBullets[type][id].y2 = y + sizeVertical / 2;
    ArrayOfBullets[type][id].id = id;
    ArrayOfBullets[type][id].px = px;
    ArrayOfBullets[type][id].py = py;
    ArrayOfBullets[type][id].speed = speed;
    ArrayOfBullets[type][id].type = type;
    ArrayOfBullets[type][id].move = 0;
    ArrayOfBullets[type][id].delay = 0.0;
}

void CreateenemyBullets(Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT])
{
    for (int j = 0; j < ENEMY_BULLETS_TYPES; j++)
    {
        for (int i = 0; i < ENEMY_BULLETS_AMOUNT; i++)
        {
            CreateEnemyBullet(ArrayOfBullets, j, i, 0, LEVEL_HEIGHT / 2 - ENEMY_1_VERTICAL_SIZE / 2, BULLET_SPEED, BULLET_VERTICAL_SIZE, BULLET_HORIZONTAL_SIZE, SCREEN_WIDTH / 2, LEVEL_HEIGHT / 2 - ENEMY_1_VERTICAL_SIZE / 2);
        }
    }
}

void MoveEnemy(Enemy* enemy, GameVariables* gameData)
{
    enemy->px = enemy->px + cos(gameData->worldTime) * 3;
    enemy->x1 = enemy->x1 - cos(gameData->worldTime) * 3;
    enemy->x2 = enemy->x2 - cos(gameData->worldTime) * 3;
}

void SetLevel(SDLVariables* SDLData, Player* gracz, Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], GameVariables* gameData, Enemy* enemy, ColorSet* colors, Health* HP)
{
    if (gameData->lastMove == RIGHT)
    {
        if (gameData->intWorldTime % 2 == 0)
            DrawSurface(SDLData->screen, SDLData->champ1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        else if (gameData->intWorldTime % 2 == 1)
            DrawSurface(SDLData->screen, SDLData->champ2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
    if (gameData->lastMove == LEFT)
    {
        if (gameData->intWorldTime % 2 == 0)
            DrawSurface(SDLData->screen, SDLData->champ3, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        else if (gameData->intWorldTime % 2 == 1)
            DrawSurface(SDLData->screen, SDLData->champ4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
    if (gameData->lastMove == TOP)
    {
        if (gameData->intWorldTime % 2 == 0)
            DrawSurface(SDLData->screen, SDLData->champ6, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        else if (gameData->intWorldTime % 2 == 1)
            DrawSurface(SDLData->screen, SDLData->champ7, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
    if (gameData->lastMove == BOTTOM)
    {
        if (gameData->intWorldTime % 2 == 0)
            DrawSurface(SDLData->screen, SDLData->champ1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        else if (gameData->intWorldTime % 2 == 1)
            DrawSurface(SDLData->screen, SDLData->champ2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
    PlayerShooting(ArrayOfPlayerBullets, SDLData, gameData, gracz);
    DrawTopBar(SDLData, gameData, colors, ArrayOfBullets);
    if (HP->called == 1)
        DrawSurface(SDLData->screen, SDLData->HP, gracz->px - HP->px, gracz->py - HP->py);
    CheckCollisionEnemyBullet_Player(gameData, ArrayOfBullets, gracz);
    CheckCollisionPlayerBullet_enemy(gameData, ArrayOfPlayerBullets, enemy);
    Grade(gameData, SDLData);
}

void Grade(GameVariables* gameData, SDLVariables* SDLData)
{
    if (gameData->score < 100)
        DrawSurface(SDLData->screen, SDLData->D, SCREEN_WIDTH - 100, SCREEN_HEIGHT / 5);
    if (gameData->score >= 100 && gameData->score < 300)
        DrawSurface(SDLData->screen, SDLData->C, SCREEN_WIDTH - 100, SCREEN_HEIGHT / 5);
    if (gameData->score >= 300 && gameData->score < 500)
        DrawSurface(SDLData->screen, SDLData->B, SCREEN_WIDTH - 100, SCREEN_HEIGHT / 5);
    if (gameData->score >= 500)
        DrawSurface(SDLData->screen, SDLData->A, SCREEN_WIDTH - 100, SCREEN_HEIGHT / 2);

}

void ShootMissiles3(Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], SDLVariables* SDLData, GameVariables* gameData, Player* gracz, Enemy* enemy)
{
    for (int i = 0; i < ENEMY_BULLETS_AMOUNT; i++)
    {
        for (int j = 0; j < ENEMY_BULLETS_TYPES; j++)
        {
            if (ArrayOfBullets[j][i].delay <= 0)
            {
                if (gameData->stage == 0 && j < 9)
                {
                    if (gameData->intWorldTime % ENEMY_BULLETS_AMOUNT == i)
                    {
                        ArrayOfBullets[j][i].move = 1;
                    }
                }
                if (gameData->stage == 1 && j > 8)
                {
                    if (gameData->intWorldTime % ENEMY_BULLETS_AMOUNT == i)
                    {
                        ArrayOfBullets[j][i].move = 1;
                    }
                }
                if (ArrayOfBullets[j][i].move == 0)
                {
                    ArrayOfBullets[j][i].px = enemy->px;
                    ArrayOfBullets[j][i].x1 = (enemy->x1 + enemy->x2) / 2 - 25;
                    ArrayOfBullets[j][i].x2 = (enemy->x1 + enemy->x2) / 2 + 25;
                }
                if (ArrayOfBullets[j][i].move == 1)
                {
                    if (j == 0)
                    {
                        ArrayOfBullets[j][i].py -= 3;
                        ArrayOfBullets[j][i].y1 -= 3;
                        ArrayOfBullets[j][i].y2 -= 3;
                        ArrayOfBullets[j][i].x1 += (tan(gameData->worldTime / 2) + 1);
                        ArrayOfBullets[j][i].x2 += (tan(gameData->worldTime / 2) + 1);
                        ArrayOfBullets[j][i].px -= (tan(gameData->worldTime / 2) + 1);
                        DrawSurface(SDLData->screen, SDLData->missile3, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 1)
                    {
                        ArrayOfBullets[j][i].py -= 3;
                        ArrayOfBullets[j][i].y1 -= 3;
                        ArrayOfBullets[j][i].y2 -= 3;
                        ArrayOfBullets[j][i].x1 += tan(gameData->worldTime / 2);
                        ArrayOfBullets[j][i].x2 += tan(gameData->worldTime / 2);
                        ArrayOfBullets[j][i].px -= tan(gameData->worldTime / 2);
                        DrawSurface(SDLData->screen, SDLData->missile3, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 3)
                    {
                        ArrayOfBullets[j][i].py -= 3;
                        ArrayOfBullets[j][i].y1 -= 3;
                        ArrayOfBullets[j][i].y2 -= 3;
                        ArrayOfBullets[j][i].x1 -= (tan(gameData->worldTime / 2) + 1);
                        ArrayOfBullets[j][i].x2 -= (tan(gameData->worldTime / 2) + 1);
                        ArrayOfBullets[j][i].px += (tan(gameData->worldTime / 2) + 1);
                        DrawSurface(SDLData->screen, SDLData->missile3, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 4)
                    {
                        ArrayOfBullets[j][i].py -= 3;
                        ArrayOfBullets[j][i].y1 -= 3;
                        ArrayOfBullets[j][i].y2 -= 3;
                        ArrayOfBullets[j][i].x1 += (tan(gameData->worldTime / 2) + 2);
                        ArrayOfBullets[j][i].x2 += (tan(gameData->worldTime / 2) + 2);
                        ArrayOfBullets[j][i].px -= (tan(gameData->worldTime / 2) + 2);
                        DrawSurface(SDLData->screen, SDLData->missile3, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 8)
                    {
                        ArrayOfBullets[j][i].py -= 3;
                        ArrayOfBullets[j][i].y1 -= 3;
                        ArrayOfBullets[j][i].y2 -= 3;
                        ArrayOfBullets[j][i].x1 -= (tan(gameData->worldTime / 2) + 2);
                        ArrayOfBullets[j][i].x2 -= (tan(gameData->worldTime / 2) + 2);
                        ArrayOfBullets[j][i].px += (tan(gameData->worldTime / 2) + 2);
                        DrawSurface(SDLData->screen, SDLData->missile3, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 9)
                    {
                        ArrayOfBullets[j][i].py -= 4;
                        ArrayOfBullets[j][i].y1 -= 4;
                        ArrayOfBullets[j][i].y2 -= 4;
                        DrawSurface(SDLData->screen, SDLData->missile3, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 11)
                    {
                        ArrayOfBullets[j][i].py -= 4;
                        ArrayOfBullets[j][i].y1 -= 4;
                        ArrayOfBullets[j][i].y2 -= 4;
                        ArrayOfBullets[j][i].x1 += 2;
                        ArrayOfBullets[j][i].x2 += 2;
                        ArrayOfBullets[j][i].px -= 2;
                        DrawSurface(SDLData->screen, SDLData->missile3, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 12)
                    {
                        ArrayOfBullets[j][i].py -= 4;
                        ArrayOfBullets[j][i].y1 -= 4;
                        ArrayOfBullets[j][i].y2 -= 4;
                        ArrayOfBullets[j][i].x1 += 1;
                        ArrayOfBullets[j][i].x2 += 1;
                        ArrayOfBullets[j][i].px -= 1;
                        DrawSurface(SDLData->screen, SDLData->missile3, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 13)
                    {
                        ArrayOfBullets[j][i].py -= 4;
                        ArrayOfBullets[j][i].y1 -= 4;
                        ArrayOfBullets[j][i].y2 -= 4;
                        ArrayOfBullets[j][i].x1 -= 2;
                        ArrayOfBullets[j][i].x2 -= 2;
                        ArrayOfBullets[j][i].px += 2;
                        DrawSurface(SDLData->screen, SDLData->missile3, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 14)
                    {
                        ArrayOfBullets[j][i].py -= 4;
                        ArrayOfBullets[j][i].y1 -= 4;
                        ArrayOfBullets[j][i].y2 -= 4;
                        ArrayOfBullets[j][i].x1 -= 1;
                        ArrayOfBullets[j][i].x2 -= 1;
                        ArrayOfBullets[j][i].px += 1;
                        DrawSurface(SDLData->screen, SDLData->missile3, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (ArrayOfBullets[j][i].py <= -LEVEL_HEIGHT / 2)
                    {
                        MoveMissileToStartPos3(ArrayOfBullets, j, i, enemy);
                    }

                }
            }
        }
    }
}

void ShootMissiles2(Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], SDLVariables* SDLData, GameVariables* gameData, Player* gracz)
{
    for (int i = 0; i < ENEMY_BULLETS_AMOUNT; i++)
    {
        for (int j = 0; j < ENEMY_BULLETS_TYPES; j++)
        {
            if (ArrayOfBullets[j][i].delay <= 0)
            {
                if (gameData->stage == 0 && j < 9)
                {
                    if (gameData->intWorldTime % ENEMY_BULLETS_AMOUNT == i * 2)
                        ArrayOfBullets[j][i].move = 1;
                }
                if (gameData->stage == 1 && j > 8)
                {
                    if (gameData->intWorldTime % ENEMY_BULLETS_AMOUNT == i * 2)
                        ArrayOfBullets[j][i].move = 1;
                }
                if (ArrayOfBullets[j][i].move == 1)
                {
                    if (j == 0)
                    {
                        ArrayOfBullets[j][i].py -= 2;
                        ArrayOfBullets[j][i].y1 -= 2;
                        ArrayOfBullets[j][i].y2 -= 2;
                        ArrayOfBullets[j][i].x1 += (sin(gameData->worldTime) * 2 + 1);
                        ArrayOfBullets[j][i].x2 += (sin(gameData->worldTime) * 2 + 1);
                        ArrayOfBullets[j][i].px -= (sin(gameData->worldTime) * 2 + 1);
                        DrawSurface(SDLData->screen, SDLData->missile2, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 1)
                    {
                        ArrayOfBullets[j][i].py -= 3;
                        ArrayOfBullets[j][i].y1 -= 3;
                        ArrayOfBullets[j][i].y2 -= 3;
                        ArrayOfBullets[j][i].x1 += (sin(gameData->worldTime) * 2);
                        ArrayOfBullets[j][i].x2 += (sin(gameData->worldTime) * 2);
                        ArrayOfBullets[j][i].px -= (sin(gameData->worldTime) * 2);
                        DrawSurface(SDLData->screen, SDLData->missile2, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 3)
                    {
                        ArrayOfBullets[j][i].py -= 2;
                        ArrayOfBullets[j][i].y1 -= 2;
                        ArrayOfBullets[j][i].y2 -= 2;
                        ArrayOfBullets[j][i].x1 -= (sin(gameData->worldTime) * 2 + 1);
                        ArrayOfBullets[j][i].x2 -= (sin(gameData->worldTime) * 2 + 1);
                        ArrayOfBullets[j][i].px += (sin(gameData->worldTime) * 2 + 1);
                        DrawSurface(SDLData->screen, SDLData->missile2, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 4)
                    {
                        ArrayOfBullets[j][i].py -= 3;
                        ArrayOfBullets[j][i].y1 -= 3;
                        ArrayOfBullets[j][i].y2 -= 3;
                        ArrayOfBullets[j][i].x1 += (sin(gameData->worldTime) * 2 + 2);
                        ArrayOfBullets[j][i].x2 += (sin(gameData->worldTime) * 2 + 2);
                        ArrayOfBullets[j][i].px -= (sin(gameData->worldTime) * 2 + 2);
                        DrawSurface(SDLData->screen, SDLData->missile2, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 8)
                    {
                        ArrayOfBullets[j][i].py -= 3;
                        ArrayOfBullets[j][i].y1 -= 3;
                        ArrayOfBullets[j][i].y2 -= 3;
                        ArrayOfBullets[j][i].x1 -= (sin(gameData->worldTime) * 2 + 2);
                        ArrayOfBullets[j][i].x2 -= (sin(gameData->worldTime) * 2 + 2);
                        ArrayOfBullets[j][i].px += (sin(gameData->worldTime) * 2 + 2);
                        DrawSurface(SDLData->screen, SDLData->missile2, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 9)
                    {
                        ArrayOfBullets[j][i].py -= 4;
                        ArrayOfBullets[j][i].y1 -= 4;
                        ArrayOfBullets[j][i].y2 -= 4;
                        DrawSurface(SDLData->screen, SDLData->missile2, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 11)
                    {
                        ArrayOfBullets[j][i].py -= 4;
                        ArrayOfBullets[j][i].y1 -= 4;
                        ArrayOfBullets[j][i].y2 -= 4;
                        ArrayOfBullets[j][i].x1 += 2;
                        ArrayOfBullets[j][i].x2 += 2;
                        ArrayOfBullets[j][i].px -= 2;
                        DrawSurface(SDLData->screen, SDLData->missile2, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 12)
                    {
                        ArrayOfBullets[j][i].py -= 4;
                        ArrayOfBullets[j][i].y1 -= 4;
                        ArrayOfBullets[j][i].y2 -= 4;
                        ArrayOfBullets[j][i].x1 += 1;
                        ArrayOfBullets[j][i].x2 += 1;
                        ArrayOfBullets[j][i].px -= 1;
                        DrawSurface(SDLData->screen, SDLData->missile2, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 13)
                    {
                        ArrayOfBullets[j][i].py -= 4;
                        ArrayOfBullets[j][i].y1 -= 4;
                        ArrayOfBullets[j][i].y2 -= 4;
                        ArrayOfBullets[j][i].x1 -= 2;
                        ArrayOfBullets[j][i].x2 -= 2;
                        ArrayOfBullets[j][i].px += 2;
                        DrawSurface(SDLData->screen, SDLData->missile2, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (j == 14)
                    {
                        ArrayOfBullets[j][i].py -= 4;
                        ArrayOfBullets[j][i].y1 -= 4;
                        ArrayOfBullets[j][i].y2 -= 4;
                        ArrayOfBullets[j][i].x1 -= 1;
                        ArrayOfBullets[j][i].x2 -= 1;
                        ArrayOfBullets[j][i].px += 1;
                        DrawSurface(SDLData->screen, SDLData->missile2, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                    if (ArrayOfBullets[j][i].py <= -LEVEL_HEIGHT / 2)
                    {
                        MoveMissileToStartPos(ArrayOfBullets, j, i);
                    }

                }
            }
        }
    }
}

void ShootMissiles1(Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], SDLVariables* SDLData, GameVariables* gameData, Player* gracz)
{
    for (int i = 0; i < ENEMY_BULLETS_AMOUNT; i++)
    {
        for (int j = 0; j < ENEMY_BULLETS_TYPES; j++)
        {
            if (ArrayOfBullets[j][i].delay <= 0)
            {
                if (i % 2 == 0 && j < 10)
                {
                    if (gameData->intWorldTime % ENEMY_BULLETS_AMOUNT == i * 2)
                        ArrayOfBullets[j][i].move = 1;
                    if (ArrayOfBullets[j][i].move == 1)
                    {
                        if (j == 0)
                        {
                            ArrayOfBullets[j][i].py -= 2;
                            ArrayOfBullets[j][i].y1 -= 2;
                            ArrayOfBullets[j][i].y2 -= 2;
                            ArrayOfBullets[j][i].x1 += 4;
                            ArrayOfBullets[j][i].x2 += 4;
                            ArrayOfBullets[j][i].px -= 4;
                            DrawSurface(SDLData->screen, SDLData->missile, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                        }
                        if (j == 1)
                        {
                            ArrayOfBullets[j][i].py -= 2;
                            ArrayOfBullets[j][i].y1 -= 2;
                            ArrayOfBullets[j][i].y2 -= 2;
                            ArrayOfBullets[j][i].x1 -= 4;
                            ArrayOfBullets[j][i].x2 -= 4;
                            ArrayOfBullets[j][i].px += 4;
                            DrawSurface(SDLData->screen, SDLData->missile, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                        }
                        if (j == 2)
                        {
                            ArrayOfBullets[j][i].py -= 4;
                            ArrayOfBullets[j][i].y1 -= 4;
                            ArrayOfBullets[j][i].y2 -= 4;
                            DrawSurface(SDLData->screen, SDLData->missile, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                        }
                        if (j == 3)
                        {
                            ArrayOfBullets[j][i].py -= 4;
                            ArrayOfBullets[j][i].y1 -= 4;
                            ArrayOfBullets[j][i].y2 -= 4;
                            ArrayOfBullets[j][i].x1 -= 2;
                            ArrayOfBullets[j][i].x2 -= 2;
                            ArrayOfBullets[j][i].px += 2;
                            DrawSurface(SDLData->screen, SDLData->missile, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                        }
                        if (j == 4)
                        {
                            ArrayOfBullets[j][i].py -= 4;
                            ArrayOfBullets[j][i].y1 -= 4;
                            ArrayOfBullets[j][i].y2 -= 4;
                            ArrayOfBullets[j][i].x1 += 2;
                            ArrayOfBullets[j][i].x2 += 2;
                            ArrayOfBullets[j][i].px -= 2;
                            DrawSurface(SDLData->screen, SDLData->missile, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                        }
                        if (ArrayOfBullets[j][i].py <= -LEVEL_HEIGHT / 2)
                        {
                            MoveMissileToStartPos(ArrayOfBullets, j, i);
                        }
                    }
                }
                if (i % 2 == 1 && j != 10)
                {
                    if (gameData->intWorldTime % ENEMY_BULLETS_AMOUNT == i * 2)
                        ArrayOfBullets[j][i].move = 1;
                    if (ArrayOfBullets[j][i].move == 1)
                    {
                        if (j == 5)
                        {
                            ArrayOfBullets[j][i].py -= 4;
                            ArrayOfBullets[j][i].y1 -= 4;
                            ArrayOfBullets[j][i].y2 -= 4;
                            ArrayOfBullets[j][i].x1 += 4;
                            ArrayOfBullets[j][i].x2 += 4;
                            ArrayOfBullets[j][i].px -= 4;
                            DrawSurface(SDLData->screen, SDLData->explosion, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                        }
                        if (j == 6)
                        {
                            ArrayOfBullets[j][i].py -= 4;
                            ArrayOfBullets[j][i].y1 -= 4;
                            ArrayOfBullets[j][i].y2 -= 4;
                            ArrayOfBullets[j][i].x1 -= 4;
                            ArrayOfBullets[j][i].x2 -= 4;
                            ArrayOfBullets[j][i].px += 4;
                            DrawSurface(SDLData->screen, SDLData->explosion, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                        }
                        if (j == 7)
                        {
                            for (int i = 0; i < ENEMY_BULLETS_AMOUNT; i++)
                            {
                                int k = 10;
                                ArrayOfBullets[j][i].py -= 6;
                                ArrayOfBullets[j][i].y1 -= 6;
                                ArrayOfBullets[j][i].y2 -= 6;
                                DrawSurface(SDLData->screen, SDLData->missile, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                                if (ArrayOfBullets[j][i].py > 0 && ArrayOfBullets[j][i].py < 10)
                                {
                                    ArrayOfBullets[k][i].move = 1;
                                    ArrayOfBullets[k][i].px = 0.0;
                                    ArrayOfBullets[k][i].py = 0.0;
                                    ArrayOfBullets[k][i].y1 = SCREEN_HEIGHT / 2 + 5;
                                    ArrayOfBullets[k][i].y2 = SCREEN_HEIGHT / 2 - 5;
                                    ArrayOfBullets[k][i].x1 = SCREEN_WIDTH / 2 + 5;
                                    ArrayOfBullets[k][i].x2 = SCREEN_WIDTH / 2 + 5;
                                    MoveMissileToStartPos(ArrayOfBullets, j, i);
                                }
                            }
                        }
                        if (j == 8)
                        {
                            ArrayOfBullets[j][i].py -= 6;
                            ArrayOfBullets[j][i].y1 -= 6;
                            ArrayOfBullets[j][i].y2 -= 6;
                            ArrayOfBullets[j][i].x1 -= 2;
                            ArrayOfBullets[j][i].x2 -= 2;
                            ArrayOfBullets[j][i].px += 2;
                            DrawSurface(SDLData->screen, SDLData->missile, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);

                        }
                        if (j == 9)
                        {
                            ArrayOfBullets[j][i].py -= 6;
                            ArrayOfBullets[j][i].y1 -= 6;
                            ArrayOfBullets[j][i].y2 -= 6;
                            ArrayOfBullets[j][i].x1 += 2;
                            ArrayOfBullets[j][i].x2 += 2;
                            ArrayOfBullets[j][i].px -= 2;
                            DrawSurface(SDLData->screen, SDLData->missile, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                        }
                        if (j == 11)
                        {
                            ArrayOfBullets[j][i].py -= 6;
                            ArrayOfBullets[j][i].y1 -= 6;
                            ArrayOfBullets[j][i].y2 -= 6;
                            DrawSurface(SDLData->screen, SDLData->missile, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                        }
                        if (ArrayOfBullets[j][i].py <= -LEVEL_HEIGHT / 2)
                        {
                            MoveMissileToStartPos(ArrayOfBullets, j, i);
                        }
                    }
                }
                if (j == 10)
                {
                    if (ArrayOfBullets[j][i].move == 1)
                    {
                        ArrayOfBullets[j][i].py += (cos(6.28 / 15 * (1 + i))) * 4;
                        ArrayOfBullets[j][i].px += (sin(6.28 / 15 * (1 + i))) * 4;
                        ArrayOfBullets[j][i].y1 -= (cos(6.28 / 15 * (1 + i)));
                        ArrayOfBullets[j][i].y2 -= (cos(6.28 / 15 * (1 + i)));
                        ArrayOfBullets[j][i].x1 -= (sin(6.28 / 15 * (1 + i)));
                        ArrayOfBullets[j][i].x2 -= (sin(6.28 / 15 * (1 + i)));
                        DrawSurface(SDLData->screen, SDLData->missile, ArrayOfBullets[j][i].px + gracz->px, ArrayOfBullets[j][i].py + gracz->py);
                    }
                }
            }
        }
    }
}

void MoveMissileToStartPos(Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], int type, int id)
{
    ArrayOfBullets[type][id].py = LEVEL_HEIGHT / 2 - ENEMY_1_VERTICAL_SIZE / 2;
    ArrayOfBullets[type][id].y1 = LEVEL_HEIGHT / 2 - ENEMY_1_VERTICAL_SIZE / 2 - BULLET_VERTICAL_SIZE;
    ArrayOfBullets[type][id].y2 = LEVEL_HEIGHT / 2 - ENEMY_1_VERTICAL_SIZE / 2 + BULLET_VERTICAL_SIZE;
    ArrayOfBullets[type][id].move = 0;
    ArrayOfBullets[type][id].px = 0;
    ArrayOfBullets[type][id].x1 = SCREEN_WIDTH / 2;
    ArrayOfBullets[type][id].x2 = SCREEN_WIDTH / 2;
    ArrayOfBullets[type][id].delay = 1.0;
}

void MoveMissileToStartPos3(Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], int type, int id, Enemy* enemy)
{
    ArrayOfBullets[type][id].py = LEVEL_HEIGHT / 2 - ENEMY_3_VERTICAL_SIZE / 2;
    ArrayOfBullets[type][id].y1 = LEVEL_HEIGHT / 2 - ENEMY_3_VERTICAL_SIZE / 2 - BULLET_VERTICAL_SIZE;
    ArrayOfBullets[type][id].y2 = LEVEL_HEIGHT / 2 - ENEMY_3_VERTICAL_SIZE / 2 + BULLET_VERTICAL_SIZE;
    ArrayOfBullets[type][id].move = 0;
    ArrayOfBullets[type][id].px = enemy->px;
    ArrayOfBullets[type][id].x1 = SCREEN_WIDTH / 2 + enemy->x1 - ENEMY_3_HORIZONTAL_SIZE / 2;
    ArrayOfBullets[type][id].x2 = SCREEN_WIDTH / 2 + enemy->x1 + ENEMY_3_HORIZONTAL_SIZE / 2;
    ArrayOfBullets[type][id].delay = 1.0;
    ArrayOfBullets[type][id].move = 0;
}

void CheckCollisionEnemyBullet_Player(GameVariables* gameData, Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], Player* gracz)
{
    if (gameData->indestructiblePlayer <= 0.0)
    {
        for (int i = 0; i < ENEMY_BULLETS_AMOUNT; i++)
        {
            for (int j = 0; j < ENEMY_BULLETS_TYPES; j++)
            {
                if (ArrayOfBullets[j][i].move == 1 && j != 7 && j != 10)
                {
                    if (ArrayOfBullets[j][i].y1 >= gracz->y1 - SCREEN_HEIGHT / 2 && ArrayOfBullets[j][i].y1 <= gracz->y2 - SCREEN_HEIGHT / 2)
                    {
                        if (ArrayOfBullets[j][i].x1 >= gracz->x1 && ArrayOfBullets[j][i].x1 <= gracz->x2)
                        {
                            MoveMissileToStartPos(ArrayOfBullets, j, i);
                            gameData->playerHP--;
                            gameData->indestructiblePlayer = INVISIBILITY_PLAYER;
                        }
                        else if (ArrayOfBullets[j][i].x2 <= gracz->x2 && ArrayOfBullets[j][i].x2 >= gracz->x1)
                        {
                            MoveMissileToStartPos(ArrayOfBullets, j, i);
                            gameData->playerHP--;
                            gameData->indestructiblePlayer = INVISIBILITY_PLAYER;
                        }
                    }
                    else if (ArrayOfBullets[j][i].y2 >= gracz->y1 - SCREEN_HEIGHT / 2 && ArrayOfBullets[j][i].y2 <= gracz->y2 - SCREEN_HEIGHT / 2)
                    {
                        if (ArrayOfBullets[j][i].x1 >= gracz->x1 && ArrayOfBullets[j][i].x1 <= gracz->x2)
                        {
                            MoveMissileToStartPos(ArrayOfBullets, j, i);
                            gameData->playerHP--;
                            gameData->indestructiblePlayer = INVISIBILITY_PLAYER;
                        }
                        else if (ArrayOfBullets[j][i].x2 <= gracz->x2 && ArrayOfBullets[j][i].x2 >= gracz->x1)
                        {
                            MoveMissileToStartPos(ArrayOfBullets, j, i);
                            gameData->playerHP--;
                            gameData->indestructiblePlayer = INVISIBILITY_PLAYER;
                        }
                    }
                    if (j == 5 || j == 6)
                    {
                        if (gameData->indestructiblePlayer < 0)
                        {
                            if (gracz->x1 + 50 > ArrayOfBullets[j][i].x1 - EXPLOSION_SIZE / 2 && gracz->x1 + 50 < ArrayOfBullets[j][i].x1 + EXPLOSION_SIZE / 2)
                            {
                                if (gracz->y1 - SCREEN_HEIGHT / 2 > ArrayOfBullets[j][i].y1 - EXPLOSION_SIZE / 2 && gracz->y1 - SCREEN_HEIGHT / 2 < ArrayOfBullets[j][i].y1 + EXPLOSION_SIZE / 2)
                                {
                                    MoveMissileToStartPos(ArrayOfBullets, j, i);
                                    gameData->playerHP--;
                                    gameData->indestructiblePlayer = INVISIBILITY_PLAYER;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int CheckCollisionPlayerBullet_enemy(GameVariables* gameData, Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], Enemy* enemy)
{
    for (int i = 0; i < gameData->playerBullets; i++)
    {
        if (ArrayOfPlayerBullets[i].move == 0)
        {
            if (ArrayOfPlayerBullets[i].y1 >= enemy->y1 && ArrayOfPlayerBullets[i].y1 <= enemy->y2)
            {
                if (ArrayOfPlayerBullets[i].x1 >= enemy->x1 && ArrayOfPlayerBullets[i].x1 <= enemy->x2)
                {
                    if (gameData->bonusTime > 0)
                        gameData->bonusPoints++;
                    gameData->bonusTime = BONUS_TMIE;
                    gameData->enemyHP--;
                    ArrayOfPlayerBullets[i].move = 2;
                    return 1;
                }
                if (ArrayOfPlayerBullets[i].x2 <= enemy->x1 && ArrayOfPlayerBullets[i].x2 >= enemy->x2)
                {
                    if (gameData->bonusTime > 0)
                        gameData->bonusPoints++;
                    gameData->bonusTime = BONUS_TMIE;
                    gameData->enemyHP--;
                    ArrayOfPlayerBullets[i].move = 2;
                    return 1;
                }
            }
            else if (ArrayOfPlayerBullets[i].y2 >= enemy->y1 && ArrayOfPlayerBullets[i].y2 <= enemy->y2)
            {
                if (ArrayOfPlayerBullets[i].x1 >= enemy->x1 && ArrayOfPlayerBullets[i].x1 <= enemy->x2)
                {
                    if (gameData->bonusTime > 0)
                        gameData->bonusPoints++;
                    gameData->bonusTime = BONUS_TMIE;
                    gameData->enemyHP--;
                    ArrayOfPlayerBullets[i].move = 2;
                    return 1;
                }
                else if (ArrayOfPlayerBullets[i].x2 <= enemy->x1 && ArrayOfPlayerBullets[i].x2 >= enemy->x2)
                {
                    if (gameData->bonusTime > 0)
                        gameData->bonusPoints++;
                    gameData->bonusTime = BONUS_TMIE;
                    gameData->enemyHP--;
                    ArrayOfPlayerBullets[i].move = 2;
                    return 1;
                }
            }
        }
    }
}

void CreatePlayerBullet(Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], int type, int id, int px, int py, int speed, int sizeVertical, int sizeHorizontal, int x, int y)
{
    ArrayOfPlayerBullets[id].sizeVertical = sizeVertical;
    ArrayOfPlayerBullets[id].sizeHorizontal = sizeHorizontal;
    ArrayOfPlayerBullets[id].x1 = x - sizeHorizontal / 2;
    ArrayOfPlayerBullets[id].x2 = x + sizeHorizontal / 2;
    ArrayOfPlayerBullets[id].y1 = y - sizeVertical / 2;
    ArrayOfPlayerBullets[id].y2 = y + sizeVertical / 2;
    ArrayOfPlayerBullets[id].id = id;
    ArrayOfPlayerBullets[id].px = px;
    ArrayOfPlayerBullets[id].py = py;
    ArrayOfPlayerBullets[id].speed = speed;
    ArrayOfPlayerBullets[id].type = type;
    ArrayOfPlayerBullets[id].move = 0;
}

void PlayerShooting(Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], SDLVariables* SDLData, GameVariables* gameData, Player* gracz)
{
    for (int i = 0; i < gameData->playerBullets; i++)
    {
        if (ArrayOfPlayerBullets[i].move == 0)
        {
            ArrayOfPlayerBullets[i].py = ArrayOfPlayerBullets[i].py + PLAYER_UNIT_BULLET_SPEED;
            ArrayOfPlayerBullets[i].y1 = ArrayOfPlayerBullets[i].y1 + PLAYER_UNIT_BULLET_SPEED;
            ArrayOfPlayerBullets[i].y2 = ArrayOfPlayerBullets[i].y2 + PLAYER_UNIT_BULLET_SPEED;
            DrawSurface(SDLData->screen, SDLData->playermissile, ArrayOfPlayerBullets[i].px, ArrayOfPlayerBullets[i].py);
        }
    }
}

void MovePlayerMissilesToStartPos(Bullet ArrayOfPlayerBullets[MAX_PLAYER_BULLET_AMOUNT], int id)
{
    ArrayOfPlayerBullets[id].py = LEVEL_HEIGHT / 2 - ENEMY_1_VERTICAL_SIZE / 2;
    ArrayOfPlayerBullets[id].y1 = LEVEL_HEIGHT / 2 - ENEMY_1_VERTICAL_SIZE / 2 - BULLET_VERTICAL_SIZE;
    ArrayOfPlayerBullets[id].y2 = LEVEL_HEIGHT / 2 - ENEMY_1_VERTICAL_SIZE / 2 + BULLET_VERTICAL_SIZE;
    ArrayOfPlayerBullets[id].move = 0;
}

void SetValues(Player* gracz, GameVariables* gameData, Camera* camera, Enemy* enemy, Health* HP, Shape shape[SHAPE_TYPES])
{
    gracz->px = SCREEN_WIDTH / 2;
    gracz->py = SCREEN_HEIGHT / 2;
    gracz->rel_py = SCREEN_HEIGHT / 2;
    gracz->x1 = SCREEN_WIDTH / 2 - PLAYER_HORIZONTAL_SIZE / 2;
    gracz->x2 = SCREEN_WIDTH / 2 + PLAYER_HORIZONTAL_SIZE / 2;
    gracz->y1 = SCREEN_HEIGHT / 2 - PLAYER_VERTICAL_SIZE / 2;
    gracz->y2 = SCREEN_HEIGHT / 2 + PLAYER_VERTICAL_SIZE / 2;
    gameData->turn = 0;
    camera->x1 = LEVEL_WIDTH / 2 - SCREEN_WIDTH / 2;
    camera->x2 = LEVEL_WIDTH / 2 + SCREEN_WIDTH / 2;
    camera->y1 = LEVEL_HEIGHT / 2 - SCREEN_HEIGHT / 2;
    camera->y2 = LEVEL_HEIGHT / 2 + SCREEN_HEIGHT / 2;
    if (gameData->level == 1)
    {
        enemy->x1 = SCREEN_WIDTH / 2 - ENEMY_1_HORIZONTAL_SIZE / 2;
        enemy->x2 = SCREEN_WIDTH / 2 + ENEMY_1_HORIZONTAL_SIZE / 2;
        enemy->y1 = LEVEL_HEIGHT / 2 + SCREEN_HEIGHT / 2 - ENEMY_1_VERTICAL_SIZE / 2;
        enemy->y2 = LEVEL_HEIGHT / 2 + SCREEN_HEIGHT / 2;
    }
    if (gameData->level == 2)
    {
        enemy->x1 = SCREEN_WIDTH / 2 - ENEMY_2_HORIZONTAL_SIZE / 2;
        enemy->x2 = SCREEN_WIDTH / 2 + ENEMY_2_HORIZONTAL_SIZE / 2;
        enemy->y1 = LEVEL_HEIGHT / 2 + SCREEN_HEIGHT / 2 - ENEMY_2_VERTICAL_SIZE / 2;
        enemy->y2 = LEVEL_HEIGHT / 2 + SCREEN_HEIGHT / 2;
    }
    if (gameData->level == 3)
    {
        enemy->x1 = SCREEN_WIDTH / 2 - ENEMY_3_HORIZONTAL_SIZE / 2;
        enemy->x2 = SCREEN_WIDTH / 2 + ENEMY_3_HORIZONTAL_SIZE / 2;
        enemy->y1 = LEVEL_HEIGHT / 2 + SCREEN_HEIGHT / 2 - ENEMY_3_VERTICAL_SIZE / 2;
        enemy->y2 = LEVEL_HEIGHT / 2 + SCREEN_HEIGHT / 2;
    }
    gameData->t1 = SDL_GetTicks();
    gameData->frames = 0;
    gameData->fpsTimer = 0;
    gameData->fps = 0;
    gameData->quit = 0;
    gameData->worldTime = 0;
    gameData->distance = 0;
    gameData->indestructiblePlayer = 0.0;
    gameData->enemyPoints = 0;
    gameData->playerPoints = 0;
    gameData->explosionTime1 = 0.0;
    gameData->explosionTime2 = 0.0;
    gameData->explosion1X = 0.0;
    gameData->explosion2X = 0.0;
    gameData->explosion1Y = 0.0;
    gameData->explosion2Y = 0.0;
    gameData->playerBullets = 0;
    gameData->stage = 1;
    gameData->delay = 0.0;
    enemy->px = 0;
    gameData->enemyHP = ENEMY_HP;
    gameData->playerHP = PLAYER_HP;
    gameData->shootingDelay = 0.0;
    gameData->bonusTime = 0;
    gameData->bonusPoints = 0;
    gameData->lastMove = BOTTOM;
    gameData->HPdelay = 0;
    HP->called = 0;
    for (int i = 0; i < SHAPE_TYPES; i++)
    {
        shape[i].called = 0;
        shape[i].shapeTime = 0;
    }
}

void ChangeVarialbes(GameVariables* gameData, Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], Shape shape[SHAPE_TYPES])
{
    if (gameData->turn == 0) {
        CreateenemyBullets(ArrayOfBullets);
    }
    gameData->t2 = SDL_GetTicks();
    gameData->delta = (gameData->t2 - gameData->t1) * 0.001;
    gameData->t1 = gameData->t2;
    gameData->worldTime += gameData->delta;
    gameData->indestructiblePlayer -= gameData->delta;
    gameData->explosionTime1 -= gameData->delta;
    gameData->explosionTime2 -= gameData->delta;
    gameData->delay -= gameData->delta;
    for (int j = 0; j < ENEMY_BULLETS_TYPES; j++)
    {
        for (int i = 0; i < ENEMY_BULLETS_AMOUNT; i++)
        {
            if (ArrayOfBullets[j][i].delay > 0)
                ArrayOfBullets[j][i].delay -= gameData->delta;
        }
    }
    gameData->intWorldTime = gameData->worldTime;
    if (gameData->intWorldTime % 10 == 0 && gameData->delay <= 0)
    {
        if (gameData->stage == 0)
            gameData->stage = 1;
        else if (gameData->stage == 1)
            gameData->stage = 0;
        gameData->delay = 2.0;
    }
    gameData->score = (gameData->playerHP * 100) - (gameData->enemyHP * 50) + (gameData->bonusPoints * 20);
    gameData->shootingDelay -= gameData->delta;
    gameData->bonusTime -= gameData->delta;
    gameData->HPdelay -= gameData->delta;
    for (int i = 0; i < SHAPE_TYPES; i++)
    {
        shape[i].shapeDelay -= gameData->delta;
        shape[i].shapeTime -= gameData->delta;
    }
}

int PrepareSDLs(GameVariables* gameData, SDLVariables* SDLData)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }
    gameData->rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &SDLData->window, &SDLData->renderer);
    if (gameData->rc != 0) {
        SDL_Quit();
        printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
        return 1;
    };
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(SDLData->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(SDLData->renderer, 0, 0, 0, 255);

    SDL_SetWindowTitle(SDLData->window, "BULLET HELL");
    SDL_DestroyRenderer(SDLData->renderer);
    SDLData->renderer = SDL_CreateRenderer(SDLData->window, 0, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    SDLData->screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDLData->scrtex = SDL_CreateTexture(SDLData->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void LoadBMP(SDLVariables* SDLData)
{
    SDLData->charset = SDL_LoadBMP("./cs8x8.bmp");
    if (SDLData->charset == NULL)
        ErrorBMP(SDLData, ". / cs8x8.bmp");
    SDL_SetColorKey(SDLData->charset, true, 0x000000);
    SDLData->eti = SDL_LoadBMP("./Bob.bmp");
    if (SDLData->eti == NULL)
        ErrorBMP(SDLData, "./Bob.bmp");
    SDLData->missile = SDL_LoadBMP("./fireball1.bmp");
    if (SDLData->missile == NULL)
        ErrorBMP(SDLData, "./fireball1.bmp");
    SDLData->player = SDL_LoadBMP("./champ.bmp");
    if (SDLData->player == NULL)
        ErrorBMP(SDLData, "./champ.bmp");
    SDLData->background = SDL_LoadBMP("./background1.bmp");
    if (SDLData->background == NULL)
        ErrorBMP(SDLData, "./background1.bmp");
    SDLData->playermissile = SDL_LoadBMP("./plasmaball.bmp");
    if (SDLData->playermissile == NULL)
        ErrorBMP(SDLData, "./plasmaball.bmp");
    SDLData->explosion = SDL_LoadBMP("./wybuch.bmp");
    if (SDLData->explosion == NULL)
        ErrorBMP(SDLData, "./wybuch.bmp");
    SDLData->enemy2 = SDL_LoadBMP("./enemy2.bmp");
    if (SDLData->enemy2 == NULL)
        ErrorBMP(SDLData, "./enemy2.bmp");
    SDLData->background2 = SDL_LoadBMP("./background2.bmp");
    if (SDLData->background2 == NULL)
        ErrorBMP(SDLData, "./background2.bmp");
    SDLData->missile2 = SDL_LoadBMP("./fireball2.bmp");
    if (SDLData->missile2 == NULL)
        ErrorBMP(SDLData, "./fireball2.bmp");
    SDLData->enemy3 = SDL_LoadBMP("./enemy3.bmp");
    if (SDLData->enemy3 == NULL)
        ErrorBMP(SDLData, "./enemy3.bmp");
    SDLData->shapebullet = SDL_LoadBMP("./shapeBullet.bmp");
    if (SDLData->shapebullet == NULL)
        ErrorBMP(SDLData, "./shapeBullet.bmp");
    SDLData->missile3 = SDL_LoadBMP("./missile3.bmp");
    if (SDLData->missile3 == NULL)
        ErrorBMP(SDLData, "./missile3.bmp");
    SDLData->background3 = SDL_LoadBMP("./background3.bmp");
    if (SDLData->background3 == NULL)
        ErrorBMP(SDLData, "./background3.bmp");
    SDLData->champ1 = SDL_LoadBMP("./champ1.bmp");
    if (SDLData->champ1 == NULL)
        ErrorBMP(SDLData, "./champ1.bmp");
    SDLData->champ2 = SDL_LoadBMP("./champ2.bmp");
    if (SDLData->champ2 == NULL)
        ErrorBMP(SDLData, "./champ2.bmp");
    SDLData->champ3 = SDL_LoadBMP("./champ3.bmp");
    if (SDLData->champ3 == NULL)
        ErrorBMP(SDLData, "./champ3.bmp");
    SDLData->champ4 = SDL_LoadBMP("./champ4.bmp");
    if (SDLData->champ4 == NULL)
        ErrorBMP(SDLData, "./champ4.bmp");
    SDLData->champ6 = SDL_LoadBMP("./champ6.bmp");
    if (SDLData->champ6 == NULL)
        ErrorBMP(SDLData, "./champ6.bmp");
    SDLData->champ7 = SDL_LoadBMP("./champ7.bmp");
    if (SDLData->champ7 == NULL)
        ErrorBMP(SDLData, "./champ7.bmp");
    SDLData->HP = SDL_LoadBMP("./HP.bmp");
    if (SDLData->HP == NULL)
        ErrorBMP(SDLData, "./HP.bmp");
    SDLData->shape1 = SDL_LoadBMP("./shapeBullet.bmp");
    if (SDLData->shape1 == NULL)
        ErrorBMP(SDLData, "./shapeBullet.bmp");
    SDLData->shape2 = SDL_LoadBMP("./poison2.bmp");
    if (SDLData->shape2 == NULL)
        ErrorBMP(SDLData, "./B.bmp");
    SDLData->B = SDL_LoadBMP("./B.bmp");
    if (SDLData->B == NULL)
        ErrorBMP(SDLData, "./B.bmp");
    SDLData->A = SDL_LoadBMP("./A.bmp");
    if (SDLData->A == NULL)
        ErrorBMP(SDLData, "./A.bmp");
    SDLData->C = SDL_LoadBMP("./C.bmp");
    if (SDLData->C == NULL)
        ErrorBMP(SDLData, "./C.bmp");
    SDLData->D = SDL_LoadBMP("./D.bmp");
    if (SDLData->D == NULL)
        ErrorBMP(SDLData, "./D.bmp");
    SDLData->enemy3A = SDL_LoadBMP("./enemy3A.bmp");
    if (SDLData->enemy3A == NULL)
        ErrorBMP(SDLData, "./enemy3A.bmp");
    SDLData->enemy3B = SDL_LoadBMP("./enemy3B.bmp");
    if (SDLData->enemy3B == NULL)
        ErrorBMP(SDLData, "./enemy3B.bmp");
}

int     ErrorBMP(SDLVariables* SDLData, char* name)
{
    printf("SDL_LoadBMP(%s) error:% s\n", name, SDL_GetError());
    SDL_FreeSurface(SDLData->charset);
    SDL_FreeSurface(SDLData->screen);
    SDL_DestroyTexture(SDLData->scrtex);
    SDL_DestroyWindow(SDLData->window);
    SDL_DestroyRenderer(SDLData->renderer);
    SDL_Quit();
    exit(0);
}

void NewGame(GameVariables* gameData, Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT], Player* gracz, Camera* camera, Enemy* enemy, Health* HP, Shape shape[SHAPE_TYPES])
{
    for (int i = 0; i < ENEMY_BULLETS_AMOUNT; i++)
    {
        for (int j = 0; j < ENEMY_BULLETS_TYPES; j++)
        {
            ArrayOfBullets[j][i].py = LEVEL_HEIGHT / 2 - ENEMY_1_VERTICAL_SIZE / 2;
            ArrayOfBullets[j][i].px = 0;
            ArrayOfBullets[j][i].x1 = SCREEN_WIDTH / 2 - BULLET_HORIZONTAL_SIZE / 2;
            ArrayOfBullets[j][i].x2 = SCREEN_WIDTH / 2 + BULLET_HORIZONTAL_SIZE / 2;
            ArrayOfBullets[j][i].y1 = LEVEL_HEIGHT / 2 - ENEMY_1_VERTICAL_SIZE / 2;
            ArrayOfBullets[j][i].y2 = LEVEL_HEIGHT / 2 + ENEMY_1_VERTICAL_SIZE / 2;
            ArrayOfBullets[j][i].move = 0;
            MoveMissileToStartPos(ArrayOfBullets, j, i);
        }
        SetValues(gracz, gameData, camera, enemy, HP, shape);
    }
}

void SetColor(ColorSet* colors, SDLVariables* SDLData)
{
    colors->czarny = SDL_MapRGB(SDLData->screen->format, 0x00, 0x00, 0x00);
    colors->zielony = SDL_MapRGB(SDLData->screen->format, 0x00, 0xFF, 0x00);
    colors->czerwony = SDL_MapRGB(SDLData->screen->format, 0xFF, 0x00, 0x00);
    colors->niebieski = SDL_MapRGB(SDLData->screen->format, 0x11, 0x11, 0xCC);
}

void Fps(GameVariables* gameData)
{
    gameData->fpsTimer += gameData->delta;
    if (gameData->fpsTimer > 0.5) {
        gameData->fps = gameData->frames * 2;
        gameData->frames = 0;
        gameData->fpsTimer -= 0.5;
    }
}

void DrawRectangle(SDLVariables* SDLData, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor)
{
    int i;
    DrawLine(SDLData, x, y, k, 0, 1, outlineColor);
    DrawLine(SDLData, x + l - 1, y, k, 0, 1, outlineColor);
    DrawLine(SDLData, x, y, l, 1, 0, outlineColor);
    DrawLine(SDLData, x, y + k - 1, l, 1, 0, outlineColor);
    for (i = y + 1; i < y + k - 1; i++)
        DrawLine(SDLData, x + 1, i, l - 2, 1, 0, fillColor);
}

void DrawLine(SDLVariables* SDLData, int x, int y, int l, int dx, int dy, Uint32 color)
{
    for (int i = 0; i < l; i++)
    {
        DrawPixel(SDLData->screen, x, y, color);
        x += dx;
        y += dy;
    }
}

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
    *(Uint32*)p = color;
}

void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y)
{
    SDL_Rect dest;
    dest.x = x - sprite->w / 2;
    dest.y = y - sprite->h / 2;
    dest.w = sprite->w;
    dest.h = sprite->h;
    SDL_BlitSurface(sprite, NULL, screen, &dest);
}

void DrawString(SDLVariables* SDLData, int x, int y, const char* text)
{
    int px, py, c;
    SDL_Rect s, d;
    s.w = 8;
    s.h = 8;
    d.w = 8;
    d.h = 8;
    while (*text)
    {
        c = *text & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitSurface(SDLData->charset, &s, SDLData->screen, &d);
        x += 8;
        text++;
    }
}

void DrawTopBar(SDLVariables* SDLData, GameVariables* gameData, ColorSet* colors, Bullet ArrayOfBullets[][ENEMY_BULLETS_AMOUNT])
{
    DrawRectangle(SDLData, 4, 4, SCREEN_WIDTH - 8, 36, colors->czerwony, colors->czarny);
    sprintf(gameData->text, " TIME = %.1lf s  %.0lf frames / s enemyHP: %d playerHP: %d  score: %d", gameData->worldTime, gameData->fps, gameData->enemyHP, gameData->playerHP, gameData->score);
    DrawString(SDLData, SDLData->screen->w / 2 - strlen(gameData->text) * 8 / 2, 10, gameData->text);
    sprintf(gameData->text, "Esc - quit, \030 \031 \032 \033 - movement, 1, 2, 3 - pick stage , m - menu, n - new game");
    DrawString(SDLData, SDLData->screen->w / 2 - strlen(gameData->text) * 8 / 2, 26, gameData->text);
    DrawRectangle(SDLData, SCREEN_WIDTH - 300, SCREEN_HEIGHT - 100, gameData->playerHP * 20, 20, colors->czerwony, colors->czerwony);
}