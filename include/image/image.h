#pragma once

#include "ipp.h"
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
  size_t m_widthPix = 0;
  size_t m_heightPix = 0;
  IppSizeL m_stepBytes = 0; // This is returned during ippiMalloc functions
  T* m_data = nullptr;

  // Internal allocator (see specializations below)
  T* internal_malloc(const IppSizeL width, const IppSizeL height);

public:
  // Default constructor
  image()
  {
    DEBUG("image()\n");
  }

  // Construct with the IPP struct that contains both width and height
  explicit image(const IppiSize size)
  {
    DEBUG("image(IppiSize)\n");
    reserve(size.width, size.height); // this will set internal member sizes
  }

  // Construct with width, height; stepBytes is assumed equal to the width bytes
  explicit image(
    const size_t width,
    const size_t height = 1
  ){
    DEBUG("image(width, height)\n");
    reserve(width, height); // this will set internal member sizes
  }

  // Copy constructor
  image(const image& other)
  {
    DEBUG("image(const image&)\n");
    reserve(other.m_widthPix, other.m_heightPix); // this will set internal member sizes
    // copy data
    // TODO: use ippiCopy?
    for (size_t i = 0; i < m_heightPix; ++i)
      for (size_t j = 0; j < m_widthPix; ++j)
        this->at(i, j) = other.at(i,j);
  }

  // Assignment operator
  image& operator=(const image& other)
  {
    DEBUG("image& operator=(const image&)\n");
    reserve(other.m_widthPix, other.m_heightPix); // this will set internal member sizes
    // copy data
    // TODO: use ippiCopy?
    for (size_t i = 0; i < m_heightPix; ++i)
      for (size_t j = 0; j < m_widthPix; ++j)
        this->at(i, j) = other.at(i,j);

    return *this;
  }

  // Move constructor
  image(image&& other)
    : m_widthPix(other.m_widthPix),
    m_heightPix(other.m_heightPix),
    m_stepBytes(other.m_stepBytes),
    m_data(other.m_data)
  {
    DEBUG("image(image&&)\n");
    other.m_data = nullptr;
    other.m_widthPix = 0;
    other.m_heightPix = 0;
    other.m_stepBytes = 0;
  }

  // Move assignment operator
  image& operator=(image&& other)
  {
    DEBUG("image& operator=(image&&)\n");
    if (this!= &other)
    {
      // Free old data
      ippiFree(m_data);

      // Copy data from other
      m_widthPix = other.m_widthPix;
      m_heightPix = other.m_heightPix;
      m_stepBytes = other.m_stepBytes;
      m_data = other.m_data;

      // Reset other
      other.m_data = nullptr;
      other.m_widthPix = 0;
      other.m_heightPix = 0;
      other.m_stepBytes = 0;
    }

    return *this;
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
    const size_t height
  ){
    DEBUG("reserve(width, height)\n");

    // Play it safe for now, as long as either width or height has changed
    // then we re-allocate new memory
    if (width != m_widthPix || height != m_heightPix)
    {
      DEBUG("Attempting internal_malloc\n");
      T* newdata = internal_malloc(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height)
      ); // note that this sets m_stepBytes internally

      // Check not null
      if (newdata == nullptr)
      {
        DEBUG("internal_malloc() failed, throwing..\n");
        throw std::bad_alloc();
      }
      DEBUG("internal_malloc() succeeded\n");

      // TODO: copy properly somehow if possible?

      // Free old
      ippiFree(m_data);

      // Set all new internal values
      m_widthPix = width;
      m_heightPix = height;
      m_data = newdata;
    }
    DEBUG("reserve() done\n");
  }

  /* Getters */

  // Width in pixels
  size_t width() const { return m_widthPix; }
  // Height in pixels
  size_t height() const { return m_heightPix; }
  // Distance between lines in bytes
  IppSizeL stepBytes() const { return m_stepBytes; }
  // IPP-specific 'size' struct, useful when calling IPP functions
  IppiSize size() const { return { static_cast<int>(m_widthPix), static_cast<int>(m_heightPix) }; }
  IppiSizeL sizeL() const { return { static_cast<IppSizeL>(m_widthPix), static_cast<IppSizeL>(m_heightPix) }; }

  // Data pointer
  T* data() { return m_data; }
  // Capacity TODO: maybe don't use this, ceases to have same meaning as vector?
  size_t capacity() const { return m_widthPix * m_heightPix; }
  // 0 height & width
  bool empty() const { return m_widthPix == 0 && m_heightPix == 0; }

  /* Setters */

  // TODO: do we really want this? loses its meaning now
  void clear(){ m_widthPix = 0; m_heightPix = 0; m_stepBytes = 0; }

  /* Accessors */

  // Note that this method will not check for out-of-bounds access; preferably use .at()
  T* operator[](const size_t row) {
    // we need to move in byte steps
    Ipp8u *bytePtr = reinterpret_cast<Ipp8u*>(m_data);
    return reinterpret_cast<T*>(bytePtr + row * m_stepBytes);
  }

  const T* operator[](const size_t row) const {
    // we need to move in byte steps
    Ipp8u *bytePtr = reinterpret_cast<Ipp8u*>(m_data);
    return reinterpret_cast<T*>(bytePtr + row * m_stepBytes);
  }

  // Throws std::out_of_range if row or col is out of bounds
  T& at(const size_t row, const size_t col) {
    if (row >= m_heightPix || col >= m_widthPix)
      throw std::out_of_range("row or col out of bounds");

    return (*this)[row][col];
  }

  // Throws std::out_of_range if row or col is out of bounds
  const T& at(const size_t row, const size_t col) const {
    if (row >= m_heightPix || col >= m_widthPix)
      throw std::out_of_range("row or col out of bounds");

    return (*this)[row][col];
  }

};

