/*
Note that all specializations are inlined in order to ensure that
multiply defined symbols errors do not occur.
*/

#pragma once

#include "ipp.h"
#include <stdexcept>
#include <string>
#include "ipp_ext_vec.h"

namespace ipps
{
    template <typename T>
    class DFTCToC
    {
        public:
            // Constructors
            DFTCToC()
                : m_length{0}, m_flag{IPP_FFT_DIV_INV_BY_N}
            {

            }

            DFTCToC(size_t length, int flag = IPP_FFT_DIV_INV_BY_N)
                : m_length{length}, m_flag{flag}
            {
                if (m_length == 0)
                {
                    throw std::invalid_argument("DFTCToC: length cannot be 0");
                }
                prepare_dft();
            }

            // Main runtime methods (see below for the specializations)

            /// @brief Runs the forward DFT on the data.
            /// @param src Real part of input for (32f/64f), full complex input for (32fc/64fc)
            /// @param dst Real part of output for (32f/64f), full complex output for (32fc/64fc)
            /// @param srcIm Imaginary part of input for (32f/64f), ignored for (32fc/64fc)
            /// @param dstIm Imaginary part of output for (32f/64f), ignored for (32fc/64fc)
            void fwd(const T* src, T* dst, const T* srcIm=nullptr, T* dstIm=nullptr);

            /// @brief Runs the backward DFT on the data.
            /// @param src Real part of input for (32f/64f), full complex input for (32fc/64fc)
            /// @param dst Real part of output for (32f/64f), full complex output for (32fc/64fc)
            /// @param srcIm Imaginary part of input for (32f/64f), ignored for (32fc/64fc)
            /// @param dstIm Imaginary part of output for (32f/64f), ignored for (32fc/64fc)
            void bwd(const T* src, T* dst, const T* srcIm=nullptr, T* dstIm=nullptr);

            // Alias for bwd (since Inv is the name given by IPP)
            void inv(const T* src, T* dst, const T* srcIm=nullptr, T* dstIm=nullptr)
            {
                bwd(src, dst, srcIm, dstIm); 
            }

            // Some getters
            size_t getLength() const { return m_length; }
            int getFlag() const { return m_flag; }
            const vector<Ipp8u>& getDFTSpec() const { return m_pDFTSpec; }
            const vector<Ipp8u>& getDFTBuf() const { return m_pDFTBuf; }
            const vector<Ipp8u>& getMemInit() const { return m_pMemInit; }

        private:
            size_t m_length;
            int m_flag;
            int m_SizeSpec;
            int m_SizeInit;
            int m_SizeBuf;

            vector<Ipp8u> m_pDFTSpec;
            vector<Ipp8u> m_pDFTBuf;
            vector<Ipp8u> m_pMemInit;

            // the constructor will call this, and this will contain the specializations
            void prepare_dft();
            // which in turn calls this after it discovers the sizes, along with other things
            void allocate_vectors()
            {
                m_pDFTSpec.resize(m_SizeSpec);
                m_pDFTBuf.resize(m_SizeBuf);
                m_pMemInit.resize(m_SizeInit);
            }
    };

    /*
    ==================== SPECIALIZATIONS FOR PREPARE ====================================
    */
    template <typename T>
    inline void DFTCToC<T>::prepare_dft()
    {
        throw std::domain_error("No constructor for this type. DFTCToC currently only supports 32f, 64f, 32fc and 64fc.");
    }

    // specialization for Ipp32f
    template <>
    inline void DFTCToC<Ipp32f>::prepare_dft()
    {
        // First get the size of the structure required
        IppStatus status = ippsDFTGetSize_C_32f(
            (int)m_length,
            m_flag, 
            ippAlgHintNone, // deprecated according to docs
            &m_SizeSpec, 
            &m_SizeInit, 
            &m_SizeBuf
        );
        if (status != ippStsNoErr){
            throw std::runtime_error("ippsDFTGetSize_C_32f failed with error code " + std::to_string(status));
        }

        // Then allocate the memory required
        allocate_vectors();

        // And finally create the DFT transform
        IppStatus status2 = ippsDFTInit_C_32f(
            (int)m_length,
            m_flag,
            ippAlgHintNone, // deprecated according to docs
            (IppsDFTSpec_C_32f*) m_pDFTSpec.data(), // explicit casting required
            m_pMemInit.data() // technically don't need this any more?
        );
        if (status2 != ippStsNoErr){
            throw std::runtime_error("ippsDFTInit_C_32f failed with error code " + std::to_string(status2));
        }
    }

