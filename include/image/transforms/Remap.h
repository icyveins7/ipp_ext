#pragma once

#include "ipp.h"
#include <stdexcept>
#include <string>
#include "../../signal/ipp_ext_vec.h"
#include "../../ipp_ext_errors.h"
#include "../channels.h"

namespace ippi
{

template <channels C, typename T, typename U>
void Remap(const T* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
           const U* pxMap, int xMapStep, const U* pyMap, int yMapStep,
           T* dst, int dstStep, IppiSize dstRoi, int interpolation);

// Specializations

// Ipp8u, C1, Ipp32f for xy
template <>
inline void Remap<channels::C1>(const Ipp8u* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                Ipp8u* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_8u_C1R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_8u_C1R");
}

// Ipp8u, C3, Ipp32f for xy
template <>
inline void Remap<channels::C3>(const Ipp8u* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                Ipp8u* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_8u_C3R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_8u_C3R");
}

// Ipp8u, C4, Ipp32f for xy
template <>
inline void Remap<channels::C4>(const Ipp8u* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                Ipp8u* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_8u_C4R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_8u_C4R");
}

// Ipp16u, C1, Ipp32f for xy
template <>
inline void Remap<channels::C1>(const Ipp16u* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                Ipp16u* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_16u_C1R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_16u_C1R");
}

// Ipp16u, C3, Ipp32f for xy
template <>
inline void Remap<channels::C3>(const Ipp16u* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                Ipp16u* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_16u_C3R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_16u_C3R");
}

// Ipp16u, C4, Ipp32f for xy
template <>
inline void Remap<channels::C4>(const Ipp16u* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                Ipp16u* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_16u_C4R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_16u_C4R");
}

// Ipp16u, AC4, Ipp32f for xy
template <>
inline void Remap<channels::AC4>(const Ipp16u* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                 const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                 Ipp16u* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_16u_AC4R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_16u_AC4R");
}


// Ipp16s, C1, Ipp32f for xy
template <>
inline void Remap<channels::C1>(const Ipp16s* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                Ipp16s* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_16s_C1R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_16s_C1R");
}

// Ipp16s, C3, Ipp32f for xy
template <>
inline void Remap<channels::C3>(const Ipp16s* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                Ipp16s* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_16s_C3R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_16s_C3R");
}

// Ipp16s, C4, Ipp32f for xy
template <>
inline void Remap<channels::C4>(const Ipp16s* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                Ipp16s* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_16s_C4R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_16s_C4R");
}

// Ipp16s, AC4, Ipp32f for xy
template <>
inline void Remap<channels::AC4>(const Ipp16s* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                 const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                 Ipp16s* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_16s_AC4R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_16s_AC4R");
}


// Ipp32f, C1, Ipp32f for xy
template <>
inline void Remap<channels::C1>(const Ipp32f* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                Ipp32f* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_32f_C1R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_32f_C1R");
}

// Ipp32f, C3, Ipp32f for xy
template <>
inline void Remap<channels::C3>(const Ipp32f* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                Ipp32f* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_32f_C3R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_32f_C3R");
}

// Ipp32f, C4, Ipp32f for xy
template <>
inline void Remap<channels::C4>(const Ipp32f* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                Ipp32f* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_32f_C4R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_32f_C4R");
}

// Ipp32f, AC4, Ipp32f for xy
template <>
inline void Remap<channels::AC4>(const Ipp32f* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                 const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap, int yMapStep,
                                 Ipp32f* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_32f_AC4R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_32f_AC4R");
}


// Ipp64f, C1, Ipp64f for xy
template <>
inline void Remap<channels::C1>(const Ipp64f* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp64f* pxMap, int xMapStep, const Ipp64f* pyMap, int yMapStep,
                                Ipp64f* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_64f_C1R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_64f_C1R");
}

// Ipp64f, C3, Ipp64f for xy
template <>
inline void Remap<channels::C3>(const Ipp64f* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp64f* pxMap, int xMapStep, const Ipp64f* pyMap, int yMapStep,
                                Ipp64f* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_64f_C3R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_64f_C3R");
}

// Ipp64f, C4, Ipp64f for xy
template <>
inline void Remap<channels::C4>(const Ipp64f* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                const Ipp64f* pxMap, int xMapStep, const Ipp64f* pyMap, int yMapStep,
                                Ipp64f* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_64f_C4R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_64f_C4R");
}

// Ipp64f, AC4, Ipp64f for xy
template <>
inline void Remap<channels::AC4>(const Ipp64f* src, IppiSize srcSize, int srcStep, IppiRect srcRoi,
                                 const Ipp64f* pxMap, int xMapStep, const Ipp64f* pyMap, int yMapStep,
                                 Ipp64f* dst, int dstStep, IppiSize dstRoi, int interpolation)
{
  IppStatus sts = ippiRemap_64f_AC4R(
    src, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, yMapStep, dst, dstStep, dstRoi, interpolation
  );
  IPP_NO_ERROR(sts, "ippiRemap_64f_AC4R");
}

} // end of namespace ippi
