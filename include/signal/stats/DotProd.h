#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ipps{
    namespace stats{

        template <typename T, typename U, typename V>
        void DotProd(const T* src1, const U* src2, int len, V* result);

        template <typename T, typename U, typename V>
        void DotProd_Sfs(const T* src1, const U* src2, int len, V* result, int scaleFactor);

        // ============================
        // ============================ 
        //  DotProd Specializations
        // ============================
        // ============================

        // 32f, 32f -> 32f
        template <>
        inline void DotProd(const Ipp32f* src1, const Ipp32f* src2, int len, Ipp32f* result)
        {
            IppStatus sts = ippsDotProd_32f(src1, src2, len, result);
            IPP_NO_ERROR(sts, "ippsDotProd_32f");
        }

        // 32fc, 32fc -> 32fc
        template <>
        inline void DotProd(const Ipp32fc* src1, const Ipp32fc* src2, int len, Ipp32fc* result)
        {
            IppStatus sts = ippsDotProd_32fc(src1, src2, len, result);
            IPP_NO_ERROR(sts, "ippsDotProd_32fc");
        }

        // 32f, 32fc -> 32fc
        template <>
        inline void DotProd(const Ipp32f* src1, const Ipp32fc* src2, int len, Ipp32fc* result)
        {
            IppStatus sts = ippsDotProd_32f32fc(src1, src2, len, result);
            IPP_NO_ERROR(sts, "ippsDotProd_32f32fc");
        }

        // 32f, 32f -> 64f
        template <>
        inline void DotProd(const Ipp32f* src1, const Ipp32f* src2, int len, Ipp64f* result)
        {
            IppStatus sts = ippsDotProd_32f64f(src1, src2, len, result);
            IPP_NO_ERROR(sts, "ippsDotProd_32f64f");
        }

        // 32fc, 32fc -> 64fc
        template <>
        inline void DotProd(const Ipp32fc* src1, const Ipp32fc* src2, int len, Ipp64fc* result)
        {
            IppStatus sts = ippsDotProd_32fc64fc(src1, src2, len, result);
            IPP_NO_ERROR(sts, "ippsDotProd_32fc64fc");
        }

        // 32f, 32fc -> 64fc
        template <>
        inline void DotProd(const Ipp32f* src1, const Ipp32fc* src2, int len, Ipp64fc* result)
        {
            IppStatus sts = ippsDotProd_32f32fc64fc(src1, src2, len, result);
            IPP_NO_ERROR(sts, "ippsDotProd_32f32fc64fc");
        }

        // 64f, 64f -> 64f
        template <>
        inline void DotProd(const Ipp64f* src1, const Ipp64f* src2, int len, Ipp64f* result)
        {
            IppStatus sts = ippsDotProd_64f(src1, src2, len, result);
            IPP_NO_ERROR(sts, "ippsDotProd_64f");
        }

        // 64fc, 64fc -> 64fc
        template <>
        inline void DotProd(const Ipp64fc* src1, const Ipp64fc* src2, int len, Ipp64fc* result)
        {
            IppStatus sts = ippsDotProd_64fc(src1, src2, len, result);
            IPP_NO_ERROR(sts, "ippsDotProd_64fc");
        }

        // 64f, 64fc -> 64fc
        template <>
        inline void DotProd(const Ipp64f* src1, const Ipp64fc* src2, int len, Ipp64fc* result)
        {
            IppStatus sts = ippsDotProd_64f64fc(src1, src2, len, result);
            IPP_NO_ERROR(sts, "ippsDotProd_64f64fc");
        }

        // 16s, 16s -> 64s
        template <>
        inline void DotProd(const Ipp16s* src1, const Ipp16s* src2, int len, Ipp64s* result)
        {
            IppStatus sts = ippsDotProd_16s64s(src1, src2, len, result);
            IPP_NO_ERROR(sts, "ippsDotProd_16s64s");
        }

        // 16sc, 16sc -> 64sc
        template <>
        inline void DotProd(const Ipp16sc* src1, const Ipp16sc* src2, int len, Ipp64sc* result)
        {
            IppStatus sts = ippsDotProd_16sc64sc(src1, src2, len, result);
            IPP_NO_ERROR(sts, "ippsDotProd_16sc64sc");
        }

        // 16s, 16sc -> 64sc
        template <>
        inline void DotProd(const Ipp16s* src1, const Ipp16sc* src2, int len, Ipp64sc* result)
        {
            IppStatus sts = ippsDotProd_16s16sc64sc(src1, src2, len, result);
            IPP_NO_ERROR(sts, "ippsDotProd_16s16sc64sc");
        }

        // 16s, 16s -> 32f
        template <>
        inline void DotProd(const Ipp16s* src1, const Ipp16s* src2, int len, Ipp32f* result)
        {
            IppStatus sts = ippsDotProd_16s32f(src1, src2, len, result);
            IPP_NO_ERROR(sts, "ippsDotProd_16s32f");
        }

        // ============================
        // ============================ 
        //  DotProd_Sfs Specializations
        // ============================
        // ============================

        // 16s, 16s -> 32s
        template <>
        inline void DotProd_Sfs(const Ipp16s* src1, const Ipp16s* src2, int len, Ipp32s* result, int scaleFactor)
        {
            IppStatus sts = ippsDotProd_16s32s_Sfs(src1, src2, len, result, scaleFactor);
            IPP_NO_ERROR(sts, "ippsDotProd_16s32s_Sfs");
        }

        // 16s, 32s -> 32s
        template <>
        inline void DotProd_Sfs(const Ipp16s* src1, const Ipp32s* src2, int len, Ipp32s* result, int scaleFactor)
        {
            IppStatus sts = ippsDotProd_16s32s32s_Sfs(src1, src2, len, result, scaleFactor);
            IPP_NO_ERROR(sts, "ippsDotProd_16s32s32s_Sfs");
        }




    }
}
