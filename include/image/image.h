#pragma once

#include "ippi.h"
#include "../ipp_ext_errors.h"
#include "channels.h"

#ifndef NDEBUG
#define DEBUG(x) printf(x);
#else
#define DEBUG(x)
#endif

namespace ippi{


template <typename T, channels U>
class image
{
protected:
    size_t cap = 0;
    size_t m_widthPix = 0;
    size_t m_heightPix = 0;
    IppSizeL m_stepBytes = 0;
    T* m_data = nullptr;

    // Internal allocator (see specializations below)
    T* internal_malloc(const IppSizeL width, const IppSizeL height, const IppSizeL *stepBytes);

public:
    // Default constructor
    image()
    {
        DEBUG("image()\n");
    }

    // Construct with the IPP struct that contains both width and height
    explicit image(const IppiSize size)
      : m_widthPix(size.width),
      m_heightPix(size.height),
      m_stepBytes(static_cast<IppSizeL>(size.width*sizeof(T)))
    {
      DEBUG("image(IppiSize)\n");
      reserve(m_widthPix, m_heightPix, m_stepBytes);
    }

    // Construct with width, height; stepBytes is assumed equal to the width bytes
    explicit image(
        const size_t width,
        const size_t height
    )
        : m_widthPix(width)
        , m_heightPix(height),
        m_stepBytes(static_cast<IppSizeL>(sizeof(T) * width))
    {
        DEBUG("image(width, height)\n");
        reserve(m_widthPix, m_heightPix, m_stepBytes);
    }

    // Construct with width, height and stepBytes
    explicit image(
        const size_t width,
        const size_t height,
        const IppSizeL stepBytes
    )
        : m_widthPix(width)
        , m_heightPix(height),
        m_stepBytes(stepBytes)
    {
        DEBUG("image(width, height, stepBytes)\n");
        reserve(m_widthPix, m_heightPix, m_stepBytes);
    }

    // Destructor
    ~image()
    {
        DEBUG("~image()\n");
        ippiFree(m_data);
    }

    // Vector-like reserve, to be template specialized
    void reserve(
        const size_t width,
        const size_t height,
        const IppSizeL stepBytes
    ){
        // Check that the stepBytes can at least accommodate the width
        if (stepBytes < static_cast<IppSizeL>(sizeof(T) * width))
        {
            throw std::invalid_argument("stepBytes insufficient for width");
        }

        DEBUG("reserve(width, height, stepBytes)\n");

        // Play it safe for now, as long as either width or height is bigger than before
        // then we re-allocate new memory
        if (width * height > cap)
        {
            DEBUG("Attempting internal_malloc()\n");
            T* newdata = internal_malloc(
                static_cast<IppSizeL>(width),
                static_cast<IppSizeL>(height),
                &stepBytes
            );

            // Check not null
            if (newdata == nullptr)
            {
                DEBUG("internal_malloc() failed, throwing..\n");
                throw std::runtime_error("internal_malloc() failed");
            }
            DEBUG("internal_malloc() succeeded\n");

            // TODO: copy properly somehow if possible?

            // Free old
            ippiFree(m_data);

            // Set all new internal values
            m_widthPix = width;
            m_heightPix = height;
            m_stepBytes = stepBytes;
            m_data = newdata;
            cap = width * height;
        }
        DEBUG("reserve() done\n");
    }

    /*
    Getters
    */

    // Width in pixels
    size_t width() const { return m_widthPix; }
    // Height in pixels
    size_t height() const { return m_heightPix; }
    // Distance between lines in bytes
    IppSizeL stepBytes() const { return m_stepBytes; }
    // IPP-specific 'size' struct, useful when calling IPP functions
    IppiSize size() const { return { static_cast<int>(m_widthPix), static_cast<int>(m_heightPix) }; }
    // Data pointer
    T* data() { return m_data; }
    // Capacity
    size_t capacity() const { return cap; }
    // 0 height & width
    bool empty() const { return m_widthPix == 0 && m_heightPix == 0; }

    /*
    Setters
    */

