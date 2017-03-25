
#include <memory>
#include "IntegerTable.h"
#include "IDataStorage.h"

class SequentialColumnPusher : public IDataStorage{
    private:
    	std::unique_ptr<IntegerTable> m_Table;
        bool m_Done;
    public:
    	SequentialColumnPusher()
        :m_Done(false){}
    	virtual ~SequentialColumnPusher(){}

        virtual void dataReady() override{
            m_Done = true;
        }

        virtual bool ready() override{
            return m_Done;
        }

    	virtual bool createTable(std::vector<int> &v, int columns) override{
            if(!columns || v.empty()) return false;
            int size = v.size();
    		int currentColumn = 0;

            m_Table = std::unique_ptr<IntegerTable>(new IntegerTable( columns));
    		for(int i = 0;i<size;i++){
                m_Table->addElementToColumn(currentColumn++, v[i]);
                
                if(currentColumn == columns) currentColumn = 0;
    		}

            dataReady();
    	}

    	virtual void dump() override{
    		if(m_Table.get()){
                m_Table->dump();
    		}
    	}

};