#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Cell {
    bool isWall;       // 是否為牆
    bool isVisited;    // 是否已經訪問過
};

class Maze {
private:
    int width, height;
    Cell** cells;  // 動態分配的迷宮格子

public:
    Maze(int w, int h) : width(w), height(h) {
        cells = new Cell * [height];
        for (int i = 0; i < height; ++i) {
            cells[i] = new Cell[width];
            for (int j = 0; j < width; ++j) {
                cells[i][j].isWall = (rand() % 4 == 0); // 25% 機率是牆壁
                cells[i][j].isVisited = false;   // 初始化為未訪問
            }
        }
        cells[0][0].isWall = false;  // 起點
        cells[height - 1][width - 1].isWall = false; // 終點
    }

    ~Maze() {
        for (int i = 0; i < height; ++i) {
            delete[] cells[i];  // 釋放每一列的記憶體
        }
        delete[] cells;  // 釋放指向列的指標
    }

    void displayMaze(int playerX, int playerY) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (i == playerX && j == playerY) {
                    cout << "P"; // 玩家位置
                }
                else if (cells[i][j].isWall) {
                    cout << "#"; // 牆
                }
                else {
                    cout << " "; // 空格
                }
            }
            cout << endl;
        }
    }

    bool move(int& x, int& y, int newX, int newY) {
        if (newX < 0 || newX >= height || newY < 0 || newY >= width || cells[newX][newY].isWall) {
            cout << "無法移動，碰到牆壁！" << endl;
            return false; // 超出邊界或碰撞牆壁
        }
        x = newX;
        y = newY;
        cells[x][y].isVisited = true; // 標記為已訪問
        if (x == height - 1 && y == width - 1) {
            cout << "恭喜你成功到達終點！" << endl;
            return true; // 成功到達終點
        }
        return false;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // 隨機種子
    Maze maze(10, 10); // 創建一個10x10的迷宮

    int x = 0, y = 0; // 起點位置
    char moveDirection;

    while (true) {
        maze.displayMaze(x, y); // 顯示迷宮及玩家位置
        cout << "請輸入移動方向 (w: 上, s: 下, a: 左, d: 右): ";
        cin >> moveDirection;

        // 保存先前的位置以便在無法移動時不改變位置
        int newX = x, newY = y;

        switch (moveDirection) {
        case 'w': newX--; break; // 向上移動
        case 's': newX++; break; // 向下移動
        case 'a': newY--; break; // 向左移動
        case 'd': newY++; break; // 向右移動
        default:
            cout << "無效指令！" << endl;
            continue;
        }

        // 嘗試移動並檢查結果
        if (maze.move(x, y, newX, newY)) {
            // 如果沒有返回true，則無需進行其他動作
            break;
        }
    }

    return 0;
}