    void clear(){ m_widthPix = 0; m_heightPix = 0; m_stepBytes = 0; }



};

/*
========================================     Specializations for internal_malloc
*/

// 8u, C1
template <>
inline Ipp8u* image<Ipp8u, channels::C1>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp8u* newdata = ippiMalloc_8u_C1_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 8u, C2
template <>
inline Ipp8u* image<Ipp8u, channels::C2>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp8u* newdata = ippiMalloc_8u_C2_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 8u, C3
template <>
inline Ipp8u* image<Ipp8u, channels::C3>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp8u* newdata = ippiMalloc_8u_C3_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 8u, C4
template <>
inline Ipp8u* image<Ipp8u, channels::C4>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp8u* newdata = ippiMalloc_8u_C4_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 8u, AC4
template <>
inline Ipp8u* image<Ipp8u, channels::AC4>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp8u* newdata = ippiMalloc_8u_AC4_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 16u, C1
template <>
inline Ipp16u* image<Ipp16u, channels::C1>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp16u* newdata = ippiMalloc_16u_C1_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 16u, C2
template <>
inline Ipp16u* image<Ipp16u, channels::C2>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp16u* newdata = ippiMalloc_16u_C2_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 16u, C3
template <>
inline Ipp16u* image<Ipp16u, channels::C3>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp16u* newdata = ippiMalloc_16u_C3_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 16u, C4
template <>
inline Ipp16u* image<Ipp16u, channels::C4>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp16u* newdata = ippiMalloc_16u_C4_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 16u, AC4
template <>
inline Ipp16u* image<Ipp16u, channels::AC4>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp16u* newdata = ippiMalloc_16u_AC4_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 16s, C1
template <>
inline Ipp16s* image<Ipp16s, channels::C1>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp16s* newdata = ippiMalloc_16s_C1_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 16s, C2
template <>
inline Ipp16s* image<Ipp16s, channels::C2>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp16s* newdata = ippiMalloc_16s_C2_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 16s, C3
template <>
inline Ipp16s* image<Ipp16s, channels::C3>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp16s* newdata = ippiMalloc_16s_C3_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 16s, C4
template <>
inline Ipp16s* image<Ipp16s, channels::C4>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp16s* newdata = ippiMalloc_16s_C4_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 16s, AC4
template <>
inline Ipp16s* image<Ipp16s, channels::AC4>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp16s* newdata = ippiMalloc_16s_AC4_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32s, C1
template <>
inline Ipp32s* image<Ipp32s, channels::C1>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32s* newdata = ippiMalloc_32s_C1_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32s, C2
template <>
inline Ipp32s* image<Ipp32s, channels::C2>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32s* newdata = ippiMalloc_32s_C2_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32s, C3
template <>
inline Ipp32s* image<Ipp32s, channels::C3>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32s* newdata = ippiMalloc_32s_C3_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32s, C4
template <>
inline Ipp32s* image<Ipp32s, channels::C4>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32s* newdata = ippiMalloc_32s_C4_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32s, AC4
template <>
inline Ipp32s* image<Ipp32s, channels::AC4>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32s* newdata = ippiMalloc_32s_AC4_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32f, C1
template <>
inline Ipp32f* image<Ipp32f, channels::C1>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32f* newdata = ippiMalloc_32f_C1_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32f, C2
template <>
inline Ipp32f* image<Ipp32f, channels::C2>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32f* newdata = ippiMalloc_32f_C2_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32f, C3
template <>
inline Ipp32f* image<Ipp32f, channels::C3>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32f* newdata = ippiMalloc_32f_C3_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32f, C4
template <>
inline Ipp32f* image<Ipp32f, channels::C4>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32f* newdata = ippiMalloc_32f_C4_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32f, AC4
template <>
inline Ipp32f* image<Ipp32f, channels::AC4>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32f* newdata = ippiMalloc_32f_AC4_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32sc, C1
template <>
inline Ipp32sc* image<Ipp32sc, channels::C1>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32sc* newdata = ippiMalloc_32sc_C1_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32sc, C2
template <>
inline Ipp32sc* image<Ipp32sc, channels::C2>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32sc* newdata = ippiMalloc_32sc_C2_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32sc, C3
template <>
inline Ipp32sc* image<Ipp32sc, channels::C3>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32sc* newdata = ippiMalloc_32sc_C3_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32sc, C4
template <>
inline Ipp32sc* image<Ipp32sc, channels::C4>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32sc* newdata = ippiMalloc_32sc_C4_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32sc, AC4
template <>
inline Ipp32sc* image<Ipp32sc, channels::AC4>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32sc* newdata = ippiMalloc_32sc_AC4_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32fc, C1
template <>
inline Ipp32fc* image<Ipp32fc, channels::C1>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32fc* newdata = ippiMalloc_32fc_C1_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32fc, C2
template <>
inline Ipp32fc* image<Ipp32fc, channels::C2>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32fc* newdata = ippiMalloc_32fc_C2_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32fc, C3
template <>
inline Ipp32fc* image<Ipp32fc, channels::C3>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32fc* newdata = ippiMalloc_32fc_C3_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32fc, C4
template <>
inline Ipp32fc* image<Ipp32fc, channels::C4>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32fc* newdata = ippiMalloc_32fc_C4_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}

// 32fc, AC4
template <>
inline Ipp32fc* image<Ipp32fc, channels::AC4>::internal_malloc(
    const IppSizeL width, const IppSizeL height, const IppSizeL* stepBytes)
{
    Ipp32fc* newdata = ippiMalloc_32fc_AC4_L(
        static_cast<IppSizeL>(m_widthPix),
        static_cast<IppSizeL>(m_heightPix),
        &m_stepBytes
    );
    return newdata;
}


};
