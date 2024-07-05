/*
You probably don't need to use this file directly.
See FIR.h for an example of a container that will encapsulate this generator function.
*/

#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include "../ipp_ext_vec.h"
#include "../ipp_ext_convert.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace filter{

        template <typename T>
        void FIRGenLowpass(
            T rFreq, T* taps, int tapsLen, 
            IppWinType winType, IppBool doNormal);

        // Wrappers to directly generate vectors of taps

        /// @brief Helper function to generate a vector of lowpass taps.
        /// @tparam T Type for the taps array. Is internally generated as 64f before converting.
        /// @param rFreq Normalised frequency (0, 0.5).
        /// @param tapsLen Length of taps, minimum 5.
        /// @param winType Window type.
        /// @param doNormal Normalised taps flag.
        /// @return ippe::vector<T> of taps.
        template <typename T>
        vector<T> generateLowpassTaps(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal);

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

        // ============================
        // ============================ 
        //  generateLowpassTaps Specializations
        // ============================
        // ============================

        // Ipp32f
        template <>
        inline vector<Ipp32f> generateLowpassTaps(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
        {
            // In general, create 64f, then convert
            vector<Ipp64f> tmp((size_t)tapsLen);
            FIRGenLowpass<Ipp64f>(rFreq, tmp.data(), tapsLen, winType, doNormal);
            vector<Ipp32f> taps((size_t)tapsLen);
            convert::Convert<Ipp64f, Ipp32f>(tmp.data(), taps.data(), (int)taps.size());
            return taps;
        }

        // Ipp64f
        template <>
        inline vector<Ipp64f> generateLowpassTaps(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
        {
            // For 64f, we can directly generate the taps
            vector<Ipp64f> tmp((size_t)tapsLen);
            FIRGenLowpass<Ipp64f>(rFreq, tmp.data(), tapsLen, winType, doNormal);
            return tmp;
        }

        // Ipp32fc
        template <>
        inline vector<Ipp32fc> generateLowpassTaps(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
        {
            // In general, create 64f, then convert
            vector<Ipp64f> tmp((size_t)tapsLen);
            FIRGenLowpass<Ipp64f>(rFreq, tmp.data(), tapsLen, winType, doNormal);
            // For complex we need 1 more step, so make the real vec first
            vector<Ipp32f> taps((size_t)tapsLen);
            convert::Convert<Ipp64f, Ipp32f>(tmp.data(), taps.data(), (int)taps.size());
            // Then create the complex vector
            vector<Ipp32fc> complexTaps((size_t)tapsLen);
            convert::RealToCplx<Ipp32f, Ipp32fc>(
                taps.data(), static_cast<Ipp32f*>(nullptr),
                complexTaps.data(), (int)complexTaps.size());
            return complexTaps;
        }

        // Ipp64fc
        template <>
        inline vector<Ipp64fc> generateLowpassTaps(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
        {
            // For 64f, we can directly generate the taps
            vector<Ipp64f> tmp((size_t)tapsLen);
            FIRGenLowpass<Ipp64f>(rFreq, tmp.data(), tapsLen, winType, doNormal);
            // Then create the complex vector
            vector<Ipp64fc> complexTaps((size_t)tapsLen);
            convert::RealToCplx<Ipp64f, Ipp64fc>(
                tmp.data(), static_cast<Ipp64f*>(nullptr),
                complexTaps.data(), (int)complexTaps.size());
            return complexTaps;
        }



    }
}