    // specialization for Ipp64f
    template <>
    inline void DFTCToC<Ipp64f>::prepare_dft()
    {
        // First get the size of the structure required
        IppStatus status = ippsDFTGetSize_C_64f(
            (int)m_length,
            m_flag, 
            ippAlgHintNone, // deprecated according to docs
            &m_SizeSpec, 
            &m_SizeInit, 
            &m_SizeBuf
        );
        if (status!= ippStsNoErr){
            throw std::runtime_error("ippsDFTGetSize_C_64f failed with error code " + std::to_string(status));
        }
        
        // Then allocate the memory required
        allocate_vectors();
        
        // And finally create the DFT transform
        IppStatus status2 = ippsDFTInit_C_64f(
            (int)m_length,
            m_flag,
            ippAlgHintNone, // deprecated according to docs
            (IppsDFTSpec_C_64f*) m_pDFTSpec.data(), // explicit casting required
            m_pMemInit.data() // technically don't need this any more?
        );
        if (status2!= ippStsNoErr){
            throw std::runtime_error("ippsDFTInit_C_64f failed with error code " + std::to_string(status2));
        }
    }

    // specialization for Ipp32fc
    template <>
    inline void DFTCToC<Ipp32fc>::prepare_dft()
    {
        // First get the size of the structure required
        IppStatus status = ippsDFTGetSize_C_32fc(
            (int)m_length,
            m_flag, 
            ippAlgHintNone, // deprecated according to docs
            &m_SizeSpec, 
            &m_SizeInit, 
            &m_SizeBuf
        );
        if (status!= ippStsNoErr){
            throw std::runtime_error("ippsDFTGetSize_C_32fc failed with error code " + std::to_string(status));
        }
        
        // Then allocate the memory required
        allocate_vectors();
        
        // And finally create the DFT transform
        IppStatus status2 = ippsDFTInit_C_32fc(
            (int)m_length,
            m_flag,
            ippAlgHintNone, // deprecated according to docs
            (IppsDFTSpec_C_32fc*) m_pDFTSpec.data(), // explicit casting required
            m_pMemInit.data() // technically don't need this any more?
        );
        if (status2!= ippStsNoErr){
            throw std::runtime_error("ippsDFTInit_C_32fc failed with error code " + std::to_string(status2));
        }

    }

    // specialization for Ipp64fc
    template <>
    inline void DFTCToC<Ipp64fc>::prepare_dft()
    {
        // First get the size of the structure required
        IppStatus status = ippsDFTGetSize_C_64fc(
            (int)m_length,
            m_flag, 
            ippAlgHintNone, // deprecated according to docs
            &m_SizeSpec, 
            &m_SizeInit, 
            &m_SizeBuf
        );
        if (status!= ippStsNoErr){
            throw std::runtime_error("ippsDFTGetSize_C_64fc failed with error code " + std::to_string(status));
        }
        
        // Then allocate the memory required
        allocate_vectors();
        
        // And finally create the DFT transform
        IppStatus status2 = ippsDFTInit_C_64fc(
            (int)m_length,
            m_flag,
            ippAlgHintNone, // deprecated according to docs
            (IppsDFTSpec_C_64fc*) m_pDFTSpec.data(), // explicit casting required
            m_pMemInit.data() // technically don't need this any more?
        );
        if (status2!= ippStsNoErr){
            throw std::runtime_error("ippsDFTInit_C_64fc failed with error code " + std::to_string(status2));
        }
    }

    /*
    ======================= SPECIALIZATIONS FOR FORWARD ====================================
    */
    template <typename T>
    inline void DFTCToC<T>::fwd(const T* /*src*/, T* /*dst*/, const T* /*srcIm*/, T* /*dstIm*/)
    {
        throw std::domain_error("We should never hit this error. DFTCToC currently only supports 32f, 64f, 32fc and 64fc.");
    }

    // specialization for Ipp32f
    template <>
    inline void DFTCToC<Ipp32f>::fwd(const Ipp32f* src, Ipp32f* dst, const Ipp32f* srcIm, Ipp32f* dstIm)
    {
        // call the IPP specific fwd function for Ipp32f
        IppStatus status = ippsDFTFwd_CToC_32f(
            src, 
            srcIm, // this must be supplied for Ipp32f/Ipp64f i.e. the non-complex data types
            dst, 
            dstIm, // this must be supplied for Ipp32f/Ipp64f i.e. the non-complex data types
            (const IppsDFTSpec_C_32f*) m_pDFTSpec.data(),
            m_pDFTBuf.data()
        );
        if (status!= ippStsNoErr){
            throw std::runtime_error("ippsDFTFwd_C_32f failed with error code " + std::to_string(status));
        }
    }

    // specialization for Ipp64f
    template <>
    inline void DFTCToC<Ipp64f>::fwd(const Ipp64f* src, Ipp64f* dst, const Ipp64f* srcIm, Ipp64f* dstIm)
    {
        // call the IPP specific fwd function for Ipp64f
        IppStatus status = ippsDFTFwd_CToC_64f(
            src, 
            srcIm, // this must be supplied for Ipp32f/Ipp64f i.e. the non-complex data types
            dst, 
            dstIm, // this must be supplied for Ipp32f/Ipp64f i.e. the non-complex data types
            (const IppsDFTSpec_C_64f*) m_pDFTSpec.data(),
            m_pDFTBuf.data()
        );
        if (status!= ippStsNoErr){
            throw std::runtime_error("ippsDFTFwd_C_64f failed with error code " + std::to_string(status));
        }
    }

