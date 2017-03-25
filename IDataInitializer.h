#pragma once
#include <vector>

class IInitializer{
public:
	virtual ~IInitializer(){}
public:
    virtual bool initializeData(int size) = 0;
    virtual int size() = 0;	
};

class IDataInitializer : public IInitializer{
public:
    virtual ~IDataInitializer(){}
};