/*
========================================     Specializations for internal_malloc
*/

// 8u, C1
template <>
inline Ipp8u* image<Ipp8u, channels::C1>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp8u* newdata = ippiMalloc_8u_C1_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 8u, C2
template <>
inline Ipp8u* image<Ipp8u, channels::C2>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp8u* newdata = ippiMalloc_8u_C2_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 8u, C3
template <>
inline Ipp8u* image<Ipp8u, channels::C3>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp8u* newdata = ippiMalloc_8u_C3_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 8u, C4
template <>
inline Ipp8u* image<Ipp8u, channels::C4>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp8u* newdata = ippiMalloc_8u_C4_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 8u, AC4
template <>
inline Ipp8u* image<Ipp8u, channels::AC4>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp8u* newdata = ippiMalloc_8u_AC4_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 16u, C1
template <>
inline Ipp16u* image<Ipp16u, channels::C1>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp16u* newdata = ippiMalloc_16u_C1_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 16u, C2
template <>
inline Ipp16u* image<Ipp16u, channels::C2>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp16u* newdata = ippiMalloc_16u_C2_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 16u, C3
template <>
inline Ipp16u* image<Ipp16u, channels::C3>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp16u* newdata = ippiMalloc_16u_C3_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 16u, C4
template <>
inline Ipp16u* image<Ipp16u, channels::C4>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp16u* newdata = ippiMalloc_16u_C4_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 16u, AC4
template <>
inline Ipp16u* image<Ipp16u, channels::AC4>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp16u* newdata = ippiMalloc_16u_AC4_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 16s, C1
template <>
inline Ipp16s* image<Ipp16s, channels::C1>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp16s* newdata = ippiMalloc_16s_C1_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 16s, C2
template <>
inline Ipp16s* image<Ipp16s, channels::C2>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp16s* newdata = ippiMalloc_16s_C2_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 16s, C3
template <>
inline Ipp16s* image<Ipp16s, channels::C3>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp16s* newdata = ippiMalloc_16s_C3_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 16s, C4
template <>
inline Ipp16s* image<Ipp16s, channels::C4>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp16s* newdata = ippiMalloc_16s_C4_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 16s, AC4
template <>
inline Ipp16s* image<Ipp16s, channels::AC4>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp16s* newdata = ippiMalloc_16s_AC4_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32s, C1
template <>
inline Ipp32s* image<Ipp32s, channels::C1>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    printf("%lld, %lld\n", width, height);
    Ipp32s* newdata = ippiMalloc_32s_C1_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32s, C2
