#pragma once
#include "IExperimentalMeasurement.h"
#include <stdexcept>

class ExperimentalMeasurement : public IExperimentalMeasurement{
private:
	int m_T1,m_T2;
public:
	ExperimentalMeasurement()
	:m_T1(-1)
	,m_T2(-1)
	{}

	virtual ~ExperimentalMeasurement(){}

    virtual int get(int pos) override{
       if(pos < 0 || pos > 2){
       	throw std::runtime_error("There are no data in pos "+std::to_string(pos));
       }
       switch(pos){
       	case 0: return m_T1;
       	case 1: return m_T2;
       }
    }

    virtual void add(int data) override{
        if(m_T1 == -1) {
        	m_T1 = data;
        	return;
        }

       if(m_T2 == -1) {
        	m_T2 = data;
        	return;
        }
    }
};