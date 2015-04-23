#include "PvaExceptionTranslator.h"
#include "boost/python.hpp"

namespace epics { namespace pvaPy {


void PvaExceptionTranslator::translator(const PvaException& ex)
{
    PyErr_SetString(PyExc_UserWarning, ex.what());
}

}}

