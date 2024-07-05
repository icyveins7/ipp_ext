#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace math{

        template <typename T>
        void AddProductC(const T* src, const T val, T* srcDst, int len);

        // ============================
        // ============================ 
        //  AddProductC Specializations
        // ============================
        // ============================

        // Ipp32f
        template <>
        inline void AddProductC<Ipp32f>(const Ipp32f* src, const Ipp32f val, Ipp32f* srcDst, int len)
        {
            IppStatus sts = ippsAddProductC_32f(
                src, val, srcDst, len
            );
            IPP_NO_ERROR(sts, "ippsAddProductC_32f");
        }

        // Ipp64f
        template <>
        inline void AddProductC<Ipp64f>(const Ipp64f* src, const Ipp64f val, Ipp64f* srcDst, int len)
        {
            IppStatus sts = ippsAddProductC_64f(
                src, val, srcDst, len
            );
            IPP_NO_ERROR(sts, "ippsAddProductC_64f");
        }

    }
}