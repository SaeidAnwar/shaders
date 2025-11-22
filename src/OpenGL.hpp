#pragma once

#include <GL/glew.h>
#include <cstdlib>
#include <iostream>
#include <vector>

#define ASSERT(x)                                                              \
    if (x)                                                                     \
        exit(1);
#define GLCall(x)                                                              \
    GLClearError();                                                            \
    x;                                                                         \
    ASSERT(GLCheckError(#x, __FILE__, __LINE__))

using namespace std;

void GLClearError();

bool GLCheckError(const char *functionName, const char *fileName,
                  int lineNumber);
