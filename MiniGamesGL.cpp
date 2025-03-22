#include <iostream>
#include <functional>

#include <GLFW\glfw3.h>
#include "include/glad/glad.h"

#include "MonsterGame.h"

#include <fstream>
#include <sstream>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

GLFWwindow* InitializeGLViewport()
{
    if (!glfwInit()) {
        return nullptr;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* glWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mini Games", NULL, NULL);
    if (glWindow == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(glWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(glWindow, [](GLFWwindow* inWindow, const int inWidth, const int inHeight) {
            glViewport(0, 0, inWidth, inHeight);
            Game* game = static_cast<Game*>(glfwGetWindowUserPointer(inWindow));
            game->UpdateProjectionMatrix(static_cast<float>(inWidth), static_cast<float>(inHeight));
        });
    return glWindow;
}

void Testido() 
{
    /*LMatrix<int> A = LMatrix<int>::Build<3, 2>(3, 1, 7, 2, 5, 1);
    LMatrix<int> B = LMatrix<int>::Build<2, 3>(1, 3, 4, 2, 5, 0);

    LMatrix<int> C = A * B;
    C.Print();*/

    //t.Print();

    /*std::ifstream meshFile("Resources/test.obj");
    if (!meshFile) {
        std::cerr << "Unable to open file\n";
    }

    std::string line;
    while (std::getline(meshFile, line)) {
        //std::cout << line;

        std::istringstream lineStringStream(line);
        std::string linePrefix;
        lineStringStream >> linePrefix;

        if (linePrefix == "v") 
        {
            float x = 0, y = 0, z = 0;
            lineStringStream >> x >> y >> z;
            std::cout << x << "," << y << "," << z << std::endl;
        }

        /*if (linePrefix == "f")
        {
            std::cout << "Index: ";
            std::string indexLineString;

            while (lineStringStream >> indexLineString) {
                int posIndex = 0, texIndex = 0, normIndex = 0;
                std::istringstream indexLineStringStream(indexLineString);

                while (indexLineStringStream)
                {
                    while (indexLineStringStream.peek() == '/')
                    {
                        indexLineStringStream.get();
                    }

                    int number;
                    if (indexLineStringStream >> number)
                        std::cout << number << " ";
                    break;  // remove this to continue reading other indeces
                }
                std::cout << std::endl;
            }
        }
    }
    meshFile.close();*/
}

int main()
{
    Testido();

    GLFWwindow* glWindow = InitializeGLViewport();
    Game* game = new MonsterGame(glWindow, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT));    

    if (!glWindow || !game)
        return -1;

    glfwSetWindowUserPointer(glWindow, game);
    glfwSetKeyCallback(glWindow, [](GLFWwindow* inGLWindow, int inKey, int inScancode, int inAction, int inModifier) {
            Game* game = static_cast<Game*>(glfwGetWindowUserPointer(inGLWindow));
            game->HandleInputBase(inKey, inAction, inModifier);
    });

    glfwSetInputMode(glWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // used for FPS mode
    glfwSetCursorPosCallback(glWindow, [](GLFWwindow* inGLWindow, double xPos, double yPos) {
        Game* game = static_cast<Game*>(glfwGetWindowUserPointer(inGLWindow));
        game->HandleMouseMovement(xPos, yPos);
    });

    game->InitializeScene(); // here we do asset loading
    while (!glfwWindowShouldClose(glWindow))
    {
        game->BaseUpdate();
        game->Render();
        
        glfwPollEvents();
        glfwSwapBuffers(glWindow);
    }

    delete game;
    glfwTerminate();
    return 0;
}