#include "ipp.h"
#include "../ipp_ext_errors.h"
#include <stdexcept>
#include <string>

namespace ipps{
    namespace convert{

        template <typename T, typename U>
        void Convert(const T* src, U* dst, int len);

        template <typename T, typename U>
        void Convert_Sfs(const T* src, U* dst, int len, int scaleFactor, IppRoundMode rndMode=IppRoundMode::ippRndZero);

        // ============================
        // ============================ 
        //  Convert Specializations
        // ============================
        // ============================

        template <typename T, typename U>
        inline void Convert(const T* src, U* dst, int len){
            throw std::runtime_error("ippsConvert not implemented for generic types");
        }

        // 8s to 16s
        template <>
        inline void Convert(const Ipp8s* src, Ipp16s* dst, int len){
            IppStatus sts = ippsConvert_8s16s(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConvert_8s16s");
        }

        // 8s to 32f
        template <>
        inline void Convert(const Ipp8s* src, Ipp32f* dst, int len){
            IppStatus sts = ippsConvert_8s32f(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConvert_8s32f");
        }

        // 8u to 32f
        template <>
        inline void Convert(const Ipp8u* src, Ipp32f* dst, int len){
            IppStatus sts = ippsConvert_8u32f(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConvert_8u32f");
        }

        // 8s to 8u
        template <>
        inline void Convert(const Ipp8s* src, Ipp8u* dst, int len){
            IppStatus sts = ippsConvert_8s8u(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConvert_8s8u");
        }

        // 16s to 32s
        template <>
        inline void Convert(const Ipp16s* src, Ipp32s* dst, int len){
            IppStatus sts = ippsConvert_16s32s(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConvert_16s32s");
        }

        // 16s to 32f
        template <>
        inline void Convert(const Ipp16s* src, Ipp32f* dst, int len){
            IppStatus sts = ippsConvert_16s32f(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConvert_16s32f");
        }

        // 16u to 32f
        template <>
        inline void Convert(const Ipp16u* src, Ipp32f* dst, int len){
            IppStatus sts = ippsConvert_16u32f(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConvert_16u32f");
        }

        // 32s to 16s
        template <>
        inline void Convert(const Ipp32s* src, Ipp16s* dst, int len){
            IppStatus sts = ippsConvert_32s16s(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConvert_32s16s");
        }

        // 32s to 32f
        template <>
        inline void Convert(const Ipp32s* src, Ipp32f* dst, int len){
            IppStatus sts = ippsConvert_32s32f(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConvert_32s32f");
        }

        // 32s to 64f
        template <>
        inline void Convert(const Ipp32s* src, Ipp64f* dst, int len){
            IppStatus sts = ippsConvert_32s64f(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConvert_32s64f");
        }

        // 32f to 64f
        template <>
        inline void Convert(const Ipp32f* src, Ipp64f* dst, int len){
            IppStatus sts = ippsConvert_32f64f(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConvert_32f64f");
        }

        // 64s to 64f
        template <>
        inline void Convert(const Ipp64s* src, Ipp64f* dst, int len){
            IppStatus sts = ippsConvert_64s64f(src, dst, (Ipp32u)len);
            IPP_NO_ERROR(sts, "ippsConvert_64s64f");
        }

        // 64f to 32f
        template <>
        inline void Convert(const Ipp64f* src, Ipp32f* dst, int len){
            IppStatus sts = ippsConvert_64f32f(src, dst, len);
            IPP_NO_ERROR(sts, "ippsConvert_64f32f");
        }

        // DEV NOTE: I have skipped all the 24s/24u types because they are not built-in POD types.
        // At some point if it's desired we can figure out a nice way to template them.
        // Technically Ipp16f seems to be built in, but I'm not including them either 
        // as it's hardly ever used elsewhere in the library.

        // ============================
        // ============================ 
        //  Convert_Sfs Specializations
        // ============================
        // ============================

        template <typename T, typename U>
        inline void Convert_Sfs(const T* src, U* dst, int len, int scaleFactor, IppRoundMode rndMode){
            throw std::runtime_error("ippsConvert_Sfs not implemented for generic types");
        }

        // 8u to 8s
        template <>
        inline void Convert_Sfs(const Ipp8u* src, Ipp8s* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_8u8s_Sfs(src, dst, len, rndMode, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_8u8s_Sfs");
        }

        // 16s to 8s
        template <>
        inline void Convert_Sfs(const Ipp16s* src, Ipp8s* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_16s8s_Sfs(src, dst, len, rndMode, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_16s8s_Sfs");
        }

        // 16s to 32f (round mode is not used)
        template <>
        inline void Convert_Sfs(const Ipp16s* src, Ipp32f* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_16s32f_Sfs(src, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_16s32f_Sfs");
        }

        // 16s to 64f (round mode is not used)
        template <>
        inline void Convert_Sfs(const Ipp16s* src, Ipp64f* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_16s64f_Sfs(src, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_16s64f_Sfs");
        }

        // 32s to 16s (round mode is not used)
        template <>
        inline void Convert_Sfs(const Ipp32s* src, Ipp16s* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_32s16s_Sfs(src, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_32s16s_Sfs");
        }

        // 32s to 32f (round mode is not used)
        template <>
        inline void Convert_Sfs(const Ipp32s* src, Ipp32f* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_32s32f_Sfs(src, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_32s32f_Sfs");
        }

        // 32s to 64f (round mode is not used)
        template <>
        inline void Convert_Sfs(const Ipp32s* src, Ipp64f* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_32s64f_Sfs(src, dst, len, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_32s64f_Sfs");
        }

        // 32f to 8s
        template <>
        inline void Convert_Sfs(const Ipp32f* src, Ipp8s* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_32f8s_Sfs(src, dst, len, rndMode, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_32f8s_Sfs");
        }

        // 32f to 8u
        template <>
        inline void Convert_Sfs(const Ipp32f* src, Ipp8u* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_32f8u_Sfs(src, dst, len, rndMode, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_32f8u_Sfs");
        }

        // 32f to 16s
        template <>
        inline void Convert_Sfs(const Ipp32f* src, Ipp16s* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_32f16s_Sfs(src, dst, len, rndMode, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_32f16s_Sfs");
        }

        // 32f to 16u
        template <>
        inline void Convert_Sfs(const Ipp32f* src, Ipp16u* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_32f16u_Sfs(src, dst, len, rndMode, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_32f16u_Sfs");
        }

        // 32f to 32s
        template <>
        inline void Convert_Sfs(const Ipp32f* src, Ipp32s* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_32f32s_Sfs(src, dst, len, rndMode, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_32f32s_Sfs");
        }

        // 64f to 8s
        template <>
        inline void Convert_Sfs(const Ipp64f* src, Ipp8s* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_64f8s_Sfs(src, dst, len, rndMode, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_64f8s_Sfs");
        }

        // 64f to 8u
        template <>
        inline void Convert_Sfs(const Ipp64f* src, Ipp8u* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_64f8u_Sfs(src, dst, len, rndMode, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_64f8u_Sfs");
        }

        // 64f to 16u
        template <>
        inline void Convert_Sfs(const Ipp64f* src, Ipp16u* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_64f16u_Sfs(src, dst, len, rndMode, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_64f16u_Sfs");
        }

        // 64s to 32s
        template <>
        inline void Convert_Sfs(const Ipp64s* src, Ipp32s* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_64s32s_Sfs(src, dst, len, rndMode, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_64s32s_Sfs");
        }

        // 64f to 16s
        template <>
        inline void Convert_Sfs(const Ipp64f* src, Ipp16s* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_64f16s_Sfs(src, dst, len, rndMode, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_64f16s_Sfs");
        }

        // 64f to 32s
        template <>
        inline void Convert_Sfs(const Ipp64f* src, Ipp32s* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_64f32s_Sfs(src, dst, len, rndMode, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_64f32s_Sfs");
        }

        // 64f to 64s
        template <>
        inline void Convert_Sfs(const Ipp64f* src, Ipp64s* dst, int len, int scaleFactor, IppRoundMode rndMode){
            IppStatus sts = ippsConvert_64f64s_Sfs(src, dst, (Ipp32u)len, rndMode, scaleFactor);
            IPP_NO_ERROR(sts, "ippsConvert_64f64s_Sfs");
        }

        // DEV NOTE: Similar to Convert, have left out anything with 24u/24s/16f.
    }
}
