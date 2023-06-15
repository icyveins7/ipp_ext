#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace math{

        /// @brief Templated function to call ippsMul.
        /// @tparam T First input type.
        /// @tparam U Second input type.
        /// @tparam V Output type.
        /// @param x First input pointer.
        /// @param y Second input pointer.
        /// @param result Output pointer.
        /// @param length Length of all arrays.
        template <typename T, typename U, typename V>
        void Mul(T* x, U* y, V* result, int length);

        /// @brief Templated function to call ippsMulC.
        /// @tparam T First input type.
        /// @tparam U Second input type.
        /// @tparam V Output type.
        /// @param x First input pointer.
        /// @param y Second input pointer.
        /// @param result Output pointer.
        /// @param length Length of all arrays.
        /// @param scaleFactor 2^-scaleFactor is applied to output.
        template <typename T, typename U, typename V>
        void Mul_Sfs(T* x, U* y, V* result, int length, int scaleFactor);

        /// @brief Templated function to call ippsMul_I.
        /// @tparam T Input type.
        /// @tparam U Input/output type. 
        /// @param x Input pointer.
        /// @param result Input/output pointer. Result is written in-place.
        /// @param length Length of all arrays.
        template <typename T, typename U>
        void Mul_I(T* x, U* result, int length);

        // /// @brief Multiplies current matrix by another, writing the result in-place.
        // /// @tparam U Type of the other matrix. In most cases this is the same type.
        // /// @param other The second matrix to multiply.
        // template <typename U>
        // void mul_I(matrix<U>& other);

        // /// @brief Multiplies current matrix by another with integer scaling, writing the result in-place.
        // /// @param other The second matrix to multiply.
        // /// @param scaleFactor The integer scaling factor. Output is multiplied by 2^(-scaleFactor).
        // void mul_ISfs(matrix& other, int scaleFactor);

        // ============================
        // ============================ 
        //     Mul Specializations
        // ============================
        // ============================

        template <typename T, typename U, typename V>
        inline void Mul(T* x, U* y, V* result, int length)
        {
            throw std::runtime_error("ippsMul only implemented for specific types.");
        }

        // Ipp16s

        template <>
        inline void Mul(Ipp16s* x, Ipp16s* y, Ipp16s* result, int length)
        {
            IppStatus sts = ippsMul_16s(x, y, result, length);
            IPP_NO_ERROR(sts, "ippsMul_16s");
        }

        // Ipp32f

        template <>
        inline void Mul(Ipp32f* x, Ipp32f* y, Ipp32f* result, int length)
        {
            IppStatus sts = ippsMul_32f(x, y, result, length);
            IPP_NO_ERROR(sts, "ippsMul_32f");
        }

        // Ipp64f

        template <>
        inline void Mul(Ipp64f* x, Ipp64f* y, Ipp64f* result, int length)
        {
            IppStatus sts = ippsMul_64f(x, y, result, length);
            IPP_NO_ERROR(sts, "ippsMul_64f");
        }

        // Ipp32fc

        template <>
        inline void Mul(Ipp32fc* x, Ipp32fc* y, Ipp32fc* result, int length)
        {
            IppStatus sts = ippsMul_32fc(x, y, result, length);
            IPP_NO_ERROR(sts, "ippsMul_32fc");
        }

        // Ipp64fc

        template <>
        inline void Mul(Ipp64fc* x, Ipp64fc* y, Ipp64fc* result, int length)
        {
            IppStatus sts = ippsMul_64fc(x, y, result, length);
            IPP_NO_ERROR(sts, "ippsMul_64fc");
        }

        // Ipp8u, Ipp8u to Ipp16u

        template <>
        inline void Mul(Ipp8u* x, Ipp8u* y, Ipp16u* result, int length)
        {
            IppStatus sts = ippsMul_8u16u(x, y, result, length);
            IPP_NO_ERROR(sts, "ippsMul_8u16u");
        }

        // Ipp32f, Ipp32fc to Ipp32fc

        template <>
        inline void Mul(Ipp32f* x, Ipp32fc* y, Ipp32fc* result, int length)
        {
            IppStatus sts = ippsMul_32f32fc(x, y, result, length);
            IPP_NO_ERROR(sts, "ippsMul_32f32fc");
        }

        // Ipp16s, Ipp16s to Ipp32f

        template <>
        inline void Mul(Ipp16s* x, Ipp16s* y, Ipp32f* result, int length)
        {
            IppStatus sts = ippsMul_16s32f(x, y, result, length);
            IPP_NO_ERROR(sts, "ippsMul_16s32f");
        }

        // ============================
        // ============================ 
        //     Mul_Sfs Specializations
        // ============================
        // ============================

        template <typename T, typename U, typename V>
        inline void Mul_Sfs(T* x, U* y, V* result, int length, int scaleFactor)
        {
            throw std::runtime_error("ippsMul_Sfs only implemented for specific types.");
        }

        // Ipp8u

        template <>
        inline void Mul_Sfs(Ipp8u* x, Ipp8u* y, Ipp8u* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsMul_8u_Sfs(x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMul_8u_Sfs");
        }

        // Ipp16u

        template <>
        inline void Mul_Sfs(Ipp16u* x, Ipp16u* y, Ipp16u* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsMul_16u_Sfs(x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMul_16u_Sfs");
        }

        // Ipp16s

        template <>
        inline void Mul_Sfs(Ipp16s* x, Ipp16s* y, Ipp16s* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsMul_16s_Sfs(x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMul_16s_Sfs");
        }

        // Ipp32s

        template <>
        inline void Mul_Sfs(Ipp32s* x, Ipp32s* y, Ipp32s* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsMul_32s_Sfs(x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMul_32s_Sfs");
        }

        // Ipp16sc

        template <>
        inline void Mul_Sfs(Ipp16sc* x, Ipp16sc* y, Ipp16sc* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsMul_16sc_Sfs(x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMul_16sc_Sfs");
        }

        // Ipp32sc

        template <>
        inline void Mul_Sfs(Ipp32sc* x, Ipp32sc* y, Ipp32sc* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsMul_32sc_Sfs(x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMul_32sc_Sfs");
        }

        // Ipp16s, Ipp16s -> Ipp32s

        template <>
        inline void Mul_Sfs(Ipp16s* x, Ipp16s* y, Ipp32s* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsMul_16s32s_Sfs(x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMul_16s32s_Sfs");
        }

        // Ipp16u, Ipp16s -> Ipp16s

        template <>
        inline void Mul_Sfs(Ipp16u* x, Ipp16s* y, Ipp16s* result, int length, int scaleFactor)
        {
            IppStatus sts = ippsMul_16u16s_Sfs(x, y, result, length, scaleFactor);
            IPP_NO_ERROR(sts, "ippsMul_16u16s_Sfs");
        }

        // ============================
        // ============================ 
        //     Mul_I Specializations
        // ============================
        // ============================

        template <typename T, typename U>
        inline void Mul_I(T* x, U* result, int length)
        {
            throw std::runtime_error("ippsMul_I only implemented for specific types.");
        }

        // Ipp16s

        template <>
        inline void Mul_I(Ipp16s* x, Ipp16s* result, int length)
        {
            IppStatus sts = ippsMul_16s_I(x, result, length);
            IPP_NO_ERROR(sts, "ippsMul_16s_I");
        }

        // Ipp32f

        template <>
        inline void Mul_I(Ipp32f* x, Ipp32f* result, int length)
        {
            IppStatus sts = ippsMul_32f_I(x, result, length);
            IPP_NO_ERROR(sts, "ippsMul_32f_I");
        }

        // Ipp64f

        template <>
        inline void Mul_I(Ipp64f* x, Ipp64f* result, int length)
        {
            IppStatus sts = ippsMul_64f_I(x, result, length);
            IPP_NO_ERROR(sts, "ippsMul_64f_I");
        }

        // Ipp32fc

        template <>
        inline void Mul_I(Ipp32fc* x, Ipp32fc* result, int length)
        {
            IppStatus sts = ippsMul_32fc_I(x, result, length);
            IPP_NO_ERROR(sts, "ippsMul_32fc_I");
        }

        // Ipp64fc

        template <>
        inline void Mul_I(Ipp64fc *x, Ipp64fc *result, int length)
        {
            IppStatus sts = ippsMul_64fc_I(x, result, length);
            IPP_NO_ERROR(sts, "ippsMul_64fc_I");
        }

        // Ipp32f to Ipp32fc

        template <>
        inline void Mul_I(Ipp32f* x, Ipp32fc* result, int length)
        {
            IppStatus sts = ippsMul_32f32fc_I(x, result, length);
            IPP_NO_ERROR(sts, "ippsMul_32f32fc_I");
        }

    }
}