#ifndef DEF_VECTOR_W
#define DEF_VECTOR_W

#include <stdlib.h>
#include <assert.h>
#include <iostream>

#define init_capacity 1
typedef unsigned WalkDataType;

class VECTOR_W{

public:
	int size_w;
	int capacity_w;
	WalkDataType *walks;

public:
	VECTOR_W(){
        // logstream(LOG_WARNING) << " create vector_w " << std::endl;
		capacity_w = init_capacity;
		size_w = 0;
		walks = (WalkDataType*)malloc(capacity_w*sizeof(WalkDataType));
	}

	~VECTOR_W(){
		free(walks);
	}

    WalkDataType& operator[] (int i){
        return walks[i];
    }

	void reserve(int newcapacity){
        // logstream(LOG_WARNING) << " newcapacity, capacity , size : " << newcapacity << " , "<< capacity_w << " , " << size_w << std::endl;
		if( newcapacity < size_w ){
            std::cout << "cannot reserve vector_w as capacity < size : " << newcapacity << " < " << size_w << std::endl;
            exit(-1);
        }
		capacity_w = newcapacity;
		walks = (WalkDataType*)realloc(walks, capacity_w*sizeof(WalkDataType));
	}

    void resize(int newsize){
        size_w = newsize;
        // if(size_w > capacity_w)
        //     reserve(2*size_w+1);
    }

	void push_back(WalkDataType w){
		if(size_w==capacity_w)
			reserve(2*capacity_w+1);
        else if(size_w > capacity_w) 
            std::cout << "size_w, capacity_w : " << size_w << " , " << capacity_w << std::endl;
        walks[size_w++] = w;
	}

    void truncate(int idx){
        assert(idx <= size_w);
        for( int i = idx; i < size_w; i++ ){
            walks[i-idx] = walks[i];
        }
        size_w = size_w - idx;
        reserve(size_w);
    }

    bool isEmpty(){
        return (size_w == 0);
    }

    int capacity() const{
        return capacity_w;
    }

    int size() const{
        return size_w;
    }
};

#endif