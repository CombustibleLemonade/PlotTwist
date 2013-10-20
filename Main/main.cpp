#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#ifdef __APPLE__
#include <GLEW/glew.h>
#include <GLUT/glut.h>
#include <OpenAL/alut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <AL/al.h>
#include <AL/alc.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "File2String.h"
#include "CreateShaderProgram.h"

using namespace std;

GLuint program;
GLint attribute_coord2d, XUL, YUL;

int fullScreen = 0;

//information for buffering mouse cursor location
int oldX = 0;
int oldY = 0;
int Xvalue = 960;
int Yvalue = 540;
float xToShader = 0.0;
float yToShader = 0.0;

//information for OpenAL
ALCdevice *device;

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

    device = alcOpenDevice(NULL);
    return 1;
}

void keyboard (unsigned char button, int x, int y)
{
    if (button == 27) {
        if (!fullScreen) {
            glutFullScreen();
            fullScreen = 1;
        }
        else {
            glutReshapeWindow(1600,900);
            fullScreen = 0;
        }
    }
    cout << int(button) << endl;
}

void motion (int x, int y)
{
    XUL = glGetUniformLocation(program, "X");
    YUL = glGetUniformLocation(program, "Y");

    Xvalue += x - oldX;
    Yvalue += y - oldY;

    xToShader = Xvalue;
    xToShader -= 960;
    xToShader /= 1000;

    yToShader = Yvalue;
    yToShader -= 540;
    yToShader /= 1000;

    glUniform1f(XUL, xToShader);
    glUniform1f(YUL, yToShader);
    glutPostRedisplay();

    oldX = x;
    oldY = y;
}

void mouse (int button, int state, int x, int y) {
    oldX = x;
    oldY = y;
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

void onIdle() {
    float move = sinf(glutGet(GLUT_ELAPSED_TIME) / 1000.0 * (2*3.14) / 5); // -1<->+1 every 5 seconds
    float angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 45;  // 45° per second
    glm::vec3 axis_z(0, 0, 1);
    glm::mat4 m_transform = glm::translate(glm::mat4(1.0f), glm::vec3(move, 0.0, 0.0)) * glm::rotate(glm::mat4(1.0f), angle, axis_z);

    glm::vec4 testVector = m_transform[0];
    cout << "x:" << testVector[0]<< " y:"<< testVector[1]<< " z:"<< testVector[2]<< endl;
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
        glutMotionFunc(motion);
        glutKeyboardFunc(keyboard);
        glutMouseFunc(mouse);
        glutDisplayFunc(onDisplay);
        glutIdleFunc(onIdle);

        glutMainLoop();
        return 1;
    }
    free_resources();
    return 0;
}
