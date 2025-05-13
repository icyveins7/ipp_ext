/*
 * For now, I will ignore the threadling layer (TL) functions.
 * These are the ones that end with _T.
 */

#pragma once

#include <stdexcept>
#include "ipp.h"
#include "../../ipp_ext_errors.h"
#include "../channels.h"
#include "../../signal/ipp_ext_vec.h"

namespace ippi{

/*
* Valid flavours:
* 8u_C1R, 16u_C1R, 16s_C1R, 32f_C1R
* 8u_C3R, 16u_C3R, 16s_C3R
* 8u_AC4R, 16u_AC4R, 16s_AC4R
* 8u_C4R, 16u_C4R, 16s_C4R
*/
template <typename T, channels C>
class FilterMedianBorder
{
public:
    FilterMedianBorder(IppiSize dstRoiSize, IppiSize maskSize)
        : m_dstRoiSize(dstRoiSize), m_maskSize(maskSize)
    {
        if (dstRoiSize.width <= 0 || dstRoiSize.height <= 0)
            throw std::invalid_argument("Invalid ROI size");
        if (maskSize.width <= 0 || maskSize.height <= 0)
            throw std::invalid_argument("Invalid mask size");

        prepare();
    }

    /**
     * @brief Primary method that median filters the image.
     *
     * @param src Source image
     * @param srcStep Number of bytes between source rows
     * @param dst Destination image
     * @param dstStep Number of bytes between destination rows
     * @param borderType Type of border
     * @param borderValue Pointer to border value (depends on type of border),
     *                    has elements equal to channels e.g. (C3) has 3 elements
     */
    void filter(
        const T* src, const int srcStep,
        T* dst, const int dstStep,
        const IppiBorderType borderType,
        const T* borderValue = nullptr
    );

    IppiSize dstRoiSize() const { return m_dstRoiSize; }
    IppiSize maskSize() const { return m_maskSize; }

private:
    IppiSize m_dstRoiSize;
    IppiSize m_maskSize;
    ipps::vector<Ipp8u> m_buffer;

