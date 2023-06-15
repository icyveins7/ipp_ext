#pragma once
#include "ipp.h"
#include <stdexcept>
#include <string>
#include "ipp_ext_errors.h"
#include "ipp_ext_vec.h"

namespace ippe
{
    template <typename T>
    class RandUniform
    {
    public:
        RandUniform()
        {

        }

        /// @brief Instantiates a RandUniform object with a particular seed.
        /// @param low Lower bound of values.
        /// @param high Upper bound of values.
        /// @param seed Seed for random number generator.
        RandUniform(T low, T high, unsigned int seed)
            : m_low{low}, m_high{high}, m_seed{seed}
        {
            prepare();
        }

        /// @brief Instantiates a RandUniform object with a seed of 0.
        /// @param low Lower bound of values.
        /// @param high Upper bound of values.
        RandUniform(T low, T high)
            : RandUniform(low, high, 0)
        {
            prepare();
        }

        /// @brief Writes uniformly distributed random values at an array pointer.
        /// @param data The output array pointer.
        /// @param length Number of values to write.
        void generate(T* data, int length);

        // Destructor
        ~RandUniform()
        {

        }

        // Getters

        T getLow(){ return m_low; }
        T getHigh(){ return m_high; }
        T getSeed(){ return m_seed; }

    private:
        T m_low = 0;
        T m_high = 1;
        unsigned int m_seed = 0;
        ippe::vector<Ipp8u> rndObj;

        void prepare();
    };


    // Template specializations for prepare

    template <typename T>
    void RandUniform<T>::prepare()
    {
        throw std::runtime_error("RandUniform not implemented for generic types.");
    }

    // Ipp8u

    template <>
    void RandUniform<Ipp8u>::prepare()
    {
        IppStatus sts;
        // Get spec size
        int sizeRndObj;
        sts = ippsRandUniformGetSize_8u(&sizeRndObj);
        IPP_NO_ERROR(sts, "ippsRandUniformGetSize_8u");

        // Allocate memory
        rndObj.resize(sizeRndObj);
        // Initialize it
        sts = ippsRandUniformInit_8u((IppsRandUniState_8u*)rndObj.data(), m_low, m_high, m_seed);
        IPP_NO_ERROR(sts, "ippsRandUniformInit_8u");
    }

    // Ipp16s

    template <>
    void RandUniform<Ipp16s>::prepare()
    {
        IppStatus sts;
        // Get spec size
        int sizeRndObj;
        sts = ippsRandUniformGetSize_16s(&sizeRndObj);
        IPP_NO_ERROR(sts, "ippsRandUniformGetSize_16s");

        // Allocate memory
        rndObj.resize(sizeRndObj);
        // Initialize it
        sts = ippsRandUniformInit_16s((IppsRandUniState_16s*)rndObj.data(), m_low, m_high, m_seed);
        IPP_NO_ERROR(sts, "ippsRandUniformInit_16s");
    }

    // Ipp32f

    template <>
    void RandUniform<Ipp32f>::prepare()
    {
        IppStatus sts;
        // Get spec size
        int sizeRndObj;
        sts = ippsRandUniformGetSize_32f(&sizeRndObj);
        IPP_NO_ERROR(sts, "ippsRandUniformGetSize_32f");

        // Allocate memory
        rndObj.resize(sizeRndObj);
        // Initialize it
        sts = ippsRandUniformInit_32f((IppsRandUniState_32f*)rndObj.data(), m_low, m_high, m_seed);
        IPP_NO_ERROR(sts, "ippsRandUniformInit_32f");
    }

    // Ipp64f

    template <>
    void RandUniform<Ipp64f>::prepare()
    {
        IppStatus sts;
        // Get spec size
        int sizeRndObj;
        sts = ippsRandUniformGetSize_64f(&sizeRndObj);
        IPP_NO_ERROR(sts, "ippsRandUniformGetSize_64f");

        // Allocate memory
        rndObj.resize(sizeRndObj);
        // Initialize it
        sts = ippsRandUniformInit_64f((IppsRandUniState_64f*)rndObj.data(), m_low, m_high, m_seed);
        IPP_NO_ERROR(sts, "ippsRandUniformInit_64f");
    }

    // Template specializations for generate

    template <typename T>
    void RandUniform<T>::generate(T* data, int length)
    {
        throw std::runtime_error("RandUniform not implemented for generic types.");
    }

    // Ipp8u

    template <>
    void RandUniform<Ipp8u>::generate(Ipp8u* data, int length)
    {
        IppStatus sts = ippsRandUniform_8u(
            data, length, (IppsRandUniState_8u*)rndObj.data()); 
        IPP_NO_ERROR(sts, "ippsRandUniform_8u");
    }

    // Ipp16s

    template <>
    void RandUniform<Ipp16s>::generate(Ipp16s* data, int length)
    {
        IppStatus sts = ippsRandUniform_16s(
            data, length, (IppsRandUniState_16s*)rndObj.data()); 
        IPP_NO_ERROR(sts, "ippsRandUniform_16s");
    }

    // Ipp32f

    template <>
    void RandUniform<Ipp32f>::generate(Ipp32f* data, int length)
    {
        IppStatus sts = ippsRandUniform_32f(
            data, length, (IppsRandUniState_32f*)rndObj.data()); 
        IPP_NO_ERROR(sts, "ippsRandUniform_32f");
    }

    // Ipp64f

    template <>
    void RandUniform<Ipp64f>::generate(Ipp64f* data, int length)
    {
        IppStatus sts = ippsRandUniform_64f(
            data, length, (IppsRandUniState_64f*)rndObj.data()); 
        IPP_NO_ERROR(sts, "ippsRandUniform_64f");
    }
}