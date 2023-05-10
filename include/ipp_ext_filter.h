/*
There are 6 available filter types for FIRSR:
32f, 64f, 32fc, 64fc and 16s, 16sc (but we will not support the 16s/16sc flavours due to scaling issues).

Taps generation is always done in 64f. Type conversion must be manually applied,
and complex conversion is also required.

The way this is structured is as follows:

1. We create the base class FIRSR, which contains the pointers to the necessary buffers.
2. The derived classes implement the taps generators, e.g. Lowpass, Highpass, Bandpass, Bandstop.
3. The base class is not meant to be instantiated directly, instead it provides a setup() method
which should be called by the derived classes. This is meant to be called after the taps have been generated.
4. The derived class is in charge of allocating memory for the taps, but nothing else.
5. The base class will allocate everything else that is required, in setup().

Note that the convention for the window is to use (0.0, 1.0), which is NOT
the range expected by the IPP functions. Hence internally we divide by 2 from the user's input.
This allows the user to input an identical window to SciPy's or MATLAB's 
FIR generating functions.
*/

#pragma once

#include "ipp.h"
#include <stdexcept>
#include <string>

namespace ippe
{
    /// @brief Basic parent class, not meant to be instantiated directly.
    /// @tparam T 32f, 64f, 32fc, 64fc
    template <typename T>
    class FIRSR
    {
    public:
        /// @brief Main runtime method, see template specializations below.
        /// @param src Source array
        /// @param dst Destination array
        /// @param len Length of either array (should be equal)
        void filter(const T* src, T* dst, int len);

        /// @brief Getter for the filter taps
        /// @return Pointer to the filter taps
        T* getTaps(){ return m_taps; }

        /// @brief Resets the delay buffer to zeroes, see template specializations.
        void reset();

    protected:
        // Constructor and destructor are protected to prevent direct instantiation.
        FIRSR(int tapsLen)
            : m_tapsLen{tapsLen}
        {
        }

        ~FIRSR()
        {
            ippsFree(m_taps);
            ippsFree(m_delay);
            ippsFree(m_pSpec);
            ippsFree(m_pBuf);
        }

        // Storage
        int m_tapsLen;
        T* m_taps = nullptr;
        T* m_delay = nullptr;
        Ipp8u* m_pSpec = nullptr; // for the specification structure
        Ipp8u* m_pBuf = nullptr; // work buffer during invocations

        /// @brief Setup method (see template specializations below).
        /// This should be called in child class constructors
        /// after the taps have been generated.
        void setup();
    };

    /*
    Template specializations for filter()
    */
    template <typename T>
    inline void FIRSR<T>::filter(const T* src, T* dst, int len)
    {
        throw std::runtime_error("FIRSR::filter() not implemented for generic types.");
    }

    // Ipp32f specialization
    template <>
    inline void FIRSR<Ipp32f>::filter(const Ipp32f* src, Ipp32f* dst, int len)
    {
        // Simply redirect to the correct function
        IppStatus sts;
        if ((sts = ippsFIRSR_32f(src, dst, len, (IppsFIRSpec_32f*)m_pSpec, m_delay, NULL, m_pBuf)) != ippStsNoErr)
            throw std::runtime_error("ippsFIRSR_32f() failed with error code " + std::to_string(sts));
        
        // For now, we perform the destination delay copy ourselves, since I'm not sure if the function
        // safely manages the case when destination delay buffer and src delay buffer are the same.
        if((sts = ippsCopy_32f(&src[len-m_tapsLen+1], m_delay, m_tapsLen-1)) != ippStsNoErr)
            throw std::runtime_error("ippsCopy_32f() failed with error code " + std::to_string(sts));
    }