    void prepare();
};


/*
* ============== prepare() specializations =================
*/

template <>
inline void FilterMedianBorder<Ipp8u, channels::C1>::prepare()
{
    int bufferSize;
    IppStatus sts = ippiFilterMedianBorderGetBufferSize(
        m_dstRoiSize, m_maskSize, ipp8u, 1, &bufferSize);
    IPP_NO_ERROR(sts, "ippiFilterMedianBorderGetBufferSize");
    m_buffer.resize((size_t)bufferSize);
}

template <>
inline void FilterMedianBorder<Ipp16u, channels::C1>::prepare()
{
    int bufferSize;
    IppStatus sts = ippiFilterMedianBorderGetBufferSize(
        m_dstRoiSize, m_maskSize, ipp16u, 1, &bufferSize);
    IPP_NO_ERROR(sts, "ippiFilterMedianBorderGetBufferSize");
    m_buffer.resize((size_t)bufferSize);
}

template <>
inline void FilterMedianBorder<Ipp16s, channels::C1>::prepare()
{
    int bufferSize;
    IppStatus sts = ippiFilterMedianBorderGetBufferSize(
        m_dstRoiSize, m_maskSize, ipp16s, 1, &bufferSize);
    IPP_NO_ERROR(sts, "ippiFilterMedianBorderGetBufferSize");
    m_buffer.resize((size_t)bufferSize);
}

template <>
inline void FilterMedianBorder<Ipp32f, channels::C1>::prepare()
{
    int bufferSize;
    IppStatus sts = ippiFilterMedianBorderGetBufferSize(
        m_dstRoiSize, m_maskSize, ipp32f, 1, &bufferSize);
    IPP_NO_ERROR(sts, "ippiFilterMedianBorderGetBufferSize");
    m_buffer.resize((size_t)bufferSize);
}

template <>
inline void FilterMedianBorder<Ipp8u, channels::C3>::prepare()
{
    int bufferSize;
    IppStatus sts = ippiFilterMedianBorderGetBufferSize(
        m_dstRoiSize, m_maskSize, ipp8u, 3, &bufferSize);
    IPP_NO_ERROR(sts, "ippiFilterMedianBorderGetBufferSize");
    m_buffer.resize((size_t)bufferSize);
}

template <>
inline void FilterMedianBorder<Ipp16u, channels::C3>::prepare()
{
    int bufferSize;
    IppStatus sts = ippiFilterMedianBorderGetBufferSize(
        m_dstRoiSize, m_maskSize, ipp16u, 3, &bufferSize);
    IPP_NO_ERROR(sts, "ippiFilterMedianBorderGetBufferSize");
    m_buffer.resize((size_t)bufferSize);
}

template <>
inline void FilterMedianBorder<Ipp16s, channels::C3>::prepare()
{
    int bufferSize;
    IppStatus sts = ippiFilterMedianBorderGetBufferSize(
        m_dstRoiSize, m_maskSize, ipp16s, 3, &bufferSize);
    IPP_NO_ERROR(sts, "ippiFilterMedianBorderGetBufferSize");
    m_buffer.resize((size_t)bufferSize);
}

template <>
inline void FilterMedianBorder<Ipp8u, channels::AC4>::prepare()
{
    int bufferSize;
    IppStatus sts = ippiFilterMedianBorderGetBufferSize(
        m_dstRoiSize, m_maskSize, ipp8u, 4, &bufferSize);
    IPP_NO_ERROR(sts, "ippiFilterMedianBorderGetBufferSize");
    m_buffer.resize((size_t)bufferSize);
}

template <>
inline void FilterMedianBorder<Ipp16u, channels::AC4>::prepare()
{
    int bufferSize;
    IppStatus sts = ippiFilterMedianBorderGetBufferSize(
        m_dstRoiSize, m_maskSize, ipp16u, 4, &bufferSize);
    IPP_NO_ERROR(sts, "ippiFilterMedianBorderGetBufferSize");
    m_buffer.resize((size_t)bufferSize);
}

template <>
inline void FilterMedianBorder<Ipp16s, channels::AC4>::prepare()
{
    int bufferSize;
    IppStatus sts = ippiFilterMedianBorderGetBufferSize(
        m_dstRoiSize, m_maskSize, ipp16s, 4, &bufferSize);
    IPP_NO_ERROR(sts, "ippiFilterMedianBorderGetBufferSize");
    m_buffer.resize((size_t)bufferSize);
}

template <>
inline void FilterMedianBorder<Ipp8u, channels::C4>::prepare()
{
    int bufferSize;
    IppStatus sts = ippiFilterMedianBorderGetBufferSize(
        m_dstRoiSize, m_maskSize, ipp8u, 4, &bufferSize);
    IPP_NO_ERROR(sts, "ippiFilterMedianBorderGetBufferSize");
    m_buffer.resize((size_t)bufferSize);
}

template <>
inline void FilterMedianBorder<Ipp16u, channels::C4>::prepare()
{
    int bufferSize;
    IppStatus sts = ippiFilterMedianBorderGetBufferSize(
        m_dstRoiSize, m_maskSize, ipp16u, 4, &bufferSize);
    IPP_NO_ERROR(sts, "ippiFilterMedianBorderGetBufferSize");
    m_buffer.resize((size_t)bufferSize);
}

template <>
inline void FilterMedianBorder<Ipp16s, channels::C4>::prepare()
{
    int bufferSize;
    IppStatus sts = ippiFilterMedianBorderGetBufferSize(
        m_dstRoiSize, m_maskSize, ipp16s, 4, &bufferSize);
    IPP_NO_ERROR(sts, "ippiFilterMedianBorderGetBufferSize");
    m_buffer.resize((size_t)bufferSize);
}


/*
* ============== filter() specializations =================
*/

template <>
inline void FilterMedianBorder<Ipp8u, channels::C1>::filter(
    const Ipp8u* src, const int srcStep,
    Ipp8u* dst, const int dstStep,
    const IppiBorderType borderType,
    const Ipp8u* borderValue
){
    Ipp8u usedBorderValue = borderValue == nullptr ? 0 : *borderValue;
    IppStatus sts = ippiFilterMedianBorder_8u_C1R(
        src, srcStep, dst, dstStep,
        m_dstRoiSize, m_maskSize, borderType, usedBorderValue,
        m_buffer.data()
    );
    IPP_NO_ERROR(sts, "ippiFilterMedianBorder_8u_C1R");
}

template <>
inline void FilterMedianBorder<Ipp16u, channels::C1>::filter(
    const Ipp16u* src, const int srcStep,
    Ipp16u* dst, const int dstStep,
    const IppiBorderType borderType,
    const Ipp16u* borderValue
){
    Ipp16u usedBorderValue = borderValue == nullptr ? 0 : *borderValue;
    IppStatus sts = ippiFilterMedianBorder_16u_C1R(
        src, srcStep, dst, dstStep,
        m_dstRoiSize, m_maskSize, borderType, usedBorderValue,
        m_buffer.data()
    );
    IPP_NO_ERROR(sts, "ippiFilterMedianBorder_16u_C1R");
}

template <>
inline void FilterMedianBorder<Ipp16s, channels::C1>::filter(
    const Ipp16s* src, const int srcStep,
    Ipp16s* dst, const int dstStep,
    const IppiBorderType borderType,
    const Ipp16s* borderValue
){
    Ipp16s usedBorderValue = borderValue == nullptr ? 0 : *borderValue;
    IppStatus sts = ippiFilterMedianBorder_16s_C1R(
        src, srcStep, dst, dstStep,
        m_dstRoiSize, m_maskSize, borderType, usedBorderValue,
        m_buffer.data()
    );
    IPP_NO_ERROR(sts, "ippiFilterMedianBorder_16s_C1R");
}

template <>
inline void FilterMedianBorder<Ipp32f, channels::C1>::filter(
    const Ipp32f* src, const int srcStep,
    Ipp32f* dst, const int dstStep,
    const IppiBorderType borderType,
    const Ipp32f* borderValue
){
    Ipp32f usedBorderValue = borderValue == nullptr ? 0 : *borderValue;
    IppStatus sts = ippiFilterMedianBorder_32f_C1R(
        src, srcStep, dst, dstStep,
        m_dstRoiSize, m_maskSize, borderType, usedBorderValue,
        m_buffer.data()
    );
    IPP_NO_ERROR(sts, "ippiFilterMedianBorder_32f_C1R");
}

// NOTE: for all the rest, the borderValue is essentially passed as a pointer

template <>
inline void FilterMedianBorder<Ipp8u, channels::C3>::filter(
    const Ipp8u* src, const int srcStep,
    Ipp8u* dst, const int dstStep,
    const IppiBorderType borderType,
    const Ipp8u* borderValue
){
    IppStatus sts = ippiFilterMedianBorder_8u_C3R(
        src, srcStep, dst, dstStep,
        m_dstRoiSize, m_maskSize, borderType, borderValue,
        m_buffer.data()
    );
    IPP_NO_ERROR(sts, "ippiFilterMedianBorder_8u_C3R");
}

template <>
inline void FilterMedianBorder<Ipp16u, channels::C3>::filter(
    const Ipp16u* src, const int srcStep,
    Ipp16u* dst, const int dstStep,
    const IppiBorderType borderType,
    const Ipp16u* borderValue
){
    IppStatus sts = ippiFilterMedianBorder_16u_C3R(
        src, srcStep, dst, dstStep,
        m_dstRoiSize, m_maskSize, borderType, borderValue,
        m_buffer.data()
    );
    IPP_NO_ERROR(sts, "ippiFilterMedianBorder_16u_C3R");
}

template <>
inline void FilterMedianBorder<Ipp16s, channels::C3>::filter(
    const Ipp16s* src, const int srcStep,
    Ipp16s* dst, const int dstStep,
    const IppiBorderType borderType,
    const Ipp16s* borderValue
){
    IppStatus sts = ippiFilterMedianBorder_16s_C3R(
        src, srcStep, dst, dstStep,
        m_dstRoiSize, m_maskSize, borderType, borderValue,
        m_buffer.data()
    );
    IPP_NO_ERROR(sts, "ippiFilterMedianBorder_16s_C3R");
}

template <>
inline void FilterMedianBorder<Ipp8u, channels::AC4>::filter(
    const Ipp8u* src, const int srcStep,
    Ipp8u* dst, const int dstStep,
    const IppiBorderType borderType,
    const Ipp8u* borderValue
){
    IppStatus sts = ippiFilterMedianBorder_8u_AC4R(
        src, srcStep, dst, dstStep,
        m_dstRoiSize, m_maskSize, borderType, borderValue,
        m_buffer.data()
    );
    IPP_NO_ERROR(sts, "ippiFilterMedianBorder_8u_AC4R");
}

template <>
inline void FilterMedianBorder<Ipp16u, channels::AC4>::filter(
    const Ipp16u* src, const int srcStep,
    Ipp16u* dst, const int dstStep,
    const IppiBorderType borderType,
    const Ipp16u* borderValue
){
    IppStatus sts = ippiFilterMedianBorder_16u_AC4R(
        src, srcStep, dst, dstStep,
        m_dstRoiSize, m_maskSize, borderType, borderValue,
        m_buffer.data()
    );
    IPP_NO_ERROR(sts, "ippiFilterMedianBorder_16u_AC4R");
}

template <>
inline void FilterMedianBorder<Ipp16s, channels::AC4>::filter(
    const Ipp16s* src, const int srcStep,
    Ipp16s* dst, const int dstStep,
    const IppiBorderType borderType,
    const Ipp16s* borderValue
){
    IppStatus sts = ippiFilterMedianBorder_16s_AC4R(
        src, srcStep, dst, dstStep,
        m_dstRoiSize, m_maskSize, borderType, borderValue,
        m_buffer.data()
    );
    IPP_NO_ERROR(sts, "ippiFilterMedianBorder_16s_AC4R");
}

template <>
inline void FilterMedianBorder<Ipp8u, channels::C4>::filter(
    const Ipp8u* src, const int srcStep,
    Ipp8u* dst, const int dstStep,
    const IppiBorderType borderType,
    const Ipp8u* borderValue
){
    IppStatus sts = ippiFilterMedianBorder_8u_C4R(
        src, srcStep, dst, dstStep,
        m_dstRoiSize, m_maskSize, borderType, borderValue,
        m_buffer.data()
    );
    IPP_NO_ERROR(sts, "ippiFilterMedianBorder_8u_C4R");
}

template <>
inline void FilterMedianBorder<Ipp16u, channels::C4>::filter(
    const Ipp16u* src, const int srcStep,
    Ipp16u* dst, const int dstStep,
    const IppiBorderType borderType,
    const Ipp16u* borderValue
){
    IppStatus sts = ippiFilterMedianBorder_16u_C4R(
        src, srcStep, dst, dstStep,
        m_dstRoiSize, m_maskSize, borderType, borderValue,
        m_buffer.data()
    );
    IPP_NO_ERROR(sts, "ippiFilterMedianBorder_16u_C4R");
}

template <>
inline void FilterMedianBorder<Ipp16s, channels::C4>::filter(
    const Ipp16s* src, const int srcStep,
    Ipp16s* dst, const int dstStep,
    const IppiBorderType borderType,
    const Ipp16s* borderValue
){
    IppStatus sts = ippiFilterMedianBorder_16s_C4R(
        src, srcStep, dst, dstStep,
        m_dstRoiSize, m_maskSize, borderType, borderValue,
        m_buffer.data()
    );
    IPP_NO_ERROR(sts, "ippiFilterMedianBorder_16s_C4R");
}


} // namespace ippi
