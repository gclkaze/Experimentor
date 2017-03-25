#pragma once
#include <vector>

class IDataStorage{
public:
	virtual ~IDataStorage(){}
    virtual void dataReady() = 0;
    virtual bool createTable(std::vector<int> &v, int columns) = 0;
    virtual void dump() = 0;
    virtual bool ready() = 0;
};
