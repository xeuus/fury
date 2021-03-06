//
// Created by aryan on 3/20/20.
//

#include "fury/memory/linear_allocator.h"

LinearAllocator::LinearAllocator(size memSize, const void* mem) :
        Allocator(memSize, mem)
{}

LinearAllocator::~LinearAllocator()
{
    this->clear();
}

void* LinearAllocator::allocate(size memSize, u8 alignment)
{
    assert(memSize > 0 && "allocate called with memSize = 0.");

    union
    {
        void* asVoidPtr;
        uptr asUptr;
    };

    asVoidPtr = (void*)this->m_MemoryFirstAddress;

    // current address
    asUptr += this->m_MemoryUsed;

    // get adjustment to align address
    u8 adjustment = getAdjustment(asVoidPtr, alignment);

    // check if there is enough memory available
    if (this->m_MemoryUsed + memSize + adjustment > this->m_MemorySize)
    {
        // not enough memory
        return nullptr;
    }

    // determine aligned memory address
    asUptr += adjustment;

    // update book keeping
    this->m_MemoryUsed += memSize + adjustment;
    this->m_MemoryAllocations++;

    // return aligned memory address
    return asVoidPtr;
}

void LinearAllocator::free(void* mem)
{
    assert(false && "Lineaer allocators do not support free operations. Use clear instead.");
}

void LinearAllocator::clear()
{
    // simply reset memory
    this->m_MemoryUsed = 0;
    this->m_MemoryAllocations = 0;
}
