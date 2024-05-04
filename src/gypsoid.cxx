#include <SDL.h>
#include <SDL_opengl.h>
#include <cmath>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void drawTorus(float radius1, float radius2, int numc, int numt) {
  float TWO_PI = 2 * 3.14159265358979323846;
  float alpha, beta;
  float x, y, z;

  for (int i = 0; i < numc; i++) {
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= numt; j++) {
      for (int k = 0; k < 2; k++) {
        alpha = (i + k) % numc * TWO_PI / numc;
        beta = j % numt * TWO_PI / numt;
        x = (radius1 + radius2 * cos(beta)) * cos(alpha);
        y = (radius1 + radius2 * cos(beta)) * sin(alpha);
        z = radius2 * sin(beta);
        glVertex3f(x, y, z);
      }
    }
    glEnd();
  }
}

void render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -5.0f);
  glRotatef(SDL_GetTicks() * 0.01f, 1.0f, 0.0f, 0.0f);
  glRotatef(SDL_GetTicks() * 0.01f, 0.0f, 1.0f, 0.0f);
  glRotatef(SDL_GetTicks() * 0.01f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  drawTorus(1.0f, 0.3f, 20, 20);
  SDL_GL_SwapWindow(window);
}

int main(int argc, char* argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("Spinning Torus",
    SCREEN_WIDTH, SCREEN_HEIGHT,
    SDL_WINDOW_OPENGL | 0);
  SDL_GLContext context = SDL_GL_CreateContext(window);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);

  bool running = true;
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = false;
    }
    render();
  }

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
