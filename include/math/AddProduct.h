#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace math{

        template <typename T>
        void AddProduct(const T* src1, const T* src2, T* dst, int len);

        template <typename T, typename U>
        void AddProduct_Sfs(const T* src1, const T* src2, U* dst, int len, int scaleFactor);

        // ============================
        // ============================ 
        //     AddProduct Specializations
        // ============================
        // ============================

        template <typename T>
        inline void AddProduct(const T* src1, const T* src2, T* dst, int len){
            throw std::runtime_error("ippsAddProduct only implemented for specific types");
        }


        // Ipp32f
        template <>
        inline void AddProduct(const Ipp32f* src1, const Ipp32f* src2, Ipp32f* dst, int len){
            IppStatus sts = ippsAddProduct_32f(src1, src2, dst, len);
            IPP_NO_ERROR(sts, "ippsAddProduct_32f");
        }

        // Ipp64f
        template <>
        inline void AddProduct(const Ipp64f* src1, const Ipp64f* src2, Ipp64f* dst, int len){
            IppStatus sts = ippsAddProduct_64f(src1, src2, dst, len);
            IPP_NO_ERROR(sts, "ippsAddProduct_64f");
        }

        // Ipp32fc
        template <>
        inline void AddProduct(const Ipp32fc* src1, const Ipp32fc* src2, Ipp32fc* dst, int len){
            IppStatus sts = ippsAddProduct_32fc(src1, src2, dst, len);
            IPP_NO_ERROR(sts, "ippsAddProduct_32fc");
        }

        // Ipp64fc
        template <>
        inline void AddProduct(const Ipp64fc* src1, const Ipp64fc* src2, Ipp64fc* dst, int len){
            IppStatus sts = ippsAddProduct_64fc(src1, src2, dst, len);
            IPP_NO_ERROR(sts, "ippsAddProduct_64fc");
        }

        // ============================
        // ============================ 
        //     AddProduct_Sfs Specializations
        // ============================
        // ============================

        template <typename T, typename U>
        void AddProduct_Sfs(const T* src1, const T* src2, U* dst, int len, int scaleFactor){
            throw std::runtime_error("ippsAddProduct_Sfs only implemented for specific types");
        }

        // Ipp16s
        template <>
        inline void AddProduct_Sfs(const Ipp16s* src1, const Ipp16s* src2, Ipp16s* dst, int len, int scaleFactor){
            IppStatus sts = ippsAddProduct_16s_Sfs(src1, src2, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddProduct_16s_Sfs");
        }

        // Ipp32s
        template <>
        inline void AddProduct_Sfs(const Ipp32s* src1, const Ipp32s* src2, Ipp32s* dst, int len, int scaleFactor){
            IppStatus sts = ippsAddProduct_32s_Sfs(src1, src2, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddProduct_32s_Sfs");
        }

        // Ipp16s to Ipp32s
        template <>
        inline void AddProduct_Sfs(const Ipp16s* src1, const Ipp16s* src2, Ipp32s* dst, int len, int scaleFactor){
            IppStatus sts = ippsAddProduct_16s32s_Sfs(src1, src2, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsAddProduct_16s32s_Sfs");
        }
    }
}