#include <stdio.h>
#include <iostream>
#include <string>

#include <emscripten/emscripten.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

EM_JS(int, canvas_get_width, (), { return canvas.width; });

EM_JS(int, canvas_get_height, (), { return canvas.height; });

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event* event = NULL;
SDL_Texture* circle = NULL;
SDL_Rect textureRect;
SDL_Rect positionRect;

bool quit = false;
bool falling = true;

int SCREEN_WIDTH = canvas_get_width();
int SCREEN_HEIGHT = canvas_get_height();

double dt = 1000;
double currentTime = SDL_GetTicks();
double accumulator = 0.0;

double velocity = 1;

SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* ren) {
    SDL_Texture* texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr) {
        std::cout << "Could not load texture" << std::endl;
        std::cout << IMG_GetError() << std::endl;
    }
    return texture;
}

void init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw("SDL failed to initialise");
    }

    window = SDL_CreateWindow(
        "checkers", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (window == nullptr) {
        SDL_Quit();
        throw("Failed to create window");
    }

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!SDL_RenderSetLogicalSize(renderer, canvas_get_width(), canvas_get_height())) {
        std::cout << SDL_GetError() << std::endl;
    }

    if (renderer == nullptr) {
        window = NULL;
        SDL_Quit();
        throw("Failed to create renderer");
    }

    event = new SDL_Event();

    circle = loadTexture("assets/man_black.png", renderer);
    textureRect = {0, 0, 64, 64};
    positionRect = {0, 0, 64, 64};
}

void input() {
    if (event->type == SDL_QUIT) {
        quit = true;
    }

    if (event->window.event == SDL_WINDOWEVENT_RESIZED) {
        SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
        std::cout << "The window was resized: " << SCREEN_WIDTH << std::endl;
    }

    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_KP_A:

                break;
            case SDLK_KP_D:

                break;
            default:
                break;
        }
    }
}

void update(double dt) {

    if (positionRect.y <= 0) {
        falling = true;
    };

    if (positionRect.y >= (480 - positionRect.h)) {
        falling = false;
    };

    if (falling) {
        positionRect.y += velocity * dt;
    } else {

        positionRect.y -= velocity * dt;
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, circle, &textureRect, &positionRect);
    SDL_RenderPresent(renderer);
}

void mainLoop() {
    double newTime = SDL_GetTicks();
    double frameTime =
        newTime -
        currentTime;  //Essentially stores how long the previous frame ran for in miliseconds

    //limits frame time to 100th of a second
    if (frameTime > 250) {
        std::cout << "UPPER BOUND HIT, LAG ENCOUNTERED" << std::endl;
        frameTime =
            250;  //Upper bound on the time between processing this loop. If physics simulation is slower than render calculation then the game could halt.
    }

    int canvasWidth = canvas_get_width();
    std::cout << "The canvas width was: " << canvasWidth << std::endl;

    currentTime = newTime;

    accumulator += frameTime;

    while (accumulator >= dt) {
        update(dt);
        accumulator -= dt;
    };

    render();

    while (SDL_PollEvent(event)) {
        input();
    }
}

int main(int, char**) {
    init();

    emscripten_set_main_loop(mainLoop, -1, 1);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    IMG_Quit();
    SDL_Quit();

    return 0;
}