#pragma once
#include "timer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

static const size_t hImg = 422;
static const size_t wImg = 149;
static const size_t winWithMs = wImg * 12;
static const size_t winWithoutMs = wImg * 8;

class Clock {
private:
    const size_t screenWidth_;
    const size_t screenHeight_;
    SDL_Window* window_;
    SDL_Surface *image_;
    SDL_Renderer* renderer_;

    void drawDig(const std::string t, int& w, bool semicolon = false, bool dot = false);
    int loadSurface(const std::string& path);

public:
    Clock(size_t width, size_t height);
    ~Clock();
    void run(ATimer& t);
};