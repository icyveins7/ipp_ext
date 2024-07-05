#pragma once

#include "ipp.h"
#include <stdexcept>
#include <string>
#include "../../ipp_ext_errors.h"

namespace ipps{
    namespace logical{

        template <typename T>
        void Xor(const T* src1, const T* src2, T* dst, int len);

        template <typename T>
        void Xor_I(const T* src, T* srcDst, int len);

        // ============================
        // ============================ 
        //  Xor specializations
        // ============================
        // ============================

        // Ipp8u
        template <>
        inline void Xor(const Ipp8u* src1, const Ipp8u* src2, Ipp8u* dst, int len)
        {
            IppStatus sts = ippsXor_8u(src1, src2, dst, len);
            IPP_NO_ERROR(sts, "ippsXor_8u");
        }

        // Ipp16u
        template <>
        inline void Xor(const Ipp16u* src1, const Ipp16u* src2, Ipp16u* dst, int len)
        {
            IppStatus sts = ippsXor_16u(src1, src2, dst, len);
            IPP_NO_ERROR(sts, "ippsXor_16u");
        }

        // Ipp32u
        template <>
        inline void Xor(const Ipp32u* src1, const Ipp32u* src2, Ipp32u* dst, int len)
        {
            IppStatus sts = ippsXor_32u(src1, src2, dst, len);
            IPP_NO_ERROR(sts, "ippsXor_32u");
        }

        // ============================
        // ============================ 
        //  Xor_I specializations
        // ============================
        // ============================

        // Ipp8u
        template <>
        inline void Xor_I(const Ipp8u* src, Ipp8u* srcDst, int len)
        {
            IppStatus sts = ippsXor_8u_I(src, srcDst, len);
            IPP_NO_ERROR(sts, "ippsXor_8u_I");
        }

        // Ipp16u
        template <>
        inline void Xor_I(const Ipp16u* src, Ipp16u* srcDst, int len)
        {
            IppStatus sts = ippsXor_16u_I(src, srcDst, len);
            IPP_NO_ERROR(sts, "ippsXor_16u_I");
        }

        // Ipp32u
        template <>
        inline void Xor_I(const Ipp32u* src, Ipp32u* srcDst, int len)
        {
            IppStatus sts = ippsXor_32u_I(src, srcDst, len);
            IPP_NO_ERROR(sts, "ippsXor_32u_I");
        }
    }
}
