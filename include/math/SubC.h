#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace math{

        template <typename T>
        void SubC(const T* src, T val, T* dst, int len);

        template <typename T>
        void SubC_Sfs(const T* src, T val, T* dst, int len, int scaleFactor);

        template <typename T>
        void SubC_I(T val, T* dst, int len);

        template <typename T>
        void SubC_ISfs(T val, T* dst, int len, int scaleFactor);

        // ============================
        // ============================ 
        //     SubC Specializations
        // ============================
        // ============================

        template <typename T>
        inline void SubC(const T* src, T val, T* dst, int len){
            throw std::runtime_error("ippsSubC not implemented for specific types");
        }

        // Ipp32f
        template <>
        inline void SubC(const Ipp32f* src, Ipp32f val, Ipp32f* dst, int len){
            IppStatus sts = ippsSubC_32f(src, val, dst, len);
            IPP_NO_ERROR(sts, "ippsSubC_32f");
        }

        // Ipp64f
        template <>
        inline void SubC(const Ipp64f* src, Ipp64f val, Ipp64f* dst, int len){
            IppStatus sts = ippsSubC_64f(src, val, dst, len);
            IPP_NO_ERROR(sts, "ippsSubC_64f");
        }

        // Ipp32fc
        template <>
        inline void SubC(const Ipp32fc* src, Ipp32fc val, Ipp32fc* dst, int len){
            IppStatus sts = ippsSubC_32fc(src, val, dst, len);
            IPP_NO_ERROR(sts, "ippsSubC_32fc");
        }

        // Ipp64fc
        template <>
        inline void SubC(const Ipp64fc* src, Ipp64fc val, Ipp64fc* dst, int len){
            IppStatus sts = ippsSubC_64fc(src, val, dst, len);
            IPP_NO_ERROR(sts, "ippsSubC_64fc");
        }

        // ============================
        // ============================ 
        //     SubC_Sfs Specializations
        // ============================
        // ============================

        template <typename T>
        inline void SubC_Sfs(const T* src, T val, T* dst, int len, int scaleFactor){
            throw std::runtime_error("ippsSubC_Sfs not implemented for specific types");
        }

        // Ipp8u
        template <>
        inline void SubC_Sfs(const Ipp8u* src, Ipp8u val, Ipp8u* dst, int len, int scaleFactor){
            IppStatus sts = ippsSubC_8u_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSubC_8u_Sfs");
        }

        // Ipp16u
        template <>
        inline void SubC_Sfs(const Ipp16u* src, Ipp16u val, Ipp16u* dst, int len, int scaleFactor){
            IppStatus sts = ippsSubC_16u_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSubC_16u_Sfs");
        }

        // Ipp16s
        template <>
        inline void SubC_Sfs(const Ipp16s* src, Ipp16s val, Ipp16s* dst, int len, int scaleFactor){
            IppStatus sts = ippsSubC_16s_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSubC_16s_Sfs");
        }

        // Ipp32s
        template <>
        inline void SubC_Sfs(const Ipp32s* src, Ipp32s val, Ipp32s* dst, int len, int scaleFactor){
            IppStatus sts = ippsSubC_32s_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSubC_32s_Sfs");
        }

        // Ipp16sc
        template <>
        inline void SubC_Sfs(const Ipp16sc* src, Ipp16sc val, Ipp16sc* dst, int len, int scaleFactor){
            IppStatus sts = ippsSubC_16sc_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSubC_16sc_Sfs");
        }

        // Ipp32sc
        template <>
        inline void SubC_Sfs(const Ipp32sc* src, Ipp32sc val, Ipp32sc* dst, int len, int scaleFactor){
            IppStatus sts = ippsSubC_32sc_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSubC_32sc_Sfs");
        }

        // ============================
        // ============================ 
        //     SubC_I Specializations
        // ============================
        // ============================

        template <typename T>
        inline void SubC_I(T val, T* dst, int len){
            throw std::runtime_error("ippsSubC_I not implemented for specific types");
        }

        // Ipp16s
        template <>
        inline void SubC_I(Ipp16s val, Ipp16s* dst, int len){
            IppStatus sts = ippsSubC_16s_I(val, dst, len);
            IPP_NO_ERROR(sts, "ippsSubC_16s_I");
        }

        // Ipp32f
        template <>
        inline void SubC_I(Ipp32f val, Ipp32f* dst, int len){
            IppStatus sts = ippsSubC_32f_I(val, dst, len);
            IPP_NO_ERROR(sts, "ippsSubC_32f_I");
        }

        // Ipp64f
        template <>
        inline void SubC_I(Ipp64f val, Ipp64f* dst, int len){
            IppStatus sts = ippsSubC_64f_I(val, dst, len);
            IPP_NO_ERROR(sts, "ippsSubC_64f_I");
        }

        // Ipp32fc
        template <>
        inline void SubC_I(Ipp32fc val, Ipp32fc* dst, int len){
            IppStatus sts = ippsSubC_32fc_I(val, dst, len);
            IPP_NO_ERROR(sts, "ippsSubC_32fc_I");
        }

        // Ipp64fc
        template <>
        inline void SubC_I(Ipp64fc val, Ipp64fc* dst, int len){
            IppStatus sts = ippsSubC_64fc_I(val, dst, len);
            IPP_NO_ERROR(sts, "ippsSubC_64fc_I");
        }

        // ============================
        // ============================ 
        //     SubC_ISfs Specializations
        // ============================
        // ============================

        template <typename T>
        inline void SubC_ISfs(T val, T* dst, int len, int scaleFactor){
            throw std::runtime_error("ippsSubC_I_Sfs not implemented for specific types");
        }

        // Ipp8u
        template <>
        inline void SubC_ISfs(Ipp8u val, Ipp8u* dst, int len, int scaleFactor){
            IppStatus sts = ippsSubC_8u_ISfs(val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSubC_8u_ISfs");
        }

        // Ipp16u
        template <>
        inline void SubC_ISfs(Ipp16u val, Ipp16u* dst, int len, int scaleFactor){
            IppStatus sts = ippsSubC_16u_ISfs(val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSubC_16u_ISfs");
        }

        // Ipp16s
        template <>
        inline void SubC_ISfs(Ipp16s val, Ipp16s* dst, int len, int scaleFactor){
            IppStatus sts = ippsSubC_16s_ISfs(val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSubC_16s_ISfs");
        }

        // Ipp32s
        template <>
        inline void SubC_ISfs(Ipp32s val, Ipp32s* dst, int len, int scaleFactor){
            IppStatus sts = ippsSubC_32s_ISfs(val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSubC_32s_ISfs");
        }

        // Ipp16sc
        template <>
        inline void SubC_ISfs(Ipp16sc val, Ipp16sc* dst, int len, int scaleFactor){
            IppStatus sts = ippsSubC_16sc_ISfs(val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSubC_16sc_ISfs");
        }

        // Ipp32sc
        template <>
        inline void SubC_ISfs(Ipp32sc val, Ipp32sc* dst, int len, int scaleFactor){
            IppStatus sts = ippsSubC_32sc_ISfs(val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSubC_32sc_ISfs");
        }


    }
}