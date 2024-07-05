#include "ipp.h"
#include "../../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ipps{
    namespace convert{
        template <typename T, typename U>
        void PolarToCart(const T* srcMagn, const T* srcPhase, U* dst, int len);

        template <typename T, typename U>
        void CartToPolar(const T* src, U* dstMagn, U* dstPhase, int len);

        template <typename T>
        void PolarToCartDeinterleaved(const T* srcMagn, const T* srcPhase, T* dstRe, T* dstIm, int len);

        // ============================
        // ============================ 
        //  PolarToCart Specializations
        // ============================
        // ============================

        template <typename T, typename U>
        inline void PolarToCart(const T* srcMagn, const T* srcPhase, U* dst, int len){
            throw std::runtime_error("PolarToCart not implemented for generic types");
        }

        // 32f,32f -> 32fc

        template <>
        inline void PolarToCart(const Ipp32f* srcMagn, const Ipp32f* srcPhase, Ipp32fc* dst, int len){
            IppStatus status = ippsPolarToCart_32fc(
                srcMagn,
                srcPhase,
                dst,
                len
            );
            IPP_NO_ERROR(status, "ippsPolarToCart_32fc");
        }

        // 64f, 64f -> 64fc
        
        template <>
        inline void PolarToCart(const Ipp64f* srcMagn, const Ipp64f* srcPhase, Ipp64fc* dst, int len){
            IppStatus status = ippsPolarToCart_64fc(
                srcMagn,
                srcPhase,
                dst,
                len
            );
            IPP_NO_ERROR(status, "ippsPolarToCart_64fc");
        }

        // ============================
        // ============================ 
        //  CartToPolar Specializations
        // ============================
        // ============================      

        template <typename T, typename U>
        inline void CartToPolar(const T* src, U* dstMagn, U* dstPhase, int len){
            throw std::runtime_error("CartToPolar not implemented for generic types");
        }    

        // 32fc -> 32f, 32f

        template <>
        inline void CartToPolar(const Ipp32fc* src, Ipp32f* dstMagn, Ipp32f* dstPhase, int len){
            IppStatus status = ippsCartToPolar_32fc(
                src,
                dstMagn,
                dstPhase,
                len
            );
            IPP_NO_ERROR(status, "ippsCartToPolar_32fc");
        }

        // 64fc -> 64f, 64f
        template <>
        inline void CartToPolar(const Ipp64fc* src, Ipp64f* dstMagn, Ipp64f* dstPhase, int len){
            IppStatus status = ippsCartToPolar_64fc(
                src,
                dstMagn,
                dstPhase,
                len
            );
            IPP_NO_ERROR(status, "ippsCartToPolar_64fc");
        }

        // ============================
        // ============================ 
        //  PolarToCartDeInterleaved Specializations
        // ============================
        // ============================

        // 32f
        template <>
        inline void PolarToCartDeinterleaved(const Ipp32f* srcMagn, const Ipp32f* srcPhase, Ipp32f* dstRe, Ipp32f* dstIm, int len){
            IppStatus status = ippsPolarToCart_32f(
                srcMagn,
                srcPhase,
                dstRe,
                dstIm,
                len
            );
            IPP_NO_ERROR(status, "ippsPolarToCart_32f");
        }

        // 64f
        template <>
        inline void PolarToCartDeinterleaved(const Ipp64f* srcMagn, const Ipp64f* srcPhase, Ipp64f* dstRe, Ipp64f* dstIm, int len){
            IppStatus status = ippsPolarToCart_64f(
                srcMagn,
                srcPhase,
                dstRe,
                dstIm,
                len
            );
            IPP_NO_ERROR(status, "ippsPolarToCart_64f");
        }
    }
}
