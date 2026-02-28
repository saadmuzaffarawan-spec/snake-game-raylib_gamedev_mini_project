#include <raylib.h>
#include <raymath.h>
#include <cmath>
enum gamestate{
               Start,
               Playing,
               Over
};
int main() {
    gamestate currentstate = Start;
    const int screenwidth= 600;
    const int screenheight= 1024;
    InitWindow(screenwidth, screenheight, "My First Raylib Program"); 
    InitAudioDevice();
    SetTargetFPS(90);


    Vector2 playerDir = {0, -1};
    bool torchOn = false;

    float x =200, y =200, radius =20;
    float speed = 5;
    
    int score = 0;
    int health = 100;

    

    int killS;
    float coinx=500, coiny=500, coinr= 15;

    float enemyx=100, enemyy=800, enemyr=10, espeed=2;

    float bulletx, bullety, bulletr=5, bspeed=3;
    bool bullet;
    bullet = false;
    
    float obx=200, oby=300;
    Rectangle obstacle = {obx,oby, 80,30};
    while (!WindowShouldClose()) {  
    BeginDrawing();
    if(currentstate == Start){

        ClearBackground(WHITE);
        DrawText(TextFormat("EARTH ENCOUNTER"), 180, 400, 25, BLACK);
        DrawText(TextFormat("  Press Enter  "), 180, 450, 25, BLACK);

        if(IsKeyPressed(KEY_ENTER)){
            currentstate = Playing;
        }
    }
    else if(currentstate== Playing){ 
        ClearBackground(BLACK);
        float flickerTime = 0.0f;
flickerTime += GetFrameTime() * 10.0f;

        if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  { x -= speed; playerDir = {-1, 0}; }
if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) { x += speed; playerDir = { 1, 0}; }
if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    { y -= speed; playerDir = { 0,-1}; }
if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  { y += speed; playerDir = { 0, 1}; }

        if (IsKeyPressed(KEY_R)) {
        torchOn = !torchOn;
        }

        if (torchOn) {

    // BASE VALUES
    float baseLength = 220;
    float baseWidth  = 80;

    float lengthFlicker = sinf(flickerTime) * 15 + GetRandomValue(-5, 5);
    float widthFlicker  = cosf(flickerTime * 1.3f) * 10;
    float alphaFlicker  = 0.18f + (sinf(flickerTime * 2.0f) * 0.05f);

    float torchLength = baseLength + lengthFlicker;
    float torchWidth  = baseWidth  + widthFlicker;

    Vector2 origin = { x, y };

    Vector2 tip = {
        x + playerDir.x * torchLength,
        y + playerDir.y * torchLength
    };

    Vector2 perp = { -playerDir.y, playerDir.x };

    Vector2 left = {
        tip.x + perp.x * torchWidth,
        tip.y + perp.y * torchWidth
    };

    Vector2 right = {
        tip.x - perp.x * torchWidth,
        tip.y - perp.y * torchWidth
    };

    DrawTriangle(origin, left, right, Fade(ORANGE, alphaFlicker));
}




        if(IsKeyDown(KEY_LEFT_SHIFT))
        {
            speed = 8;
        }
        else{
            speed =5;
        }
        if(IsKeyDown(KEY_SPACE))
        {
            speed = 0;
        }

        if(x<20) {x=20;};
        if(y<20) {y=20;};
        if(y> (screenheight-20)){ y= (screenheight-20);};
        if(x> (screenwidth-20)){ x= (screenwidth-20);};

        if(CheckCollisionCircles(
            Vector2{x,y}, radius,
            Vector2{coinx, coiny}, coinr))
        {
        score+=10;
        health += 5;
        coinx = GetRandomValue(coinr, 600-coinr);
        coiny = GetRandomValue(coinr, 1024-coinr);
        }

        if(enemyx<(x)){ enemyx += espeed;}
        if(enemyx>(x)){ enemyx -= espeed;}
        if(enemyy>(y)){ enemyy -= espeed;}
        if(enemyy<(y)){ enemyy += espeed;}

        if(CheckCollisionCircles(
            Vector2 {enemyx,enemyy}, enemyr,
            Vector2 {x, y}, radius))
        {
        score -= 10;
        health -=10;
        enemyx = GetRandomValue(enemyr, 600 - enemyr);
        enemyy = GetRandomValue(enemyr, 1024 - enemyr);
        }

        if(IsKeyPressed(KEY_F) && !bullet)
        {
        bullet = true;
        bulletx = x+bspeed;
        bullety =y;

        }
        if(bullet){
         bullety += bspeed;
        }
        // if (CheckCollisionRecs({bulletx, bullety}, obstacle)) {
        // bullet = false;
        // }
        if(bullety>1024){bullet = false;}
        if(bullet && CheckCollisionCircles(
         Vector2{bulletx, bullety}, bulletr,
         Vector2{enemyx, enemyy}, enemyr
        ))
        {
        score += 30;
        bullet = false;
        enemyx = GetRandomValue(enemyx, 600-enemyx);
        enemyy = GetRandomValue(enemyy, 1024-enemyy);
        }

        DrawCircle(x, y, radius, WHITE);
        DrawRectangleRec(obstacle, GRAY);
        DrawCircle(coinx, coiny, coinr, GOLD);
        DrawCircle(enemyx, enemyy, enemyr, RED);
        if(bullet){ 
        DrawCircle(bulletx, bullety, bulletr, WHITE);
        }
        DrawText(TextFormat("Score:%d",score), 10,10, 30, YELLOW);
        DrawText(TextFormat("Speed:%.1f",speed), 10,970, 30, WHITE);
        DrawText(TextFormat("Health:%.d",health), 400,970, 30, RED);
        if(speed>5){
        DrawText(TextFormat("Speed:%.1f",speed), 10,970, 30, RED);
        }
        DrawFPS(500,10);
        if(IsKeyPressed(KEY_E) || health<=0){
        currentstate = Over;
        }
        }

        else if(currentstate==Over){
        ClearBackground(YELLOW);
        DrawText(TextFormat("GAME OVER"), 190, 420, 30, BLACK);
        DrawText(TextFormat("  Score:%d",score), 190, 480, 30, BLACK);
        DrawText(TextFormat(" Press Enter to Restart "), 190, 520, 25, BLACK);

        if(IsKeyPressed(KEY_ENTER)){
            score=0;
            health=100;
            x=200, y=200;
            bullet=false;
            enemyx =GetRandomValue(enemyr, 600-enemyr);
            enemyy =GetRandomValue(enemyr, 1024-enemyr);
            
            currentstate = Start;
        }

        }
        EndDrawing();  
    }

    CloseWindow(); 
    CloseAudioDevice();
    return 0;
}