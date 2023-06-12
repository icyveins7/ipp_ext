#include "ipp.h"
#include <stdexcept>
#include <string>

/// @brief Helpful utility function to ensure no IPP errors are raised.
/// @param sts The IPP status code to check.
/// @param funcName A function name that can be used to identify the error.
inline void IPP_NO_ERROR(IppStatus sts, const char *funcName)
{
    if (sts != ippStsNoErr) 
        throw std::runtime_error(std::string(funcName) + " failed: " + ippGetStatusString(sts));
} 
