//Author: Hakan KABAYEL

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "stb_image.h"
#include "varyometre_degiskenler.h"
#include "varyometre_shaderSource.h"
#include "textureData.h"

// Create EGL context and surface
void createEGLContext(GLFWwindow* window)
{
    EGLint numConfigs;
    EGLConfig config;
    EGLint attributes[] =
    {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_NONE
    };

    EGLint contextAttribs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, NULL, NULL);

    eglChooseConfig(display, attributes, &config, 1, &numConfigs);

    EGLSurface surface = eglCreateWindowSurface(display, config, EGLNativeWindowType(window), NULL);

    EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);

    eglMakeCurrent(display, surface, surface, context);
}

// Create shader program
GLuint createProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glBindAttribLocation(program, 0, "position");

    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

// Load texture image
GLuint loadTexture()
{
    glGetTextureData();

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);

    stbi_image_free(texData);

    return textureId;
}

// Draw circle using texture
void drawCircleWithTexture(GLuint textureId)
{
    glUseProgram(circleProgram);
    
    int texWidth, texHeight;
    glBindTexture(GL_TEXTURE_2D, textureId);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texWidth);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texHeight);

    GLfloat vertices[(numSegments + 1) * 2];
    GLfloat texCoords[(numSegments + 1) * 2];

    for (int i = 0; i <= numSegments; ++i) {
        float angle = i * angleIncrement;
        vertices[i * 2] = radius * std::cos(angle);
        vertices[i * 2 + 1] = radius * std::sin(angle);

        texCoords[i * 2] = (std::cos(angle) + 1.0f) * 0.5f;
        texCoords[i * 2 + 1] = (std::sin(angle) + 1.0f) * 0.5f;
    }

    GLint positionLoc = glGetAttribLocation(circleProgram, "position");
    glEnableVertexAttribArray(positionLoc);
    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 0, vertices);

    GLint texCoordLoc = glGetAttribLocation(circleProgram, "texCoord");
    glEnableVertexAttribArray(texCoordLoc);
    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, 0, texCoords);

    GLint textureLoc = glGetUniformLocation(circleProgram, "texture");
    glUniform1i(textureLoc, 0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments + 1);
}

void drawNeedle()
{
    glUseProgram(triangleProgram);

    // Pass rotation value to the shader
    GLint rotationLoc = glGetUniformLocation(triangleProgram, "rotation");
    GLint positionLoc = glGetAttribLocation(triangleProgram, "position");
    GLint topColorLoc = glGetUniformLocation(triangleProgram, "topColor");
    glEnableVertexAttribArray(positionLoc);
    
    glUniform1f(rotationLoc, needleRotation);

    // Birinci üçgeni çiz
    GLfloat vertices[6] = {
        -0.55f, 0.0f, //üst
        -0.03f, 0.02f, // sağ
        -0.03f, -0.02f // sol
    };
    glUniform4f(topColorLoc, 1.0f, 0.0f, 0.0f, 0.5f); // Kırmızı
    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // İkinci üçgeni çiz
    GLfloat verticesReverse[6] = {
        0.0f, 0.0f, //üst
        -0.03f, 0.02f, // sağ
        -0.03f, -0.02f // sol
    };
    glUniform4f(topColorLoc, 1.0f, 0.0f, 0.0f, 0.5f); // Kırmızı
    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 0, verticesReverse);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

//Dönüş açısına göre needle'ı döndür
void rotateNeedle(float targetRotationAngle)
{
    // Dönüş yapılacak açı
    float rotationSpeed = 0.01f; // Dönüş hızını uygun bir değer seçin

    // Hedef açı ile mevcut açı arasındaki farkı hesaplayalım
    float angleDiff = targetRotationAngle - needleRotation;

    // Açı farkını pozitif yapalım
    angleDiff = fmodf(angleDiff + 3.04f + 3.04f, 3.04f) - 3.04f;   

    // Dönüş yönü belirleme
    float direction = (targetRotationAngle > 0) ? 1.0f : -1.0f;

    // Açı farkını pozitif yapalım
    angleDiff = fabs(angleDiff);

    // Dönüş açısına ulaşıncaya kadar needle'ı döndür
    if (angleDiff > epsilon)
    {
        // Dönüş açısını sınırla
        if (angleDiff > rotationSpeed)
            angleDiff = rotationSpeed;

        needleRotation += direction * angleDiff;
    }
}

