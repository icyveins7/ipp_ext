#pragma once

#include "ipp.h"
#include <stdexcept>
#include <string>
#include "../ipp_ext_errors.h"

namespace ipps{
    namespace generator{

        template <typename T, typename U>
        void Slope(T *dst, int length, U offset, U slope);

        template <typename T, typename U, typename V>
        void Tone(T* dst, int len, U magn, V freq, V *phase, IppHintAlgorithm hint=IppHintAlgorithm::ippAlgHintAccurate);

        // ============================
        // ============================ 
        //  Slope Specializations
        // ============================
        // ============================

        template <typename T, typename U>
        inline void Slope(T *dst, int length, U offset, U slope)
        {
            throw std::runtime_error("Slope only implemented for specific types.");
        }

        // Ipp8u, Ipp32f

        template <>
        inline void Slope(Ipp8u *dst, int length, Ipp32f offset, Ipp32f slope)
        {
            IppStatus sts = ippsVectorSlope_8u(
                dst, length, offset, slope
            );
            IPP_NO_ERROR(sts, "ippsVectorSlope_8u");
        }

        // Ipp16u, Ipp32f

        template <>
        inline void Slope(Ipp16u *dst, int length, Ipp32f offset, Ipp32f slope)
        {
            IppStatus sts = ippsVectorSlope_16u(
                dst, length, offset, slope
            );
            IPP_NO_ERROR(sts, "ippsVectorSlope_16u");
        }

        // Ipp16s, Ipp32f

        template <>
        inline void Slope(Ipp16s *dst, int length, Ipp32f offset, Ipp32f slope)
        {
            IppStatus sts = ippsVectorSlope_16s(
                dst, length, offset, slope
            );
            IPP_NO_ERROR(sts, "ippsVectorSlope_16s");
        }

        // Ipp32u, Ipp64f

        template <>
        inline void Slope(Ipp32u *dst, int length, Ipp64f offset, Ipp64f slope)
        {
            IppStatus sts = ippsVectorSlope_32u(
                dst, length, offset, slope
            );
            IPP_NO_ERROR(sts, "ippsVectorSlope_32u");
        }

        // Ipp32s, Ipp64f

        template <>
        inline void Slope(Ipp32s *dst, int length, Ipp64f offset, Ipp64f slope)
        {
            IppStatus sts = ippsVectorSlope_32s(
                dst, length, offset, slope
            );
            IPP_NO_ERROR(sts, "ippsVectorSlope_32s");
        }

        // Ipp32f, Ipp32f

        template <>
        inline void Slope(Ipp32f *dst, int length, Ipp32f offset, Ipp32f slope)
        {
            IppStatus sts = ippsVectorSlope_32f(
                dst, length, offset, slope
            );
            IPP_NO_ERROR(sts, "ippsVectorSlope_32f");
        }

        // Ipp64f, Ipp64f

        template <>
        inline void Slope(Ipp64f *dst, int length, Ipp64f offset, Ipp64f slope)
        {
            IppStatus sts = ippsVectorSlope_64f(
                dst, length, offset, slope
            );
            IPP_NO_ERROR(sts, "ippsVectorSlope_64f");
        }

        // ============================
        // ============================ 
        //  Tone Specializations
        // ============================
        // ============================

        // Ipp16s, Ipp16s, Ipp32f
        template <>
        inline void Tone(Ipp16s *dst, int len, Ipp16s magn, Ipp32f freq, Ipp32f *phase, IppHintAlgorithm hint)
        {
            IppStatus sts = ippsTone_16s(
                dst, len, magn, freq, phase, hint
            );
            IPP_NO_ERROR(sts, "ippsTone_16s");
        }

        // Ipp16sc, Ipp16s, Ipp32f
        template <>
        inline void Tone(Ipp16sc *dst, int len, Ipp16s magn, Ipp32f freq, Ipp32f *phase, IppHintAlgorithm hint)
        {
            IppStatus sts = ippsTone_16sc(
                dst, len, magn, freq, phase, hint
            );
            IPP_NO_ERROR(sts, "ippsTone_16sc");
        }

        // Ipp32f, Ipp32f, Ipp32f
        template <>
        inline void Tone(Ipp32f *dst, int len, Ipp32f magn, Ipp32f freq, Ipp32f *phase, IppHintAlgorithm hint)
        {
            IppStatus sts = ippsTone_32f(
                dst, len, magn, freq, phase, hint
            );
            IPP_NO_ERROR(sts, "ippsTone_32f");
        }

        // Ipp32fc, Ipp32f, Ipp32f
        template <>
        inline void Tone(Ipp32fc *dst, int len, Ipp32f magn, Ipp32f freq, Ipp32f *phase, IppHintAlgorithm hint)
        {
            IppStatus sts = ippsTone_32fc(
                dst, len, magn, freq, phase, hint
            );
            IPP_NO_ERROR(sts, "ippsTone_32fc");
        }

        // Ipp64f, Ipp64f, Ipp64f
        template <>
        inline void Tone(Ipp64f *dst, int len, Ipp64f magn, Ipp64f freq, Ipp64f *phase, IppHintAlgorithm hint)
        {
            IppStatus sts = ippsTone_64f(
                dst, len, magn, freq, phase, hint
            );
            IPP_NO_ERROR(sts, "ippsTone_64f");
        }

        // Ipp64fc, Ipp64f, Ipp64f
        template <>
        inline void Tone(Ipp64fc *dst, int len, Ipp64f magn, Ipp64f freq, Ipp64f *phase, IppHintAlgorithm hint)
        {
            IppStatus sts = ippsTone_64fc(
                dst, len, magn, freq, phase, hint
            );
            IPP_NO_ERROR(sts, "ippsTone_64fc");
        }
    }
}
