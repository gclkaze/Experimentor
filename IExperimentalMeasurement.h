#pragma once

class IExperimentalMeasurement{
     public:
     	virtual ~IExperimentalMeasurement(){}
     	virtual int get(int pos) = 0;
     	virtual void add(int data) = 0;
};
