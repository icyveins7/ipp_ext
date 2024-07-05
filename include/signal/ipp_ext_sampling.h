#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

/*
DEV NOTE:

I have elected to change the calling structure of these 2 functions to be safer.
The pointer dstLen is essentially the number of elements written by IPP,
but this is slightly misleading as the user (including myself at first)
would have thought that this may restrict the elements written to the specified length.

It turns out that THIS IS NOT THE CASE; coupled with IPP's memory allocation
typically allocating more memory than the requested length (due to 64-byte alignment requirements),
this can lead to inconsistent memory leaks (only when the number of elements written far exceeds the dst array length).

In essence, the value initially pointed to by dstLen is unused.
Instead, I will check the initial value of dstLen to see if there is sufficient memory
to hold the written elements, and if not, I will throw an std::out_of_range exception.
*/

namespace ipps{
    namespace sampling{

        /// @brief Performs downsampling with additional checks on memory.
        /// @tparam T Type of input/output.
        /// @param src Source array.
        /// @param srcLen Length of source array.
        /// @param dst Destination array. Must have minimum length of srcLen / factor (+1 depending on phase).
        /// @param dstLen
        /// Pointer to a variable that initially contains the number of elements of dst. 
        /// Is overwritten at the end to reflect the actual number of elements written; 
        /// for SampleDown, this is srcLen / factor (+1 depending on phase).
        /// @param factor Downsampling factor.
        /// @param phase Downsample phase, [0, factor-1]. This may change on output depending on the srcLen.
        template <typename T>
        void SampleDown(const T* src, int srcLen, T* dst, int *dstLen, int factor, int *phase);

        /// @brief Performs upsampling with additional checks on memory.
        /// @tparam T Type of input/output.
        /// @param src Source array.
        /// @param srcLen Length of the source array.
        /// @param dst Destination array. Must have minimum length of srcLen * factor.
        /// @param dstLen 
        /// Pointer to a variable that initially contains the number of elements of dst. 
        /// Is overwritten at the end to reflect the actual number of elements written; 
        /// for SampleUp, this is ALWAYS srcLen * factor.
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
            int numWritten;
            IppStatus sts = ippsSampleDown_16s(src, srcLen, dst, &numWritten, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleDown_16s");
            if (numWritten > *dstLen)
                throw std::out_of_range("ippsSampleDown_16s: dstLen input is too small");
            *dstLen = numWritten; // otherwise simply overwrite the initial value (which may be shorter)
        }

