#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace math{
        
        template <typename T>
        void Exp(const T* src, T* dst, int len);

        template <typename T>
        void Exp_Sfs(const T* src, T* dst, int len, int scaleFactor);

        template <typename T>
        void Exp_I(T* srcDst, int len);

        template <typename T>
        void Exp_ISfs(T* srcDst, int len, int scaleFactor);

        // ============================
        // ============================ 
        //     Exp Specializations
        // ============================
        // ============================

        template <typename T>
        inline void Exp(const T* src, T* dst, int len){
            throw std::runtime_error("ippsExp only implemented for specific types");
        }

        // Ipp32f
        template <>
        inline void Exp(const Ipp32f* src, Ipp32f* dst, int len){
            IppStatus sts = ippsExp_32f(src, dst, len);
            IPP_NO_ERROR(sts, "ippsExp_32f");
        }

        // Ipp64f
        template <>
        inline void Exp(const Ipp64f* src, Ipp64f* dst, int len){
            IppStatus sts = ippsExp_64f(src, dst, len);
            IPP_NO_ERROR(sts, "ippsExp_64f");
        }

        // ============================
        // ============================ 
        //     Exp_Sfs Specializations
        // ============================
        // ============================

        template <typename T>
        inline void Exp_Sfs(const T* src, T* dst, int len, int scaleFactor){
            throw std::runtime_error("ippsExp_Sfs only implemented for specific types");
        }

        // Ipp16s
        template <>
        inline void Exp_Sfs(const Ipp16s* src, Ipp16s* dst, int len, int scaleFactor){
            IppStatus sts = ippsExp_16s_Sfs(src, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsExp_16s_Sfs");
        }

        // Ipp32s
        template <>
        inline void Exp_Sfs(const Ipp32s* src, Ipp32s* dst, int len, int scaleFactor){
            IppStatus sts = ippsExp_32s_Sfs(src, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsExp_32s_Sfs");
        }

        // ============================
        // ============================ 
        //     Exp_I Specializations
        // ============================
        // ============================

        template <typename T>
        inline void Exp_I(T* srcDst, int len){
            throw std::runtime_error("ippsExp_I only implemented for specific types");
        }

        // Ipp32f
        template <>
        inline void Exp_I(Ipp32f* srcDst, int len){
            IppStatus sts = ippsExp_32f_I(srcDst, len);
            IPP_NO_ERROR(sts, "ippsExp_I_32f");
        }

        // Ipp64f
        template <>
        inline void Exp_I(Ipp64f* srcDst, int len){
            IppStatus sts = ippsExp_64f_I(srcDst, len);
            IPP_NO_ERROR(sts, "ippsExp_I_64f");
        }

        // ============================
        // ============================ 
        //     Exp_ISfs Specializations
        // ============================
        // ============================

        template <typename T>
        inline void Exp_ISfs(T* srcDst, int len, int scaleFactor){
            throw std::runtime_error("ippsExp_ISfs only implemented for specific types");
        }

        // Ipp16s
        template <>
        inline void Exp_ISfs(Ipp16s* srcDst, int len, int scaleFactor){
            IppStatus sts = ippsExp_16s_ISfs(srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsExp_16s_ISfs");
        }

        // Ipp32s
        template <>
        inline void Exp_ISfs(Ipp32s* srcDst, int len, int scaleFactor){
            IppStatus sts = ippsExp_32s_ISfs(srcDst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsExp_32s_ISfs");
        }



    }
}