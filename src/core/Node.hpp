#pragma once
#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

class Node
{
public:
    Node(const std::string &name = "Node");
    virtual ~Node() = default;

    void AddChild(std::unique_ptr<Node> child);
    void RemoveChild(Node *child);
    virtual void Update(float deltaTime);

    // Getters and setters
    const std::string &GetName() const { return m_Name; }
    void SetName(const std::string &name) { m_Name = name; }

    const glm::vec3 &GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec3 &position) { m_Position = position; }

    const glm::vec3 &GetRotation() const { return m_Rotation; }
    void SetRotation(const glm::vec3 &rotation) { m_Rotation = rotation; }

    const glm::vec3 &GetScale() const { return m_Scale; }
    void SetScale(const glm::vec3 &scale) { m_Scale = scale; }

protected:
    std::string m_Name;
    Node *m_Parent = nullptr;
    std::vector<std::unique_ptr<Node>> m_Children;

    // Transform properties
    glm::vec3 m_Position{0.0f};
    glm::vec3 m_Rotation{0.0f};
    glm::vec3 m_Scale{1.0f};
};