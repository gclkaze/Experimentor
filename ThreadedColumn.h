#pragma once
#include <thread>

class ThreadedColumn{
    private:
    	std::unique_ptr<IntegerColumn> m_Column;
    	int m_TotalColumns = 0;
    	std::vector<int> *m_Data = nullptr;
        int m_ID = 0;
        IDataStorage* m_Parent = nullptr;

        public:
    	ThreadedColumn(int id, int totalColumns, IDataStorage* parent)
        : m_TotalColumns(totalColumns)
        , m_ID(id)
        , m_Parent(parent)
    	{
            m_Column = std::unique_ptr<IntegerColumn>(new IntegerColumn(id));
    	}
        
        ~ThreadedColumn(){}
        int size() {return m_Column->size();}
        void addElementToColumn(){
        	if(!m_Data) return;

            int pos = m_ID; 
            while(pos < m_Data->size()){
            	m_Column->push(m_Data->at(pos));
                //std::cout << "<" << m_ID << ">[" << pos << "] =>" << m_Data->at(pos) << std::endl;
                pos += m_TotalColumns;
            }
            m_Parent->dataReady();
        }

    	bool populate(std::vector<int> *data){
            m_Data = data;

            std::thread t(&ThreadedColumn::addElementToColumn, this);
            //std::cout << "Starting thread!" <<std::endl;
            t.detach();
    	}

        void dump(){
            m_Column->dump();
        }
};