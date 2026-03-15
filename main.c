#include <raylib.h>
#include <stdlib.h>

void Grid(int cellSize)
{
    for (int x = 0; x <= GetScreenWidth(); x += cellSize)
    {
        DrawLine(x, 0, x, GetScreenHeight(), WHITE);
    }
    for (int y = 0; y <= GetScreenHeight(); y += cellSize)
    {
        DrawLine(0, y, GetScreenWidth(), y, WHITE);
    }
}

int main()
{

    SetConfigFlags(FLAG_FULLSCREEN_MODE);

    InitWindow(0, 0, "Horror Game ");
    SetTargetFPS(60);

    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    int cellSize = 32;

    int cols = (screen_width / cellSize) + 1;
    int rows = (screen_height / cellSize) + 1;


    int **worldMap = (int **)malloc(cols * sizeof(int *));
    for (int i = 0; i < cols; i++)
    {
        worldMap[i] = (int *)calloc(rows, sizeof(int));
    }

    Vector2 playerPos = {5.0f, 5.0f}; 
    float playerAngle = 0.0f;
    float moveSpeed = 0.5f;

    while (!WindowShouldClose())
    {
        int mouseX = GetMouseX() / cellSize;
        int mouseY = GetMouseY() / cellSize;

 

        if (IsKeyDown(KEY_A)) playerAngle -= 0.05f;
        if (IsKeyDown(KEY_D)) playerAngle += 0.05f;


        if (IsKeyDown(KEY_W))
        {
            float nextX = playerPos.x + cosf(playerAngle) ;
            float nextY = playerPos.y + sinf(playerAngle) ;
            
            
            if (nextX >= 0 && nextX < cols && nextY >= 0 && nextY < rows) {
                if (worldMap[(int)nextX][(int)nextY] == 0) {
                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }
            }
        }

    
        if (IsKeyDown(KEY_S))
        {
            float nextX = playerPos.x - cosf(playerAngle) * moveSpeed;
            float nextY = playerPos.y - sinf(playerAngle) * moveSpeed;
            
            if (nextX >= 0 && nextX < cols && nextY >= 0 && nextY < rows) {
                if (worldMap[(int)nextX][(int)nextY] == 0) {
                    playerPos.x = nextX;
                    playerPos.y = nextY;
                }
            }
        }

        if (mouseX >= 0 && mouseX < cols && mouseY >= 0 && mouseY < rows)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                worldMap[mouseX][mouseY] = 1;
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
                worldMap[mouseX][mouseY] = 0;
        }

        if (IsKeyDown(KEY_F11))
        {
            ToggleFullscreen();
        };

        BeginDrawing();
        ClearBackground(GRAY);

        Grid(cellSize);

        for (int i = 0; i < cols; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                if (worldMap[i][j] == 1)
                {
                    DrawRectangle(i * cellSize + 1, j * cellSize + 1, cellSize - 1, cellSize - 1, BLACK);
                }
            }
        }

        if (mouseX >= 0 && mouseX < cols && mouseY >= 0 && mouseY < rows)
        {
            DrawRectangle(mouseX * cellSize + 1, mouseY * cellSize + 1, cellSize - 1, cellSize - 1, ColorAlpha(LIME, 0.5f));
        }

        DrawCircle(playerPos.x * cellSize, playerPos.y * cellSize, 20, BLACK);

     
            DrawLine(playerPos.x * cellSize, playerPos.y * cellSize,
                     (playerPos.x + cosf(playerAngle) * 0.8f) * cellSize,
                     (playerPos.y + sinf(playerAngle) * 0.8f) * cellSize, BLUE);

        DrawText(TextFormat("X: %d, Y: %d", mouseX, mouseY), GetScreenWidth() - 250, GetScreenHeight() - 50, 40, YELLOW);
        DrawText(TextFormat("Player: (%.2f, %.2f)", playerPos.x, playerPos.y) , 10, GetScreenHeight() - 50, 40, YELLOW);
        DrawText(TextFormat("Angle: %.2f", playerAngle), 10, GetScreenHeight() - 100, 40, YELLOW);
        EndDrawing();
    }

    for (int i = 0; i < cols; i++)
        free(worldMap[i]);
    free(worldMap);

    CloseWindow();
    return 0;
}