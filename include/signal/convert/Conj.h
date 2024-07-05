#pragma once

#include "ipp.h"
#include "../../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ipps{
    namespace convert{

        template <typename T>
        void Conj(const T* src, T* dst, int len);

        template <typename T>
        void Conj_I(T* srcDst, int len);

        // ============================
        // ============================ 
        //  Conj Specializations
        // ============================
        // ============================

        template <typename T>
        inline void Conj(const T* src, T* dst, int len){
            throw std::runtime_error("ippsConj not implemented for generic types");
        }

        // 16sc
        template <>
        inline void Conj(const Ipp16sc* src, Ipp16sc* dst, int len){
            IppStatus sts = ippsConj_16sc(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConj_16sc");
        }

        // 32fc
        template <>
        inline void Conj(const Ipp32fc* src, Ipp32fc* dst, int len){
            IppStatus sts = ippsConj_32fc(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConj_32fc");
        }

        // 64fc
        template <>
        inline void Conj(const Ipp64fc* src, Ipp64fc* dst, int len){
            IppStatus sts = ippsConj_64fc(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConj_64fc");
        }

        // ============================
        // ============================ 
        //  Conj_I Specializations
        // ============================
        // ============================

        template <typename T>
        inline void Conj_I(T* srcDst, int len){
            throw std::runtime_error("ippsConj_I not implemented for generic types");
        }

        // 16sc
        template <>
        inline void Conj_I(Ipp16sc* srcDst, int len){
            IppStatus sts = ippsConj_16sc_I(srcDst, len);
            IPP_NO_ERROR(sts, "ippsConj_16sc_I");
        }

        // 32fc
        template <>
        inline void Conj_I(Ipp32fc* srcDst, int len){
            IppStatus sts = ippsConj_32fc_I(srcDst, len);
            IPP_NO_ERROR(sts, "ippsConj_32fc_I");
        }

        // 64fc
        template <>
        inline void Conj_I(Ipp64fc* srcDst, int len){
            IppStatus sts = ippsConj_64fc_I(srcDst, len);
            IPP_NO_ERROR(sts, "ippsConj_64fc_I");
        }
    }
}
