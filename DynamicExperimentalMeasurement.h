#pragma once
#include "IExperimentalMeasurement.h"
#include <stdexcept>
#include <vector>
#include <iostream>
#include <algorithm>    // std::reverse

class DynamicExperimentalMeasurement : public IExperimentalMeasurement{
    private:
	std::vector<int> m_Data;
	std::vector<std::string> m_Labels;
    public:
    	DynamicExperimentalMeasurement(){}
    	virtual ~DynamicExperimentalMeasurement(){}
        virtual int get(int pos) override{
           if(pos < 0 || pos > m_Data.size()){
           	throw std::runtime_error("There are no data in pos "+std::to_string(pos));
           }
           return m_Data[pos];
        }

        virtual void add(std::string& label, int data) override{
            m_Data.push_back(data);
            m_Labels.push_back(label);
        }

        virtual void calculate(std::vector<float> &storage) override{            
            if( get(1)){
                storage.push_back((float)((float)get(0) / get(1))) ;
                std::cout << (float)((float) get(0) / get(1) ) << std::endl;
            }
        }

        void getLabels(std::vector<std::string> &labels){
        	for(auto &label: m_Labels){
        		labels.push_back(label);
        	}

        	std::reverse(labels.begin(),labels.end()); 
        }

};