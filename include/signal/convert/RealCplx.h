#include "ipp.h"
#include "../../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ipps{
    namespace convert{
        template <typename T, typename U>
        void RealToCplx(const T* srcRe, const T* srcIm, U* dst, int len);

        template <typename T, typename U>
        void CplxToReal(const T* src, U* dstRe, U* dstIm, int len);

        // ============================
        // ============================ 
        //  RealToCplx Specializations
        // ============================
        // ============================

        template <typename T, typename U>
        inline void RealToCplx(const T* srcRe, const T* srcIm, U* dst, int len){
            throw std::runtime_error("RealToCplx not implemented for generic types");
        }

        // 16s -> 16sc
        template <>
        inline void RealToCplx(const Ipp16s* srcRe, const Ipp16s* srcIm, Ipp16sc* dst, int len){
            IppStatus sts = ippsRealToCplx_16s(
                srcRe, srcIm, dst, len
            );
            IPP_NO_ERROR(sts, "ippsRealToCplx_16s");
        }

        // 32f -> 32fc
        template <>
        inline void RealToCplx(const Ipp32f* srcRe, const Ipp32f* srcIm, Ipp32fc* dst, int len){
            IppStatus sts = ippsRealToCplx_32f(
                srcRe, srcIm, dst, len
            );
            IPP_NO_ERROR(sts, "ippsRealToCplx_32f");
        }

        // 64f -> 64fc
        template <>
        inline void RealToCplx(const Ipp64f* srcRe, const Ipp64f* srcIm, Ipp64fc* dst, int len){
            IppStatus sts = ippsRealToCplx_64f(
                srcRe, srcIm, dst, len
            );
            IPP_NO_ERROR(sts, "ippsRealToCplx_64f");
        }

        // ============================
        // ============================ 
        //  CplxToReal Specializations
        // ============================
        // ============================

        template <typename T, typename U>
        inline void CplxToReal(const T* src, U* dstRe, U* dstIm, int len){
            throw std::runtime_error("CplxToReal not implemented for generic types");
        }

        // 16sc -> 16s
        template <>
        inline void CplxToReal(const Ipp16sc* src, Ipp16s* dstRe, Ipp16s* dstIm, int len){
            IppStatus sts = ippsCplxToReal_16sc(
                src, dstRe, dstIm, len
            );
            IPP_NO_ERROR(sts, "ippsCplxToReal_16sc");
        }

        // 32fc -> 32f
        template <>
        inline void CplxToReal(const Ipp32fc* src, Ipp32f* dstRe, Ipp32f* dstIm, int len){
            IppStatus sts = ippsCplxToReal_32fc(
                src, dstRe, dstIm, len
            );
            IPP_NO_ERROR(sts, "ippsCplxToReal_32fc");
        }

        // 64fc -> 64f
        template <>
        inline void CplxToReal(const Ipp64fc* src, Ipp64f* dstRe, Ipp64f* dstIm, int len){
            IppStatus sts = ippsCplxToReal_64fc(
                src, dstRe, dstIm, len
            );
            IPP_NO_ERROR(sts, "ippsCplxToReal_64fc");
        }




    }
}
