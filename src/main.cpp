#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\n";

const char *fragmentShaderSourceO = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\n";

const char *fragmentShaderSourceY = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                    "}\n";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpengl", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR:SHADER:VERTEX:COMPILATION:FAILURE" << infolog << std::endl;
        std::cin >> success;

        return -1;
    }

    unsigned int fragmentShaderO;
    fragmentShaderO = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderO, 1, &fragmentShaderSourceO, NULL);
    glCompileShader(fragmentShaderO);

    glGetShaderiv(fragmentShaderO, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderO, 512, NULL, infolog);
        std::cout << "ERROR:SHADER:FRAGMENT:COMPILATION:FAILURE" << infolog << std::endl;
        std::cin >> success;

        return -1;
    }

    unsigned int fragmentShaderY;
    fragmentShaderY = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderY, 1, &fragmentShaderSourceY, NULL);
    glCompileShader(fragmentShaderY);

    glGetShaderiv(fragmentShaderY, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderY, 512, NULL, infolog);
        std::cout << "ERROR:SHADER:FRAGMENT:COMPILATION:FAILURE" << infolog << std::endl;
        std::cin >> success;

        return -1;
    }

    unsigned int shaderProgramO, shaderProgramY;

    shaderProgramO = glCreateProgram();
    glAttachShader(shaderProgramO, vertexShader);
    glAttachShader(shaderProgramO, fragmentShaderO);
    glLinkProgram(shaderProgramO);

    glGetProgramiv(shaderProgramO, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgramO, 512, NULL, infolog);
        std::cout << "ERROR:SHADER:PROGRAM:LINKING:FAILED" << infolog << std::endl;
        std::cin >> success;
        return -1;
    }

    shaderProgramY = glCreateProgram();
    glAttachShader(shaderProgramY, vertexShader);
    glAttachShader(shaderProgramY, fragmentShaderY);
    glLinkProgram(shaderProgramY);

    glGetProgramiv(shaderProgramY, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgramY, 512, NULL, infolog);
        std::cout << "ERROR:SHADER:PROGRAM:LINKING:FAILED" << infolog << std::endl;
        std::cin >> success;
        return -1;
    }

    float verticies1[] = {
        -0.8f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -0.4f, 0.5f, 0.0f

    };

    float verticies2[] = {
        0.8f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.4f, 0.5f, 0.0f};

    unsigned int VBO[2], VAO[2];
    glGenBuffers(1, &VBO[0]);
    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[1]);
    glGenVertexArrays(1, &VAO[1]);
    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies1), verticies1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies2), verticies2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderO);
    glDeleteShader(fragmentShaderY);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramO);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramY);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}