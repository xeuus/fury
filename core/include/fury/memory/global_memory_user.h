//
// Created by aryan on 3/20/20.
//

#ifndef GAME_GLOBAL_MEMORY_USER_H
#define GAME_GLOBAL_MEMORY_USER_H

#include "memory_manager.h"

class GlobalMemoryUser {
private:
    MemoryManager *ECS_MEMORY_MANAGER{};

public:
    virtual inline const void *allocate(size_t memSize, const char *user) = 0;
    virtual inline void free(void *pMem) = 0;
};

#endif