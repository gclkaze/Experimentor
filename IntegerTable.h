#pragma once
#include <vector>
#include <iostream>
#include <memory>

class IntegerColumn{
    private:
    std::vector<int> m_Data;
    int m_ID;

    public:
    	IntegerColumn(int id)
        :m_ID(id)
        {
    	}

    	~IntegerColumn(){m_Data.clear();}

        int id() const {return m_ID;}

        void push(int e){
           m_Data.push_back(e);
        }
        int size() const {return m_Data.size(); }
        void dump(){
            int i = 0;
            std::cout << "Integer Table : Total Size <=>" <<m_Data.size() << std::endl;
/*            for(auto &row : m_Data ){
                std::cout << " <"<< m_ID << ">[" << i++ << "] => " << row << std::endl;
            }*/
        }

};

class IntegerTable{
    private:
	std::vector<std::unique_ptr<IntegerColumn>> m_Columns;
public:
	IntegerTable(int columns){
        for(int i = 0;i<columns;i++){
            m_Columns.push_back(std::unique_ptr<IntegerColumn>(new IntegerColumn(i)));
        }
	}
	~IntegerTable(){
        m_Columns.clear();
	}

    void addElementToColumn(int column, int element){
        //std::cout << column << " " << element << std::endl;
        m_Columns[column]->push(element);
    }

    void dump(){
        for(auto &column : m_Columns){
            column->dump();
        }
    }
};