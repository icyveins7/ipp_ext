#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include "FIRGen.h" // include all the taps generators
#include "../ipp_ext_vec.h" // use ippe vectors
#include "../ipp_ext_convert.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace filter{

        template <typename T>
        class FIR
        {
        protected:
            FIR(int tapsLen)
                : m_taps{tapsLen}
            {

            }

            vector<T> m_taps;
        };

        template <typename T, typename U>
        class FIRLowpass : public FIR<T>
        {
        public:
            FIRLowpass(U rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
                : FIR<T>(tapsLen)
            {
                // Create a temporary vector to store the generated type
                vector<U> tmp(tapsLen);
                // Call the lowpass taps generator
                FIRGenLowpass<U>(rFreq, tmp.data(), tapsLen, winType, doNormal);
                // Convert into the internal vector at the requested type
                Convert<U,T>(tmp.data(), m_taps.data(), (int)m_taps.size());
            }
        };



    }
}