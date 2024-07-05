// This and the associated source file are only here to prove compilation
// succeeds in the test.

#pragma once

#include "ipp_ext.h"

struct EncapsulateVector
{
    ipps::vector<Ipp32fc> v;

    void setValue(Ipp32fc x);
};