    // Ipp64f specialization
    template <>
    inline void FIRSR<Ipp64f>::filter(const Ipp64f* src, Ipp64f* dst, int len)
    {
        // Simply redirect to the correct function
        IppStatus sts;
        if ((sts = ippsFIRSR_64f(src, dst, len, (IppsFIRSpec_64f*)m_pSpec, m_delay, NULL, m_pBuf))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRSR_64f() failed with error code " + std::to_string(sts));
            
        // For now, we perform the destination delay copy ourselves, since I'm not sure if the function
        // safely manages the case when destination delay buffer and src delay buffer are the same.
        if((sts = ippsCopy_64f(&src[len-m_tapsLen+1], m_delay, m_tapsLen-1)) != ippStsNoErr)
            throw std::runtime_error("ippsCopy_64f() failed with error code " + std::to_string(sts));
    }

    // Ipp32fc specialization
    template <>
    inline void FIRSR<Ipp32fc>::filter(const Ipp32fc* src, Ipp32fc* dst, int len)
    {
        // Simply redirect to the correct function
        IppStatus sts;
        if ((sts = ippsFIRSR_32fc(src, dst, len, (IppsFIRSpec_32fc*)m_pSpec, m_delay, NULL, m_pBuf))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRSR_32fc() failed with error code " + std::to_string(sts));
        
        // For now, we perform the destination delay copy ourselves, since I'm not sure if the function
        // safely manages the case when destination delay buffer and src delay buffer are the same.
        if((sts = ippsCopy_32fc(&src[len-m_tapsLen+1], m_delay, m_tapsLen-1)) != ippStsNoErr)
            throw std::runtime_error("ippsCopy_32fc() failed with error code " + std::to_string(sts));
    }

    // Ipp64fc specialization
    template <>
    inline void FIRSR<Ipp64fc>::filter(const Ipp64fc* src, Ipp64fc* dst, int len)
    {
        // Simply redirect to the correct function
        IppStatus sts;
        if ((sts = ippsFIRSR_64fc(src, dst, len, (IppsFIRSpec_64fc*)m_pSpec, m_delay, NULL, m_pBuf))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRSR_64fc() failed with error code " + std::to_string(sts));
            
        // For now, we perform the destination delay copy ourselves, since I'm not sure if the function
        // safely manages the case when destination delay buffer and src delay buffer are the same.
        if((sts = ippsCopy_64fc(&src[len-m_tapsLen+1], m_delay, m_tapsLen-1)) != ippStsNoErr)
            throw std::runtime_error("ippsCopy_64fc() failed with error code " + std::to_string(sts));
    }

    /*
    Template specializations for reset()
    */
    template <typename T>
    inline void FIRSR<T>::reset()
    {
        throw std::runtime_error("FIRSR::reset() not implemented for generic types.");
    }

    // Ipp32f specialization
    template <>
    inline void FIRSR<Ipp32f>::reset()
    {
        // Simply zero the correct length
        IppStatus sts;
        if ((sts = ippsZero_32f(m_delay, m_tapsLen-1))!= ippStsNoErr)
            throw std::runtime_error("ippsZero_32f() failed with error code " + std::to_string(sts));
    }

    // Ipp64f specialization
    template <>
    inline void FIRSR<Ipp64f>::reset()
    {
        // Simply zero the correct length
        IppStatus sts;
        if ((sts = ippsZero_64f(m_delay, m_tapsLen-1))!= ippStsNoErr)
            throw std::runtime_error("ippsZero_64f() failed with error code " + std::to_string(sts));
    }

    // Ipp32fc specialization
    template <>
    inline void FIRSR<Ipp32fc>::reset()
    {
        // Simply zero the correct length
        IppStatus sts;
        if ((sts = ippsZero_32fc(m_delay, m_tapsLen-1))!= ippStsNoErr)
            throw std::runtime_error("ippsZero_32fc() failed with error code " + std::to_string(sts));
    }

    // Ipp64fc specialization
    template <>
    inline void FIRSR<Ipp64fc>::reset()
    {
        // Simply zero the correct length
        IppStatus sts;
        if ((sts = ippsZero_64fc(m_delay, m_tapsLen-1))!= ippStsNoErr)
            throw std::runtime_error("ippsZero_64fc() failed with error code " + std::to_string(sts));
    }

    /*
    Template specializations for setup()
    */
    template <typename T>
    inline void FIRSR<T>::setup()
    {
        throw std::runtime_error("FIRSR::setup() not implemented for generic types.");
    }

    // Ipp32f specialization
    template <>
    inline void FIRSR<Ipp32f>::setup()
    {
        IppStatus sts;
        // Check that the taps are no longer null
        if (m_taps == nullptr)
            throw std::runtime_error("FIRSR::setup() - m_taps is null.");

        // Allocate the delay buffer
        m_delay = ippsMalloc_32f_L(m_tapsLen-1);
        // Zero the delay buffer
        reset();

        // Get sizes of spec structure and work buffer
        int specSize, bufSize;
        if((sts = ippsFIRSRGetSize(m_tapsLen, ipp32f, &specSize, &bufSize)) != ippStsNoErr)
            throw std::runtime_error("ippsFIRSRGetSize() failed.");

        // Allocate the two things
        m_pSpec = ippsMalloc_8u_L(specSize);
        m_pBuf = ippsMalloc_8u_L(bufSize);

        // Initialize the spec structure
        if ((sts = ippsFIRSRInit_32f(m_taps, m_tapsLen, ippAlgAuto, (IppsFIRSpec_32f*)m_pSpec)) != ippStsNoErr)
            throw std::runtime_error("ippsFIRSRInit_32f() failed.");

    }

    // Ipp64f specialization
    template <>
    inline void FIRSR<Ipp64f>::setup()
    {
        IppStatus sts;
        // Check that the taps are no longer null
        if (m_taps == nullptr)
            throw std::runtime_error("FIRSR::setup() - m_taps is null.");

        // Allocate the delay buffer
        m_delay = ippsMalloc_64f_L(m_tapsLen-1);
        // Zero the delay buffer
        reset();

        // Get sizes of spec structure and work buffer
        int specSize, bufSize;
        if((sts = ippsFIRSRGetSize(m_tapsLen, ipp64f, &specSize, &bufSize))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRSRGetSize() failed.");

        // Allocate the two things
        m_pSpec = ippsMalloc_8u_L(specSize);
        m_pBuf = ippsMalloc_8u_L(bufSize);

        // Initialize the spec structure
        if ((sts = ippsFIRSRInit_64f(m_taps, m_tapsLen, ippAlgAuto, (IppsFIRSpec_64f*)m_pSpec))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRSRInit_64f() failed.");
    }

    // Ipp32fc specialization
    template <>
    inline void FIRSR<Ipp32fc>::setup()
    {
        IppStatus sts;
        // Check that the taps are no longer null
        if (m_taps == nullptr)
            throw std::runtime_error("FIRSR::setup() - m_taps is null.");
            
        // Allocate the delay buffer
        m_delay = ippsMalloc_32fc_L(m_tapsLen-1);
        // Zero the delay buffer
        reset();

        // Get sizes of spec structure and work buffer
        int specSize, bufSize;
        if((sts = ippsFIRSRGetSize(m_tapsLen, ipp32fc, &specSize, &bufSize))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRSRGetSize() failed.");

        // Allocate the two things
        m_pSpec = ippsMalloc_8u_L(specSize);
        m_pBuf = ippsMalloc_8u_L(bufSize);

        // Initialize the spec structure
        if ((sts = ippsFIRSRInit_32fc(m_taps, m_tapsLen, ippAlgAuto, (IppsFIRSpec_32fc*)m_pSpec))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRSRInit_32fc() failed.");
    }

    // Ipp64fc specialization
    template <>
    inline void FIRSR<Ipp64fc>::setup()
    {
        IppStatus sts;
        // Check that the taps are no longer null
        if (m_taps == nullptr)
            throw std::runtime_error("FIRSR::setup() - m_taps is null.");
            
        // Allocate the delay buffer
        m_delay = ippsMalloc_64fc_L(m_tapsLen-1);
        // Zero the delay buffer
        reset();
        
        // Get sizes of spec structure and work buffer
        int specSize, bufSize;
        if((sts = ippsFIRSRGetSize(m_tapsLen, ipp64fc, &specSize, &bufSize))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRSRGetSize() failed.");
            
        // Allocate the two things
        m_pSpec = ippsMalloc_8u_L(specSize);
        m_pBuf = ippsMalloc_8u_L(bufSize);

        // Initialize the spec structure
        if ((sts = ippsFIRSRInit_64fc(m_taps, m_tapsLen, ippAlgAuto, (IppsFIRSpec_64fc*)m_pSpec))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRSRInit_64fc() failed.");
    }




    /*
    =================================================================================
    =================================================================================
    =================================================================================
    =================================================================================
    =================================================================================
                                        FIRSRLowpass
    =================================================================================
    =================================================================================
    =================================================================================
    =================================================================================
    =================================================================================
    */
    /// @brief Lowpass filter child class.
    /// @tparam T 32f, 64f, 32fc, 64fc
    template <typename T>
    class FIRSRLowpass : public FIRSR<T>
    {
    public:
        FIRSRLowpass(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
            : FIRSR<T>{tapsLen}
        {
            generate(rFreq, tapsLen, winType, doNormal);
            this->setup();
        }
        ~FIRSRLowpass()
        {
        }

    private:
        void generate(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal);
    };

    /*
    FIRSRLowpass generate() specializations.
    */
    template <typename T>
    inline void FIRSRLowpass<T>::generate(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
    {
        throw std::runtime_error("FIRSRLowpass::generate() not implemented for generic types.");
    }

    // Ipp32f generate
    template <>
    inline void FIRSRLowpass<Ipp32f>::generate(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
    {
        IppStatus sts;
        // First allocate a temporary 64f array, since thats the output of the generator function
        Ipp64f *tmp = ippsMalloc_64f_L(tapsLen);
        // Allocate internal buffer for taps generation
        int bufferSize;
        if((sts = ippsFIRGenGetBufferSize(tapsLen, &bufferSize)) != ippStsNoErr)
            throw std::runtime_error("ippsFIRGenGetBufferSize() failed with " + std::to_string(sts));
        Ipp8u *buffer = ippsMalloc_8u_L(bufferSize);

        // Generate the filter in 64f
        if((sts = ippsFIRGenLowpass_64f(rFreq/2.0, tmp, tapsLen, winType, doNormal, buffer)) != ippStsNoErr)
            throw std::runtime_error("ippsFIRGenLowpass_64f() failed with " + std::to_string(sts));
        
        // Allocate the taps memory
        m_taps = ippsMalloc_32f_L(tapsLen);

        // Convert to 32f
        if((sts = ippsConvert_64f32f(tmp, m_taps, tapsLen)) != ippStsNoErr)
            throw std::runtime_error("ippsConvert_64f32f() failed with " + std::to_string(sts));

        // Cleanup temporaries
        ippsFree(tmp);
        ippsFree(buffer);
    }

    // Ipp64f generate
    template <>
    inline void FIRSRLowpass<Ipp64f>::generate(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
    {
        IppStatus sts;
        // 64f is special, since we don't need to do conversions
        // Allocate internal buffer for taps generation
        int bufferSize;
        if((sts = ippsFIRGenGetBufferSize(tapsLen, &bufferSize))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRGenGetBufferSize() failed with " + std::to_string(sts));
        Ipp8u *buffer = ippsMalloc_8u_L(bufferSize);

        // Allocate the taps memory
        m_taps = ippsMalloc_64f_L(tapsLen);

        // Generate the filter directly into m_taps
        if((sts = ippsFIRGenLowpass_64f(rFreq/2.0, m_taps, tapsLen, winType, doNormal, buffer))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRGenLowpass_64f() failed with " + std::to_string(sts));

        // Cleanup temporaries
        ippsFree(buffer);
    }

    // Ipp32fc generate
    template <>
    inline void FIRSRLowpass<Ipp32fc>::generate(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
    {
        IppStatus sts;
        // First allocate a temporary 64f array, since thats the output of the generator function
        Ipp64f *tmp = ippsMalloc_64f_L(tapsLen);
        // Allocate internal buffer for taps generation
        int bufferSize;
        if((sts = ippsFIRGenGetBufferSize(tapsLen, &bufferSize))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRGenGetBufferSize() failed with " + std::to_string(sts));
        Ipp8u *buffer = ippsMalloc_8u_L(bufferSize);

        // Generate the filter in 64f
        if((sts = ippsFIRGenLowpass_64f(rFreq/2.0, tmp, tapsLen, winType, doNormal, buffer))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRGenLowpass_64f() failed with " + std::to_string(sts));

        // Allocate the taps memory
        m_taps = ippsMalloc_32fc_L(tapsLen);

        // Convert to 32f first
        Ipp32f *tmp32f = ippsMalloc_32f_L(tapsLen);
        if((sts = ippsConvert_64f32f(tmp, tmp32f, tapsLen))!= ippStsNoErr)
            throw std::runtime_error("ippsConvert_64f32f() failed with " + std::to_string(sts));

        // RealToCplx into a complex vector
        if((sts = ippsRealToCplx_32f(tmp32f, NULL, m_taps, tapsLen))!= ippStsNoErr)
            throw std::runtime_error("ippsRealToCplx_32fc() failed with " + std::to_string(sts));

        // Cleanup temporaries
        ippsFree(tmp32f);
        ippsFree(buffer);
        ippsFree(tmp);
        
    }

    // Ipp64fc generate
    template <>
    inline void FIRSRLowpass<Ipp64fc>::generate(Ipp64f rFreq, int tapsLen, IppWinType winType, IppBool doNormal)
    {
        IppStatus sts;

        // Allocate internal buffer for taps generation
        int bufferSize;
        if((sts = ippsFIRGenGetBufferSize(tapsLen, &bufferSize))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRGenGetBufferSize() failed with " + std::to_string(sts));
        Ipp8u *buffer = ippsMalloc_8u_L(bufferSize);

        // Allocate the taps memory
        m_taps = ippsMalloc_64fc_L(tapsLen);

        // Write to a temporary buffer to prepare to convert to complex
        Ipp64f *tmp = ippsMalloc_64f_L(tapsLen);
    
        // Generate the filter directly into tmp
        if((sts = ippsFIRGenLowpass_64f(rFreq/2.0, tmp, tapsLen, winType, doNormal, buffer))!= ippStsNoErr)
            throw std::runtime_error("ippsFIRGenLowpass_64f() failed with " + std::to_string(sts));

        // Now convert to a complex vector
        if ((sts = ippsRealToCplx_64f(tmp, NULL, m_taps, tapsLen)) != ippStsNoErr)
            throw std::runtime_error("ippsRealToCplx_64fc() failed with " + std::to_string(sts));
            
        // Cleanup temporaries
        ippsFree(tmp);
        ippsFree(buffer);
    }



}