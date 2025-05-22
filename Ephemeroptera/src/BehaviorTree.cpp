#include "BehaviorTree.h"

NodeStatus ActionNode::tick()
{
	return action();
}

NodeStatus SequenceNode::tick()
{
    for (auto& child : children) {
        NodeStatus status = child->tick();
        if (status != NodeStatus::Success) {
            return status; // 如果遇到失败或正在运行，立即返回
        }
    }
    return NodeStatus::Success; // 所有子节点成功
}

NodeStatus SelectorNode::tick()
{
    for (auto& child : children) {
        NodeStatus status = child->tick();
        if (status == NodeStatus::Success) {
            return NodeStatus::Success; // 找到一个成功的节点
        }
    }
    return NodeStatus::Failure; // 所有子节点都失败
}

void BehaviorTree::tick()
{
    root->tick(); // 每次tick更新一次行为树
}
