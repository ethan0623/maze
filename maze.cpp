#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Cell {
    bool isWall;
    bool isVisited;
};

class maze {
private:

public:
    Cell** cell;
    int width, height;
    maze(int w, int h) : width(w), height(h){
        cell = new Cell* [height];
        for (int i=0; i < height; i++) {
            cell[i] = new Cell[width];
            for (int j = 0; j < width; j++) {
                cell[i][j].isWall = (rand() % 4 == 0);
                cell[i][j].isVisited = false;
            }
        }
        cell[0][0].isWall = false;
        cell[height - 1][width - 1].isWall = false;
    }

    //~maze()為析構函數，專門釋放記憶體
    ~maze(){
        for (int i = 0; i < height; i++) {
            delete[] cell[i];
        }
        delete[] cell;
    }

    void display_maze(int player_x,int player_y) {
        for (int i=0; i < height; i++) {
            for (int j=0; j < width; j++) {
                if (cell[i][j].isWall) {
                    cout << "#";
                }
                else if (i == player_x && j == player_y) {
                    cout << "P";
                }
                else {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }
    bool player_move(int& player_x, int& player_y,int new_player_x,int new_player_y) {
        cell[player_x][player_y].isVisited = true;

        if (new_player_x<0 || new_player_y<0 || new_player_x>(height - 1) || new_player_y>(width - 1) || cell[new_player_x][new_player_y].isWall) {
            cout << "無法移動，碰到牆壁！" << endl;
            return false;
        }
        player_y=new_player_y;
        player_x=new_player_x;
        if (new_player_x == height - 1 && new_player_y == width - 1) {
            cout << "恭喜你成功到達終點！" << endl;
            return true;
        }
        else {
            return false;
        }
    }
};


int main() {
    srand(static_cast<unsigned int>(time(0)));
    maze maze_test(10, 10);
    int x = 0, y = 0,new_x,new_y;
    char move;

    while (true) {
        maze_test.display_maze(x, y);
        new_x = x;
        new_y = y;
        cout << "請輸入移動方向 (w: 上, s: 下, a: 左, d: 右): ";
        cin >> move;
        switch (move) {
            case 'w':new_x--; break;
            case 's':new_x++; break;
            case 'a':new_y--; break;
            case 'd':new_y++; break;
        }

        if (maze_test.player_move(x, y, new_x, new_y)) {
            break;
        }
        
    }
    


    return 0;
}
