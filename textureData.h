#include <fstream>
#include <iostream>
#include <iomanip>
#include "stb_image.h"

// texture datas
const char* texturePath = "varyometre.jpg";  // texture used
int texWidth, texHeight, texChannels; // variables that store the value of width, height, channels of texture
unsigned char* texData; // variable that store the value of pixels of texture. (RGBA)

// function that finds the dataSize of the file.
inline void glFindDataSize(const char* imagePath, size_t& dataSize)
{
    std::ifstream DataFile(imagePath, std::ios::binary);
    if (!DataFile.good())
    {
        dataSize = 0;
    }

    DataFile.seekg(0, std::ios::end);
    dataSize = static_cast<size_t>(DataFile.tellg());
    DataFile.seekg(0);

}

// function that displays the values of pixels of texture in order (RGBA)
inline void glDisplayData(unsigned char* textureData, size_t dataSize)
{
    for (size_t i = 0; i <= dataSize; ++i)
    {
        std::cout << static_cast<int>(textureData[i]) << " , ";
        if ((i + 1) % 4 == 0) // Her 4 veri 1 piksele denk gelmektedir. Sırası ile R, G, B, A,
            std::cout << std::endl;
    }
}

// the main code of textureData.h which is called in the loadTexture function in varyometre_main file. 
// main function that gets the value of texture by using texturePath and display them.
inline void glGetTextureData()
{
    stbi_set_flip_vertically_on_load(true);
    texData = stbi_load(texturePath, &texWidth, &texHeight, &texChannels, 0);

    size_t dataSize = 0;
    glFindDataSize(texturePath, dataSize);  

    if (dataSize != 0)
    {
        glDisplayData(texData, dataSize);
    }
}