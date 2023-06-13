#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace math{
        /// @brief Templated function to call ippsAdd.
        /// Some flavours may change the resulting type.
        /// @tparam T Input types.
        /// @tparam U Output type.
        /// @param x First input pointer.
        /// @param y Second input pointer.
        /// @param result Output pointer.
        /// @param length Length of all arrays.
        template <typename T, typename U>
        void Add(T* x, T* y, U* result, int length);

        /// @brief Templated function to call ippsAdd_Sfs.
        /// @tparam T Input/output type.
        /// @param x First input pointer.
        /// @param y Second input pointer.
        /// @param result Output pointer.
        /// @param length Length of all arrays.
        /// @param scaleFactor 2^(-scaleFactor) is applied.
        template <typename T>
        void Add_Sfs(T* x, T* y, T* result, int length, int scaleFactor);


        /// @brief Templated function to call ippsAdd_I.
        /// @tparam T Input type.
        /// @tparam U Input and Output type.
        /// @param x Input pointer.
        /// @param result Input and output pointer. Result is accumulated in place.
        /// @param length Length of all arrays.
        template <typename T, typename U>
        void Add_I(T* x, U* result, int length);

        /// @brief Templated function to call ippsAdd_I_Sfs.
        /// @tparam T Input/output type.
        /// @param x Input pointer.
        /// @param result Input and output pointer. Result is accumulated in place.
        /// @param length Length of all arrays.
        /// @param scaleFactor 2^(-scaleFactor) is applied.
        template <typename T>
        void Add_ISfs(T* x, T* result, int length, int scaleFactor);

        // ============================
        // ============================ 
        //     Add Specializations
        // ============================
        // ============================

        template <typename T, typename U>
        inline void Add(T* x, T* y, U* result, int length)
        {
            throw std::runtime_error("ippsAdd only implemented for specific types.");
        }

        // Ipp16s

        template <>
        inline void Add(Ipp16s* x, Ipp16s* y, Ipp16s* result, int length)
        {
            IppStatus sts = ippsAdd_16s(
                x, y, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_16s");
        }

        // Ipp32f

        template <>
        inline void Add(Ipp32f* x, Ipp32f* y, Ipp32f* result, int length)
        {
            IppStatus sts = ippsAdd_32f(
                x, y, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_32f");
        }

        // Ipp64f

        template <>
        inline void Add(Ipp64f* x, Ipp64f* y, Ipp64f* result, int length)
        {
            IppStatus sts = ippsAdd_64f(
                x, y, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_64f");
        }

        // Ipp32fc

        template <>
        inline void Add(Ipp32fc* x, Ipp32fc* y, Ipp32fc* result, int length)
        {
            IppStatus sts = ippsAdd_32fc(
                x, y, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_32fc");
        }

        // Ipp64fc

        template <>
        inline void Add(Ipp64fc* x, Ipp64fc* y, Ipp64fc* result, int length)
        {
            IppStatus sts = ippsAdd_64fc(
                x, y, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_64fc");
        }

        // Ipp8u to Ipp16u

        template <>
        inline void Add(Ipp8u* x, Ipp8u* y, Ipp16u* result, int length)
        {
            IppStatus sts = ippsAdd_8u16u(
                x, y, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_8u16u");
        }

        // Ipp16u

        template <>
        inline void Add(Ipp16u* x, Ipp16u* y, Ipp16u* result, int length)
        {
            IppStatus sts = ippsAdd_16u(
                x, y, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_16u");
        }

        // Ipp32u

        template <>
        inline void Add(Ipp32u* x, Ipp32u* y, Ipp32u* result, int length)
        {
            IppStatus sts = ippsAdd_32u(
                x, y, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_32u");
        }

        // Ipp16s to Ipp32f

        template <>
        inline void Add(Ipp16s* x, Ipp16s* y, Ipp32f* result, int length)
        {
            IppStatus sts = ippsAdd_16s32f(
                x, y, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_16s32f");
        }

        // ============================
        // ============================ 
        //     Add_Sfs Specializations
        // ============================
        // ============================

        template <typename T>
        inline void Add_Sfs(T* x, T* y, T* result, int length, int scaleFactor)
        {
            throw std::runtime_error("ippsAdd_Sfs only implemented for specific types.");
        }

        // Ipp8u

        template <>
        inline void Add_Sfs(Ipp8u* x, Ipp8u* y, Ipp8u* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsAdd_8u_Sfs(
                x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAdd_8u_Sfs");
        }

        // Ipp16u

        template <>
        inline void Add_Sfs(Ipp16u* x, Ipp16u* y, Ipp16u* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsAdd_16u_Sfs(
                x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAdd_16u_Sfs");
        }
        
        // Ipp16s

        template <>
        inline void Add_Sfs(Ipp16s* x, Ipp16s* y, Ipp16s* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsAdd_16s_Sfs(
                x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAdd_16s_Sfs");
        }
        
        // Ipp32s

        template <>
        inline void Add_Sfs(Ipp32s* x, Ipp32s* y, Ipp32s* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsAdd_32s_Sfs(
                x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAdd_32s_Sfs");
        }
        
        // Ipp16sc

        template <>
        inline void Add_Sfs(Ipp16sc* x, Ipp16sc* y, Ipp16sc* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsAdd_16sc_Sfs(
                x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAdd_16sc_Sfs");
        }

        // Ipp32sc

        template <>
        inline void Add_Sfs(Ipp32sc* x, Ipp32sc* y, Ipp32sc* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsAdd_32sc_Sfs(
                x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAdd_32sc_Sfs");
        }

        // Ipp64s

        template <>
        inline void Add_Sfs(Ipp64s* x, Ipp64s* y, Ipp64s* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsAdd_64s_Sfs(
                x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAdd_64s_Sfs");
        }

        // ============================
        // ============================ 
        // Add (in-place) Specializations
        // ============================
        // ============================

        template<typename T, typename U>
        inline void Add_I(T* x, U* result, int length)
        {
            throw std::runtime_error("ippsAdd_I only implemented for specific types.");
        }

        // Ipp16s

        template <>
        inline void Add_I(Ipp16s* x, Ipp16s* result, int length)
        {
            IppStatus sts = ippsAdd_16s_I(
                x, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_16s_I");
        }

        // Ipp32f

        template <>
        inline void Add_I(Ipp32f* x, Ipp32f* result, int length)
        {
            IppStatus sts = ippsAdd_32f_I(
                x, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_32f_I");
        }

        // Ipp64f

        template <>
        inline void Add_I(Ipp64f* x, Ipp64f* result, int length)
        {
            IppStatus sts = ippsAdd_64f_I(
                x, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_64f_I");
        }

        // Ipp32fc

        template <>
        inline void Add_I(Ipp32fc* x, Ipp32fc* result, int length)
        {
            IppStatus sts = ippsAdd_32fc_I(
                x, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_32fc_I");
        }

        // Ipp64fc

        template <>
        inline void Add_I(Ipp64fc* x, Ipp64fc* result, int length)
        {
            IppStatus sts = ippsAdd_64fc_I(
                x, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_64fc_I");
        }

        // Ipp16s to Ipp32s

        template <>
        inline void Add_I(Ipp16s* x, Ipp32s* result, int length)
        {
            IppStatus sts = ippsAdd_16s32s_I(
                x, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_16s32s_I");
        }

        // Ipp32u

        template <>
        inline void Add_I(Ipp32u* x, Ipp32u* result, int length)
        {
            IppStatus sts = ippsAdd_32u_I(
                x, result, length);
            IPP_NO_ERROR(sts, "ippsAdd_32u_I");
        }

        // ============================
        // ============================ 
        // Add_Sfs (in-place) Specializations
        // ============================
        // ============================

        template <typename T>
        inline void Add_ISfs(T* x, T* result, int length, int scaleFactor)
        {
            throw std::runtime_error("ippsAdd_ISfs only implemented for specific types.");
        }

        // Ipp8u

        template <>
        inline void Add_ISfs(Ipp8u* x, Ipp8u* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsAdd_8u_ISfs(
                x, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAdd_8u_ISfs");
        }

        // Ipp16u

        template <>
        inline void Add_ISfs(Ipp16u* x, Ipp16u* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsAdd_16u_ISfs(
                x, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAdd_16u_ISfs");
        }

        // Ipp16s

        template <>
        inline void Add_ISfs(Ipp16s* x, Ipp16s* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsAdd_16s_ISfs(
                x, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAdd_16s_ISfs");
        }

        // Ipp32s
        
        template <>
        inline void Add_ISfs(Ipp32s* x, Ipp32s* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsAdd_32s_ISfs(
                x, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAdd_32s_ISfs");
        }

        // Ipp16sc

        template <>
        inline void Add_ISfs(Ipp16sc* x, Ipp16sc* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsAdd_16sc_ISfs(
                x, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAdd_16sc_ISfs");
        }

        // Ipp32sc

        template <>
        inline void Add_ISfs(Ipp32sc* x, Ipp32sc* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsAdd_32sc_ISfs(
                x, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAdd_32sc_ISfs");
        }
    }
}