    // specialization for Ipp32fc
    template <>
    inline void DFTCToC<Ipp32fc>::fwd(const Ipp32fc* src, Ipp32fc* dst, const Ipp32fc* /*srcIm*/, Ipp32fc* /*dstIm*/)
    {
        // call the IPP specific fwd function for Ipp32fc
        IppStatus status = ippsDFTFwd_CToC_32fc(
            src, 
            dst, // we ignore the srcIm and dstIm parameters (should have been left as nullptr by the user)
            (const IppsDFTSpec_C_32fc*) m_pDFTSpec.data(),
            m_pDFTBuf.data()
        );
        if (status!= ippStsNoErr){
            throw std::runtime_error("ippsDFTFwd_C_32fc failed with error code " + std::to_string(status));
        }
    }

    // specialization for Ipp64fc
    template <>
    inline void DFTCToC<Ipp64fc>::fwd(const Ipp64fc* src, Ipp64fc* dst, const Ipp64fc* /*srcIm*/, Ipp64fc* /*dstIm*/)
    {
        // call the IPP specific fwd function for Ipp64fc
        IppStatus status = ippsDFTFwd_CToC_64fc(
            src, 
            dst, // we ignore the srcIm and dstIm parameters (should have been left as nullptr by the user)
            (const IppsDFTSpec_C_64fc*) m_pDFTSpec.data(),
            m_pDFTBuf.data()
        );
        if (status!= ippStsNoErr){
            throw std::runtime_error("ippsDFTFwd_C_64fc failed with error code " + std::to_string(status));
        }
    }

    /*
    ======================= SPECIALIZATIONS FOR BACKWARD ====================================
    */
    template <typename T>
    inline void DFTCToC<T>::bwd(const T* /*src*/, T* /*dst*/, const T* /*srcIm*/, T* /*dstIm*/)
    {
        throw std::domain_error("We should never hit this error. DFTCToC currently only supports 32f, 64f, 32fc and 64fc.");
    }

    // specialization for Ipp32f
    template <>
    inline void DFTCToC<Ipp32f>::bwd(const Ipp32f* src, Ipp32f* dst, const Ipp32f* srcIm, Ipp32f* dstIm)
    {
        // call the IPP specific bwd function for Ipp32f
        IppStatus status = ippsDFTInv_CToC_32f(
            src, 
            srcIm, // this must be supplied for Ipp32f/Ipp64f i.e. the non-complex data types
            dst, 
            dstIm, // this must be supplied for Ipp32f/Ipp64f i.e. the non-complex data types
            (const IppsDFTSpec_C_32f*) m_pDFTSpec.data(),
            m_pDFTBuf.data()
        );
        if (status!= ippStsNoErr){
            throw std::runtime_error("ippsDFTInv_C_32f failed with error code " + std::to_string(status));
        }
    }

    // specialization for Ipp64f
    template <>
    inline void DFTCToC<Ipp64f>::bwd(const Ipp64f* src, Ipp64f* dst, const Ipp64f* srcIm, Ipp64f* dstIm)
    {
        // call the IPP specific bwd function for Ipp64f
        IppStatus status = ippsDFTInv_CToC_64f(
            src, 
            srcIm, // this must be supplied for Ipp32f/Ipp64f i.e. the non-complex data types
            dst, 
            dstIm, // this must be supplied for Ipp32f/Ipp64f i.e. the non-complex data types
            (const IppsDFTSpec_C_64f*) m_pDFTSpec.data(),
            m_pDFTBuf.data()
        );
        if (status!= ippStsNoErr){
            throw std::runtime_error("ippsDFTInv_C_64f failed with error code " + std::to_string(status));
        }
    }

    // specialization for Ipp32fc
    template <>
    inline void DFTCToC<Ipp32fc>::bwd(const Ipp32fc* src, Ipp32fc* dst, const Ipp32fc* /*srcIm*/, Ipp32fc* /*dstIm*/)
    {
        // call the IPP specific bwd function for Ipp32fc
        IppStatus status = ippsDFTInv_CToC_32fc(
            src, 
            dst, // we ignore the srcIm and dstIm parameters (should have been left as nullptr by the user)
            (const IppsDFTSpec_C_32fc*) m_pDFTSpec.data(),
            m_pDFTBuf.data()
        );
        if (status!= ippStsNoErr){
            throw std::runtime_error("ippsDFTInv_C_32fc failed with error code " + std::to_string(status));
        }
    }

    // specialization for Ipp64fc
    template <>
    inline void DFTCToC<Ipp64fc>::bwd(const Ipp64fc* src, Ipp64fc* dst, const Ipp64fc* /*srcIm*/, Ipp64fc* /*dstIm*/)
    {
        // call the IPP specific bwd function for Ipp64fc
        IppStatus status = ippsDFTInv_CToC_64fc(
            src, 
            dst, // we ignore the srcIm and dstIm parameters (should have been left as nullptr by the user)
            (const IppsDFTSpec_C_64fc*) m_pDFTSpec.data(),
            m_pDFTBuf.data()
        );
        if (status!= ippStsNoErr){
            throw std::runtime_error("ippsDFTInv_C_64fc failed with error code " + std::to_string(status));
        }
    }


}
