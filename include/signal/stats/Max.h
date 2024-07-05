#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ipps{
    namespace stats{
        
        template <typename T>
        void Max(const T* src, int len, T* max);

        // ============================
        // ============================ 
        //  Max Specializations
        // ============================
        // ============================

        // Ipp16s
        template <>
        inline void Max(const Ipp16s* src, int len, Ipp16s* max)
        {
            IppStatus sts = ippsMax_16s(src, len, max);
            IPP_NO_ERROR(sts, "ippsMax_16s");
        }

        // Ipp32s
        template <>
        inline void Max(const Ipp32s* src, int len, Ipp32s* max)
        {
            IppStatus sts = ippsMax_32s(src, len, max);
            IPP_NO_ERROR(sts, "ippsMax_32s");
        }

        // Ipp32f
        template <>
        inline void Max(const Ipp32f* src, int len, Ipp32f* max)
        {
            IppStatus sts = ippsMax_32f(src, len, max);
            IPP_NO_ERROR(sts, "ippsMax_32f");
        }

        // Ipp64f
        template <>
        inline void Max(const Ipp64f* src, int len, Ipp64f* max)
        {
            IppStatus sts = ippsMax_64f(src, len, max);
            IPP_NO_ERROR(sts, "ippsMax_64f");
        }


    }
}
