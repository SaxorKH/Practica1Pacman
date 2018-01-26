#pragma once
#include <stdexcept>
#include <string>
#include "checkML.h"
using namespace std;
class PacManError : public logic_error
{
public:
	PacManError(string m);
	virtual ~PacManError();
};

