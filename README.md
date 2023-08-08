VARIOMETER INDICATOR SIMULATION
**********************************************************
LIBRARIES

* #include <EGL/egl.h>: This header file is used to include the necessary declarations and functions for using the EGL (Embedded Graphics Library) API. EGL is used in this code to manage graphics contexts, surfaces, and rendering for OpenGL ES.

* #include <GLES2/gl2.h>: This header file includes the declarations and functions for using the OpenGL ES 2.0 API. It provides the necessary functions and constants for rendering graphics using OpenGL ES.

* #include <GLFW/glfw3.h>: This header file is used to include the declarations and functions from the GLFW (Graphics Library Framework) library. GLFW is a library that provides a simple and consistent interface for creating windows, handling input, and managing OpenGL contexts.

* #include <iostream>: This is the standard C++ input-output stream library. It is used in this code to output error messages to the console using std::cerr.

* #include <math.h>: This header file includes various mathematical functions and constants. It's used in the code to perform mathematical calculations, such as trigonometric functions for positioning and rotating elements.

* "stb_image.h": This is a custom header file that likely includes declarations and functions for loading image data using the STB Image library. STB Image is a popular library for loading various image formats, and it's used here to load texture data for the OpenGL application.

* "varyometre_degiskenler.h": Custom header for variable definitions.
  
* "varyometre_shaderSource.h": Custom header for shader source code.
  
* "textureData.h": Custom header for texture data.
  
**********************************************************
FUNCTIONS

* createEGLContext() Function:
  
This function creates an EGL context and surface. It initializes EGL, selects an appropriate configuration, creates a window surface, and establishes a rendering context.

![Ekran görüntüsü 2023-08-08 102453](https://github.com/hakankabayell/OpenGL-ES-2.0-VariometerIndicatorSimulation/assets/127239422/4891e6ea-48b9-415b-8e32-2909d5f69a51)

* createProgram() Function:

This function creates an OpenGL shader program. It compiles and attaches both vertex and fragment shaders, links them into a program, and manages attribute locations.

* loadTexture() Function:

This function loads an OpenGL texture from image data. It generates a texture ID, sets texture parameters, specifies texture data, and frees the image data memory.

* drawCircleWithTexture() Function:

This function draws a circle using a texture. It uses a shader program, calculates vertex positions and texture coordinates, enables attribute arrays, and performs the drawing using glDrawArrays.

![dcwt](https://github.com/hakankabayell/OpenGL-ES-2.0-VariometerIndicatorSimulation/assets/127239422/24845032-a051-4892-8e7e-25ef34f1db6f)

* drawNeedle() Function:

This function draws the needle of a compass. It creates two colored triangles representing the needle, sets up shader uniform values, and draws the triangles using glDrawArrays.

![dn](https://github.com/hakankabayell/OpenGL-ES-2.0-VariometerIndicatorSimulation/assets/127239422/820d4d44-cb9e-4148-a88b-0174bd734f9b)

* rotateNeedle() Function:

This function rotates the needle towards a target rotation angle. It calculates the angle difference, determines the rotation direction, and updates the needle's rotation based on a rotation speed.

* prepareMoving() Function:

This function prepares and performs needle rotation towards a target angle. It calculates the target rotation angle, rotates the needle, and checks if the target is reached.

![prf](https://github.com/hakankabayell/OpenGL-ES-2.0-VariometerIndicatorSimulation/assets/127239422/5d1b3404-5bc4-4efc-8587-0d47f187550e)

* drawProgressBar() Function: 

Draws a progress bar indicating the needle's position using a shader program.

![pbar](https://github.com/hakankabayell/OpenGL-ES-2.0-VariometerIndicatorSimulation/assets/127239422/d973aefd-18ff-424e-bbe7-122fa1d76713)

* drawRedProgressBar() Function:

Draws a red progress bar representing the needle's position.

![rpb](https://github.com/hakankabayell/OpenGL-ES-2.0-VariometerIndicatorSimulation/assets/127239422/d37e5313-4ec2-4d97-9b59-30fa5748efd9)

* destroyEGLContext() Function:

This function destroys the EGL context and surface, cleaning up resources.


**********************************************************

OUTPUT


https://github.com/hakankabayell/OpenGL-ES-2.0-VariometerIndicatorSimulation/assets/127239422/213dec23-684a-46b1-bdd3-3e99f8b0b2b8


