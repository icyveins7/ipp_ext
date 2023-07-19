#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace math{

        template <typename T>
        void MulC(const T* src, const T val, T* dst, int len);

        template <typename T, typename U>
        void MulC_Sfs(const T* src, const T val, U* dst, int len, int scaleFactor);

        template <typename T>
        void MulC_I(const T val, T* srcDst, int len);

        template <typename T, typename U, typename V>
        void MulC_ISfs(const T val, U* srcDst, V len, int scaleFactor);

        // ============================
        // ============================ 
        //     MulC Specializations
        // ============================
        // ============================

        template <typename T>
        inline void MulC(const T* src, const T val, T* dst, int len){
            throw std::runtime_error("ippsMulC not implemented for generic type");
        }

        // Ipp32f
        template <>
        inline void MulC(const Ipp32f* src, const Ipp32f val, Ipp32f* dst, int len){
            IppStatus sts = ippsMulC_32f(src, val, dst, len);
            IPP_NO_ERROR(sts, "ippsMulC_32f");
        }

        // Ipp64f
        template <>
        inline void MulC(const Ipp64f* src, const Ipp64f val, Ipp64f* dst, int len){
            IppStatus sts = ippsMulC_64f(src, val, dst, len);
            IPP_NO_ERROR(sts, "ippsMulC_64f");
        }

        // Ipp32fc
        template <>
        inline void MulC(const Ipp32fc* src, const Ipp32fc val, Ipp32fc* dst, int len){
            IppStatus sts = ippsMulC_32fc(src, val, dst, len);
            IPP_NO_ERROR(sts, "ippsMulC_32fc");
        }

        // Ipp64fc
        template <>
        inline void MulC(const Ipp64fc* src, const Ipp64fc val, Ipp64fc* dst, int len){
            IppStatus sts = ippsMulC_64fc(src, val, dst, len);
            IPP_NO_ERROR(sts, "ippsMulC_64fc");
        }

        // ============================
        // ============================ 
        //     MulC_Sfs Specializations
        // ============================
        // ============================

        template <typename T, typename U>
        inline void MulC_Sfs(const T* src, const T val, U* dst, int len, int scaleFactor){
            throw std::runtime_error("ippsMulC_Sfs not implemented for generic type");
        }

        // Ipp8u
        template <>
        inline void MulC_Sfs(const Ipp8u* src, const Ipp8u val, Ipp8u* dst, int len, int scaleFactor){
            IppStatus sts = ippsMulC_8u_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_8u_Sfs");
        }

        // Ipp16s
        template <>
        inline void MulC_Sfs(const Ipp16s* src, const Ipp16s val, Ipp16s* dst, int len, int scaleFactor){
            IppStatus sts = ippsMulC_16s_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_16s_Sfs");
        }

        // Ipp16u
        template <>
        inline void MulC_Sfs(const Ipp16u* src, const Ipp16u val, Ipp16u* dst, int len, int scaleFactor){
            IppStatus sts = ippsMulC_16u_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_16u_Sfs");
        }

        // Ipp32s
        template <>
        inline void MulC_Sfs(const Ipp32s* src, const Ipp32s val, Ipp32s* dst, int len, int scaleFactor){
            IppStatus sts = ippsMulC_32s_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_32s_Sfs");
        }

        // Ipp16sc
        template <>
        inline void MulC_Sfs(const Ipp16sc* src, const Ipp16sc val, Ipp16sc* dst, int len, int scaleFactor){
            IppStatus sts = ippsMulC_16sc_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_16sc_Sfs");
        }

        // Ipp32sc
        template <>
        inline void MulC_Sfs(const Ipp32sc* src, const Ipp32sc val, Ipp32sc* dst, int len, int scaleFactor){
            IppStatus sts = ippsMulC_32sc_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_32sc_Sfs");
        }

        // Ipp32f to Ipp16s
        template <>
        inline void MulC_Sfs(const Ipp32f* src, const Ipp32f val, Ipp16s* dst, int len, int scaleFactor){
            IppStatus sts = ippsMulC_32f16s_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_32f16s_Sfs");
        }

        // ============================
        // ============================ 
        //     MulC_I Specializations
        // ============================
        // ============================

        template <typename T>
        inline void MulC_I(const T val, T* srcDst, int len){
            throw std::runtime_error("ippsMulC_I not implemented for generic type");
        }

        // Ipp16s
        template <>
        inline void MulC_I(const Ipp16s val, Ipp16s* srcDst, int len){
            IppStatus sts = ippsMulC_16s_I(val, srcDst, len);
            IPP_NO_ERROR(sts, "ippsMulC_16s_I");
        }

        // Ipp32f
        template <>
        inline void MulC_I(const Ipp32f val, Ipp32f* srcDst, int len){
            IppStatus sts = ippsMulC_32f_I(val, srcDst, len);
            IPP_NO_ERROR(sts, "ippsMulC_32f_I");
        }

        // Ipp64f
        template <>
        inline void MulC_I(const Ipp64f val, Ipp64f* srcDst, int len){
            IppStatus sts = ippsMulC_64f_I(val, srcDst, len);
            IPP_NO_ERROR(sts, "ippsMulC_64f_I");
        }

        // Ipp32fc
        template <>
        inline void MulC_I(const Ipp32fc val, Ipp32fc* srcDst, int len){
            IppStatus sts = ippsMulC_32fc_I(val, srcDst, len);
            IPP_NO_ERROR(sts, "ippsMulC_32fc_I");
        }

        // Ipp64fc
        template <>
        inline void MulC_I(const Ipp64fc val, Ipp64fc* srcDst, int len){
            IppStatus sts = ippsMulC_64fc_I(val, srcDst, len);
            IPP_NO_ERROR(sts, "ippsMulC_64fc_I");
        }


        // ============================
        // ============================ 
        //     MulC_ISfs Specializations
        // ============================
        // ============================

        template <typename T, typename U, typename V>
        inline void MulC_ISfs(const T val, U* srcDst, V len, int scaleFactor){
            throw std::runtime_error("ippsMulC_ISfs not implemented for generic type");
        }

        // Ipp8u
        template <>
        inline void MulC_ISfs(const Ipp8u val, Ipp8u* srcDst, int len, int scaleFactor){
            IppStatus sts = ippsMulC_8u_ISfs(val, srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_8u_ISfs");
        }

        // Ipp16u
        template <>
        inline void MulC_ISfs(const Ipp16u val, Ipp16u* srcDst, int len, int scaleFactor){
            IppStatus sts = ippsMulC_16u_ISfs(val, srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_16u_ISfs");
        }

        // Ipp16s
        template <>
        inline void MulC_ISfs(const Ipp16s val, Ipp16s* srcDst, int len, int scaleFactor){
            IppStatus sts = ippsMulC_16s_ISfs(val, srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_16s_ISfs");
        }

        // Ipp32s
        template <>
        inline void MulC_ISfs(const Ipp32s val, Ipp32s* srcDst, int len, int scaleFactor){
            IppStatus sts = ippsMulC_32s_ISfs(val, srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_32s_ISfs");
        }

        // Ipp64f to Ipp64s
        template <>
        inline void MulC_ISfs(const Ipp64f val, Ipp64s* srcDst, Ipp32u len, int scaleFactor){
            IppStatus sts = ippsMulC_64f64s_ISfs(val, srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_64f64s_ISfs");
        }

        // Ipp16sc
        template <>
        inline void MulC_ISfs(const Ipp16sc val, Ipp16sc* srcDst, int len, int scaleFactor){
            IppStatus sts = ippsMulC_16sc_ISfs(val, srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_16sc_ISfs");
        }

        // Ipp32sc
        template <>
        inline void MulC_ISfs(const Ipp32sc val, Ipp32sc* srcDst, int len, int scaleFactor){
            IppStatus sts = ippsMulC_32sc_ISfs(val, srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_32sc_ISfs");
        }

        // Ipp64s
        template <>
        inline void MulC_ISfs(const Ipp64s val, Ipp64s* srcDst, Ipp32u len, int scaleFactor){
            IppStatus sts = ippsMulC_64s_ISfs(val, srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMulC_64s_ISfs");
        }

    }
}