#pragma once

class c_custom_allocator {
public:
    c_custom_allocator(size_t size) : totalSize(size), freeList(nullptr) {
        // Allocate the memory pool
        memoryPool = new char[size];
        // Initialize the free list with the entire pool
        freeList = reinterpret_cast<MemoryBlock*>(memoryPool);
        freeList->size = size - sizeof(MemoryBlock);
        freeList->next = nullptr;
    }

    ~c_custom_allocator() {
        delete[] memoryPool;
    }

    void* allocate(size_t size) {
        MemoryBlock* current = freeList;
        MemoryBlock* previous = nullptr;

        while (current) {
            if (current->size >= size) {
                if (current->size > size + sizeof(MemoryBlock)) {
                    // Split the block
                    MemoryBlock* newBlock = reinterpret_cast<MemoryBlock*>(
                        reinterpret_cast<char*>(current) + sizeof(MemoryBlock) + size);
                    newBlock->size = current->size - size - sizeof(MemoryBlock);
                    newBlock->next = current->next;
                    current->size = size;
                    current->next = newBlock;
                }
                if (previous) {
                    previous->next = current->next;
                } else {
                    freeList = current->next;
                }
                return reinterpret_cast<void*>(reinterpret_cast<char*>(current) + sizeof(MemoryBlock));
            }
            previous = current;
            current = current->next;
        }

        // No suitable block found
        return nullptr;
    }

    void deallocate(void* ptr) {
        if (!ptr) return;

        // Get the block to free
        MemoryBlock* block = reinterpret_cast<MemoryBlock*>(reinterpret_cast<char*>(ptr) - sizeof(MemoryBlock));
        block->next = freeList;
        freeList = block;

        // Coalesce adjacent free blocks (optional for optimization)
        coalesce();
    }

    void displayMemory() {
        std::cout << "Free list:\n";
        MemoryBlock* current = freeList;
        while (current) {
            std::cout << "Block at " << current << ", size: " << current->size << "\n";
            current = current->next;
        }
    }

private:
    struct MemoryBlock {
        size_t size;
        MemoryBlock* next;
    };

    char* memoryPool;
    size_t totalSize;
    MemoryBlock* freeList;

    void coalesce() {
        MemoryBlock* current = freeList;

        while (current && current->next) {
            if (reinterpret_cast<char*>(current) + sizeof(MemoryBlock) + current->size ==
                reinterpret_cast<char*>(current->next)) {
                current->size += sizeof(MemoryBlock) + current->next->size;
                current->next = current->next->next;
            } else {
                current = current->next;
            }
        }
    }
};