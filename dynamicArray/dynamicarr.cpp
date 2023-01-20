#include "dynamicarr.h"

template <typename T>
Container<T>::Container(){
    this->size = 0;
    this->trueSize = 0;
    std::cout<< "Creating Container: ";
    this->arr = new (std::nothrow) T*[this->size];
    if(!this->arr) {
        std::cerr << "Failed!\n";
        throw(std::bad_alloc());
    }
    std::cout << "Succeded!\n";
    clear(0);
}

template <typename T>
Container<T>::Container(const unsigned long &size){
    this->size = size > 0 ? size : 0;
    this->trueSize = 0;
    std::cout << "Creating Container: ";
    this->arr = new (std::nothrow) T*[this->size];
    if(!this->arr) {
        std::cerr << "Failed!\n";
        throw(std::bad_alloc());
    }
    std::cout << "Succeded!\n";
    clear(0);
}

template <typename T>
Container<T>::Container(Container&& objToMove) {
    std::cout << "Moving container\n";
    this->size = objToMove.size;
    this->trueSize = objToMove.trueSize;
    this->arr = objToMove.arr;

    objToMove.size = 0;
    objToMove.trueSize = 0;
    objToMove.arr = nullptr;
    if(!this->arr) {
        std::cerr <<"Failed\n";
        throw("Could not move Constructor");
    }
    std::cout << "Succeded!\n";
}

template <typename T>
Container<T>::Container(const Container& objToCopy){
    std::cout << "Copying container: ";
    this->size = objToCopy.size;
    this->trueSize = objToCopy.trueSize;
    this->arr = new (std::nothrow) T*[this->size];
    if(!this->arr) {
        std::cerr << "Failed!\n";
        throw(std::bad_alloc());
    }
    std::cout << "Succeded!\n";
    for (size_t i = 0; i < this->trueSize; i++){
        this->arr[i] = new T(*objToCopy.arr[i]);
    }  
    clear(this->trueSize);
}

template <typename T>
Container<T>::~Container() {
    std::cout << "Destroying Container: Destroyed";
    if(this->arr == nullptr) {
        std::cout << " null";
    }
    else {
        for (size_t i = 0; i < this->trueSize; i++){ delete this->arr[i]; }
        delete[] this->arr;
    }
    std::cout << " object!\n";
}

template <typename T>
T& Container<T>::operator[](unsigned const long index) {
    if(index < 0 || index >= this->trueSize) {
        throw(std::out_of_range("Index out of range!"));
    }
    return *this->arr[index];
}

template <typename T>
void Container<T>::clear(unsigned int range) {
    for (size_t i = range; i < this->size; i++) { 
        this->arr[i] == nullptr; 
    }
}

template <typename T>
void Container<T>::enlarge(){
    std::cout << "Reached full capacity. Enlarging Container: ";
    this->size = this->size == 0 ? 1 : this->multiplayer * this->size;
    T** temp = new (std::nothrow) T*[this->size];
    if(!this->arr) {
        std::cerr << "Failed!\n";
        throw(std::bad_alloc());
    }
    std::cout << "Succeded!\n";
    for (size_t i = 0; i < this->trueSize; i++) {
        temp[i] = this->arr[i];
    }
    delete [] this->arr;
    this->arr = temp;
    clear(this->trueSize);
}

template <typename T>
const unsigned long& Container<T>::getTrueSize() {return this->trueSize;}

template <typename T>
const unsigned long& Container<T>::getSize() {return this->size;}

template <typename T>
void Container<T>::push(const T& elment) {
    if(this->trueSize >= this->size) { enlarge(); }
    this->arr[this->trueSize++] = new T(elment);
}

template <typename T>
void Container<T>::remove(long index) {
    if(index > this->size) { throw(std::out_of_range("Index out of range")); }
    
    delete this->arr[index];
    for (size_t i = index; i < this->trueSize; i++) {
        this->arr[i] = this->arr[i + 1];
    }
    this->arr[this->trueSize--] = nullptr;
}

template <typename T>
void Container<T>::insert(unsigned long index, T element) {
    if(index > this->trueSize) { throw(std::out_of_range("Index out of range")); }
    if(this->trueSize >= this->size) { enlarge(); }
    for (size_t i = this->trueSize; i > index - 1; i--) {
        this->arr[i + 1] = this->arr[i];
    }
    this->trueSize++;

    this->arr[index] = new T(element);
}

template <typename T>
void Container<T>::sort() {
    int i, j;
    T* ptr_;
    for(i = 0; i < this->trueSize - 1; i++) {
        j = i + 1;
        ptr_ = this->arr[j];
        while(j != 0 && *this->arr[j-1] > *ptr_) {
            this->arr[j] = this->arr[j - 1];
            j-=1;
        }
        this->arr[j] = ptr_;
    }
}

template <typename T>
long Container<T>::find(T element) {
    for (size_t i = 0; i < this->trueSize; i++) {
        if(*arr[i] == element) {
            return i;
        }
    }
    return -1;
}

template class Container<int>;
template class Container<char>;
template class Container<float>;
template class Container<long>;