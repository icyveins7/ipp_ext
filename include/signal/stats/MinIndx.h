#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ipps{
    namespace stats{
        
        template <typename T>
        void MinIndx(const T* src, int len, T* min, int *indx);

        // ============================
        // ============================ 
        //  MinIndx Specializations
        // ============================
        // ============================

        // Ipp16s
        template <>
        inline void MinIndx(const Ipp16s* src, int len, Ipp16s* min, int *indx)
        {
            IppStatus sts = ippsMinIndx_16s(src, len, min, indx);
            IPP_NO_ERROR(sts, "ippsMinIndx_16s");
        }

        // Ipp32s
        template <>
        inline void MinIndx(const Ipp32s* src, int len, Ipp32s* min, int *indx)
        {
            IppStatus sts = ippsMinIndx_32s(src, len, min, indx);
            IPP_NO_ERROR(sts, "ippsMinIndx_32s");
        }

        // Ipp32f
        template <>
        inline void MinIndx(const Ipp32f* src, int len, Ipp32f* min, int *indx)
        {
            IppStatus sts = ippsMinIndx_32f(src, len, min, indx);
            IPP_NO_ERROR(sts, "ippsMinIndx_32f");
        }

        // Ipp64f
        template <>
        inline void MinIndx(const Ipp64f* src, int len, Ipp64f* min, int *indx)
        {
            IppStatus sts = ippsMinIndx_64f(src, len, min, indx);
            IPP_NO_ERROR(sts, "ippsMinIndx_64f");
        }


    }
}
