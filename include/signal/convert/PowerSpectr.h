#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace convert{
        // we use template overloads here

        // complex interleaved inputs

        template <typename T, typename U>
        void PowerSpectr(const T* src, U* dst, int len);

        // real, separate inputs

        template <typename T, typename U>
        void PowerSpectr(const T* srcRe, const T* srcIm, U* dst, int len);

        // TODO: implement Sfs flavours

        // ============================
        // ============================ 
        //  PowerSpectr Specializations, complex
        // ============================
        // ============================

        template <typename T, typename U>
        inline void PowerSpectr(const T* src, U* dst, int len){
            throw std::runtime_error("PowerSpectr not implemented for generic types");
        }

        // 64fc to 64f
        template <>
        inline void PowerSpectr(const Ipp64fc* src, Ipp64f* dst, int len){
            IppStatus sts = ippsPowerSpectr_64fc(src, dst, len);
            IPP_NO_ERROR(sts, "ippsPowerSpectr_64fc");
        }

        // 32fc to 32f
        template <>
        inline void PowerSpectr(const Ipp32fc* src, Ipp32f* dst, int len){
            IppStatus sts = ippsPowerSpectr_32fc(src, dst, len);
            IPP_NO_ERROR(sts, "ippsPowerSpectr_32fc");
        }

        // 16sc to 32f
        template <>
        inline void PowerSpectr(const Ipp16sc* src, Ipp32f* dst, int len){
            IppStatus sts = ippsPowerSpectr_16sc32f(src, dst, len);
            IPP_NO_ERROR(sts, "ippsPowerSpectr_16sc32f");
        }

        // ============================
        // ============================ 
        //  PowerSpectr Specializations, real
        // ============================
        // ============================

        template <typename T, typename U>
        inline void PowerSpectr(const T* srcRe, const T* srcIm, U* dst, int len){
            throw std::runtime_error("PowerSpectr not implemented for generic types");
        }

        // 64f,64f to 64f
        template <>
        inline void PowerSpectr(const Ipp64f* srcRe, const Ipp64f* srcIm, Ipp64f* dst, int len){
            IppStatus sts = ippsPowerSpectr_64f(srcRe, srcIm, dst, len);
            IPP_NO_ERROR(sts, "ippsPowerSpectr_64f");
        }

        // 32f,32f to 32f
        template <>
        inline void PowerSpectr(const Ipp32f* srcRe, const Ipp32f* srcIm, Ipp32f* dst, int len){
            IppStatus sts = ippsPowerSpectr_32f(srcRe, srcIm, dst, len);
            IPP_NO_ERROR(sts, "ippsPowerSpectr_32f");
        }

        // 16s,16s to 32f
        template <>
        inline void PowerSpectr(const Ipp16s* srcRe, const Ipp16s* srcIm, Ipp32f* dst, int len){
            IppStatus sts = ippsPowerSpectr_16s32f(srcRe, srcIm, dst, len);
            IPP_NO_ERROR(sts, "ippsPowerSpectr_16s32f");
        }

    }
}