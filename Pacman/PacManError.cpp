#include "PacManError.h"
#include "checkML.h"



PacManError::PacManError(string m) : logic_error(m)
{
}


PacManError::~PacManError()
{
}
