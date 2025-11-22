#include "OpenGL.hpp"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR)
        ;
}

bool GLCheckError(const char *functionName, const char *fileName,
                  int lineNumber) {
    while (GLenum error = glGetError()) {
        cout << "Opengl Error: " << error << " -> " << functionName << " -> "
             << fileName << " -> " << lineNumber << endl;
        return true;
    }
    return false;
}
