#include <iostream>
#include <stdio.h>
#include <string>

#ifdef __APPLE__
#include <GLEW/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include "File2String.h"
#include "CreateShaderProgram.h"

using namespace std;

GLuint program;
GLint attribute_coord2d, XUL, YUL;

int init_resources()
{
    GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char *vs_source = FileToString("VertexShader.vs").c_str();
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
    if (!compile_ok) {
        fprintf(stderr, "Error in vertex shader\n");
        return 0;
    }
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fs_source = FileToString("FragmentShader.fs").c_str();
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
    if (!compile_ok) {
        fprintf(stderr, "Error in fragment shader\n");
        return 0;
    }
    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
    if (!link_ok) {
        fprintf(stderr, "glLinkProgram:");
        return 0;
    }

    const char* attribute_name = "coord2d";
    attribute_coord2d = glGetAttribLocation(program, attribute_name);
    if (attribute_coord2d == -1) {
        fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
        return 0;
    }
    return 1;
}

void mouse (int button, int state, int x, int y)
{
    if (button == 0) {
        glutFullScreen();
    }
    if (button) {
        glutReshapeWindow(1600,900);
    }
}

void motion (int x, int y)
{
    XUL = glGetUniformLocation(program, "X");
    YUL = glGetUniformLocation(program, "Y");

    float xToShader = x;
    xToShader -= 960;
    xToShader /= 200;
    float yToShader = y;
    yToShader -= 540;
    yToShader /= 200;


    glUniform1f(XUL, xToShader);
    glutPostRedisplay();
    glUniform1f(YUL, yToShader);
    glutPostRedisplay();
}

void onDisplay()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(attribute_coord2d);
    GLfloat triangle_vertices[] = {
        -1.0, -1.0,
        -1.0, 1.0,
        1.0, 1.0,
        -1.0, -1.0,
        1.0, -1.0,
        1.0, 1.0
    };
    // Describe our vertices array to OpenGL (it can't guess its format automatically)
    glVertexAttribPointer(
                attribute_coord2d, // attribute
                2, // number of elements per vertex, here (x,y)
                GL_FLOAT, // the type of each element
                GL_FALSE, // take our values as-is
                0, // no extra data between each position
                triangle_vertices // pointer to the C array
                );
    // Push each element in buffer_vertices to the vertex shader
    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(attribute_coord2d);
    glutSwapBuffers();
}

void free_resources()
{
    glDeleteProgram(program);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(1600, 900);
    glutCreateWindow("PlotTwist");


    GLenum glew_status = glewInit();

    if (glew_status != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return 1;
    }
    if (init_resources()) {
        glutPassiveMotionFunc(motion);
        glutMotionFunc(motion);
        glutMouseFunc(mouse);
        glutDisplayFunc(onDisplay);
        glutMainLoop();
        return 1;
    }
    free_resources();
    return 0;
}
