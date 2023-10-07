#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include "../ipp_ext_vec.h" // use ippe vectors
#include <stdexcept>
#include <string>

namespace ippe{
    namespace filter
    {
        /// @brief Class for filtering single-rate.
        /// @tparam T Type of the taps.
        /// @tparam U Type of the input/output.
        template <typename T, typename U>
        class FIRSR
        {
        public:
            FIRSR()
            {}

            FIRSR(vector<T>& taps, IppAlgType algType=IppAlgType::ippAlgDirect)
                : m_taps{taps}, // copy the taps internally
                m_dly{taps.size() - 1}, // construct with 0s,
                m_dlyDst{taps.size() - 1},
                m_algType{algType}
            {
                reset();
                prepare();
                isPrepared = true;
            }

            FIRSR(vector<T>&& taps, IppAlgType algType = IppAlgType::ippAlgDirect)
                : m_taps(std::move(taps)),
                m_dly{m_taps.size() - 1}, // important that this is after m_taps, like in declaration order; we must use m_taps since we moved from it already
                m_dlyDst{m_taps.size() - 1},
                m_algType{algType}
            {
                reset();
                prepare();
                isPrepared = true;
            }
            
            void filter(const U* in, U* out, int len);

            // Accessors for the delay vector

            void reset(){ m_dly.zero(); }
            void setDelay(const U* dly)
            {
                Copy<U>(dly, m_dly.data(), (int)m_dly.size());
            }
            const vector<U>& getDelayVector() { return m_dly; }
            const U* getDelay() { return m_dly.data(); }

            const vector<T>& getTaps() { return m_taps; }

        private:
            vector<T> m_taps;
            // Workspaces for the filter
            vector<U> m_dly;
            vector<U> m_dlyDst;
            vector<Ipp8u> m_spec;
            vector<Ipp8u> m_buf;
            IppAlgType m_algType;

            void prepare();
            bool isPrepared = false; // flag to ensure that taps have been initialized
        };

        // ============================
        // ============================ 
        //  FIRSR prepare Specializations
        // ============================
        // ============================

        // 32f taps, 32f input/output
        template <>
        inline void FIRSR<Ipp32f, Ipp32f>::prepare()
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
                m_algType,
                (IppsFIRSpec_32f*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSRInit_32f");
        }

        // 64f taps, 64f input/output
        template <>
        inline void FIRSR<Ipp64f, Ipp64f>::prepare()
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
                m_algType,
                (IppsFIRSpec_64f*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSRInit_64f");
        }

        // 32fc taps, 32fc input/output
        template <>
        inline void FIRSR<Ipp32fc, Ipp32fc>::prepare()
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
                m_algType,
                (IppsFIRSpec_32fc*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSRInit_32fc");
        }

        // 64fc taps, 64fc input/output
        template <>
        inline void FIRSR<Ipp64fc, Ipp64fc>::prepare()
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
                m_algType,
                (IppsFIRSpec_64fc*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSRInit_64fc");
        }

        // 32f taps, 32fc input/output
        template <>
        inline void FIRSR<Ipp32f, Ipp32fc>::prepare()
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
                m_algType,
                (IppsFIRSpec_32f*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSRInit_32f");
        }

        // 32f taps, 16s input/output
        template <>
        inline void FIRSR<Ipp32f, Ipp16s>::prepare()
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
                m_algType,
                (IppsFIRSpec_32f*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSRInit_32f");
        }

        // 32fc taps, 16sc input/output
        template <>
        inline void FIRSR<Ipp32fc, Ipp16sc>::prepare()
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
                m_algType,
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
            if (!isPrepared)
                throw std::runtime_error("FIRSR filter not prepared");

            IppStatus sts = ippsFIRSR_32f(
                in, out, len,
                (IppsFIRSpec_32f*)m_spec.data(),
                (const Ipp32f*)m_dly.data(),
                m_dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSR_32f");
            // Copy the delay back to internal vector
            m_dly = m_dlyDst;
        }

        // 64f taps, 64f input/output
        template <>
        inline void FIRSR<Ipp64f, Ipp64f>::filter(
            const Ipp64f* in,
            Ipp64f* out,
            int len
        ){
            if (!isPrepared)
                throw std::runtime_error("FIRSR filter not prepared");

            IppStatus sts = ippsFIRSR_64f(
                in, out, len,
                (IppsFIRSpec_64f*)m_spec.data(),
                (const Ipp64f*)m_dly.data(),
                m_dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSR_64f");
            // Copy the delay back to internal vector
            m_dly = m_dlyDst;
        }

        // 32fc taps, 32fc input/output
        template <>
        inline void FIRSR<Ipp32fc, Ipp32fc>::filter(
            const Ipp32fc* in,
            Ipp32fc* out,
            int len
        ){
            if (!isPrepared)
                throw std::runtime_error("FIRSR filter not prepared");

            IppStatus sts = ippsFIRSR_32fc(
                in, out, len,
                (IppsFIRSpec_32fc*)m_spec.data(),
                (const Ipp32fc*)m_dly.data(),
                m_dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSR_32fc");
            // Copy the delay back to internal vector
            m_dly = m_dlyDst;
        }

        // 64fc taps, 64fc input/output
        template <>
        inline void FIRSR<Ipp64fc, Ipp64fc>::filter(
            const Ipp64fc* in,
            Ipp64fc* out,
            int len
        ){
            if (!isPrepared)
                throw std::runtime_error("FIRSR filter not prepared");

            IppStatus sts = ippsFIRSR_64fc(
                in, out, len,
                (IppsFIRSpec_64fc*)m_spec.data(),
                (const Ipp64fc*)m_dly.data(),
                m_dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSR_64fc");
            // Copy the delay back to internal vector
            m_dly = m_dlyDst;
        }
    
        // 32f taps, 32fc input/output (note that it is not understood how the results of this combination are calculated)
        template <>
        inline void FIRSR<Ipp32f, Ipp32fc>::filter(
            const Ipp32fc* in,
            Ipp32fc* out,
            int len
        ){
            if (!isPrepared)
                throw std::runtime_error("FIRSR filter not prepared");

            IppStatus sts = ippsFIRSR32f_32fc(
                in, out, len,
                (IppsFIRSpec32f_32fc*)m_spec.data(),
                (const Ipp32fc*)m_dly.data(),
                m_dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSR32f_32fc");
            // Copy the delay back to internal vector
            m_dly = m_dlyDst;
        }

        // 32f taps, 16s input/output
        template <>
        inline void FIRSR<Ipp32f, Ipp16s>::filter(
            const Ipp16s* in,
            Ipp16s* out,
            int len
        ){
            if (!isPrepared)
                throw std::runtime_error("FIRSR filter not prepared");

            IppStatus sts = ippsFIRSR_16s(
                in, out, len,
                (IppsFIRSpec_32f*)m_spec.data(),
                (const Ipp16s*)m_dly.data(),
                m_dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSR_16s");
            // Copy the delay back to internal vector
            m_dly = m_dlyDst;
        }

        // 32fc taps, 16sc input/output
        template <>
        inline void FIRSR<Ipp32fc, Ipp16sc>::filter(
            const Ipp16sc* in,
            Ipp16sc* out,
            int len
        ){
            if (!isPrepared)
                throw std::runtime_error("FIRSR filter not prepared");
                
            IppStatus sts = ippsFIRSR_16sc(
                in, out, len,
                (IppsFIRSpec_32fc*)m_spec.data(),
                (const Ipp16sc*)m_dly.data(),
                m_dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRSR_16sc");
            // Copy the delay back to internal vector
            m_dly = m_dlyDst;
        }
    
    }
}