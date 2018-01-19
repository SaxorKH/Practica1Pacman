#pragma once
#include "PacManError.h"
class FileNotFoundError :
	public PacManError
{
public:
	FileNotFoundError(string m);
	~FileNotFoundError();
};

