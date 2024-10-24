#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <iostream>
#include <chrono>
#include <thread>

void error_callback(int error, const char *description)
{
    spdlog::error("GLFW Error {}: {}", error, description);
}

int main()
{
    // 設置日誌級別
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Starting game engine...");

    // 設置 GLFW 錯誤回調
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        spdlog::error("Failed to initialize GLFW");
        std::cout << "Press Enter to exit..." << std::endl;
        std::cin.get();
        return -1;
    }

    spdlog::debug("GLFW initialized successfully");

    // 設置 OpenGL 版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Game Engine", nullptr, nullptr);
    if (!window)
    {
        spdlog::error("Failed to create GLFW window");
        glfwTerminate();
        std::cout << "Press Enter to exit..." << std::endl;
        std::cin.get();
        return -1;
    }

    spdlog::debug("Window created successfully");
    glfwMakeContextCurrent(window);

    // 啟用垂直同步
    glfwSwapInterval(1);

    // 獲取 OpenGL 版本信息
    spdlog::info("OpenGL Version: {}", (const char *)glGetString(GL_VERSION));

    // 設置清除顏色為深藍色
    glClearColor(0.0f, 0.1f, 0.2f, 1.0f);

    // 主循環
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // 添加一些延遲以避免 CPU 使用率過高
        std::this_thread::sleep_for(std::chrono::milliseconds(16));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    spdlog::info("Shutting down game engine");
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}