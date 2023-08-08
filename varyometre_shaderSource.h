// Shader kaynak kodları
const char* circleVertexShaderSource =
    "attribute vec2 position;\n"
    "attribute vec2 texCoord;\n"
    "varying vec2 vTexCoord;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(position, 0.0, 1.0);\n"
    "    vTexCoord = texCoord;\n"
    "}\n";

const char* circleFragmentShaderSource =
    "precision mediump float;\n"
    "uniform sampler2D texture;\n"
    "varying vec2 vTexCoord;\n"
    "void main()\n"
    "{\n"
    "    // Calculate distance from the center (0,0)\n"
    "    float distance = length(vTexCoord - vec2(0.5));\n"
    "    // Set border width\n"
    "    float borderWidth = 0.02;\n"
    "    // Set border color\n"
    "    vec4 borderColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
    "    // Determine if inside or outside the border\n"
    "    if (distance > (0.5 - borderWidth) && distance < (0.5 + borderWidth))\n"
    "        gl_FragColor = borderColor;\n"
    "    else\n"
    "        gl_FragColor = texture2D(texture, vTexCoord);\n"
    "}\n";

const char* triangleVertexShaderSource =
    "attribute vec2 position;\n"
    "uniform float rotation;\n"
    "void main()\n"
    "{\n"
    "    float cosTheta = cos(rotation);\n"
    "    float sinTheta = sin(rotation);\n"
    "    mat2 rotationMatrix = mat2(cosTheta, -sinTheta, sinTheta, cosTheta);\n"
    "    vec2 rotatedPosition = rotationMatrix * position;\n"
    "    gl_Position = vec4(rotatedPosition, 0.0, 1.0);\n"
    "}\n";

const char* triangleFragmentShaderSource =
    "precision mediump float;\n"
    "uniform vec4 topColor;\n"
    "varying float distance;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = topColor;\n"
    "}\n";

const char* progressBarVertexShaderSource =
    "attribute vec2 position;\n"
    "varying float progress;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(position, 0.0, 1.0);\n"
    "}\n";

const char* progressBarFragmentShaderSource =
    "precision mediump float;\n"
    "uniform vec4 color;\n"
    "uniform float progress;\n"
    "void main()\n"
    "{\n"
    "    // Draw progress bar as a simple colored rectangle\n"
    "    gl_FragColor = color;\n"
    "}\n";

const char* redProgressBarVertexShaderSource =
    "attribute vec2 position;\n"
    "uniform float progress;\n"
    "void main()\n"
    "{\n"
    "    float height = position.y * progress;\n" // İlerlemeye (veya needleRotation'a) göre yüksekliği hesapla
    "    gl_Position = vec4(position.x, height, 0.0, 1.0);\n"
    "}\n";

const char* redProgressBarFragmentShaderSource =
    "precision mediump float;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n" // Rengi kırmızı (1.0, 0.0, 0.0) ve tamamen opak (alpha = 1.0) olarak ayarla
    "}\n";