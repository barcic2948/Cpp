#ifndef DYNAMICARR_H
#define DYNAMICARR_H

#include <iostream>
#include <new>

template <typename T>
class Container {
    private:

        /**
         * @brief Pointer to the array containing pointers to the data
         * 
         */
        T** arr;

        /**
         * @brief Capacity of the array
         * 
         */
        unsigned long size;

        /**
         * @brief Number of elements stored inside the Container
         * 
         */
        unsigned long trueSize;

        /**
         * @brief Multiplayer for the enlarge() method. New capacity(size) of the array is the multiplicant of this variable
         * 
         */
        unsigned long multiplayer = 2;

        /**
         * @brief Alocates more space if maximum capacity(size) is reached
         * 
         */
        void enlarge();

        /**
         * @brief "Clears" alocated memory and prepares it for new data
         * 
         * @param range How much of the capacity to clear
         */
        void clear(unsigned int range);

    public:

        /**
         * @brief Construct a new Container object. The size is set to 0
         * 
         */
        Container();

        /**
         * @brief Construct a new Container object. Size is dependant on the parameter
         * 
         * @param size Parameter which sets the Capacity(size) of new Container
         */
        Container(const unsigned long &size);

        /**
         * @brief Copy Constructor
         * 
         * @param objToCopy object to copy
         */
        Container(const Container& objToCopy);

        /**
         * @brief Move Constructor
         * 
         * @param objToMove object to move
         */
        Container(Container&& objToMove);

        /**
         * @brief Destroy the Container object
         * 
         */
        ~Container();

        /**
         * @brief Typical [] operator for class
         * 
         * @param index index of the element that sholud be accesed
         * @return T& 
         */
        T& operator[](unsigned const long index);

        /**
         * @brief Get the True Size varible
         * 
         * @return const unsigned& 
         */
        const unsigned long& getTrueSize();

        /**
         * @brief Get the Size vairable
         * 
         * @return const unsigned& 
         */
        const unsigned long& getSize();

        /**
         * @brief Push new element to the back of the Container
         * 
         * @param elment element to push
         */
        void push(const T& elment);

        /**
         * @brief Removes element from the Container
         * 
         * @param index index of the element that needs to be removed
         */
        void remove(long index);

        /**
         * @brief Inserts element on the chosen position
         * 
         * @param index position to insert
         * @param element element to insert
         */
        void insert(unsigned long index, T element);

        /**
         * @brief Finds element in Container. If not found returns -1
         * 
         * @param element Element to find
         * @return long Returns the index of the element
         */
        long find(T element);

        /**
         * @brief Sorts the Container
         * 
         */
        void sort();

        /**
         * @brief Custom iterator for the function: Based on https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
         * 
         */
        struct Iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = T*;
            using pointer = T**;
            using reference = T*&;
            Iterator(pointer ptr) : m_ptr(ptr) {}
            reference operator*() const { return *m_ptr; }
            pointer operator->() { return m_ptr; }
            Iterator& operator++() { m_ptr++; return *this; }
            Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

            friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

        private:
            pointer m_ptr;
        };

        Iterator begin() { return Iterator(&arr[0]); }
        Iterator end() { return Iterator(&arr[this->trueSize]); }
        
};

#endif