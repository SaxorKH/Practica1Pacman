#pragma once
#include "PacManError.h"
class FileFormatError :
	public PacManError
{
public:
	FileFormatError(string m);
	~FileFormatError();
};

