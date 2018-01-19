#pragma once
#include <stdexcept>
#include <string>
using namespace std;
class PacManError : public logic_error
{
public:
	PacManError(string m);
	virtual ~PacManError();
};

