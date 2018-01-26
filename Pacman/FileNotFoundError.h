#pragma once
#include "PacManError.h"
#include "checkML.h"
class FileNotFoundError :
	public PacManError
{
public:
	FileNotFoundError(string m);
	~FileNotFoundError();
};

