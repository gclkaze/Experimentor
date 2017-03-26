#pragma once
#include <vector>
#include <string>

class IExperimentalMeasurement{
     public:
     	virtual ~IExperimentalMeasurement(){}
     	virtual int get(int pos) = 0;
     	virtual void add(std::string&, int data) = 0;
     	virtual void calculate(std::vector<float> &storage) = 0;
     	virtual void getLabels(std::vector<std::string> &labels) = 0;
};
