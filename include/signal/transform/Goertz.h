#pragma once

#include "ipp.h"
#include "../../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ipps{
    namespace transform{

        template <typename T, typename U, typename V>
        void Goertz(const T* src, int len, U* val, V rFreq);

        // Developer note: Not exactly sure how the values of the Sfs functions are computed
        // 32f then downconvert? or 64f then downconvert? 
        template <typename T, typename U, typename V>
        void Goertz_Sfs(const T* src, int len, U* val, V rFreq, int scaleFactor);

        // ============================
        // ============================ 
        //  Goertz Specializations
        // ============================
        // ============================

        template <typename T, typename U, typename V>
        inline void Goertz(const T* src, int len, U* val, V rFreq){
            throw std::runtime_error("Goertz not implemented for generic types");
        }

        // 32f to 32fc
        template <>
        inline void Goertz(const Ipp32f* src, int len, Ipp32fc* val, Ipp32f rFreq){
            IppStatus sts = ippsGoertz_32f(src, len, val, rFreq);
            IPP_NO_ERROR(sts, "ippsGoertz_32f");
        }

        // 64f to 64fc
        template <>
        inline void Goertz(const Ipp64f* src, int len, Ipp64fc* val, Ipp64f rFreq){
            IppStatus sts = ippsGoertz_64f(src, len, val, rFreq);
            IPP_NO_ERROR(sts, "ippsGoertz_64f");
        }

        // 32fc to 32fc
        template <>
        inline void Goertz(const Ipp32fc* src, int len, Ipp32fc* val, Ipp32f rFreq){
            IppStatus sts = ippsGoertz_32fc(src, len, val, rFreq);
            IPP_NO_ERROR(sts, "ippsGoertz_32fc");
        }

        // 64fc to 64fc
        template <>
        inline void Goertz(const Ipp64fc* src, int len, Ipp64fc* val, Ipp64f rFreq){
            IppStatus sts = ippsGoertz_64fc(src, len, val, rFreq);
            IPP_NO_ERROR(sts, "ippsGoertz_64fc");
        }

        // ============================
        // ============================ 
        //  Goertz_Sfs Specializations
        // ============================
        // ============================

        template <typename T, typename U, typename V>
        inline void Goertz_Sfs(const T* src, int len, U* val, V rFreq, int scaleFactor){
            throw std::runtime_error("Goertz_Sfs not implemented for generic types");
        }

        // 16s to 16sc
        template <>
        inline void Goertz_Sfs(const Ipp16s* src, int len, Ipp16sc* val, Ipp32f rFreq, int scaleFactor){
            IppStatus sts = ippsGoertz_16s_Sfs(src, len, val, rFreq, scaleFactor);
            IPP_NO_ERROR(sts, "ippsGoertz_16s_Sfs");
        }

        // 16sc to 16sc
        template <>
        inline void Goertz_Sfs(const Ipp16sc* src, int len, Ipp16sc* val, Ipp32f rFreq, int scaleFactor){
            IppStatus sts = ippsGoertz_16sc_Sfs(src, len, val, rFreq, scaleFactor);
            IPP_NO_ERROR(sts, "ippsGoertz_16sc_Sfs");
        }
    }
}
