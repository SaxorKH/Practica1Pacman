#include "FileNotFoundError.h"

#include "checkML.h"


FileNotFoundError::FileNotFoundError(string m) : PacManError(m)
{
}


FileNotFoundError::~FileNotFoundError()
{
}
