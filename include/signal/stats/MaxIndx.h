#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ipps{
    namespace stats{
        
        template <typename T>
        void MaxIndx(const T* src, int len, T* max, int *indx);

        // ============================
        // ============================ 
        //  MaxIndx Specializations
        // ============================
        // ============================

        // Ipp16s
        template <>
        inline void MaxIndx(const Ipp16s* src, int len, Ipp16s* max, int *indx)
        {
            IppStatus sts = ippsMaxIndx_16s(src, len, max, indx);
            IPP_NO_ERROR(sts, "ippsMaxIndx_16s");
        }

        // Ipp32s
        template <>
        inline void MaxIndx(const Ipp32s* src, int len, Ipp32s* max, int *indx)
        {
            IppStatus sts = ippsMaxIndx_32s(src, len, max, indx);
            IPP_NO_ERROR(sts, "ippsMaxIndx_32s");
        }

        // Ipp32f
        template <>
        inline void MaxIndx(const Ipp32f* src, int len, Ipp32f* max, int *indx)
        {
            IppStatus sts = ippsMaxIndx_32f(src, len, max, indx);
            IPP_NO_ERROR(sts, "ippsMaxIndx_32f");
        }

        // Ipp64f
        template <>
        inline void MaxIndx(const Ipp64f* src, int len, Ipp64f* max, int *indx)
        {
            IppStatus sts = ippsMaxIndx_64f(src, len, max, indx);
            IPP_NO_ERROR(sts, "ippsMaxIndx_64f");
        }


    }
}
