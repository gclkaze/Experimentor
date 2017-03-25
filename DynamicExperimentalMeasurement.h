#pragma once
#include "IExperimentalMeasurement.h"
#include <stdexcept>
#include <vector>

class DynamicExperimentalMeasurement : public IExperimentalMeasurement{
    private:
	std::vector<int> m_Data;
    public:
    	DynamicExperimentalMeasurement(){}
    	virtual ~DynamicExperimentalMeasurement(){}
        virtual int get(int pos) override{
           if(pos < 0 || pos > m_Data.size()){
           	throw std::runtime_error("There are no data in pos "+std::to_string(pos));
           }
           return m_Data[pos];
        }

        virtual void add(int data) override{
            m_Data.push_back(data);
        }
};