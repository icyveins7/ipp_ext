#pragma once

#include "ipp.h"
#include <stdexcept>
#include <string>
#include "ipp_ext_errors.h"

namespace ippe{
    namespace generator{

        template <typename T, typename U>
        void Slope(T *dst, int length, U offset, U slope);

        // Specializations for Slope

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
    }
}