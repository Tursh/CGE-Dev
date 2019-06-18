//#include <freetype/config/ftheader.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftimage.h>
//#include <glm/detail/qualifier.hpp>
#include <glm/detail/type_vec2.hpp>
#include <glm/mat4x4.hpp>
//#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_int2.hpp>
#include <GL/glew.h>
#include <IO/Window.h>
#include <Text/TextShader.h> //TextShader
#include <Utils/GLDebug.h>    //GLCall
#include <Utils/Log.h>        //logError
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <utility>
#include <Text/TextRenderer.h>


namespace CGE::Text::textRenderer
{
    //Set font size
#define setFontSize(size) FT_Set_Pixel_Sizes(font, 0, size)

    FT_Library ft;
    FT_Face font;

    TextShader *shader;

    //Graphic part

    struct Character
    {
        unsigned int textureID; // ID handle of the glyph texture
        glm::ivec2 size; // Size of glyph
        glm::ivec2 bearing; // Offset from baseline to left/top of glyph
        unsigned int advance; // Offset to advance to next glyph
    };

    std::map<char, Character> characters;
    unsigned int VAO, VBO;

    //Load font
    void loadFont()
    {
        GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1)); // Disable byte-alignment restriction

        //Load texture
        for (GLubyte c = 0; c < 255; c++)
        {
            // Load character glyph
            if (FT_Load_Char(font, c, FT_LOAD_RENDER))
            {
                logError("ERROR::FREETYTPE: Failed to load Glyph");
                continue;
            }
            // Generate texture
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                    GL_TEXTURE_2D, 0,
                    GL_RED, font->glyph->bitmap.width, font->glyph->bitmap.rows, 0,
                    GL_RED,
                    GL_UNSIGNED_BYTE, font->glyph->bitmap.buffer);
            // Set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // Now store character for later use
            Character character =
                    {texture, glm::ivec2(font->glyph->bitmap.width,
                                         font->glyph->bitmap.rows), glm::ivec2(font->glyph->bitmap_left,
                                                                               font->glyph->bitmap_top),
                     (unsigned int) font->glyph->advance.x};
            characters.insert(std::pair<char, Character>(c, character)); // @suppress("Invalid arguments")
        }

        //Create VAO and VBO to stock chraracter informations

        GLCall(glGenVertexArrays(1, &VAO));
        GLCall(glGenBuffers(1, &VBO));
        GLCall(glBindVertexArray(VAO));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
        GLCall(
                glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW));
        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindVertexArray(0));
    }

    static glm::vec2 displayScale = glm::vec2(1.0f, 1.0f);

    float getStringLength(std::string string, float size)
    {
        float length = 0.0f;
        for (std::string::const_iterator c = string.begin(); c != string.end(); c++)
            length += (characters[*c].advance >> 6); // @suppress("Field cannot be resolved")
        return length / CGE::IO::DEFAULT_WIDTH / displayScale.x * size;
    }

    void renderText(std::string text, float x, float y, float scale, glm::vec3 color,
                    bool centered)
    {
        // Activate corresponding render state
        shader->start();
        shader->setTextColor(color);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        //Set the x position to center the text
        if (centered)
            x -= static_cast<float>(getStringLength(text, scale));
        else
            y -= characters[*text.begin()].size.y / (float) CGE::IO::DEFAULT_HEIGHT / displayScale.y *
                 scale; // @suppress("Field cannot be resolved")


        for (std::string::const_iterator c = text.begin(); c != text.end(); ++c)
        {
            Character ch = characters[*c];

            const float xpos = x + (ch.bearing.x * scale) / CGE::IO::DEFAULT_WIDTH / displayScale.x * 2;
            /*
             * We calculate the y position by centering the caracter position on the y axis and
             * transforming the pixel coordinates to opengl coordinates.
             * Base expression: yPos = y - scale * (bearing.y / 2 + size.y - bearing.y) / (display->height * 2)
             */
            const float ypos =
                    y - scale * (17 + ch.size.y - ch.bearing.y) / CGE::IO::DEFAULT_HEIGHT / displayScale.y * 2;

            const float w = (ch.size.x * scale) / CGE::IO::DEFAULT_WIDTH / displayScale.x * 2;
            const float h = (ch.size.y * scale) / CGE::IO::DEFAULT_HEIGHT / displayScale.y * 2;
            // Update VBO for each character
            GLfloat vertices[6][4] =
                    {
                            {xpos,     ypos + h, 0.0, 0.0},
                            {xpos,     ypos,     0.0, 1.0},
                            {xpos + w, ypos,     1.0, 1.0},

                            {xpos,     ypos + h, 0.0, 0.0},
                            {xpos + w, ypos,     1.0, 1.0},
                            {xpos + w, ypos + h, 1.0, 0.0}};
            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.textureID);
            // Update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.advance >> 6) * scale / displayScale.x / CGE::IO::DEFAULT_WIDTH *
                 2; // Bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glDisable(GL_BLEND);

        shader->stop();
    }

    //Initialization and clean part

    //Init the library
    void init(const char *fontToUse)
    {
        //Init freetype library
        if (FT_Init_FreeType(&ft))
        logError("FREETYPE: Could not init FreeType Library");
        //Load the font
        if (FT_New_Face(ft, fontToUse, 0, &font))
        logError("FREETYPE: Could not load the font " << fontToUse);
        //Set default font size to 120
        setFontSize(120);
        //TODO: load different font size to not get pixelized text and keep performance
        //Load the font
        loadFont();
        //Create shader
        shader = new TextShader();
    }

    //Terminate the ressources
    void clean()
    {
        //Delete the textures
        for (auto &character : characters)
            //Delete all textures
        GLCall(glDeleteTextures(0, &character.second.textureID));
        //Delete VAO and VBO
        GLCall(glDeleteVertexArrays(1, &VAO));
        GLCall(glDeleteBuffers(1, &VBO));
        //Destroy shader
        shader->destroy();
        //Terminate the library
        FT_Done_Face(font);
        FT_Done_FreeType(ft);
    }

    void resetWindowDimension(const glm::vec2 &newResolution)
    {
        displayScale = (glm::vec2) newResolution / glm::vec2(CGE::IO::DEFAULT_WIDTH, CGE::IO::DEFAULT_HEIGHT);
    }

}
