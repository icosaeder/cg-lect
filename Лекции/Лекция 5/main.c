////////////////////////////////////////////////////////////////////////////////
// OpenGL first shader program
// Special for course "Algorithmic basics of multimedia"
//
// Copyright (C) 2011 by icosaeder
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/glut.h>


// Maximal size of shader source in bytes
#define MAX_SHADER_SIZE 10240 // 10 Kb

GLuint g_shaderProgram;
GLuint g_vbo;
GLuint g_ibo;
GLint g_vertexAttribute;
GLint g_colorAttribute;
GLint g_mvpUniform;

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);   
    
    // Make shader prgram active
    glUseProgram(g_shaderProgram);
    
    // Set MVP matrix to shader program
    const GLfloat mvp[] =
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    glUniformMatrix4fv(g_mvpUniform, 1, GL_FALSE, mvp);
    
    // Make VBO active
    glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
    
    // Make IBO active
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ibo);
    
    // Set vertex attrib arrays to shader program
    glVertexAttribPointer(g_vertexAttribute, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);
    glVertexAttribPointer(g_colorAttribute, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));
    
    // Draw VBO with IBO
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
}

GLuint loadShader(const char *fileName, GLenum type)
{
    GLuint result;
    GLint compiled;
    FILE *pFile;

    char buffer[MAX_SHADER_SIZE];
    memset(buffer, 0, MAX_SHADER_SIZE);
    
    const GLchar *source[1];

    pFile = fopen(fileName, "rb");
    if (!pFile)
    {
        printf("Cannot open file <%s>\n", fileName);
        exit(-1);
    }
    
    fread(buffer, 1, MAX_SHADER_SIZE, pFile);
    
    fclose(pFile);
    
    // Create shader of given type (vertex or fragment)
    result = glCreateShader(type);
    // Load the source code into shader
    source[0] = buffer;
    glShaderSource(result, 1, source, NULL);
    // Compile shader
    glCompileShader(result);
    // Check compilation status
    glGetShaderiv(result, GL_COMPILE_STATUS, &compiled);
    
    if (!compiled)
    {
        // We have compilation errors, display them
        GLint infoLen = 0;
        glGetShaderiv(result, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 0)
        {
            char infoLog[infoLen];
            glGetShaderInfoLog(result, infoLen, NULL, infoLog);
            printf("Shader compilation error: %s", infoLog);
        }
        // Kill shader, it won't work anyway
        glDeleteShader(result);
        // Let's define error as -1 casted to handle
        return (GLuint)(-1);
    }
    
    return result;
}

GLuint loadShaderProgram(const char *vertexShaderName, const char *fragmentShaderName)
{
    GLuint result;
    GLint linked;
    
    // Load shaders
    GLuint vertexShader = loadShader(vertexShaderName, GL_VERTEX_SHADER);
    if (vertexShader == (GLuint)(-1))
        return (GLuint)(-1);
    GLuint fragmentShader = loadShader(fragmentShaderName, GL_FRAGMENT_SHADER);
    if (vertexShader == (GLuint)(-1))
        return (GLuint)(-1);
        
    // Create shader program
    result = glCreateProgram();
    
    // Attach shaders to program
    glAttachShader(result, vertexShader);
    glAttachShader(result, fragmentShader);
    
    // Link shader program
    glLinkProgram(result);
    
    // Chack linking status
    glGetProgramiv(result, GL_LINK_STATUS, &linked);
    
    if (!linked)
    {
        // We have linking errors, display them
        GLint infoLen = 0;
        glGetProgramiv(result, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 0)
        {
            char infoLog[infoLen];
            glGetProgramInfoLog(result, infoLen, NULL, infoLog);
            printf("Shader program linking error: %s", infoLog);
        }
        // Kill shader program, it won't work anyway
        glDeleteProgram(result);
        // Let's define error as -1 casted to handle
        return (GLuint)(-1);
    }
    
    return result;
}

void setUp()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    // Prepare data for VBO representing square, the values are X, Y, R, G, B
    const GLfloat vertices[] =
    {
        -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };
    
    // Create VBO
    glGenBuffers(1, &g_vbo);
    // Make created VBO active
    glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
    // Copy data to buffer
    glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    
    // Prepare data for IBO representing square
    const GLuint indices[] =
    {
        0, 1, 3,
        3, 1, 2
    };
    
    // Create IBO
    glGenBuffers(1, &g_ibo);
    // Make created IBO active
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ibo);
    // Copy data to buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);
    
    // Load shaders
    g_shaderProgram = loadShaderProgram("shader.vsh", "shader.fsh");
    
    // Get shader program attributes by names
    g_vertexAttribute = glGetAttribLocation(g_shaderProgram, "a_vertex");
    if (g_vertexAttribute == -1)
    {
        // Oops, we have no such attrib in shader program
        printf("a_vertex not found\n");
        exit(-1);
    }
    g_colorAttribute = glGetAttribLocation(g_shaderProgram, "a_color");
    if (g_colorAttribute == -1)
    {
        // Oops, we have no such attrib in shader program
        printf("a_color not found\n");
        exit(-1);
    }
    
    // Enable attrib arrays used in shader
    glEnableVertexAttribArray(g_vertexAttribute);
    glEnableVertexAttribArray(g_colorAttribute);
    
    // Get shader program uniforms by names
    g_mvpUniform = glGetUniformLocation(g_shaderProgram, "u_mvp");
    if (g_mvpUniform == -1)
    {
        // Oops, we have no such uniform in shader program
        printf("u_mvp not found\n");
        exit(-1);
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Test of shaders");
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    
    // Init GLEW to obtain OpenGL 3+ functions
    if (glewInit() != GLEW_OK)
    {
        // Problem: glewInit failed, something is seriously wrong
        printf("GLEW failed\n");
    }
    else if (glCreateShader == NULL)
    {
        // Problem: OpenGL 3.3+ not supported
        printf("OpenGL 3.3+ not supported\n");
    }
    
    setUp();
    
    glutMainLoop();
    
    return 0;
}

