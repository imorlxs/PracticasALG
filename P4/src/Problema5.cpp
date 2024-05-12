#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Node {
    int x, y, cost, estimate;
    Node* parent;

    Node(int x, int y, int cost, int estimate, Node* parent)
        : x(x), y(y), cost(cost), estimate(estimate), parent(parent) {}
};

bool isValid(int x, int y, int n, const vector<vector<bool>>& maze) {
    return x >= 0 && y >= 0 && x < n && y < n && maze[x][y];
}

int heuristic(int x, int y, int targetX, int targetY) {
    // Manhattan distance as a heuristic
    return abs(targetX - x) + abs(targetY - y);
}

void printPath(Node* node) {
    if (node == nullptr) return;
    printPath(node->parent);
    cout << "(" << node->x << ", " << node->y << ") ";
}

vector<vector<bool>> createStaticMaze() {
    return {
        {true, true, false, true},
        {false, true, true, true},
        {true, true, false, false},
        {true, true, true, true}
    };
}

Node* findPathWithBranchAndBound(vector<vector<bool>>& maze, int startX, int startY, int endX, int endY) {
    int n = maze.size();
    auto cmp = [](Node* a, Node* b) { return a->estimate > b->estimate; };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> pq(cmp);
    vector<vector<int>> minCost(n, vector<int>(n, numeric_limits<int>::max()));
    
    int startEstimate = heuristic(startX, startY, endX, endY);
    Node* start = new Node(startX, startY, 0, startEstimate, nullptr);
    pq.push(start);
    minCost[startX][startY] = 0;

    vector<pair<int, int>> directions{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();

        if (current->x == endX && current->y == endY) {
            return current;
        }

        for (auto& dir : directions) {
            int newX = current->x + dir.first;
            int newY = current->y + dir.second;

            if (isValid(newX, newY, n, maze)) {
                int newCost = current->cost + 1;
                int newEstimate = newCost + heuristic(newX, newY, endX, endY);

                if (newCost < minCost[newX][newY]) {
                    minCost[newX][newY] = newCost;
                    pq.push(new Node(newX, newY, newCost, newEstimate, current));
                }
            }
        }
    }

    return nullptr;
}

int main() {
    auto maze = createStaticMaze();
    Node* path = findPathWithBranchAndBound(maze, 0, 0, 3, 3);
    if (path) {
        cout << "Path found: ";
        printPath(path);
    } else {
        cout << "No path found.";
    }
    return 0;
}