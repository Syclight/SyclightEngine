#pragma once

#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <memory>

// 定义节点结构体
struct Node {
    int x, y;           // 坐标
    int g;             // 从起点到当前点的代价
    int h;             // 到终点的启发式估计值
    int f;             // f = g + h
    std::shared_ptr<Node> parent; // 父节点指针

    Node(int _x, int _y) : x(_x), y(_y), g(0), h(0), f(0), parent(nullptr) {}
};

// 优先队列比较器，按f值从小到大排序
struct CompareNode {
    bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
        return a->f > b->f;
    }
};

// 用于unordered_set的哈希函数
struct HashPair {
    size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};

std::vector<std::pair<int, int>> JPS(std::vector<std::vector<int>>& grid, std::pair<int, int> start, std::pair<int, int> goal);