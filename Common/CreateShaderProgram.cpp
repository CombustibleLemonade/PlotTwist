#ifdef __APPLE__
#include <GLEW/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include <string>
#include <fstream>
#include <iostream>


using namespace std;

#include "File2String.h"
#include "CreateShaderProgram.h"

/* GLuint program;

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){
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
}*/
