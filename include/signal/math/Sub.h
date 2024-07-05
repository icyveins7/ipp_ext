#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace math{

        /// @brief Templated function to call ippsSub.
        /// The form that is computed is result = y - x.
        /// @tparam T Input types.
        /// @tparam U Output type. May be different from T.
        /// @param x The input pointer of subtrahends (y-x)
        /// @param y The input pointer of minuends (y-x)
        /// @param result Output vector.
        /// @param len Length of all arrays.
        template <typename T, typename U>
        void Sub(const T* x, const T* y, U* result, int len);


        /// @brief Templated function to call ippsSub_Sfs.
        /// The form that is computed is result = y - x.
        /// @tparam T Input/output types.
        /// @param x The input pointer of subtrahends (y-x)
        /// @param y The input pointer of minuends (y-x)
        /// @param result Output vector.
        /// @param len Length of all arrays.
        /// @param scaleFactor 2^(-scaleFactor) is applied.
        template <typename T>
        void Sub_Sfs(const T* x, const T* y, T* result, int len, int scaleFactor);


        /// @brief Templated function to call ippsSub_I.
        /// The form that is computed is result = result - x.
        /// @tparam T Input/output types.
        /// @param x The input pointer of subtrahends (y-x)
        /// @param result Output vector.
        /// @param len Length of all arrays.
        template <typename T>
        void Sub_I(const T* x, T* result, int len);


        /// @brief Templated function to call ippsSub_ISfs.
        /// The form that is computed is result = result - x.
        /// @tparam T Input/output types.
        /// @param x The input pointer of subtrahends (y-x)
        /// @param result Output vector.
        /// @param len Length of all arrays.
        /// @param scaleFactor 2^(-scaleFactor) is applied.
        template <typename T>
        void Sub_ISfs(const T* x, T* result, int len, int scaleFactor);

        // ============================
        // ============================ 
        //     Sub Specializations
        // ============================
        // ============================

        // template <typename T, typename U>
        // inline void Sub(T* x, T* y, U* result, int len){
        //     throw std::runtime_error("ippsSub not implemented for generic types.");
        // }

        // Ipp16s

        template <>
        inline void Sub(const Ipp16s* x, const Ipp16s* y, Ipp16s* result, int len)
        {
            IppStatus sts = ippsSub_16s(x, y, result, len);
            IPP_NO_ERROR(sts, "ippsSub_16s");
        }

        // Ipp32f

        template <>
        inline void Sub(const Ipp32f* x, const Ipp32f* y, Ipp32f* result, int len)
        {
            IppStatus sts = ippsSub_32f(x, y, result, len);
            IPP_NO_ERROR(sts, "ippsSub_32f");
        }

        // Ipp64f

        template <>
        inline void Sub(const Ipp64f* x, const Ipp64f* y, Ipp64f* result, int len)
        {
            IppStatus sts = ippsSub_64f(x, y, result, len);
            IPP_NO_ERROR(sts, "ippsSub_64f");
        }

        // Ipp32fc

        template <>
        inline void Sub(const Ipp32fc* x, const Ipp32fc* y, Ipp32fc* result, int len)
        {
            IppStatus sts = ippsSub_32fc(x, y, result, len);
            IPP_NO_ERROR(sts, "ippsSub_32fc");
        }

        // Ipp64fc

        template <>
        inline void Sub(const Ipp64fc* x, const Ipp64fc* y, Ipp64fc* result, int len)
        {
            IppStatus sts = ippsSub_64fc(x, y, result, len);
            IPP_NO_ERROR(sts, "ippsSub_64fc");
        }

        // Ipp16s to Ipp32f

        template <>
        inline void Sub(const Ipp16s* x, const Ipp16s* y, Ipp32f* result, int len)
        {
            IppStatus sts = ippsSub_16s32f(x, y, result, len);
            IPP_NO_ERROR(sts, "ippsSub_16s32f");
        }

        // ============================
        // ============================ 
        //     Sub_Sfs Specializations
        // ============================
        // ============================

        // template <typename T>
        // inline void Sub_Sfs(T* x, T* y, T* result, int len, int scaleFactor)
        // {
        //     throw std::runtime_error("ippsSub_Sfs not implemented for generic types.");
        // }

        // Ipp8u

        template <>
        inline void Sub_Sfs(const Ipp8u* x, const Ipp8u* y, Ipp8u* result, int len, int scaleFactor)
        {
            IppStatus sts = ippsSub_8u_Sfs(x, y, result, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSub_8u_Sfs");
        }

        // Ipp16u

        template <>
        inline void Sub_Sfs(const Ipp16u* x, const Ipp16u* y, Ipp16u* result, int len, int scaleFactor)
        {
            IppStatus sts = ippsSub_16u_Sfs(x, y, result, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSub_16u_Sfs");
        }

        // Ipp16s

        template <>
        inline void Sub_Sfs(const Ipp16s* x, const Ipp16s* y, Ipp16s* result, int len, int scaleFactor)
        {
            IppStatus sts = ippsSub_16s_Sfs(x, y, result, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSub_16s_Sfs");
        }

        // Ipp32s

        template <>
        inline void Sub_Sfs(const Ipp32s* x, const Ipp32s* y, Ipp32s* result, int len, int scaleFactor)
        {
            IppStatus sts = ippsSub_32s_Sfs(x, y, result, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSub_32s_Sfs");
        }

        // Ipp16sc

        template <>
        inline void Sub_Sfs(const Ipp16sc* x, const Ipp16sc* y, Ipp16sc* result, int len, int scaleFactor)
        {
            IppStatus sts = ippsSub_16sc_Sfs(x, y, result, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSub_16sc_Sfs");
        }

        // Ipp32sc

        template <>
        inline void Sub_Sfs(const Ipp32sc* x, const Ipp32sc* y, Ipp32sc* result, int len, int scaleFactor)
        {
            IppStatus sts = ippsSub_32sc_Sfs(x, y, result, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSub_32sc_Sfs");
        }

        // ============================
        // ============================ 
        //     Sub_I Specializations
        // ============================
        // ============================

        // template <typename T>
        // inline void Sub_I(T* x, T* result, int len)
        // {
        //     throw std::runtime_error("ippsSub_I not implemented for generic types.");
        // }

        // Ipp16s

        template <>
        inline void Sub_I(const Ipp16s* x, Ipp16s* result, int len)
        {
            IppStatus sts = ippsSub_16s_I(x, result, len);
            IPP_NO_ERROR(sts, "ippsSub_16s_I");
        }

        // Ipp32f 

        template <>
        inline void Sub_I(const Ipp32f* x, Ipp32f* result, int len)
        {
            IppStatus sts = ippsSub_32f_I(x, result, len);
            IPP_NO_ERROR(sts, "ippsSub_32f_I");
        }

        // Ipp64f

        template <>
        inline void Sub_I(const Ipp64f* x, Ipp64f* result, int len)
        {
            IppStatus sts = ippsSub_64f_I(x, result, len);
            IPP_NO_ERROR(sts, "ippsSub_64f_I");
        }

        // Ipp32fc

        template <>
        inline void Sub_I(const Ipp32fc* x, Ipp32fc* result, int len)
        {
            IppStatus sts = ippsSub_32fc_I(x, result, len);
            IPP_NO_ERROR(sts, "ippsSub_32fc_I");
        }

        // Ipp64fc

        template <>
        inline void Sub_I(const Ipp64fc* x, Ipp64fc* result, int len)
        {
            IppStatus sts = ippsSub_64fc_I(x, result, len);
            IPP_NO_ERROR(sts, "ippsSub_64fc_I");
        }

        // ============================
        // ============================ 
        //     Sub_ISfs Specializations
        // ============================
        // ============================

        // template <typename T>
        // inline void Sub_ISfs(T* x, T* result, int len, int scaleFactor)
        // {
        //     throw std::runtime_error("ippsSub_ISfs not implemented for generic types.");
        // }

        // Ipp8u

        template <>
        inline void Sub_ISfs(const Ipp8u* x, Ipp8u* result, int len, int scaleFactor)
        {
            IppStatus sts = ippsSub_8u_ISfs(x, result, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSub_8u_ISfs");
        }

        // Ipp16u

        template <>
        inline void Sub_ISfs(const Ipp16u* x, Ipp16u* result, int len, int scaleFactor)
        {
            IppStatus sts = ippsSub_16u_ISfs(x, result, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSub_16u_ISfs");
        }

        // Ipp16s

        template <>
        inline void Sub_ISfs(const Ipp16s* x, Ipp16s* result, int len, int scaleFactor)
        {
            IppStatus sts = ippsSub_16s_ISfs(x, result, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSub_16s_ISfs");
        }

        // Ipp32s

        template <>
        inline void Sub_ISfs(const Ipp32s* x, Ipp32s* result, int len, int scaleFactor)
        {
            IppStatus sts = ippsSub_32s_ISfs(x, result, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSub_32s_ISfs");
        }

        // Ipp16sc

        template <>
        inline void Sub_ISfs(const Ipp16sc* x, Ipp16sc* result, int len, int scaleFactor)
        {
            IppStatus sts = ippsSub_16sc_ISfs(x, result, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSub_16sc_ISfs");
        }

        // Ipp32sc

        template <>
        inline void Sub_ISfs(const Ipp32sc* x, Ipp32sc* result, int len, int scaleFactor)
        {
            IppStatus sts = ippsSub_32sc_ISfs(x, result, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsSub_32sc_ISfs");
        }
    }
}
