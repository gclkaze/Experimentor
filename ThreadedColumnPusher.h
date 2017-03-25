#pragma once
#include "IDataStorage.h"
#include "IntegerTable.h"
#include "ThreadedColumn.h"

#include <atomic>
#include <mutex>
#include <condition_variable>


class ThreadedColumnPusher : public IDataStorage{
    private:
    	std::vector<std::unique_ptr<ThreadedColumn>> m_Columns;
        std::atomic<int> m_ReadyColumns;
        std::condition_variable m_Finished;
        int m_TotalColumns;

    public:
    	ThreadedColumnPusher()
        : m_ReadyColumns(0)
        , m_TotalColumns(0)
        { }
    	virtual ~ThreadedColumnPusher(){ m_Columns.clear(); }

        virtual void dataReady() override{
             m_ReadyColumns ++;
             //std::cout << "dataReady => " << m_ReadyColumns << std::endl;
             if(m_ReadyColumns == m_TotalColumns) m_Finished.notify_one();
        }

        virtual bool ready() override{   
            std::mutex m;
            std::unique_lock<std::mutex> lk(m);
            m_Finished.wait(lk, [&]{return m_ReadyColumns == m_TotalColumns;});
            return true;
        }

        virtual void dump() override{
            int cnt = 0;
            int total = 0;
            int amountPerColumn = 0;

            for(auto &c : m_Columns){
                amountPerColumn = c->size();
                std::cout << "Column #" << cnt++ << " => " << amountPerColumn << " elements" << std::endl;
                total += amountPerColumn;
                c->dump();
            }
        }

    	virtual bool createTable(std::vector<int> &v, int columns) override{
            m_TotalColumns = columns;
            for(int i = 0;i<m_TotalColumns;i++){
                m_Columns.push_back(std::unique_ptr<ThreadedColumn>(new ThreadedColumn(i,m_TotalColumns,this)));
            }

            for(int i = 0;i<m_TotalColumns;i++){
            	m_Columns[i]->populate(&v);          
            }
    	}
};