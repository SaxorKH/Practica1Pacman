#pragma once
#include "PacManError.h"
#include "checkML.h"
class FileFormatError :
	public PacManError
{
public:
	FileFormatError(string m);
	~FileFormatError();
};

