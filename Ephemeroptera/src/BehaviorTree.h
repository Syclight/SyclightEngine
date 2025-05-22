#pragma once

#include <Syclight.h>

enum class NodeStatus {
    Success,
    Failure,
    Running
};

class Node {
public:
    virtual ~Node() = default;
    virtual NodeStatus tick() = 0; // 每次“tick”调用一次，更新节点状态
};

// 行为节点
class ActionNode : public Node {
public:
    using ActionFunc = std::function<NodeStatus()>;

    ActionNode(ActionFunc action) : action(action) {}

    virtual NodeStatus tick() override;

private:
    ActionFunc action;
};

// 顺序节点
class SequenceNode : public Node {
public:
    SequenceNode(std::vector<syc::Ref<Node>> children) : children(std::move(children)) {}

    virtual NodeStatus tick() override;

private:
    std::vector<syc::Ref<Node>> children;
};

// 选择节点
class SelectorNode : public Node {
public:
    SelectorNode(std::vector<syc::Ref<Node>> children) : children(std::move(children)) {}

    virtual NodeStatus tick() override;

private:
    std::vector<syc::Ref<Node>> children;
};


class BehaviorTree {
public:
    explicit BehaviorTree(syc::Ref<Node> root) : root(std::move(root)) {}

    void tick();

private:
    syc::Ref<Node> root;
};