// Move fonksiyonunu güncelle
void prepareMoving(int i)
{
    float targetRotationAngle;
    if (i < (sizeof(artificialData) / sizeof(*artificialData)))
    {
        //BOUNDRIES
        if (artificialData[i] > 80.0f)
        {
            artificialData[i] = 80.0f;
        }
        else if (artificialData[i] < -80.0f)
        {
            artificialData[i] = -80.0f;
        }
        
        float step = ((artificialData[i]) - firstplaceOfNeedle);
        if (step == 0)
        {
            step = (artificialData[i] - firstplaceOfNeedle);
        }

        targetRotationAngle = (step / 20.0f * radians);
        // Needle'ı döndür
        rotateNeedle(targetRotationAngle);
    }

    // Dönüş hedefine ulaşıldığında işlem tamamlandı
    if ((fabs(needleRotation - targetRotationAngle) <= epsilon) && artificialDataCounter < (sizeof(artificialData)/sizeof(*artificialData)))
    {
        artificialDataCounter++;
    }
}

// İlerleme çubuğunu çizme
void drawProgressBar()
{
    glUseProgram(progressBarProgram);

    progressBarPositionLoc = glGetAttribLocation(progressBarProgram, "position");
    progressBarFillColorLoc = glGetUniformLocation(progressBarProgram, "color");
    progressBarProgressLoc = glGetUniformLocation(progressBarProgram, "progress");

    // Progress bar rengi (örneğin, beyaz)
    glUniform4f(progressBarColorLoc, 1.0f, 1.0f, 1.0f, 1.0f);

    // Progress değerini -20 ile 20 arasında ölçekle ve shader'a gönder
    float scaledProgress = (needleRotation + 4 * radians) / (8 * radians) * 2 - 1;
    glUniform1f(progressBarProgressLoc, scaledProgress);

    glEnableVertexAttribArray(progressBarPositionLoc);
    glVertexAttribPointer(progressBarPositionLoc, 2, GL_FLOAT, GL_FALSE, 0, progressBarVertices);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

// Kırmızı ilerleme çubuğu çizme
void drawRedProgressBar()
{
    glUseProgram(redProgressBarProgram);

    redProgressBarPositionLoc = glGetAttribLocation(redProgressBarProgram, "position");
    redProgressBarProgressLoc = glGetUniformLocation(redProgressBarProgram, "progress");

    // Progress değerini -20 ile 20 arasında ölçekle ve shader'a gönder
    float scaledProgress = (needleRotation + 4 * radians) / ((8 * radians)) * 2 - 1;
    glUniform1f(redProgressBarProgressLoc, scaledProgress);

    glEnableVertexAttribArray(redProgressBarPositionLoc);
    glVertexAttribPointer(redProgressBarPositionLoc, 2, GL_FLOAT, GL_FALSE, 0, redProgressBarVertices);

    // Kırmızı progress barı çiz
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

// Destroy EGL context and surface
void destroyEGLContext()
{
    eglDestroyContext(eglGetCurrentDisplay(), eglGetCurrentContext());
    eglDestroySurface(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW));
    eglTerminate(eglGetCurrentDisplay());
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed" << std::endl;
        return 1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(800, 800, "VARYOMETRE", NULL, NULL);

    if (!window)
    {
        std::cerr << "GLFW window creation failed" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    createEGLContext(window);

    circleProgram = createProgram(circleVertexShaderSource, circleFragmentShaderSource);
    triangleProgram = createProgram(triangleVertexShaderSource, triangleFragmentShaderSource);
    progressBarProgram = createProgram(progressBarVertexShaderSource, progressBarFragmentShaderSource);
    redProgressBarProgram = createProgram(redProgressBarVertexShaderSource, redProgressBarFragmentShaderSource);

    GLuint textureId = loadTexture();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawCircleWithTexture(textureId);
        drawNeedle();

        prepareMoving(artificialDataCounter);

        drawProgressBar();
        drawRedProgressBar();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    destroyEGLContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}