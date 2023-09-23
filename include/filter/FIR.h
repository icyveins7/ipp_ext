#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include "FIRGen.h" // include all the taps generators
#include "../ipp_ext_vec.h" // use ippe vectors
#include "../ipp_ext_convert.h"
#include <stdexcept>
#include <string>

namespace ippe{
    namespace filter{

        // Wrappers to directly generate vectors of taps

        template <typename T>
        vector<T> generateLowpassTaps(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal);

        // ============================
        // ============================ 
        //  generateLowpassTaps Specializations
        // ============================
        // ============================

        // Ipp32f
        template <>
        inline vector<Ipp32f> generateLowpassTaps(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
        {
            // In general, create 64f, then convert
            vector<Ipp64f> tmp((size_t)tapsLen);
            FIRGenLowpass<Ipp64f>(rFreq, tmp.data(), tapsLen, winType, doNormal);
            vector<Ipp32f> taps((size_t)tapsLen);
            convert::Convert<Ipp64f, Ipp32f>(tmp.data(), taps.data(), (int)taps.size());
            return taps;
        }

        // Ipp64f
        template <>
        inline vector<Ipp64f> generateLowpassTaps(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
        {
            // For 64f, we can directly generate the taps
            vector<Ipp64f> tmp((size_t)tapsLen);
            FIRGenLowpass<Ipp64f>(rFreq, tmp.data(), tapsLen, winType, doNormal);
            return tmp;
        }

        // Ipp32fc
        template <>
        inline vector<Ipp32fc> generateLowpassTaps(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
        {
            // In general, create 64f, then convert
            vector<Ipp64f> tmp((size_t)tapsLen);
            FIRGenLowpass<Ipp64f>(rFreq, tmp.data(), tapsLen, winType, doNormal);
            // For complex we need 1 more step, so make the real vec first
            vector<Ipp32f> taps((size_t)tapsLen);
            convert::Convert<Ipp64f, Ipp32f>(tmp.data(), taps.data(), (int)taps.size());
            // Then create the complex vector
            vector<Ipp32fc> complexTaps((size_t)tapsLen);
            convert::RealToCplx<Ipp32f, Ipp32fc>(
                taps.data(), static_cast<Ipp32f*>(nullptr),
                complexTaps.data(), (int)complexTaps.size());
            return complexTaps;
        }

        // Ipp64fc
        template <>
        inline vector<Ipp64fc> generateLowpassTaps(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
        {
            // For 64f, we can directly generate the taps
            vector<Ipp64f> tmp((size_t)tapsLen);
            FIRGenLowpass<Ipp64f>(rFreq, tmp.data(), tapsLen, winType, doNormal);
            // Then create the complex vector
            vector<Ipp64fc> complexTaps((size_t)tapsLen);
            convert::RealToCplx<Ipp64f, Ipp64fc>(
                tmp.data(), static_cast<Ipp64f*>(nullptr),
                complexTaps.data(), (int)complexTaps.size());
            return complexTaps;
        }

        ///////////////////////////////////////////////////

        /// @brief Class for filtering single-rate.
        /// @tparam T Type of the taps container e.g. FIRLowpass.
        /// @tparam U Type of the input/output.
        template <typename T, typename U>
        class FIRSR
        {
        public:
            FIRSR(vector<T> taps, IppAlgType algType=IppAlgType::ippAlgDirect);

            void filter(const U* in, U* out, int len);

            // Accessors for the delay vector

            void reset(){ m_dly.zero(); }
            void setDelay(const U* dly)
            {
                Copy<U>(dly, m_dly.data(), (int)m_dly.size());
            }
            const vector<U>& getDelay() { return m_dly; }
            const U* getDelay() { return m_dly.data(); }

            const vector<T>& getTaps() { return m_taps; }

        private:
            vector<T> m_taps;
            // Workspaces for the filter
            vector<U> m_dly;
            vector<Ipp8u> m_spec;
            vector<Ipp8u> m_buf;
        };

        // ============================
        // ============================ 
        //  FIRSR Ctor Specializations
        // ============================
        // ============================

        // 32f taps, 32f input/output
        template <>
        FIRSR<Ipp32f, Ipp32f>::FIRSR(vector<Ipp32f> taps, IppAlgType algType)
            : m_taps{taps}, // copy the taps internally
            m_dly{taps.size() - 1, 0.0f} // construct with 0s
        {
            int specSize, bufSize;
            IppStatus sts = ippsFIRSRGetSize(
                (int)m_taps.size(),
                IppDataType::ipp32f,
                &specSize, &bufSize
            );
            IPP_NO_ERROR(sts, "ippsFIRSRGetSize");
            m_spec.resize((size_t)specSize);
            m_buf.resize((size_t)bufSize);
            // Then initialize the spec
            sts = ippsFIRSRInit_32f(
                m_taps.data(), (int)m_taps.size(),
                algType,
                (IppsFIRSpec_32f*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSRInit_32f");
        }

        // 64f taps, 64f input/output
        template <>
        FIRSR<Ipp64f, Ipp64f>::FIRSR(vector<Ipp64f> taps, IppAlgType algType)
            : m_taps{taps}, // copy the taps internally,
            m_dly{taps.size() - 1, 0.0} // construct with 0s
        {
            int specSize, bufSize;
            IppStatus sts = ippsFIRSRGetSize(
                (int)m_taps.size(),
                IppDataType::ipp64f,
                &specSize, &bufSize
            );
            IPP_NO_ERROR(sts, "ippsFIRSRGetSize");
            m_spec.resize((size_t)specSize);
            m_buf.resize((size_t)bufSize);
            // Then initialize the spec
            sts = ippsFIRSRInit_64f(
                m_taps.data(), (int)m_taps.size(),
                algType,
                (IppsFIRSpec_64f*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSRInit_64f");
        }

        // 32fc taps, 32fc input/output
        template <>
        FIRSR<Ipp32fc, Ipp32fc>::FIRSR(vector<Ipp32fc> taps, IppAlgType algType)
            : m_taps{taps}, // copy the taps internally,
            m_dly{taps.size() - 1, {0.0f, 0.0f}} // construct with 0s
        {
            int specSize, bufSize;
            IppStatus sts = ippsFIRSRGetSize(
                (int)m_taps.size(),
                IppDataType::ipp32fc,
                &specSize, &bufSize
            );
            IPP_NO_ERROR(sts, "ippsFIRSRGetSize");
            m_spec.resize((size_t)specSize);
            m_buf.resize((size_t)bufSize);
            // Then initialize the spec
            sts = ippsFIRSRInit_32fc(
                m_taps.data(), (int)m_taps.size(),
                algType,
                (IppsFIRSpec_32fc*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSRInit_32fc");
        }

        // 64fc taps, 64fc input/output
        template <>
        FIRSR<Ipp64fc, Ipp64fc>::FIRSR(vector<Ipp64fc> taps, IppAlgType algType)
            : m_taps{taps}, // copy the taps internally,
            m_dly{taps.size() - 1, {0.0, 0.0}} // construct with 0s
        {
            int specSize, bufSize;
            IppStatus sts = ippsFIRSRGetSize(
                (int)m_taps.size(),
                IppDataType::ipp64fc,
                &specSize, &bufSize
            );
            IPP_NO_ERROR(sts, "ippsFIRSRGetSize");
            m_spec.resize((size_t)specSize);
            m_buf.resize((size_t)bufSize);
            // Then initialize the spec
            sts = ippsFIRSRInit_64fc(
                m_taps.data(), (int)m_taps.size(),
                algType,
                (IppsFIRSpec_64fc*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSRInit_64fc");
        }

        // 32f taps, 32fc input/output
        template <>
        FIRSR<Ipp32f, Ipp32fc>::FIRSR(vector<Ipp32f> taps, IppAlgType algType)
            : m_taps{taps},
            m_dly{taps.size() - 1, {0.0f, 0.0f}} // construct with 0s
        {
            int specSize, bufSize;
            IppStatus sts = ippsFIRSRGetSize(
                (int)m_taps.size(),
                IppDataType::ipp32f,
                &specSize, &bufSize
            );
            IPP_NO_ERROR(sts, "ippsFIRSRGetSize");
            m_spec.resize((size_t)specSize);
            m_buf.resize((size_t)bufSize);
            // Then initialize the spec
            sts = ippsFIRSRInit_32f(
                m_taps.data(), (int)m_taps.size(),
                algType,
                (IppsFIRSpec_32f*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSRInit_32f");
        }

        // 32f taps, 16s input/output
        template <>
        FIRSR<Ipp32f, Ipp16s>::FIRSR(vector<Ipp32f> taps, IppAlgType algType)
            : m_taps{taps}, // copy the taps internally,
            m_dly{taps.size() - 1, 0} // construct with 0s
        {
            int specSize, bufSize;
            IppStatus sts = ippsFIRSRGetSize(
                (int)m_taps.size(),
                IppDataType::ipp32f,
                &specSize, &bufSize
            );
            IPP_NO_ERROR(sts, "ippsFIRSRGetSize");
            m_spec.resize((size_t)specSize);
            m_buf.resize((size_t)bufSize);
            // Then initialize the spec
            sts = ippsFIRSRInit_32f(
                m_taps.data(), (int)m_taps.size(),
                algType,
                (IppsFIRSpec_32f*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSRInit_32f");
        }

        // 32fc taps, 16sc input/output
        template <>
        FIRSR<Ipp32fc, Ipp16sc>::FIRSR(vector<Ipp32fc> taps, IppAlgType algType)
            : m_taps{taps}, // copy the taps internally,
            m_dly{taps.size() - 1, {0, 0}} // construct with 0s
        {
            int specSize, bufSize;
            IppStatus sts = ippsFIRSRGetSize(
                (int)m_taps.size(),
                IppDataType::ipp32fc,
                &specSize, &bufSize
            );
            IPP_NO_ERROR(sts, "ippsFIRSRGetSize");
            m_spec.resize((size_t)specSize);
            m_buf.resize((size_t)bufSize);
            // Then initialize the spec
            sts = ippsFIRSRInit_32fc(
                m_taps.data(), (int)m_taps.size(),
                algType,
                (IppsFIRSpec_32fc*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSRInit_32fc");
        }

        // ============================
        // ============================ 
        //  FIRSR filter Specializations
        // ============================
        // ============================

        // 32f taps, 32f input/output
        template <>
        inline void FIRSR<Ipp32f, Ipp32f>::filter(
            const Ipp32f* in,
            Ipp32f* out,
            int len
        ){
            // Create temporary vector for output of delay
            vector<Ipp32f> dlyDst(m_dly.size());
            IppStatus sts = ippsFIRSR_32f(
                in, out, len,
                (IppsFIRSpec_32f*)m_spec.data(),
                (const Ipp32f*)m_dly.data(),
                dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSR_32f");
            // Copy the delay back to internal vector
            m_dly = dlyDst;
        }

        // 32fc taps, 32fc input/output
        template <>
        inline void FIRSR<Ipp32fc, Ipp32fc>::filter(
            const Ipp32fc* in,
            Ipp32fc* out,
            int len
        ){
            // Create temporary vector for output of delay
            vector<Ipp32fc> dlyDst(m_dly.size());
            IppStatus sts = ippsFIRSR_32fc(
                in, out, len,
                (IppsFIRSpec_32fc*)m_spec.data(),
                (const Ipp32fc*)m_dly.data(),
                dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSR_32fc");
            // Copy the delay back to internal vector
            m_dly = dlyDst;
        }

        // 64f taps, 64fc input/output
        template <>
        inline void FIRSR<Ipp64fc, Ipp64fc>::filter(
            const Ipp64fc* in,
            Ipp64fc* out,
            int len
        ){
            // Create temporary vector for output of delay
            vector<Ipp64fc> dlyDst(m_dly.size());
            IppStatus sts = ippsFIRSR_64fc(
                in, out, len,
                (IppsFIRSpec_64fc*)m_spec.data(),
                (const Ipp64fc*)m_dly.data(),
                dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSR_64fc");
            // Copy the delay back to internal vector
            m_dly = dlyDst;
        }

        // 64fc taps, 64fc input/output
        template <>
        inline void FIRSR<Ipp64fc, Ipp64fc>::filter(
            const Ipp64fc* in,
            Ipp64fc* out,
            int len
        ){
            // Create temporary vector for output of delay
            vector<Ipp64fc> dlyDst(m_dly.size());
            IppStatus sts = ippsFIRSR_64fc(
                in, out, len,
                (IppsFIRSpec_64fc*)m_spec.data(),
                (const Ipp64fc*)m_dly.data(),
                dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSR_64fc");
            // Copy the delay back to internal vector
            m_dly = dlyDst;
        }
    
        // 32f taps, 32fc input/output
        template <>
        inline void FIRSR<Ipp32f, Ipp32fc>::filter(
            const Ipp32fc* in,
            Ipp32fc* out,
            int len
        ){
            // Create temporary vector for output of delay
            vector<Ipp32fc> dlyDst(m_dly.size());
            IppStatus sts = ippsFIRSR32f_32fc(
                in, out, len,
                (IppsFIRSpec32f_32fc*)m_spec.data(),
                (const Ipp32fc*)m_dly.data(),
                dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSR32f_32fc");
            // Copy the delay back to internal vector
            m_dly = dlyDst;
        }

        // 32f taps, 16s input/output
        template <>
        inline void FIRSR<Ipp32f, Ipp16s>::filter(
            const Ipp16s* in,
            Ipp16s* out,
            int len
        ){
            // Create temporary vector for output of delay
            vector<Ipp16s> dlyDst(m_dly.size());
            IppStatus sts = ippsFIRSR_16s(
                in, out, len,
                (IppsFIRSpec_32f*)m_spec.data(),
                (const Ipp16s*)m_dly.data(),
                dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSR_16s");
            // Copy the delay back to internal vector
            m_dly = dlyDst;
        }

        // 32fc taps, 16sc input/output
        template <>
        inline void FIRSR<Ipp32fc, Ipp16sc>::filter(
            const Ipp16sc* in,
            Ipp16sc* out,
            int len
        ){
            // Create temporary vector for output of delay
            vector<Ipp16sc> dlyDst(m_dly.size());
            IppStatus sts = ippsFIRSR_16sc(
                in, out, len,
                (IppsFIRSpec_32fc*)m_spec.data(),
                (const Ipp16sc*)m_dly.data(),
                dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSR_16sc");
            // Copy the delay back to internal vector
            m_dly = dlyDst;
        }
    
    }
}