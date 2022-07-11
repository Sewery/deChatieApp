#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <cstdlib>
#include <climits>
#include <thread>   //std::thread
#include <future>   //std::future std::promise
#include <utility>   //std::ref
#include <chrono>   //std::chrono::seconds
#include <thread>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "SDL_thread.h"
#include <enet/enet.h>
#define LIMIT_INT (1<<30)
#define ZERO_FRECT  (SDL_FRect{0.f,0.f,0.f,0.f})
std::time_t*  getTime();


#define LOG(text) \
    std::cout <<std::ctime(getTime())<<"Log: " << text << std::endl 
#define LOG_ERROR(text) \
    std::cerr << "Error in "<<__FILE__ << "(" << __LINE__ << "): " << text << std::endl 

#pragma warning(disable : 4996)//
void copyCString(char* destination, const  char* source);
inline bool operator==(const SDL_FRect& lhs, const SDL_FRect& rhs) { return lhs.x== rhs.x &&  lhs.y == rhs.y &&  lhs.w == rhs.w &&  lhs.h == rhs.h; }
