// This and the associated header file are only here to prove compilation
// succeeds in the test.

#include "test_vectors_encapsulation.h"

void EncapsulateVector::setValue(Ipp32fc x)
{
    for (int i = 0; i < v.size(); i++){
        v.at(i) = x;
    }
}