#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace math{

        template <typename T>
        void AddC(const T* src, T val, T* dst, int len);

        template <typename T, typename U>
        void AddC_Sfs(const T* src, T val, T* dst, U len, int scaleFactor, IppRoundMode rndMode=ippRndZero);

        template <typename T>
        void AddC_I(T val, T* srcDst, int len);

        template <typename T>
        void AddC_ISfs(T val, T* srcDst, int len, int scaleFactor);

        // ============================
        // ============================ 
        //     AddC Specializations
        // ============================
        // ============================

        // template <typename T>
        // inline void AddC(T* src, T val, T* dst, int len){
        //     throw std::runtime_error("ippsAddC only implemented for specific types.");
        // }

        // Ipp32f
        template <>
        inline void AddC(const Ipp32f* src, Ipp32f val, Ipp32f* dst, int len){
            IppStatus sts = ippsAddC_32f(src, val, dst, len);
            IPP_NO_ERROR(sts, "ippsAddC_32f");
        }

        // Ipp64f
        template <>
        inline void AddC(const Ipp64f* src, Ipp64f val, Ipp64f* dst, int len){
            IppStatus sts = ippsAddC_64f(src, val, dst, len);
            IPP_NO_ERROR(sts, "ippsAddC_64f");
        }

        // Ipp32fc
        template <>
        inline void AddC(const Ipp32fc* src, Ipp32fc val, Ipp32fc* dst, int len){
            IppStatus sts = ippsAddC_32fc(src, val, dst, len);
            IPP_NO_ERROR(sts, "ippsAddC_32fc");
        }

        // Ipp64fc
        template <>
        inline void AddC(const Ipp64fc* src, Ipp64fc val, Ipp64fc* dst, int len){
            IppStatus sts = ippsAddC_64fc(src, val, dst, len);
            IPP_NO_ERROR(sts, "ippsAddC_64fc");
        }


        // ============================
        // ============================ 
        //     AddC_Sfs Specializations
        // ============================
        // ============================

        // template <typename T, typename U>
        // inline void AddC_Sfs(T* src, T val, T* dst, U len, int scaleFactor, IppRoundMode rndMode){
        //     throw std::runtime_error("ippsAddC_Sfs only implemented for specific types.");
        // }

        // Ipp8u
        template <>
        inline void AddC_Sfs(const Ipp8u* src, Ipp8u val, Ipp8u* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsAddC_8u_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddC_8u_Sfs");
        }

        // Ipp16s
        template <>
        inline void AddC_Sfs(const Ipp16s* src, Ipp16s val, Ipp16s* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsAddC_16s_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddC_16s_Sfs");
        }

        // Ipp16u
        template <>
        inline void AddC_Sfs(const Ipp16u* src, Ipp16u val, Ipp16u* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsAddC_16u_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddC_16u_Sfs");
        }

        // Ipp32s
        template <>
        inline void AddC_Sfs(const Ipp32s* src, Ipp32s val, Ipp32s* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsAddC_32s_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddC_32s_Sfs");
        }

        // Ipp16sc
        template <>
        inline void AddC_Sfs(const Ipp16sc* src, Ipp16sc val, Ipp16sc* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsAddC_16sc_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddC_16sc_Sfs");
        }

        // Ipp32sc
        template <>
        inline void AddC_Sfs(const Ipp32sc* src, Ipp32sc val, Ipp32sc* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsAddC_32sc_Sfs(src, val, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddC_32sc_Sfs");
        }

        // Ipp64u
        template <>
        inline void AddC_Sfs(const Ipp64u* src, Ipp64u val, Ipp64u* dst, Ipp32u len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsAddC_64u_Sfs(src, val, dst, len, scaleFactor, rndMode);
            IPP_NO_ERROR(sts, "ippsAddC_64u_Sfs");
        }

        // Ipp64s
        template <>
        inline void AddC_Sfs(const Ipp64s* src, Ipp64s val, Ipp64s* dst, Ipp32u len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsAddC_64s_Sfs(src, val, dst, len, scaleFactor, rndMode);
            IPP_NO_ERROR(sts, "ippsAddC_64s_Sfs");
        }


        // ============================
        // ============================ 
        // AddC_I Specializations
        // ============================
        // ============================

        // template <typename T>
        // inline void AddC_I(T val, T* srcDst, int len){
        //     throw std::runtime_error("ippsAddC_I only implemented for specific types.");
        // }

        // Ipp16s
        template <>
        inline void AddC_I(Ipp16s val, Ipp16s* srcDst, int len){
            IppStatus sts = ippsAddC_16s_I(val, srcDst, len);
            IPP_NO_ERROR(sts, "ippsAddC_16s_I");
        }

        // Ipp32f
        template <>
        inline void AddC_I(Ipp32f val, Ipp32f* srcDst, int len){
            IppStatus sts = ippsAddC_32f_I(val, srcDst, len);
            IPP_NO_ERROR(sts, "ippsAddC_32f_I");
        }

        // Ipp64f
        template <>
        inline void AddC_I(Ipp64f val, Ipp64f* srcDst, int len){
            IppStatus sts = ippsAddC_64f_I(val, srcDst, len);
            IPP_NO_ERROR(sts, "ippsAddC_64f_I");
        }

        // Ipp32fc
        template <>
        inline void AddC_I(Ipp32fc val, Ipp32fc* srcDst, int len){
            IppStatus sts = ippsAddC_32fc_I(val, srcDst, len);
            IPP_NO_ERROR(sts, "ippsAddC_32fc_I");
        }

        // Ipp64fc
        template <>
        inline void AddC_I(Ipp64fc val, Ipp64fc* srcDst, int len){
            IppStatus sts = ippsAddC_64fc_I(val, srcDst, len);
            IPP_NO_ERROR(sts, "ippsAddC_64fc_I");
        }

        // ============================
        // ============================ 
        // AddC_ISfs Specializations
        // ============================
        // ============================

        template <typename T>
        inline void AddC_ISfs(T val, T* srcDst, int len, int scaleFactor){
            throw std::runtime_error("ippsAddC_ISfs only implemented for specific types.");
        }

        // Ipp8u
        template <>
        inline void AddC_ISfs(Ipp8u val, Ipp8u* srcDst, int len, int scaleFactor){
            IppStatus sts = ippsAddC_8u_ISfs(val, srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddC_8u_ISfs");
        }

        // Ipp16u
        template <>
        inline void AddC_ISfs(Ipp16u val, Ipp16u* srcDst, int len, int scaleFactor){
            IppStatus sts = ippsAddC_16u_ISfs(val, srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddC_16u_ISfs");
        }

        // Ipp16s
        template <>
        inline void AddC_ISfs(Ipp16s val, Ipp16s* srcDst, int len, int scaleFactor){
            IppStatus sts = ippsAddC_16s_ISfs(val, srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddC_16s_ISfs");
        }

        // Ipp32s
        template <>
        inline void AddC_ISfs(Ipp32s val, Ipp32s* srcDst, int len, int scaleFactor){
            IppStatus sts = ippsAddC_32s_ISfs(val, srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddC_32s_ISfs");
        }

        // Ipp16sc
        template <>
        inline void AddC_ISfs(Ipp16sc val, Ipp16sc* srcDst, int len, int scaleFactor){
            IppStatus sts = ippsAddC_16sc_ISfs(val, srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddC_16sc_ISfs");
        }

        // Ipp32sc
        template <>
        inline void AddC_ISfs(Ipp32sc val, Ipp32sc* srcDst, int len, int scaleFactor){
            IppStatus sts = ippsAddC_32sc_ISfs(val, srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddC_32sc_ISfs");
        }
    }
}
