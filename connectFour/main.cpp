#include <bits/stdc++.h>
#include <raylib.h>
using namespace std;

struct Point{
    int x = 0, y = 0, direction = 0, player = 0;
};

const int n = 6, m = 7;
const int screenWidth = 700;
const int screenHeight = 600;
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
int heights[] = {0, 0, 0, 0, 0, 0, 0};
vector<vector<Point>> arr(n);

void initialize(){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++){
            arr[i][j].direction = 9;
        }
}

bool check4winner (int start_x, int start_y) {
    initialize();
    int score[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int real_score = 0;
    queue<Point> q;
    for(int i = 0; i < 8; i++){
        if(start_x + dx[i] >= 0 && start_x + dx[i] < n)
            if(start_y + dy[i] >= 0 && start_y + dy[i] < m)
                if(arr[start_x + dx[i]][start_y + dy[i]].player == arr[start_x][start_y].player){
                    arr[start_x + dx[i]][start_y + dy[i]].direction = i;
                    score[i]++;
                    q.push(arr[start_x + dx[i]][start_y + dy[i]]);
                }
    }
    while(q.size()){
        Point curr = q.front();
        q.pop();
        int cd = curr.direction;
        if(curr.x + dx[cd] >= 0 && curr.x + dx[cd] < n)
            if(curr.y + dy[cd] >= 0 && curr.y + dy[cd] < m)
                if(arr[curr.x + dx[cd]][curr.y + dy[cd]].player == arr[curr.x][curr.y].player){
                    arr[curr.x + dx[cd]][curr.y + dy[cd]].direction = cd;
                    score[cd]++;
                    q.push(arr[curr.x + dx[cd]][curr.y + dy[cd]]);
                }
    }
    for(vector<Point> a : arr){
        for(Point b : a){
            if(b.direction != 9)
                cout << score[b.direction] << " ";
            else
                cout << ". ";
        }
        cout << '\n';
    }
    for(int i = 0; i < 4; i++){
        int temp = score[i] + score[i + 4];
        real_score = max(real_score, temp);
    }
    real_score++;
    if(real_score >= 4) return false;
    else return true;
}

void draw(){
    cout << '\n' << "INFO: CURRENT GAME STATE:" << '\n';
    /*
    for(vector<Point> a : arr){
        for(Point b : a){
            if(b.player == 0)
                cout << ". ";
            else
                cout << b.player << " ";
        }
        cout << '\n';
    }
    */
}
//void DrawRectangle(int posX, int posY, int width, int height, Color color); // Draw a color-filled rectangle

void drawGrid(int coord_y){
    for(vector<Point> a : arr){
        for(Point b : a){
            if(b.y == coord_y)
                DrawRectangle(b.y * 100, b.x * 100, 99, 99, RAYWHITE);
            else
                DrawRectangle(b.y * 100, b.x * 100, 99, 99, LIGHTGRAY);
            if(b.player == 1){
                DrawCircle(50 + b.y * 100, 50 + b.x * 100, 49, MAROON);
            }
            else if(b.player == 2){
                DrawCircle(50 + b.y * 100, 50 + b.x * 100, 49, GOLD);
            }
        }
    }
}

int main(){
    InitWindow(screenWidth, screenHeight, "Connect Four");
    SetTargetFPS(60);
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++){
            Point temp = {i, j, 9, 0};
            arr[i].push_back(temp);
        }
    bool no_winner = true;
    int curr_player = 1;
    draw();
    bool update = false, update_info = false;
    bool updateDraw = true;
    int coord_x = 0, coord_y = 0;
    while(no_winner && !WindowShouldClose()){
        if (IsKeyPressed(KEY_RIGHT)){
            update_info = true;
            updateDraw = true;
            coord_y++;
        }
        if (IsKeyPressed(KEY_LEFT)){
            update_info = true;
            updateDraw = true;
            coord_y--;
        }
        if(update_info){
            update_info = false;
            cout << "INFO: CURRENT LOCATION: " << coord_y << '\n';
        }
        if (IsKeyPressed(KEY_ENTER)){
            update = true;
            updateDraw = true;
        }
        if(update){
            update = false;
            if(heights[coord_y] == 6 || coord_y > 6){
                cout << "You cannot place a piece here\n";
            }
            else{
                coord_x = 5 - heights[coord_y];
                heights[coord_y]++;
                arr[coord_x][coord_y].player = curr_player;
                no_winner = check4winner(coord_x, coord_y);
                curr_player = curr_player % 2 + 1;
                draw();
            }
        }
        BeginDrawing();
        if(updateDraw){
            ClearBackground(DARKGRAY);
            drawGrid(coord_y);
            updateDraw = false;
        }
        EndDrawing();
    }
    cout << arr[coord_x][coord_y].player;
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(DARKGRAY);
        if(arr[coord_x][coord_y].player == 1)
            DrawText("Red player wins!", 150, 250, 50, LIGHTGRAY);
        else if(arr[coord_x][coord_y].player == 2)
            DrawText("Yellow player wins!", 110, 250, 50, LIGHTGRAY);
        else
            DrawText("Game not concluded", 100, 250, 50, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
}
