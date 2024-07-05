#pragma once

#include "ippi.h"
#include "../ipp_ext_errors.h"

#ifndef NDEBUG
#define DEBUG(x) printf(x);
#else
#define DEBUG(x)
#endif

namespace ippi{

// Define possible types for malloc
enum class channels{
    C1, // 1 channel
    C2, // 2 channels
    C3, // 3 channels
    C4, // 4 channels
    AC4 // 4 channels with alpha at end
};

/*

*/
template <typename T, channels U>
class image
{
protected:
    size_t m_widthPix = 0;
    size_t m_heightPix = 0;
    IppSizeL m_stepBytes = 0;
    bool m_hasAlpha = false;
    T* m_data = nullptr;

public:
    // Default constructor
    image()
    {
        DEBUG("image()\n");
    }

    // Construct with width, height, stepBytes is exactly equal to the width bytes
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
    );

    /*
    Getters
    */

    // Width in pixels
    size_t width() const { return m_widthPix; }
    // Height in pixels
    size_t height() const { return m_heightPix; }
    // Step in bytes
    IppSizeL stepBytes() const { return m_stepBytes; }
    // Has alpha channel
    bool hasAlpha() const { return m_hasAlpha; }
    // Data pointer
    T* data() { return m_data; }

};

/*
========================================     Specializations for reserve
*/
template <>
inline void image<Ipp8u, channels::C1>::reserve(const size_t width, const size_t height, const IppSizeL stepBytes)
{
    // Play it safe for now, as long as either width or height is bigger than before
    // then we re-allocate new memory
    if (width > m_widthPix || height > m_heightPix)
    {
        Ipp8u* newdata = ippiMalloc_8u_C1_L(
            static_cast<IppSizeL>(m_widthPix),
            static_cast<IppSizeL>(m_heightPix),
            &m_stepBytes
        );

        // Check not null
        if (newdata == nullptr)
        {
            throw std::bad_alloc();
        }

        // TODO: copy properly somehow if possible?

        // Free old
        ippiFree(m_data);

        // Set all new internal values
        m_widthPix = width;
        m_heightPix = height;
        m_stepBytes = stepBytes;
        m_hasAlpha = false;
        m_data = newdata;
    }
}

};
