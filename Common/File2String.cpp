#ifdef __APPLE__
#include <GLEW/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include <fstream>
#include <iostream>

#include "File2String.h"

using namespace std;


string FileToString (char* Shader) {
    string ShaderCode = "";

    ifstream ShaderStream(Shader, std::ios::in);

    if(ShaderStream.is_open()){
        string Line = "";
        while(getline(ShaderStream, Line))
        ShaderCode += "\n" + Line;
        ShaderStream.close();
    }else{
        printf("Impossible to open. Are you in the right directory ? Don't forget to read the FAQ !\n");
        return 0;
    }
    return ShaderCode;
}
