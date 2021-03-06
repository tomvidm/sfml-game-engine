#ifndef POOL_H
#define POOL_H

#include <list>

namespace engine
{
    typedef unsigned int uint;

    const uint TOTALLY_UNUSED   = 0;
    const uint HAS_BEEN_USED    = 1 << 0;
    const uint ACTIVE           = 1 << 1;

    // The Pool class is a template class that preallocates a fixed size 
    // array of ObjectType on the stack. One application can be to store
    // objects that will have a very short lifetime resulting in rapid creation
    // and deletion. Using a standard vector would lead to O(N) time complexity
    // for deletion, but this Pool class will lead to constant time complexity.
    // In addition to the fixed array, a linked list containing indexes for 
    // "deleted" objects is stored. therefore, when creating a new object,
    // the Pool will always allocate the object to the first element of the
    // linked list of unused indexes.

    template <class ObjectType, uint POOL_SIZE>
    class Pool
    {
    public:
        typedef std::list<uint>::iterator ListIterator;
        Pool();

        inline uint getPoolSize() const { return poolSize_; }
        inline uint getNumObjects() const { return numObjects_; }
        inline uint getFirstFreeIndex() const { return firstFreeObject_; }

        uint activateObject();
        void pushObject(ObjectType obj);
        
        uint getFirstAvailableIndex(uint id = 0) const;

        void deactivateObject(uint id);
        void freeAll();

        void setState(uint id, uint state);
        void addState(uint id, uint state);
        void subState(uint id, uint state);
        void toggleState(uint id, uint state);
        uint getState(uint id) const;

        inline ObjectType& get(uint id) { return objectPool_[id]; }
        
    private:
        uint poolSize_ = POOL_SIZE;
        uint numObjects_ = 0;
        uint firstFreeObject_ = 0;

        uint objectPoolStates_[POOL_SIZE];
        ObjectType objectPool_[POOL_SIZE];
        std::list<uint> freeList_;
    };

    template <class ObjectType, uint POOL_SIZE>
    Pool<ObjectType, POOL_SIZE>::Pool()
    {
        freeAll();
    }

    // This method is named ActivateObject, but it is misleading.
    // It simply looks for a free index, sets the bitmask to ACTIVE
    // and returns said index.

    template <class ObjectType, uint POOL_SIZE>
    uint Pool<ObjectType, POOL_SIZE>::activateObject()
    {
        if (!freeList_.empty())
        {
            uint index = freeList_.front();
            objectPoolStates_[index] |= ACTIVE;
            freeList_.pop_front();
            numObjects_ += 1;
            return index;

        }
        else if (numObjects_ < poolSize_)
        {
            objectPoolStates_[firstFreeObject_] = ACTIVE | HAS_BEEN_USED;
            numObjects_ += 1;
            return firstFreeObject_++;
        }
        else
        {
            return -1; // No more space
        }
    }

    // TThis method copies the contents of the input object to the index
    // returned by activateObject().

    template <class ObjectType, uint POOL_SIZE>
    void Pool<ObjectType, POOL_SIZE>::pushObject(ObjectType obj)
    {
        objectPool_[activateObject()] = obj;
    }

    /*
        given an index, first the first index which is free and also bigger than the parameter id.
    */
    template <class ObjectType, uint POOL_SIZE>
    uint Pool<ObjectType, POOL_SIZE>::getFirstAvailableIndex(uint id = 0) const
    {
        
        if (freeList_.empty())
        {
            return firstFreeObject_;
        }
        else if (freeList_.back() < id)
        {
            return firstFreeObject_;
        }
        else
        {
            for (auto id_iter : freeList_)
            {
                if (id_iter > id)
                {
                    return id_iter;
                }
            }
            return firstFreeObject_;
        }
    }

    // TODO: Try to modify how the linked list is pushed onto, to always ensure
    // that new objects are set to the first available "hole". (OR: In order. Heap?)
    template <class ObjectType, uint POOL_SIZE>
    void Pool<ObjectType, POOL_SIZE>::deactivateObject(uint id)
    {
        if (objectPoolStates_[id] & ACTIVE) // If a number is >0, then true
        {
            objectPoolStates_[id] &= ~ACTIVE; // Switch of ACTIVE bit
            freeList_.push_back(id);
            numObjects_ -= 1;
        }
        freeList_.sort();
    }

    template <class ObjectType, uint POOL_SIZE>
    void Pool<ObjectType, POOL_SIZE>::setState(uint id, uint state)
    {
        objectPoolStates_[id] = state;
    }

    template <class ObjectType, uint POOL_SIZE>
    void Pool<ObjectType, POOL_SIZE>::addState(uint id, uint state)
    {
        objectPoolStates_[id] |= state;
    }

    template <class ObjectType, uint POOL_SIZE>
    void Pool<ObjectType, POOL_SIZE>::subState(uint id, uint state)
    {
        objectPoolStates_[id] &= ~state;
    }

    template <class ObjectType, uint POOL_SIZE>
    void Pool<ObjectType, POOL_SIZE>::toggleState(uint id, uint state)
    {
        objectPoolStates_[id] ^= state;
    }

    template <class ObjectType, uint POOL_SIZE>
    uint Pool<ObjectType, POOL_SIZE>::getState(uint id) const
    {
        return objectPoolStates_[id];
    }


    template <class ObjectType, uint POOL_SIZE>
    void Pool<ObjectType, POOL_SIZE>::freeAll()
    {
        for (uint i = 0; i < poolSize_; i++)
        {
            objectPoolStates_[i] = TOTALLY_UNUSED;
            freeList_.clear();
        }
    }
}

#endif