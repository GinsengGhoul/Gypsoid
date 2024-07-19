#include <SDL3/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
using namespace std;

SDL_Window* window = 0;

int main(int argc, char* args[]){
  // display 0 is primary display
  int windowPosX = SDL_WINDOWPOS_CENTERED_DISPLAY(0);
  int windowPosY = SDL_WINDOWPOS_CENTERED_DISPLAY(0);
  int width = 800;
  int height = 600;
  const char* title = "wowza it's a title";
  // or the flags together
  int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  if(SDL_Init(SDL_INIT_EVENTS) >= 0){
    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_CENTERED_DISPLAY(0));
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_CENTERED_DISPLAY(0));
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, width);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, height);
    SDL_SetNumberProperty(props, "flags", flags);

    window = SDL_CreateWindowWithProperties(props);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    float red = 0.0f;
    float blu = 0.0f;
    float grn = 0.0f;
    int frame{};

    bool isRunning = true;
    while(isRunning){

      red += 0.1f;
      if(red > 1.1f){
        red = 0.0f;
      }
      glClearColor(red, blu, grn, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      SDL_GL_SwapWindow(window);
      SDL_Event event;
      while (SDL_PollEvent(&event)){
        if(event.type == SDL_EVENT_QUIT){
          isRunning = false;
        }
      }
    }
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    return 0;

  }
  else {
    return 1;
  }
}

