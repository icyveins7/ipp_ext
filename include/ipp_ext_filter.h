/*
There are 6 available filter types for FIRSR:
32f, 64f, 32fc, 64fc, 16s, 16sc

Taps generation is always done in 64f. Type conversion must be manually applied,
and complex conversion is also required.
*/

#pragma once

#include "ipp.h"
#include <stdexcept>

namespace ippe
{
    // Basic parent class, not meant to be instantiated directly.
    template <typename T>
    class FIRSR
    {
    public:
        // Main runtime method, see template specializations below.
        filter(const T* src, T* dst, int dstLen);

    protected:
        // Constructor and destructor are protected to prevent instantiation.
        FIRSR()
        {
        }

        ~FIRSR()
        {
            ippsFree(m_taps);
            ippsFree(m_delay);
            ippsFree(m_pSpec);
            ippsFree(m_pBuf);
        }

        // Storage
        T* m_taps = nullptr;
        T* m_delay = nullptr;
        Ipp8u* m_pSpec = nullptr; // for the specification structure
        Ipp8u* m_pBuf = nullptr; // work buffer during invocations

        // Setup method (see template specializations below)
        void setup();

    };

    // Child classes for the different filter types
    template <typename T>
    class FIRSRLowpass : public FIRSR<T>
    {
    public:
        FIRSRLowpass(Ipp64f rFreq, int tapsLen, ippWinType, IppBool doNormal);
        ~FIRSRLowpass();

    private:

    }


}