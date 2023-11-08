#pragma once

#include "ipp.h"
#include "ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace sampling{

        template <typename T>
        void SampleDown(const T* src, int srcLen, T* dst, int *dstLen, int factor, int *phase);

        /// @brief Note that this function ignores the initial value of dstLen, 
        /// and will always write srcSize * factor elements to dst.
        /// @tparam T Type of input/output.
        /// @param src Source array.
        /// @param srcLen Length of the source array.
        /// @param dst Destination array. Must have minimum length of srcLen * factor.
        /// @param dstLen For SampleUp, this is effectively ignored, and always returns as srcLen * factor.
        /// @param factor Upsample factor
        /// @param phase Upsample phase, [0, factor-1]. For SampleUp, this always returns as the phase that was input.
        template <typename T>
        void SampleUp(const T* src, int srcLen, T* dst, int *dstLen, int factor, int *phase);

        // ============================
        // ============================ 
        //  SampleDown Specializations
        // ============================
        // ============================

        // 16s
        template <>
        inline void SampleDown(const Ipp16s* src, int srcLen, Ipp16s* dst, int *dstLen, int factor, int *phase)
        {
            IppStatus sts = ippsSampleDown_16s(src, srcLen, dst, dstLen, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleDown_16s");
        }

        // 32f
        template <>
        inline void SampleDown(const Ipp32f* src, int srcLen, Ipp32f* dst, int *dstLen, int factor, int *phase)
        {
            IppStatus sts = ippsSampleDown_32f(src, srcLen, dst, dstLen, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleDown_32f");
        }

        // 64f
        template <>
        inline void SampleDown(const Ipp64f* src, int srcLen, Ipp64f* dst, int *dstLen, int factor, int *phase)
        {
            IppStatus sts = ippsSampleDown_64f(src, srcLen, dst, dstLen, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleDown_64f");
        }

        // 16sc
        template <>
        inline void SampleDown(const Ipp16sc* src, int srcLen, Ipp16sc* dst, int *dstLen, int factor, int *phase)
        {
            IppStatus sts = ippsSampleDown_16sc(src, srcLen, dst, dstLen, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleDown_16sc");
        }

        // 32fc
        template <>
        inline void SampleDown(const Ipp32fc* src, int srcLen, Ipp32fc* dst, int *dstLen, int factor, int *phase)
        {
            IppStatus sts = ippsSampleDown_32fc(src, srcLen, dst, dstLen, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleDown_32fc");
        }

        // 64fc
        template <>
        inline void SampleDown(const Ipp64fc* src, int srcLen, Ipp64fc* dst, int *dstLen, int factor, int *phase)
        {
            IppStatus sts = ippsSampleDown_64fc(src, srcLen, dst, dstLen, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleDown_64fc");
        }

        // ============================
        // ============================ 
        //  SampleUp Specializations
        // ============================
        // ============================

        // 16s
        template <>
        inline void SampleUp(const Ipp16s* src, int srcLen, Ipp16s* dst, int *dstLen, int factor, int *phase)
        {
            IppStatus sts = ippsSampleUp_16s(src, srcLen, dst, dstLen, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleUp_16s");
        }

        // 32f
        template <>
        inline void SampleUp(const Ipp32f* src, int srcLen, Ipp32f* dst, int *dstLen, int factor, int *phase)
        {
            IppStatus sts = ippsSampleUp_32f(src, srcLen, dst, dstLen, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleUp_32f");
        }

        // 64f
        template <>
        inline void SampleUp(const Ipp64f* src, int srcLen, Ipp64f* dst, int *dstLen, int factor, int *phase)
        {
            IppStatus sts = ippsSampleUp_64f(src, srcLen, dst, dstLen, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleUp_64f");
        }

        // 16sc
        template <>
        inline void SampleUp(const Ipp16sc* src, int srcLen, Ipp16sc* dst, int *dstLen, int factor, int *phase)
        {
            IppStatus sts = ippsSampleUp_16sc(src, srcLen, dst, dstLen, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleUp_16sc");
        }

        // 32fc
        template <>
        inline void SampleUp(const Ipp32fc* src, int srcLen, Ipp32fc* dst, int *dstLen, int factor, int *phase)
        {
            IppStatus sts = ippsSampleUp_32fc(src, srcLen, dst, dstLen, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleUp_32fc");
        }

        // 64fc
        template <>
        inline void SampleUp(const Ipp64fc* src, int srcLen, Ipp64fc* dst, int *dstLen, int factor, int *phase)
        {
            IppStatus sts = ippsSampleUp_64fc(src, srcLen, dst, dstLen, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleUp_64fc");
        }


    }
}