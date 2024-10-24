#pragma once
#include <memory>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include "Node.hpp"

class Engine
{
public:
    static Engine &GetInstance()
    {
        static Engine instance;
        return instance;
    }

    bool Initialize();
    void Run();
    void Shutdown();

    // Window management
    GLFWwindow *GetWindow() const { return m_Window; }
    void GetWindowSize(int &width, int &height);

    // Scene management
    Node *GetRootNode() const { return m_RootNode.get(); }
    void AddNode(std::unique_ptr<Node> node);

    // Delete copy constructor and assignment operator
    Engine(const Engine &) = delete;
    Engine &operator=(const Engine &) = delete;

    // Delta time accessor
    float GetDeltaTime() const { return m_DeltaTime; }

private:
    Engine() = default;

    // Core systems
    GLFWwindow *m_Window = nullptr;
    std::unique_ptr<Node> m_RootNode;
    bool m_IsRunning = false;
    float m_DeltaTime = 0.0f;

    // Window properties
    int m_WindowWidth = 1280;
    int m_WindowHeight = 720;
    const char *m_WindowTitle = "Game Engine";

    // Core loop methods
    void Update();
    void Render();
    void ProcessInput();

    // GLFW callbacks
    static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
    static void ErrorCallback(int error, const char *description);
};