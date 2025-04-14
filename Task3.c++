
#include <bits/stdc++.h>

using namespace std;


int Tx[4] = {-1, 1, 0, 0};
int Ty[4] = {0, 0, -1, 1};


int Cost(char c) {

    if(c=='S') return 0;
    else if(c=='G') return 0;
    else if(c=='.') return 1;
    else if(c=='~') return 3;
    else if(c=='^') return 5;
    else if(c=='#') return -1;
    else return -1;
    
}


struct Robo {
    int x, y, cost;
    bool operator>(const Robo& other) const {
        return cost > other.cost;
    }
};

int main() {
    int rows, col;
    cout << "Enter grid dimension (rows cols): ";
    cin >> rows >> col;

    vector<vector<char>> grid(rows, vector<char>(col));
    vector<vector<int>> cosGrid(rows, vector<int>(col));
    pair<int, int> start = {-1, -1}, goal = {-1, -1};

    cout << "Enter the grid (S G . # ~ ^):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < col; ++j) {
            cin >> grid[i][j];
            cosGrid[i][j] = Cost(grid[i][j]);
            if (grid[i][j] == 'S') start = {i, j};
            if (grid[i][j] == 'G') goal = {i, j};
        }
    }

    if (start.first == -1 || goal.first == -1) {
        cout << "Start or Goal not in grid\n";
        return 1;
    }

    vector<vector<int>> dis(rows, vector<int>(col, INT_MAX));
    vector<vector<pair<int, int>>> previous(rows, vector<pair<int, int>>(col, {-1, -1}));
    priority_queue<Robo, vector<Robo>, greater<Robo>> pq;

    dis[start.first][start.second] = 0;
    pq.push({start.first, start.second, 0});

    cout << "\nVisited order:\n";

    while (!pq.empty()) {
        Robo now = pq.top();
        pq.pop();

        int x = now.x;
        int y = now.y;
        int cost = now.cost;

        if (cost > dis[x][y]) continue;

        cout << "(" << x << "," << y << ") ";

        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + Tx[dir];
            int ny = y + Ty[dir];

            if (nx >= 0 && ny >= 0 && nx < rows && ny < col && cosGrid[nx][ny] != -1) {
                int moveCost = Cost(grid[nx][ny]);
                int newCost = dis[x][y] + moveCost;

                if (newCost < dis[nx][ny]) {
                    dis[nx][ny] = newCost;
                    previous[nx][ny] = {x, y};
                    pq.push({nx, ny, newCost});
                }
            }
        }
    }

    cout << "\n\nLeast Cost Path:\n";

    if (dis[goal.first][goal.second] == INT_MAX) {
        cout << "No path found.\n";
    } else {
        stack<pair<int, int>> path;
        pair<int, int> current = goal;

        while (current != make_pair(-1, -1)) {
            path.push(current);
            current = previous[current.first][current.second];
        }

        while (!path.empty()) {
            pair<int, int> p = path.top(); path.pop();
            int x = p.first, y = p.second;
            cout << "(" << x << "," << y << ")";
            if (!path.empty()) cout << " -> ";
        }

        cout << "\n\nTotal Cost = " << dis[goal.first][goal.second] << endl;
    }

    return 0;
}