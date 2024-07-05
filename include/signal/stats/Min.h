#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ipps{
    namespace stats{
        
        template <typename T>
        void Min(const T* src, int len, T* min);

        // ============================
        // ============================ 
        //  min Specializations
        // ============================
        // ============================

        // Ipp16s
        template <>
        inline void Min(const Ipp16s* src, int len, Ipp16s* min)
        {
            IppStatus sts = ippsMin_16s(src, len, min);
            IPP_NO_ERROR(sts, "ippsMin_16s");
        }

        // Ipp32s
        template <>
        inline void Min(const Ipp32s* src, int len, Ipp32s* min)
        {
            IppStatus sts = ippsMin_32s(src, len, min);
            IPP_NO_ERROR(sts, "ippsMin_32s");
        }

        // Ipp32f
        template <>
        inline void Min(const Ipp32f* src, int len, Ipp32f* min)
        {
            IppStatus sts = ippsMin_32f(src, len, min);
            IPP_NO_ERROR(sts, "ippsMin_32f");
        }

        // Ipp64f
        template <>
        inline void Min(const Ipp64f* src, int len, Ipp64f* min)
        {
            IppStatus sts = ippsMin_64f(src, len, min);
            IPP_NO_ERROR(sts, "ippsMin_64f");
        }


    }
}
