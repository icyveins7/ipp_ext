#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace math{

        template <typename T, typename U>
        void Norm_L2(const T* src, int len, U* norm);

        // ============================
        // ============================ 
        //     Norm_L2 Specializations
        // ============================
        // ============================

        // template <typename T, typename U>
        // inline void Norm_L2(T* src, int len, U* norm)
        // {
        //     throw std::runtime_error("Norm_L2 not implemented for generic types");
        // }

        // Ipp32f

        template <>
        inline void Norm_L2(const Ipp32f* src, int len, Ipp32f* norm)
        {
            IppStatus sts = ippsNorm_L2_32f(src, len, norm);
            IPP_NO_ERROR(sts, "ippsNorm_L2_32f");
        }

        // Ipp64f

        template <>
        inline void Norm_L2(const Ipp64f* src, int len, Ipp64f* norm)
        {
            IppStatus sts = ippsNorm_L2_64f(src, len, norm);
            IPP_NO_ERROR(sts, "ippsNorm_L2_64f");
        }

        // Ipp16s -> Ipp32f

        template <>
        inline void Norm_L2(const Ipp16s* src, int len, Ipp32f* norm)
        {
            IppStatus sts = ippsNorm_L2_16s32f(src, len, norm);
            IPP_NO_ERROR(sts, "ippsNorm_L2_16s32f");
        }

        // Ipp32fc -> Ipp64f

        template <>
        inline void Norm_L2(const Ipp32fc* src, int len, Ipp64f* norm)
        {
            IppStatus sts = ippsNorm_L2_32fc64f(src, len, norm);
            IPP_NO_ERROR(sts, "ippsNorm_L2_32fc64f");
        }

        // Ipp64fc -> Ipp64f

        template <>
        inline void Norm_L2(const Ipp64fc* src, int len, Ipp64f* norm)
        {
            IppStatus sts = ippsNorm_L2_64fc64f(src, len, norm);
            IPP_NO_ERROR(sts, "ippsNorm_L2_64fc64f");
        }
    }
}
