#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace math{

        template <typename T>
        void Div(const T* src1, const T* src2, T* dst, int len);

        template <typename T, typename U>
        void Div_Sfs(const T* src1, const U* src2, T* dst, int len, int scaleFactor);

        template <typename T>
        void Div_I(const T* src, T* dst, int len);

        template <typename T>
        void Div_ISfs(const T* src, T* dst, int len, int scaleFactor);

        // ============================
        // ============================ 
        //     Div Specializations
        // ============================
        // ============================

        template <typename T>
        inline void Div(const T* src1, const T* src2, T* dst, int len){
            throw std::runtime_error("ippsDiv only implemented for specific types");
        }

        // Ipp32f
        template <>
        inline void Div(const Ipp32f* src1, const Ipp32f* src2, Ipp32f* dst, int len){
            IppStatus sts = ippsDiv_32f(src1, src2, dst, len);
            IPP_NO_ERROR(sts, "ippsDiv_32f");
        }

        // Ipp64f
        template <>
        inline void Div(const Ipp64f* src1, const Ipp64f* src2, Ipp64f* dst, int len){
            IppStatus sts = ippsDiv_64f(src1, src2, dst, len);
            IPP_NO_ERROR(sts, "ippsDiv_64f");
        }

        // Ipp32fc
        template <>
        inline void Div(const Ipp32fc* src1, const Ipp32fc* src2, Ipp32fc* dst, int len){
            IppStatus sts = ippsDiv_32fc(src1, src2, dst, len);
            IPP_NO_ERROR(sts, "ippsDiv_32fc");
        }

        // Ipp64fc
        template <>
        inline void Div(const Ipp64fc* src1, const Ipp64fc* src2, Ipp64fc* dst, int len){
            IppStatus sts = ippsDiv_64fc(src1, src2, dst, len);
            IPP_NO_ERROR(sts, "ippsDiv_64fc");
        }

        // ============================
        // ============================ 
        //     Div_Sfs Specializations
        // ============================
        // ============================

        template <typename T, typename U>
        inline void Div_Sfs(const T* src1, const U* src2, T* dst, int len, int scaleFactor){
            throw std::runtime_error("ippsDiv_Sfs only implemented for specific types");
        }

        // Ipp8u
        template <>
        inline void Div_Sfs(const Ipp8u* src1, const Ipp8u* src2, Ipp8u* dst, int len, int scaleFactor){
            IppStatus sts = ippsDiv_8u_Sfs(src1, src2, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsDiv_8u_Sfs");
        }

        // Ipp16u
        template <>
        inline void Div_Sfs(const Ipp16u* src1, const Ipp16u* src2, Ipp16u* dst, int len, int scaleFactor){
            IppStatus sts = ippsDiv_16u_Sfs(src1, src2, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsDiv_16u_Sfs");
        }

        // Ipp16s
        template <>
        inline void Div_Sfs(const Ipp16s* src1, const Ipp16s* src2, Ipp16s* dst, int len, int scaleFactor){
            IppStatus sts = ippsDiv_16s_Sfs(src1, src2, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsDiv_16s_Sfs");
        }

        // Ipp32s
        template <>
        inline void Div_Sfs(const Ipp32s* src1, const Ipp32s* src2, Ipp32s* dst, int len, int scaleFactor){
            IppStatus sts = ippsDiv_32s_Sfs(src1, src2, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsDiv_32s_Sfs");
        }

        // Ipp16sc
        template <>
        inline void Div_Sfs(const Ipp16sc* src1, const Ipp16sc* src2, Ipp16sc* dst, int len, int scaleFactor){
            IppStatus sts = ippsDiv_16sc_Sfs(src1, src2, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsDiv_16sc_Sfs");
        }

        // Ipp16s, Ipp32s
        template <>
        inline void Div_Sfs(const Ipp16s* src1, const Ipp32s* src2, Ipp16s* dst, int len, int scaleFactor){
            IppStatus sts = ippsDiv_32s16s_Sfs(src1, src2, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsDiv_32s16s_Sfs");
        }

        // ============================
        // ============================ 
        //     Div_I Specializations
        // ============================
        // ============================

        template <typename T>
        inline void Div_I(const T* src, T* dst, int len){
            throw std::runtime_error("ippsDiv_I only implemented for specific types");
        }

        // Ipp32f
        template <>
        inline void Div_I(const Ipp32f* src, Ipp32f* dst, int len){
            IppStatus sts = ippsDiv_32f_I(src, dst, len);
            IPP_NO_ERROR(sts, "ippsDiv_32f_I");
        }

        // Ipp64f
        template <>
        inline void Div_I(const Ipp64f* src, Ipp64f* dst, int len){
            IppStatus sts = ippsDiv_64f_I(src, dst, len);
            IPP_NO_ERROR(sts, "ippsDiv_64f_I");
        }

        // Ipp32fc
        template <>
        inline void Div_I(const Ipp32fc* src, Ipp32fc* dst, int len){
            IppStatus sts = ippsDiv_32fc_I(src, dst, len);
            IPP_NO_ERROR(sts, "ippsDiv_32fc_I");
        }

        // Ipp64fc
        template <>
        inline void Div_I(const Ipp64fc* src, Ipp64fc* dst, int len){
            IppStatus sts = ippsDiv_64fc_I(src, dst, len);
            IPP_NO_ERROR(sts, "ippsDiv_64fc_I");
        }

        // ============================
        // ============================ 
        //     Div_ISfs Specializations
        // ============================
        // ============================

        template <typename T>
        inline void Div_ISfs(const T* src, T* dst, int len, int scaleFactor){
            throw std::runtime_error("ippsDiv_ISfs only implemented for specific types");
        }

        // Ipp8u
        template <>
        inline void Div_ISfs(const Ipp8u* src, Ipp8u* dst, int len, int scaleFactor){
            IppStatus sts = ippsDiv_8u_ISfs(src, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsDiv_8u_ISfs");
        }

        // Ipp16u
        template <>
        inline void Div_ISfs(const Ipp16u* src, Ipp16u* dst, int len, int scaleFactor){
            IppStatus sts = ippsDiv_16u_ISfs(src, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsDiv_16u_ISfs");
        }

        // Ipp16s
        template <>
        inline void Div_ISfs(const Ipp16s* src, Ipp16s* dst, int len, int scaleFactor){
            IppStatus sts = ippsDiv_16s_ISfs(src, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsDiv_16s_ISfs");
        }

        // Ipp16sc
        template <>
        inline void Div_ISfs(const Ipp16sc* src, Ipp16sc* dst, int len, int scaleFactor){
            IppStatus sts = ippsDiv_16sc_ISfs(src, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsDiv_16sc_ISfs");
        }

        // Ipp32s
        template <>
        inline void Div_ISfs(const Ipp32s* src, Ipp32s* dst, int len, int scaleFactor){
            IppStatus sts = ippsDiv_32s_ISfs(src, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsDiv_32s_ISfs");
        }
    }
}