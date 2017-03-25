#include "Experimentor.h"
#include <functional>
#include "SequentialColumnPusher.h"
#include "ThreadedColumnPusher.h"

std::vector<int>* createDataVector(int size){
    std::vector<int>* v = new std::vector<int>(size);
    for(int i = 0;i<size;i++){
        v->at(i) = i;
    }
    return v;
}

int main(){
    int columns = 3;
    Experimentor exp(100000000, 10000000);
    exp.Execute( 
        [](int size){
            return createDataVector(size);
        },

        [&]( std::vector<int>* v){

            ThreadedColumnPusher t;
            t.createTable(*v,columns);
            if(t.ready()){ }
        },
        [&]( std::vector<int>* v){

            SequentialColumnPusher s;
            s.createTable(*v,columns); 

    });
    return 0;
}
