//////////////////////////////////////////////////////////////////////////////
//
//  --- LoadShaders.c ---
//
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include "LoadShaders.h"

static const GLchar*
ReadShader( const char* filename )
{
    FILE* infile = fopen( filename, "rb" );
    if( !infile ) {
        return NULL;
    }

    fseek( infile, 0, SEEK_END );
    int len = ftell( infile );
    fseek( infile, 0, SEEK_SET);

    GLchar* source = (GLchar*)malloc(sizeof(GLchar) * (len + 1));

    fread( source, 1, len, infile );
    fclose( infile );

    source[len] = 0;

    return (const GLchar*)source;
}

GLuint
LoadShaders(ShaderInfo* shaders)
{
    if ( shaders == NULL ) { return 0; }

    GLuint program = glCreateProgram();

    ShaderInfo* entry = shaders;
    while( entry->type != GL_NONE ) {
        GLuint shader = glCreateShader( entry->type );

        entry->shader = shader;

        const GLchar* source = ReadShader( entry->filename );
        if( source == NULL ) {
            for ( entry = shaders; entry->type != GL_NONE; ++entry) {
                glDeleteShader( entry->shader );
                entry->shader = 0;
            }

            return 0;
        }

        glShaderSource( shader, 1, &source, NULL );
        free((void *)source);

        glCompileShader( shader );

        GLint compiled;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
        if( !compiled ) {
            return 0;
        }

        glAttachShader(program, shader );

        ++entry;
    }

    glLinkProgram( program );

    GLint linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if( !linked ) {
        for(entry = shaders; entry->type != GL_NONE; ++entry ) {
            glDeleteShader( entry->shader );
            entry->shader = 0;
        }

        return 0;
    }

    return program;
}