#include "Engine.hpp"
#include <chrono>
#include <thread>

// GLFW callback implementations
void Engine::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    // Store new dimensions
    if (auto *engine = static_cast<Engine *>(glfwGetWindowUserPointer(window)))
    {
        engine->m_WindowWidth = width;
        engine->m_WindowHeight = height;
    }
}

void Engine::ErrorCallback(int error, const char *description)
{
    spdlog::error("GLFW Error {}: {}", error, description);
}

bool Engine::Initialize()
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Initializing engine...");

    // Set GLFW error callback
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit())
    {
        spdlog::error("Failed to initialize GLFW");
        return false;
    }

    // Configure OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    m_Window = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_WindowTitle, nullptr, nullptr);
    if (!m_Window)
    {
        spdlog::error("Failed to create window");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, this);

    // Set callbacks
    glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);

    // Enable V-Sync
    glfwSwapInterval(1);

    // Initialize root node
    m_RootNode = std::make_unique<Node>("Root");

    spdlog::info("Engine initialized successfully");
    m_IsRunning = true;
    return true;
}

void Engine::Run()
{
    auto lastFrame = std::chrono::high_resolution_clock::now();

    while (m_IsRunning && !glfwWindowShouldClose(m_Window))
    {
        // Calculate delta time
        auto currentFrame = std::chrono::high_resolution_clock::now();
        m_DeltaTime = std::chrono::duration<float>(currentFrame - lastFrame).count();
        lastFrame = currentFrame;

        ProcessInput();
        Update();
        Render();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();

        // Cap frame rate to ~60 FPS
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void Engine::ProcessInput()
{
    // Close window on ESC
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_Window, true);
    }
}

void Engine::Update()
{
    if (m_RootNode)
    {
        m_RootNode->Update(m_DeltaTime);
    }
}

void Engine::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Future: Render scene graph here
}

void Engine::Shutdown()
{
    spdlog::info("Shutting down engine");

    // Clean up nodes
    m_RootNode.reset();

    if (m_Window)
    {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
    }

    glfwTerminate();
}

void Engine::GetWindowSize(int &width, int &height)
{
    width = m_WindowWidth;
    height = m_WindowHeight;
}

void Engine::AddNode(std::unique_ptr<Node> node)
{
    if (m_RootNode && node)
    {
        m_RootNode->AddChild(std::move(node));
    }
}