#pragma once

#include "ipp.h"
#include "../ipp_ext_errors.h"
#include "../ipp_ext_vec.h" // use ippe vectors
#include <stdexcept>
#include <string>

namespace ippe{
    namespace filter
    {
        /// @brief Class for filtering multi-rate i.e. upfirdn.
        /// @tparam T Type of the taps.
        /// @tparam U Type of the input/output.
        template <typename T, typename U>
        class FIRMR
        {
            public:
                FIRMR() {}
                FIRMR(
                    vector<T>& taps,
                    int upFactor, int upPhase,
                    int downFactor, int downPhase
                ) : m_taps{taps},
                    m_upFactor{upFactor}, m_upPhase{upPhase},
                    m_downFactor{downFactor}, m_downPhase{downPhase},
                    m_dly{(taps.size()+upFactor-1)/upFactor},
                    m_dlyDst{(taps.size()+upFactor-1)/upFactor}
                {
                    reset();
                    prepare();
                    isPrepared = true;
                }
                FIRMR(
                    vector<T>&& taps,
                    int upFactor, int upPhase,
                    int downFactor, int downPhase
                ) : m_taps{std::move(taps)},
                    m_upFactor{upFactor}, m_upPhase{upPhase},
                    m_downFactor{downFactor}, m_downPhase{downPhase},
                    m_dly{(m_taps.size()+upFactor-1)/upFactor}, // must use m_taps cause we already moved
                    m_dlyDst{(m_taps.size()+upFactor-1)/upFactor}
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
                int m_upFactor = 1;
                int m_upPhase = 0;
                int m_downFactor = 1;
                int m_downPhase = 0;
                // Workspaces for the filter
                vector<U> m_dly;
                vector<U> m_dlyDst;
                vector<Ipp8u> m_spec;
                vector<Ipp8u> m_buf;

                void prepare();
                bool isPrepared = false; // flag to ensure that taps have been initialized
        };

        // ============================
        // ============================ 
        //  FIRMR prepare Specializations
        // ============================
        // ============================

        // 32f taps, 32f data
        template <>
        inline void FIRMR<Ipp32f, Ipp32f>::prepare()
        {
            int specSize, bufSize;
            IppStatus sts = ippsFIRMRGetSize(
                (int)m_taps.size(),
                m_upFactor, m_downFactor,
                IppDataType::ipp32f,
                &specSize, &bufSize
            );
            IPP_NO_ERROR(sts, "ippsFIRMRGetSize");
            m_spec.resize((size_t)specSize);
            m_buf.resize((size_t)bufSize);
            sts = ippsFIRMRInit_32f(
                m_taps.data(), (int)m_taps.size(),
                m_upFactor, m_upPhase,
                m_downFactor, m_downPhase,
                (IppsFIRSpec_32f*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRMRInit_32f");
        }

        // 64f taps, 64f data
        template <>
        inline void FIRMR<Ipp64f, Ipp64f>::prepare()
        {
            int specSize, bufSize;
            IppStatus sts = ippsFIRMRGetSize(
                (int)m_taps.size(),
                m_upFactor, m_downFactor,
                IppDataType::ipp64f,
                &specSize, &bufSize
            );
            IPP_NO_ERROR(sts, "ippsFIRMRGetSize");
            m_spec.resize((size_t)specSize);
            m_buf.resize((size_t)bufSize);
            sts = ippsFIRMRInit_64f(
                m_taps.data(), (int)m_taps.size(),
                m_upFactor, m_upPhase,
                m_downFactor, m_downPhase,
                (IppsFIRSpec_64f*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRMRInit_64f");
        }

        // 32fc taps, 32fc data
        template <>
        inline void FIRMR<Ipp32fc, Ipp32fc>::prepare()
        {
            int specSize, bufSize;
            IppStatus sts = ippsFIRMRGetSize(
                (int)m_taps.size(),
                m_upFactor, m_downFactor,
                IppDataType::ipp32fc,
                &specSize, &bufSize
            );
            IPP_NO_ERROR(sts, "ippsFIRMRGetSize");
            m_spec.resize((size_t)specSize);
            m_buf.resize((size_t)bufSize);
            sts = ippsFIRMRInit_32fc(
                m_taps.data(), (int)m_taps.size(),
                m_upFactor, m_upPhase,
                m_downFactor, m_downPhase,
                (IppsFIRSpec_32fc*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRMRInit_32fc");
        }

        // 64fc taps, 64fc data
        template <>
        inline void FIRMR<Ipp64fc, Ipp64fc>::prepare()
        {
            int specSize, bufSize;
            IppStatus sts = ippsFIRMRGetSize(
                (int)m_taps.size(),
                m_upFactor, m_downFactor,
                IppDataType::ipp64fc,
                &specSize, &bufSize
            );
            IPP_NO_ERROR(sts, "ippsFIRMRGetSize");
            m_spec.resize((size_t)specSize);
            m_buf.resize((size_t)bufSize);
            sts = ippsFIRMRInit_64fc(
                m_taps.data(), (int)m_taps.size(),
                m_upFactor, m_upPhase,
                m_downFactor, m_downPhase,
                (IppsFIRSpec_64fc*)m_spec.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRMRInit_64fc");
        }

        // ============================
        // ============================ 
        //  FIRMR filter Specializations
        // ============================
        // ============================

        // 32f taps, 32f data
        template <>
        inline void FIRMR<Ipp32f, Ipp32f>::filter(const Ipp32f* in, Ipp32f* out, int len)
        {
            if (!isPrepared)
                throw std::runtime_error("FIRMR not prepared");

            IppStatus sts = ippsFIRMR_32f(
                in, out, len,
                (IppsFIRSpec_32f*)m_spec.data(),
                (const Ipp32f*)m_dly.data(),
                m_dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRMR_32f");
            // Copy the delay back
            m_dly = m_dlyDst;
        }

        // 64f taps, 64f data
        template <>
        inline void FIRMR<Ipp64f, Ipp64f>::filter(const Ipp64f* in, Ipp64f* out, int len)
        {
            if (!isPrepared)
                throw std::runtime_error("FIRMR not prepared");

            IppStatus sts = ippsFIRMR_64f(
                in, out, len,
                (IppsFIRSpec_64f*)m_spec.data(),
                (const Ipp64f*)m_dly.data(),
                m_dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRMR_64f");
            // Copy the delay back
            m_dly = m_dlyDst;
        }

        // 32fc taps, 32fc data
        template <>
        inline void FIRMR<Ipp32fc, Ipp32fc>::filter(const Ipp32fc* in, Ipp32fc* out, int len)
        {
            if (!isPrepared)
                throw std::runtime_error("FIRMR not prepared");

            IppStatus sts = ippsFIRMR_32fc(
                in, out, len,
                (IppsFIRSpec_32fc*)m_spec.data(),
                (const Ipp32fc*)m_dly.data(),
                m_dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRMR_32fc");
            // Copy the delay back
            m_dly = m_dlyDst;
        }

        // 64fc taps, 64fc data
        template <>
        inline void FIRMR<Ipp64fc, Ipp64fc>::filter(const Ipp64fc* in, Ipp64fc* out, int len)
        {
            if (!isPrepared)
                throw std::runtime_error("FIRMR not prepared");

            IppStatus sts = ippsFIRMR_64fc(
                in, out, len,
                (IppsFIRSpec_64fc*)m_spec.data(),
                (const Ipp64fc*)m_dly.data(),
                m_dlyDst.data(),
                m_buf.data()
            );
            IPP_NO_ERROR(sts, "ippsFIRMR_64fc");
            // Copy the delay back
            m_dly = m_dlyDst;
        }


    }
}