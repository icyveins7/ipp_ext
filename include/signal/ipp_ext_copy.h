#pragma once
#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ipps{

    template <typename T>
    void Copy(const T* src, T* dst, int len);

    // Specializations

    template <typename T>
    inline void Copy(const T* /*src*/, T* /*dst*/, int /*len*/)
    {
        throw std::runtime_error("ippsCopy only implemented for specific types.");
    }


    // Ipp8u
    template <>
    inline void Copy(const Ipp8u* src, Ipp8u* dst, int len)
    {
        IppStatus sts = ippsCopy_8u(src, dst, len);
        IPP_NO_ERROR(sts, "ippsCopy_8u");
    }

    // Ipp16s
    template <>
    inline void Copy(const Ipp16s* src, Ipp16s* dst, int len)
    {
        IppStatus sts = ippsCopy_16s(src, dst, len);
        IPP_NO_ERROR(sts, "ippsCopy_16s");
    }

    // Ipp32s
    template <>
    inline void Copy(const Ipp32s* src, Ipp32s* dst, int len)
    {
        IppStatus sts = ippsCopy_32s(src, dst, len);
        IPP_NO_ERROR(sts, "ippsCopy_32s");
    }

    // Ipp32f
    template <>
    inline void Copy(const Ipp32f* src, Ipp32f* dst, int len)
    {
        IppStatus sts = ippsCopy_32f(src, dst, len);
        IPP_NO_ERROR(sts, "ippsCopy_32f");
    }

    // Ipp64s
    template <>
    inline void Copy(const Ipp64s* src, Ipp64s* dst, int len)
    {
        IppStatus sts = ippsCopy_64s(src, dst, len);
        IPP_NO_ERROR(sts, "ippsCopy_64s");
    }

    // Ipp64f
    template <>
    inline void Copy(const Ipp64f* src, Ipp64f* dst, int len)
    {
        IppStatus sts = ippsCopy_64f(src, dst, len);
        IPP_NO_ERROR(sts, "ippsCopy_64f");
    }

    // Ipp16sc
    template <>
    inline void Copy(const Ipp16sc* src, Ipp16sc* dst, int len)
    {
        IppStatus sts = ippsCopy_16sc(src, dst, len);
        IPP_NO_ERROR(sts, "ippsCopy_16sc");
    }

    // Ipp32sc
    template <>
    inline void Copy(const Ipp32sc* src, Ipp32sc* dst, int len)
    {
        IppStatus sts = ippsCopy_32sc(src, dst, len);
        IPP_NO_ERROR(sts, "ippsCopy_32sc");
    }

    // Ipp32fc
    template <>
    inline void Copy(const Ipp32fc* src, Ipp32fc* dst, int len)
    {
        IppStatus sts = ippsCopy_32fc(src, dst, len);
        IPP_NO_ERROR(sts, "ippsCopy_32fc");
    }

    // Ipp64sc
    template <>
    inline void Copy(const Ipp64sc* src, Ipp64sc* dst, int len)
    {
        IppStatus sts = ippsCopy_64sc(src, dst, len);
        IPP_NO_ERROR(sts, "ippsCopy_64sc");
    }

    // Ipp64fc
    template <>
    inline void Copy(const Ipp64fc* src, Ipp64fc* dst, int len)
    {
        IppStatus sts = ippsCopy_64fc(src, dst, len);
        IPP_NO_ERROR(sts, "ippsCopy_64fc");
    }


}
