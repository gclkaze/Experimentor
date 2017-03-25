#include "Experimentor.h"
#include <functional>
#include "SequentialColumnPusher.h"
#include "ThreadedColumnPusher.h"

class DataInitializer: public IDataInitializer{
    std::vector<int>* m_Data;
    public:
        DataInitializer(int size){
            initializeData(size);
        }
        virtual ~DataInitializer(){}

        virtual bool initializeData(int size) override{
            m_Data = new std::vector<int>(size);
            for(int i = 0;i<size;i++){
                m_Data->at(i) = i;
            }
        };
        virtual int size() override{
            return m_Data->size();
        }

        std::vector<int>* getData(){
            return m_Data;
        }
};

int main(){
    int columns = 3;
    Experimentor exp(100000000, 10000000);
    exp.Execute( 
        [](int size){
            return std::unique_ptr<DataInitializer>(new DataInitializer(size));
        },

        [&]( IDataInitializer* _data){
            DataInitializer* data = dynamic_cast<DataInitializer*>(_data);
            ThreadedColumnPusher t;
            t.createTable( *(data->getData()) ,columns);
            if(t.ready()){ }
        },
        [&]( IDataInitializer* _data){
            DataInitializer* data = dynamic_cast<DataInitializer*>(_data);

            SequentialColumnPusher s;
            s.createTable(*(data->getData()) ,columns); 

    });
    return 0;
}
