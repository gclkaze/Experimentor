#pragma once
#include "IExperimentalMeasurement.h"
#include <stdexcept>

class ExperimentalMeasurement : public IExperimentalMeasurement{
private:
	int m_T1,m_T2;
	std::vector<std::string> m_Labels;
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

    virtual void calculate(std::vector<float> &storage) override{            
        if( get(1)){
            storage.push_back((float)((float)get(0) / get(1))) ;
            std::cout << (float)((float) get(0) / get(1) ) << std::endl;
        }
    }

    virtual void add(std::string& label, int data) override{
        if(m_T1 == -1) {
        	m_T1 = data;
        	m_Labels.push_back(label);
        	return;
        }

       if(m_T2 == -1) {
        	m_T2 = data;
        	m_Labels.push_back(label);
        	return;
        }
    }

    virtual void getLabels(std::vector<std::string> &labels) override{
	     if(m_Labels.size() == 2){
	     	labels.push_back(m_Labels[0]);
	     	labels.push_back(m_Labels[1]);
	     	return;
	     }
    }
};