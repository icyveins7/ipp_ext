#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ipps{
    namespace math{

        template <typename T>
        void Ln(const T* src, T* dst, int len);

        template <typename T>
        void Ln_I(T* srcDst, int len);

        template <typename T>
        void Ln_Sfs(const T* src, T* dst, int len, int scaleFactor);

        template <typename T>
        void Ln_ISfs(T* srcDst, int len, int scaleFactor);

        // ============================
        // ============================ 
        //     Ln Specializations
        // ============================
        // ============================

        // Ipp32f
        template <>
        inline void Ln<Ipp32f>(const Ipp32f* src, Ipp32f* dst, int len)
        {
            IppStatus sts = ippsLn_32f(src, dst, len);
            IPP_NO_ERROR(sts, "ippsLn_32f");
        }

        // Ipp64f
        template <>
        inline void Ln<Ipp64f>(const Ipp64f* src, Ipp64f* dst, int len)
        {
            IppStatus sts = ippsLn_64f(src, dst, len);
            IPP_NO_ERROR(sts, "ippsLn_64f");
        }

        // ============================
        // ============================ 
        //     Ln_I Specializations
        // ============================
        // ============================

        // Ipp32f
        template <>
        inline void Ln_I<Ipp32f>(Ipp32f* srcDst, int len)
        {
            IppStatus sts = ippsLn_32f_I(srcDst, len);
            IPP_NO_ERROR(sts, "ippsLn_32f_I");
        }

        // Ipp64f
        template <>
        inline void Ln_I<Ipp64f>(Ipp64f* srcDst, int len)
        {
            IppStatus sts = ippsLn_64f_I(srcDst, len);
            IPP_NO_ERROR(sts, "ippsLn_64f_I");
        }

        // ============================
        // ============================ 
        //     Ln_Sfs Specializations
        // ============================
        // ============================

        // Ipp16s
        template <>
        inline void Ln_Sfs<Ipp16s>(const Ipp16s* src, Ipp16s* dst, int len, int scaleFactor)
        {
            IppStatus sts = ippsLn_16s_Sfs(src, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsLn_16s_Sfs");
        }

        // Ipp32s
        template <>
        inline void Ln_Sfs<Ipp32s>(const Ipp32s* src, Ipp32s* dst, int len, int scaleFactor)
        {
            IppStatus sts = ippsLn_32s_Sfs(src, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsLn_32s_Sfs");
        }

        // ============================
        // ============================ 
        //     Ln_ISfs Specializations
        // ============================
        // ============================

        // Ipp16s
        template <>
        inline void Ln_ISfs<Ipp16s>(Ipp16s* srcDst, int len, int scaleFactor)
        {
            IppStatus sts = ippsLn_16s_ISfs(srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsLn_16s_ISfs");
        }

        // Ipp32s
        template <>
        inline void Ln_ISfs<Ipp32s>(Ipp32s* srcDst, int len, int scaleFactor)
        {
            IppStatus sts = ippsLn_32s_ISfs(srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsLn_32s_ISfs");
        }

    }
}