        // 32f
        template <>
        inline void SampleDown(const Ipp32f* src, int srcLen, Ipp32f* dst, int *dstLen, int factor, int *phase)
        {
            int numWritten;
            IppStatus sts = ippsSampleDown_32f(src, srcLen, dst, &numWritten, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleDown_32f");
            if (numWritten > *dstLen)
                throw std::out_of_range("ippsSampleDown_32f: dstLen input is too small");
            *dstLen = numWritten; // otherwise simply overwrite the initial value (which may be shorter)
        }

        // 64f
        template <>
        inline void SampleDown(const Ipp64f* src, int srcLen, Ipp64f* dst, int *dstLen, int factor, int *phase)
        {
            int numWritten;
            IppStatus sts = ippsSampleDown_64f(src, srcLen, dst, &numWritten, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleDown_64f");
            if (numWritten > *dstLen)
                throw std::out_of_range("ippsSampleDown_64f: dstLen input is too small");
            *dstLen = numWritten; // otherwise simply overwrite the initial value (which may be shorter)
        }

        // 16sc
        template <>
        inline void SampleDown(const Ipp16sc* src, int srcLen, Ipp16sc* dst, int *dstLen, int factor, int *phase)
        {
            int numWritten;
            IppStatus sts = ippsSampleDown_16sc(src, srcLen, dst, &numWritten, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleDown_16sc");
            if (numWritten > *dstLen)
                throw std::out_of_range("ippsSampleDown_16sc: dstLen input is too small");
            *dstLen = numWritten; // otherwise simply overwrite the initial value (which may be shorter)
        }

        // 32fc
        template <>
        inline void SampleDown(const Ipp32fc* src, int srcLen, Ipp32fc* dst, int *dstLen, int factor, int *phase)
        {
            int numWritten;
            IppStatus sts = ippsSampleDown_32fc(src, srcLen, dst, &numWritten, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleDown_32fc");
            if (numWritten > *dstLen)
                throw std::out_of_range("ippsSampleDown_32fc: dstLen input is too small");
            *dstLen = numWritten; // otherwise simply overwrite the initial value (which may be shorter)
        }

        // 64fc
        template <>
        inline void SampleDown(const Ipp64fc* src, int srcLen, Ipp64fc* dst, int *dstLen, int factor, int *phase)
        {
            int numWritten;
            IppStatus sts = ippsSampleDown_64fc(src, srcLen, dst, &numWritten, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleDown_64fc");
            if (numWritten > *dstLen)
                throw std::out_of_range("ippsSampleDown_64fc: dstLen input is too small");
            *dstLen = numWritten; // otherwise simply overwrite the initial value (which may be shorter)
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
            int numWritten;
            IppStatus sts = ippsSampleUp_16s(src, srcLen, dst, &numWritten, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleUp_16s");
            if (numWritten > *dstLen)
                throw std::out_of_range("ippsSampleUp_16s: dstLen input is too small");
            *dstLen = numWritten; // otherwise simply overwrite the initial value (which may be shorter)
        }

        // 32f
        template <>
        inline void SampleUp(const Ipp32f* src, int srcLen, Ipp32f* dst, int *dstLen, int factor, int *phase)
        {
            int numWritten;
            IppStatus sts = ippsSampleUp_32f(src, srcLen, dst, &numWritten, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleUp_32f");
            if (numWritten > *dstLen)
                throw std::out_of_range("ippsSampleUp_32f: dstLen input is too small");
            *dstLen = numWritten; // otherwise simply overwrite the initial value (which may be shorter)
        }

        // 64f
        template <>
        inline void SampleUp(const Ipp64f* src, int srcLen, Ipp64f* dst, int *dstLen, int factor, int *phase)
        {
            int numWritten;
            IppStatus sts = ippsSampleUp_64f(src, srcLen, dst, &numWritten, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleUp_64f");
            if (numWritten > *dstLen)
                throw std::out_of_range("ippsSampleUp_64f: dstLen input is too small");
            *dstLen = numWritten; // otherwise simply overwrite the initial value (which may be shorter)
        }

        // 16sc
        template <>
        inline void SampleUp(const Ipp16sc* src, int srcLen, Ipp16sc* dst, int *dstLen, int factor, int *phase)
        {
            int numWritten;
            IppStatus sts = ippsSampleUp_16sc(src, srcLen, dst, &numWritten, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleUp_16sc");
            if (numWritten > *dstLen)
                throw std::out_of_range("ippsSampleUp_16sc: dstLen input is too small");
            *dstLen = numWritten; // otherwise simply overwrite the initial value (which may be shorter)
        }

        // 32fc
        template <>
        inline void SampleUp(const Ipp32fc* src, int srcLen, Ipp32fc* dst, int *dstLen, int factor, int *phase)
        {
            int numWritten;
            IppStatus sts = ippsSampleUp_32fc(src, srcLen, dst, &numWritten, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleUp_32fc");
            if (numWritten > *dstLen)
                throw std::out_of_range("ippsSampleUp_32fc: dstLen input is too small");
            *dstLen = numWritten; // otherwise simply overwrite the initial value (which may be shorter)
        }

        // 64fc
        template <>
        inline void SampleUp(const Ipp64fc* src, int srcLen, Ipp64fc* dst, int *dstLen, int factor, int *phase)
        {
            int numWritten;
            IppStatus sts = ippsSampleUp_64fc(src, srcLen, dst, &numWritten, factor, phase);
            IPP_NO_ERROR(sts, "ippsSampleUp_64fc");
            if (numWritten > *dstLen)
                throw std::out_of_range("ippsSampleUp_64fc: dstLen input is too small");
            *dstLen = numWritten; // otherwise simply overwrite the initial value (which may be shorter)
        }


    }
}
