#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <thread>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <thread>   //std::thread
#include <future>   //std::future std::promise
#include <utility>   //std::ref
#include <chrono>   //std::chrono::seconds
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <enet/enet.h>
#define LIMIT_INT (1<<30)
#define ZERO_FRECT  (SDL_FRect{0.f,0.f,0.f,0.f})
#define TICKRATE 128
#define SECOND_IN_MS 1000
#define LOG(text) \
    std::cout <<text << std::endl 
#define LOG_ERROR(text) \
    std::cerr << "Error in "<<__FILE__ << "(" << __LINE__ << "): " << text << std::endl 



void copyCString(char* source, const char* destination);

