#include "Util.h"

// 跳点搜索函数
bool Jump(const std::vector<std::vector<int>>& grid, int x, int y, int dx, int dy, const std::pair<int, int>& goal, int& jumpX, int& jumpY) {
    int rows = grid.size();
    int cols = grid[0].size();

    int nextX = x + dx;
    int nextY = y + dy;

    // 检查边界和障碍物
    if (nextX < 0 || nextX >= rows || nextY < 0 || nextY >= cols || grid[nextX][nextY] == 1) {
        return false;
    }

    jumpX = nextX;
    jumpY = nextY;

    // 到达目标点
    if (nextX == goal.first && nextY == goal.second) {
        return true;
    }

    // 检查是否是跳点（仅处理直线移动的强制邻居）
    if (dx != 0 && dy == 0) { // 水平移动
        if ((nextY - 1 >= 0 && grid[nextX][nextY - 1] == 1 && grid[nextX + dx][nextY - 1] == 0) ||
            (nextY + 1 < cols && grid[nextX][nextY + 1] == 1 && grid[nextX + dx][nextY + 1] == 0)) {
            return true;
        }
    }
    else if (dx == 0 && dy != 0) { // 垂直移动
        if ((nextX - 1 >= 0 && grid[nextX - 1][nextY] == 1 && grid[nextX - 1][nextY + dy] == 0) ||
            (nextX + 1 < rows && grid[nextX + 1][nextY] == 1 && grid[nextX + 1][nextY + dy] == 0)) {
            return true;
        }
    }

    // 递归继续跳跃
    return Jump(grid, nextX, nextY, dx, dy, goal, jumpX, jumpY);
}

// JPS算法主函数
std::vector<std::pair<int, int>> JPS(std::vector<std::vector<int>>& grid, std::pair<int, int> start, std::pair<int, int> goal)
{
    int rows = grid.size();
    int cols = grid[0].size();

    // 定义4方向移动：上、下、左、右
    std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    // 开放列表（优先队列）和关闭列表（哈希集）
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNode> openList;
    std::unordered_set<std::pair<int, int>, HashPair> closedSet;

    // 初始化起点
    std::shared_ptr<Node> startNode = std::make_shared<Node>(start.first, start.second);
    startNode->g = 0;
    startNode->h = abs(start.first - goal.first) + abs(start.second - goal.second); // 曼哈顿距离
    startNode->f = startNode->g + startNode->h;
    openList.push(startNode);

    while (!openList.empty()) {
        std::shared_ptr<Node> current = openList.top();
        openList.pop();

        // 到达目标
        if (current->x == goal.first && current->y == goal.second) {
            std::vector<std::pair<int, int>> path;
            std::shared_ptr<Node> node = current;
            while (node != nullptr) {
                path.push_back({ node->x, node->y });
                node = node->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // 将当前节点加入关闭列表
        closedSet.insert({ current->x, current->y });

        // 在每个方向上寻找跳点
        for (const auto& dir : directions) {
            int dx = dir.first;
            int dy = dir.second;
            int jumpX, jumpY;

            // 尝试跳跃到下一个跳点
            if (Jump(grid, current->x, current->y, dx, dy, goal, jumpX, jumpY)) {
                if (closedSet.find({ jumpX, jumpY }) != closedSet.end()) continue;

                std::shared_ptr<Node> jumpNode = std::make_shared<Node>(jumpX, jumpY);
                jumpNode->g = current->g + abs(jumpX - current->x) + abs(jumpY - current->y);
                jumpNode->h = abs(jumpX - goal.first) + abs(jumpY - goal.second);
                jumpNode->f = jumpNode->g + jumpNode->h;
                jumpNode->parent = current;

                openList.push(jumpNode);
            }
        }
    }

    // 未找到路径
    return std::vector<std::pair<int, int>>();
}

//// 测试代码
//int main() {
//    // 0表示可通行，1表示障碍物
//    vector<vector<int>> grid = {
//        {0, 0, 0, 0, 0},
//        {0, 1, 1, 0, 0},
//        {0, 0, 0, 0, 0},
//        {0, 1, 0, 1, 0},
//        {0, 0, 0, 0, 0}
//    };
//
//    pair<int, int> start = { 0, 0 }; // 起点
//    pair<int, int> goal = { 4, 4 };  // 终点
//
//    vector<pair<int, int>> path = jps(grid, start, goal);
//
//    if (path.empty()) {
//        cout << "未找到路径！" << endl;
//    }
//    else {
//        cout << "找到路径：" << endl;
//        for (const auto& p : path) {
//            cout << "(" << p.first << "," << p.second << ")" << endl;
//        }
//    }
//
//    return 0;
//}

