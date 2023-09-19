/*
You probably don't need to use this file directly.
See FIR.h for an example of a container that will encapsulate this generator function.
*/

#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include "../ipp_ext_vec.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace filter{

        template <typename T>
        void FIRGenLowpass(
            T rFreq, T* taps, int tapsLen, 
            IppWinType winType, IppBool doNormal);

        // ============================
        // ============================ 
        //  FIRGenLowpass Specializations
        // ============================
        // ============================

        // Ipp64f
        template <>
        inline void FIRGenLowpass(
            Ipp64f rFreq, Ipp64f* taps, int tapsLen, 
            IppWinType winType, IppBool doNormal)
        {
            int bufSize;
            IppStatus sts = ippsFIRGenGetBufferSize(
                tapsLen, &bufSize 
            );
            IPP_NO_ERROR(sts, "ippsFIRGenGetBufferSize");

            // Create a vector
            vector<Ipp8u> buf(bufSize);

            sts = ippsFIRGenLowpass_64f(
                rFreq, taps, tapsLen,
                winType, doNormal, buf.data());
            IPP_NO_ERROR(sts, "ippsFIRGenLowpass_64f");
        }


    }
}