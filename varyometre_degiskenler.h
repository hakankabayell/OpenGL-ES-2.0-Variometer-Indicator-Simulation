//Author: Hakan KABAYEL

// OpenGL ES program and shader variables
GLuint circleProgram;
GLint circlePositionLoc, circleTexCoordLoc, circleTextureLoc;

GLuint triangleProgram;
GLint trianglePositionLoc, triangleColorLoc;

GLuint progressBarProgram;
GLint progressBarPositionLoc, progressBarFillColorLoc, progressBarProgressLoc, progressBarColorLoc;
GLfloat progressBarVertices[] = {
    -0.90f, -0.8f, // Sol
    -0.85f, -0.8f, // Sağ
    -0.90f, 0.8f,  // Sol
    -0.85f, 0.8f   // Sağ
};

GLuint redProgressBarProgram;
GLint redProgressBarPositionLoc, redProgressBarProgressLoc,redProgressBarColorLoc,redProgressBarFillColorLoc;
// Define vertices of red progress bar
float redProgressBarWidth = 0.805f; // height of red progress bar . 0.805 OpenGL unit

GLfloat redProgressBarVertices[] = {
    -0.9f, 0.0f,         // Start point (x=0, top edge)
    -0.85f, 0.0f, // Start point (x=0, bottom edge)
    -0.9f, redProgressBarWidth,          // end point (x=width, top edge)
    -0.85f, redProgressBarWidth  // end point (x=width, bottom edge)
};

// Circle parameters
const float radius = 0.7f;
const int numSegments = 360;
const float angleIncrement = (2.0f * M_PI) / numSegments;
const float radians = cos(41.0f * M_PI / 180.0f);

// Rotation parameters
float needleRotation = 0.0f;
int artificialDataCounter = 0;
float artificialData[4] = {-20.0f, 20.0f, 0.0f,80.0f};
float firstplaceOfNeedle = 0.0;
float epsilon = 0.025f;