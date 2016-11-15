#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
#include <stdbool.h>

int
main()
{
    SDL_Window *window;
    SDL_GLContext glcontext;
    bool running = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    
    printf("Initialized SDL successfully\n");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    window = SDL_CreateWindow("Test",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        480, 272, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

    if (!window) {
        fprintf(stderr, "Failed to create OpenGL window: %s\n", SDL_GetError());
        exit(1);
    }

    glcontext = SDL_GL_CreateContext(window);

    if (!glcontext) {
        fprintf(stderr, "Failed to create OpenGL context: %s\n", SDL_GetError());
        exit(1);
    }

    printf("OpenGL vendor: %s\n", glGetString(GL_VENDOR));
    printf("OpenGL renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
    printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                case SDL_KEYDOWN:
                    running = false;
                    break;
            }
        }
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
