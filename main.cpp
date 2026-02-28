#include <raylib.h>
#include <raymath.h>

struct enemy{
    Vector2 enemyhead;
    Vector2 enemydir;
    int x[100];
    int y[100];
    int enemylength;
};

int main(){

    bool ate = false;
    int score = 0;

    int gridsize = 25;
    
    enemy Enemy;
    
    Enemy.enemylength = 1;
    Enemy.enemydir = {0, 1};
    Enemy.enemyhead = {600, 400};

    for(int i = 0; i < Enemy.enemylength; i++){
    Enemy.x[i] = Enemy.enemyhead.x;
    Enemy.y[i] = Enemy.enemyhead.y - i * gridsize;
    }

    Vector2 snake{ 200, 200};

    Vector2 direction = {1, 0};

    InitWindow(1280, 720, "SNAKE GAME");
    SetTargetFPS(144);

    float x = 230;
    float y = 430;

    Vector2 food{x, y};

    int mxlength= 100;
    int length = 3;
    int snakex[100];
    int snakey[100];

    for (int i = 0; i < length; i++) {
    snakex[i] = snake.x - i * gridsize;
    snakey[i] = snake.y;
    }

    float movedelay= 0.2f;
    float timer =0;

    while(!WindowShouldClose()){

    float dt = GetFrameTime();
    timer += dt;

    
    BeginDrawing();
    ClearBackground(WHITE);


    for(int x = 0; x<720; x+=gridsize){
        DrawLine(0,x, 1280, x, DARKBROWN);
    }
    
    for(int y = 0; y<1280; y+=gridsize){
        DrawLine(y, 0, y, 720, DARKBROWN);
    }

    

    for(int i = 0; i<length; i++){
    DrawRectangle(snakex[i], snakey[i], gridsize, gridsize, GREEN);
    }

    for(int j = 0; j<Enemy.enemylength; j++){
    DrawRectangle(Enemy.x[j], Enemy.y[j], gridsize, gridsize, RED);
    }

    if(timer>=movedelay){

 
   for(int i= length-1; i> 0; i--){
        snakex[i] = snakex[i-1];
        snakey[i] = snakey[i-1];
    }


    snake.x += direction.x * gridsize;
    snake.y += direction.y * gridsize;

    snakex[0]= snake.x;
    snakey[0]= snake.y;

    for(int i = Enemy.enemylength - 1; i > 0; i--){
    Enemy.x[i] = Enemy.x[i-1];
    Enemy.y[i] = Enemy.y[i-1];
    }

    if(food.x > Enemy.enemyhead.x) {
        Enemy.enemydir = {1, 0};
    }
    else if(food.x < Enemy.enemyhead.x) {
        Enemy.enemydir = {-1, 0};
    }
    else if(food.y > Enemy.enemyhead.y) {
        Enemy.enemydir = {0, 1};
    }
    else if(food.y < Enemy.enemyhead.y) {
        Enemy.enemydir = {0, -1};
    }

    Enemy.enemyhead.x += Enemy.enemydir.x * gridsize;
    Enemy.enemyhead.y += Enemy.enemydir.y * gridsize;

    if(Enemy.enemyhead.x >= 1280) Enemy.enemyhead.x = 0;
    if(Enemy.enemyhead.x < 0) Enemy.enemyhead.x = 1280 - gridsize;

    if(Enemy.enemyhead.y >= 720) Enemy.enemyhead.y = 0;
    if(Enemy.enemyhead.y < 0) Enemy.enemyhead.y = 720 - gridsize; 

    Enemy.x[0] = Enemy.enemyhead.x;
    Enemy.y[0] = Enemy.enemyhead.y;

    timer = 0;
    }

    

    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
        direction = {-1, 0};
    }
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){
        direction = {1, 0};
    }
    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
        direction = {0, -1};
    }
    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        direction = {0, 1};
    }

    if(snakex[0] >= 1280) {
    snakex[0] = 0;
    }
    if(snakex[0] < 0){
     snakex[0] = 1280 - gridsize;
}
    if(snakey[0] >= 720){
     snakey[0] = 0;
    }
    if(snakey[0] < 0){ 
    snakey[0] = 720 - gridsize;
    }

    snake.x = snakex[0];
    snake.y = snakey[0];


    if(CheckCollisionCircleRec(
         food,10,
         Rectangle{float(snakex[0]), float(snakey[0]), float(gridsize), float(gridsize)}
         )
    ){
      ate = true;
    
    }


    if(CheckCollisionCircleRec(
    food, 10,
    Rectangle{float(Enemy.x[0]), float(Enemy.y[0]), float(gridsize), float(gridsize)}
    )){
    food.x = GetRandomValue(0, 1280/gridsize - 1) * gridsize;
    food.y = GetRandomValue(0, 720/gridsize - 1) * gridsize;

    if(Enemy.enemylength < mxlength)
        Enemy.enemylength++;
    }

    if(ate){
    food.x = GetRandomValue(0, 1280/gridsize - 1) * gridsize;
    food.y = GetRandomValue(0, 720/gridsize -1) *gridsize;
    if(length<mxlength){
    length ++;
    }
    score+= GetRandomValue(1,10);
    ate = false;
    }

    DrawCircle(food.x, food.y, 10, GOLD);


    DrawText(TextFormat("Score: %i", score), 20, 20, 30, BLACK);

    EndDrawing();
    }

    CloseWindow();
}