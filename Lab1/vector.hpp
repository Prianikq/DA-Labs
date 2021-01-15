#pragma once
#include <cassert>
namespace NMyStd {
    template<class T>
    class TVector {
        public :
            void Assert(const T& elem);
            TVector();
            TVector(const unsigned int newSize);
            TVector(const unsigned int newSize, const T& elem);
            ~TVector();
            void PushBack(const T& elem);
            unsigned int GetSize();
            T& operator[](const unsigned int index);
            TVector<T>& operator=(const TVector<T>& vector);
        private :
            unsigned int Size;
            unsigned int Capacity;
            T* Data;
    };
    template<class T>
    void TVector<T>::Assert(const T& elem) {
        for (int i = 0; i < Size; ++i) {
	        Data[i] = elem;
	    }
    }
    template<class T>
    TVector<T>::TVector() {
	    Size = 0;
	    Capacity = 0;
	    Data = nullptr;
    }
    template<class T>
    TVector<T>::TVector(const unsigned int newSize) {
	    Size = newSize;
	    Capacity = Size * 2;
	    Data = new T[Capacity];
	    Assert(T());
    }
    template<class T>
    TVector<T>::TVector(const unsigned int newSize, const T& elem) {
	    Size = newSize;
	    Capacity = Size*2;
	    Data = new T[Capacity];
	    Assert(elem);
    }
    template<class T>
        TVector<T>::~TVector() {
	    delete[] Data;
    }
    template<class T>
    void TVector<T>::PushBack(const T& elem) {
        if (Data == nullptr) {
	        Capacity = 2;
	        Data = new T[Capacity];
        }
        if (Size == Capacity) {
	        Capacity *= 2;
	        T* buffer = new T[Capacity];
	        for (int i = 0; i < Size; ++i) {
	            buffer[i] = Data[i];
	        }
	        delete[] Data;
	        Data = buffer;
        }
        Data[Size++] = elem;
    }
    template<class T>
    unsigned int TVector<T>::GetSize() {
        return Size;
    }
    template<class T>
    T& TVector<T>::operator[](const unsigned int index) {
	    assert(index < Size);
	    return Data[index];
    }
    template<class T>
    TVector<T>& TVector<T>::operator=(const TVector<T>& vector) {
	    Size = vector.Size;
	    Capacity = vector.Capacity;
	    delete[] Data;
	    Data = new T[Capacity];
	    for (int i = 0; i < Size; ++i) {
	        Data[i] = vector.Data[i];
	    }
	    return *this;
    }
}
