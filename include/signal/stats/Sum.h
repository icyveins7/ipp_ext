#pragma once

#include "ipp.h"
#include "../../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ipps{
    namespace stats{

        template <typename T>
        void Sum(const T* src, int len, T* sum, IppHintAlgorithm hint=IppHintAlgorithm::ippAlgHintNone);

        // TODO: add Sfs flavours

        // ============================
        // ============================ 
        //  Sum Specializations
        // ============================
        // ============================

        template <typename T>
        inline void Sum(const T* /*src*/, int /*len*/, T* /*sum*/, IppHintAlgorithm /*hint*/){
            throw std::runtime_error("Sum not implemented for generic types");
        }

        // 32f, uses hint
        template <>
        inline void Sum(const Ipp32f* src, int len, Ipp32f* sum, IppHintAlgorithm hint){
            IppStatus sts = ippsSum_32f(src, len, sum, hint);
            IPP_NO_ERROR(sts, "ippsSum_32f");
        }

        // 32fc, uses hint
        template <>
        inline void Sum(const Ipp32fc* src, int len, Ipp32fc* sum, IppHintAlgorithm hint){
            IppStatus sts = ippsSum_32fc(src, len, sum, hint);
            IPP_NO_ERROR(sts, "ippsSum_32fc");
        }

        // 64f, hint ignored
        template <>
        inline void Sum(const Ipp64f* src, int len, Ipp64f* sum, IppHintAlgorithm /*hint*/){
            IppStatus sts = ippsSum_64f(src, len, sum);
            IPP_NO_ERROR(sts, "ippsSum_64f");
        }

        // 64fc, hint ignored
        template <>
        inline void Sum(const Ipp64fc* src, int len, Ipp64fc* sum, IppHintAlgorithm /*hint*/){
            IppStatus sts = ippsSum_64fc(src, len, sum);
            IPP_NO_ERROR(sts, "ippsSum_64fc");
        }

    }
}
