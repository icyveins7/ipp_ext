#pragma once

#include "ipp.h"
#include <stdexcept>
#include <string>
#include "../../signal/ipp_ext_vec.h"
#include "../../ipp_ext_errors.h"
#include "../channels.h"

namespace ippi
{

template <typename T>
class DFT_RToPack
{
public:
  DFT_RToPack() = default;

  DFT_RToPack(IppiSize roiSize, int flag = IPP_FFT_NODIV_BY_ANY)
    : m_roiSize(roiSize), m_flag(flag)
  {
    if (roiSize.width <= 0 || roiSize.height <= 0)
      throw std::invalid_argument("Invalid ROI size");

    prepare_dft();
  }

  template <channels U>
  void fwd(const T* src, int srcStep, T* dst, int dstStep);

  template <channels U>
  void inv(const T* src, int srcStep, T* dst, int dstStep);

  // Getters
  IppiSize roiSize() const { return m_roiSize; }

  // Fwd output size (for real types)
  IppiSize fwdOutputSize() const{
    // NOTE: this is columns * rows
    return {
      m_roiSize.width,
      m_roiSize.height % 2 == 0 ?
        m_roiSize.height :   // even rows
        m_roiSize.height + 1 // odd rows
    };
  }

  // Bwd output size (for real types)
  IppiSize bwdOutputSize() const{
    // NOTE: this is columns * rows
    return { m_roiSize.width, 1 };
  }

private:
  IppiSize m_roiSize = {0, 0};
  int m_flag = 0;

  ipps::vector<Ipp8u> m_DFTSpec;
  ipps::vector<Ipp8u> m_MemBuffer;

  void prepare_dft();

};

// ============================================================
// prepare_dft specializations
// ============================================================

// Ipp32f
template <>
inline void DFT_RToPack<Ipp32f>::prepare_dft()
{
  int sizeSpec, sizeInit, sizeBuffer;
  IPP_NO_ERROR(
    ippiDFTGetSize_R_32f(
      m_roiSize, m_flag, ippAlgHintNone,
      &sizeSpec, &sizeInit, &sizeBuffer
    ),
    "ippiDFTGetSize_R_32f"
  );

  // Resize the buffers
  m_DFTSpec.resize(sizeSpec);
  if (sizeBuffer > 0)
    m_MemBuffer.resize(sizeBuffer);

  // Temporary memInit buffer if required
  ipps::vector<Ipp8u> memInit;
  if (sizeInit > 0)
    memInit.resize(sizeInit);

  // Initialize DFT spec
  IPP_NO_ERROR(
    ippiDFTInit_R_32f(
      m_roiSize, m_flag,
      ippAlgHintNone, 
      reinterpret_cast<IppiDFTSpec_R_32f*>(m_DFTSpec.data()),
      memInit.data()
    ),
    "ippiDFTInit_R_32f"
  );
}

// ============================================================
// fwd specializations
// ============================================================

// Ipp32f, C1
template <>
template <>
inline void DFT_RToPack<Ipp32f>::fwd<channels::C1>(
  const Ipp32f* src, int srcStep, Ipp32f* dst, int dstStep
){
  IPP_NO_ERROR(
    ippiDFTFwd_RToPack_32f_C1R(
      src, srcStep, dst, dstStep,
      reinterpret_cast<IppiDFTSpec_R_32f*>(m_DFTSpec.data()),
      m_MemBuffer.data()
    ),
    "ippiDFTFwd_RToPack_32f_C1R"
  );
}

// Ipp32f, C3
template <>
template <>
inline void DFT_RToPack<Ipp32f>::fwd<channels::C3>(
  const Ipp32f* src, int srcStep, Ipp32f* dst, int dstStep
){
  IPP_NO_ERROR(
    ippiDFTFwd_RToPack_32f_C3R(
      src, srcStep, dst, dstStep,
      reinterpret_cast<IppiDFTSpec_R_32f*>(m_DFTSpec.data()),
      m_MemBuffer.data()
    ),
    "ippiDFTFwd_RToPack_32f_C3R"
  );
}

// Ipp32f, C4
template <>
template <>
inline void DFT_RToPack<Ipp32f>::fwd<channels::C4>(
  const Ipp32f* src, int srcStep, Ipp32f* dst, int dstStep
){
  IPP_NO_ERROR(
    ippiDFTFwd_RToPack_32f_C4R(
      src, srcStep, dst, dstStep,
      reinterpret_cast<IppiDFTSpec_R_32f*>(m_DFTSpec.data()),
      m_MemBuffer.data()
    ),
    "ippiDFTFwd_RToPack_32f_C4R"
  );
}

// Ipp32f, AC4
template <>
template <>
inline void DFT_RToPack<Ipp32f>::fwd<channels::AC4>(
  const Ipp32f* src, int srcStep, Ipp32f* dst, int dstStep
){
  IPP_NO_ERROR(
    ippiDFTFwd_RToPack_32f_AC4R(
      src, srcStep, dst, dstStep,
      reinterpret_cast<IppiDFTSpec_R_32f*>(m_DFTSpec.data()),
      m_MemBuffer.data()
    ),
    "ippiDFTFwd_RToPack_32f_AC4R"
  );
}


// ============================================================
// inv specializations
// ============================================================

// Ipp32f, C1
template <>
template <>
inline void DFT_RToPack<Ipp32f>::inv<channels::C1>(
  const Ipp32f* src, int srcStep, Ipp32f* dst, int dstStep
){
  IPP_NO_ERROR(
    ippiDFTInv_PackToR_32f_C1R(
      src, srcStep, dst, dstStep,
      reinterpret_cast<IppiDFTSpec_R_32f*>(m_DFTSpec.data()),
      m_MemBuffer.data()
    ),
    "ippiDFTInv_PackToR_32f_C1R"
  );
}

// Ipp32f, C3
template <>
template <>
inline void DFT_RToPack<Ipp32f>::inv<channels::C3>(
  const Ipp32f* src, int srcStep, Ipp32f* dst, int dstStep
){
  IPP_NO_ERROR(
    ippiDFTInv_PackToR_32f_C3R(
      src, srcStep, dst, dstStep,
      reinterpret_cast<IppiDFTSpec_R_32f*>(m_DFTSpec.data()),
      m_MemBuffer.data()
    ),
    "ippiDFTInv_PackToR_32f_C3R"
  );
}

// Ipp32f, C4
template <>
template <>
inline void DFT_RToPack<Ipp32f>::inv<channels::C4>(
  const Ipp32f* src, int srcStep, Ipp32f* dst, int dstStep
){
  IPP_NO_ERROR(
    ippiDFTInv_PackToR_32f_C4R(
      src, srcStep, dst, dstStep,
      reinterpret_cast<IppiDFTSpec_R_32f*>(m_DFTSpec.data()),
      m_MemBuffer.data()
    ),
    "ippiDFTInv_PackToR_32f_C4R"
  );
}

// Ipp32f, AC4
template <>
template <>
inline void DFT_RToPack<Ipp32f>::inv<channels::AC4>(
  const Ipp32f* src, int srcStep, Ipp32f* dst, int dstStep
){
  IPP_NO_ERROR(
    ippiDFTInv_PackToR_32f_AC4R(
      src, srcStep, dst, dstStep,
      reinterpret_cast<IppiDFTSpec_R_32f*>(m_DFTSpec.data()),
      m_MemBuffer.data()
    ),
    "ippiDFTInv_PackToR_32f_AC4R"
  );
}


}
