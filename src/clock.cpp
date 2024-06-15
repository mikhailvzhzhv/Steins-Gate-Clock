#include "clock.h"

static const std::string PATH = "../images/";

Clock::Clock(size_t width, size_t height) : 
screenWidth_(width), screenHeight_(height),
window_(nullptr), image_(nullptr), renderer_(nullptr) {
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window_ = SDL_CreateWindow("Steins;Gate", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth_, screenHeight_, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window_) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_SetWindowBordered(window_, SDL_TRUE);

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) {
        std::cerr << "Can't create renderer_: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_SetRenderDrawColor(renderer_, 0x0, 0x0, 0x0, 0x0);
}

Clock::~Clock() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Clock::drawDig(const std::string digs, int& w, bool semicolon, bool dot) {  
    SDL_Rect rect;
    SDL_Texture* texture;
    std::vector<std::string> d;
    for (auto dig : digs) {
        d.push_back(std::string(sizeof(dig), dig));
    }
    if (semicolon) d.push_back("semicolon");
    if (dot) d.push_back("dot");
    for (auto pic : d) {
        if (loadSurface(PATH + pic + ".bmp")) {
            exit(1);
        }
        texture = SDL_CreateTextureFromSurface(renderer_, image_);
        rect = {w, 0, image_->w, image_->h};
        SDL_RenderCopy(renderer_, texture, nullptr, &rect);
        w += image_->w;

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(image_);
    }
}

int Clock::loadSurface(const std::string& path) {
    image_ = SDL_LoadBMP(path.c_str());
    if(!image_) {
        std::cerr << "Unable to load image_ " << path.c_str() << "\n" << "SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    return 0;
}

void Clock::run(ATimer& t) {
    const size_t ms = 100;
    SDL_Event event;
    bool quit = false;
    bool withMs = false;
    while (!quit) { 
        while ( SDL_PollEvent(&event) ) { 
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true; 
            }
            switch (event.key.keysym.sym) {
            case SDLK_w:
                SDL_SetWindowBordered(window_, SDL_TRUE);
                break;
            case SDLK_q:
                SDL_SetWindowBordered(window_, SDL_FALSE);
                break;
            case SDLK_m:
                SDL_SetWindowSize(window_, winWithMs, hImg);
                withMs = true;
                break;
            case SDLK_n:
                SDL_SetWindowSize(window_, winWithoutMs, hImg);
                withMs = false;
                break;
            default:
                break;
            }
        }
        int w = 0;
        SDL_Delay(ms);
        SDL_RenderClear(renderer_);
        drawDig(t.getHour(), w, true);
        drawDig(t.getMin(), w, true);
        if (withMs) {
            drawDig(t.getSec(), w, false, true);
            drawDig(t.getMs(), w);
        }
        else {
            drawDig(t.getSec(), w);
        }
        SDL_RenderPresent(renderer_);
    }
}