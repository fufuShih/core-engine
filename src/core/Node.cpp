#include "Node.hpp"
#include <algorithm>

Node::Node(const std::string &name)
    : m_Name(name)
{
}

void Node::AddChild(std::unique_ptr<Node> child)
{
    if (child)
    {
        child->m_Parent = this;
        m_Children.push_back(std::move(child));
    }
}

void Node::RemoveChild(Node *child)
{
    if (!child)
        return;

    auto it = std::find_if(m_Children.begin(), m_Children.end(),
                           [child](const std::unique_ptr<Node> &ptr)
                           { return ptr.get() == child; });

    if (it != m_Children.end())
    {
        (*it)->m_Parent = nullptr;
        m_Children.erase(it);
    }
}

void Node::Update(float deltaTime)
{
    // Update this node
    // ... 可以在這裡添加更多邏輯

    // Update children
    for (auto &child : m_Children)
    {
        child->Update(deltaTime);
    }
}