template <>
inline Ipp32s* image<Ipp32s, channels::C2>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32s* newdata = ippiMalloc_32s_C2_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32s, C3
template <>
inline Ipp32s* image<Ipp32s, channels::C3>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32s* newdata = ippiMalloc_32s_C3_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32s, C4
template <>
inline Ipp32s* image<Ipp32s, channels::C4>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32s* newdata = ippiMalloc_32s_C4_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32s, AC4
template <>
inline Ipp32s* image<Ipp32s, channels::AC4>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32s* newdata = ippiMalloc_32s_AC4_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32f, C1
template <>
inline Ipp32f* image<Ipp32f, channels::C1>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32f* newdata = ippiMalloc_32f_C1_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32f, C2
template <>
inline Ipp32f* image<Ipp32f, channels::C2>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32f* newdata = ippiMalloc_32f_C2_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32f, C3
template <>
inline Ipp32f* image<Ipp32f, channels::C3>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32f* newdata = ippiMalloc_32f_C3_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32f, C4
template <>
inline Ipp32f* image<Ipp32f, channels::C4>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32f* newdata = ippiMalloc_32f_C4_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32f, AC4
template <>
inline Ipp32f* image<Ipp32f, channels::AC4>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32f* newdata = ippiMalloc_32f_AC4_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32sc, C1
template <>
inline Ipp32sc* image<Ipp32sc, channels::C1>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32sc* newdata = ippiMalloc_32sc_C1_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32sc, C2
template <>
inline Ipp32sc* image<Ipp32sc, channels::C2>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32sc* newdata = ippiMalloc_32sc_C2_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32sc, C3
template <>
inline Ipp32sc* image<Ipp32sc, channels::C3>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32sc* newdata = ippiMalloc_32sc_C3_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32sc, C4
template <>
inline Ipp32sc* image<Ipp32sc, channels::C4>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32sc* newdata = ippiMalloc_32sc_C4_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32sc, AC4
template <>
inline Ipp32sc* image<Ipp32sc, channels::AC4>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32sc* newdata = ippiMalloc_32sc_AC4_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32fc, C1
template <>
inline Ipp32fc* image<Ipp32fc, channels::C1>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32fc* newdata = ippiMalloc_32fc_C1_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32fc, C2
template <>
inline Ipp32fc* image<Ipp32fc, channels::C2>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32fc* newdata = ippiMalloc_32fc_C2_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32fc, C3
template <>
inline Ipp32fc* image<Ipp32fc, channels::C3>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32fc* newdata = ippiMalloc_32fc_C3_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32fc, C4
template <>
inline Ipp32fc* image<Ipp32fc, channels::C4>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    Ipp32fc* newdata = ippiMalloc_32fc_C4_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    return newdata;
}

// 32fc, AC4
template <>
inline Ipp32fc* image<Ipp32fc, channels::AC4>::internal_malloc(
    const IppSizeL width, const IppSizeL height)
{
    printf("in malloc_32fc_AC4 with %lld, %lld\n", width, height);
    Ipp32fc* newdata = ippiMalloc_32fc_AC4_L(
        static_cast<IppSizeL>(width),
        static_cast<IppSizeL>(height),
        &m_stepBytes
    );
    if(newdata == nullptr) printf("ippiMalloc_32fc_AC4_L failed\n");
    return newdata;
}


};
