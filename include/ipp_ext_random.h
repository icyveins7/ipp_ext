#pragma once
#include "ipp.h"
#include <stdexcept>
#include <string>
#include "ipp_ext_errors.h"
#include "ipp_ext_vec.h"

namespace ippe
{
    /*
    =====================
    UNIFORM DISTRIBUTION
    =====================
    */
    template <typename T>
    class RandUniform
    {
    public:
        /// @brief Instantiates a RandUniform object with default values.
        /// Low: 0.0, High: 1.0. Seed: 0.
        RandUniform()
        {
            prepare();
        }

        /// @brief Instantiates a RandUniform object with a particular seed.
        /// @param low Lower bound of values.
        /// @param high Upper bound of values (inclusive).
        /// @param seed Seed for random number generator.
        RandUniform(T low, T high, unsigned int seed)
            : m_low{low}, m_high{high}, m_seed{seed}
        {
            prepare();
        }

        /// @brief Instantiates a RandUniform object with a seed of 0.
        /// @param low Lower bound of values.
        /// @param high Upper bound of values (inclusive).
        RandUniform(T low, T high)
            : m_low{low}, m_high{high}, m_seed{0}
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
        unsigned int getSeed(){ return m_seed; }

    private:
        T m_low = 0;
        T m_high = 1;
        unsigned int m_seed = 0;
        ippe::vector<Ipp8u> rndObj;

        void prepare();
    };


    // Template specializations for prepare

    template <typename T>
    inline void RandUniform<T>::prepare()
    {
        throw std::runtime_error("RandUniform not implemented for generic types.");
    }

    // Ipp8u

    template <>
    inline void RandUniform<Ipp8u>::prepare()
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
    inline void RandUniform<Ipp16s>::prepare()
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
    inline void RandUniform<Ipp32f>::prepare()
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
    inline void RandUniform<Ipp64f>::prepare()
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
    inline void RandUniform<T>::generate(T* data, int length)
    {
        throw std::runtime_error("RandUniform not implemented for generic types.");
    }

    // Ipp8u

    template <>
    inline void RandUniform<Ipp8u>::generate(Ipp8u* data, int length)
    {
        IppStatus sts = ippsRandUniform_8u(
            data, length, (IppsRandUniState_8u*)rndObj.data()); 
        IPP_NO_ERROR(sts, "ippsRandUniform_8u");
    }

    // Ipp16s

    template <>
    inline void RandUniform<Ipp16s>::generate(Ipp16s* data, int length)
    {
        IppStatus sts = ippsRandUniform_16s(
            data, length, (IppsRandUniState_16s*)rndObj.data()); 
        IPP_NO_ERROR(sts, "ippsRandUniform_16s");
    }

    // Ipp32f

    template <>
    inline void RandUniform<Ipp32f>::generate(Ipp32f* data, int length)
    {
        IppStatus sts = ippsRandUniform_32f(
            data, length, (IppsRandUniState_32f*)rndObj.data()); 
        IPP_NO_ERROR(sts, "ippsRandUniform_32f");
    }

    // Ipp64f

    template <>
    inline void RandUniform<Ipp64f>::generate(Ipp64f* data, int length)
    {
        IppStatus sts = ippsRandUniform_64f(
            data, length, (IppsRandUniState_64f*)rndObj.data()); 
        IPP_NO_ERROR(sts, "ippsRandUniform_64f");
    }



    /*
    =====================
    GAUSSIAN DISTRIBUTION
    =====================
    */
    template <typename T>
    class RandGauss
    {
    public:
        /// @brief Instantiates a RandGauss object with default values.
        /// Mean: 0.0, Stddev: 1.0. Seed: 0.
        RandGauss()
        {
            prepare();
        }

        /// @brief Instantiates a RandGauss object with a particular seed.
        /// @param mean Mean of Gaussian distribution.
        /// @param stddev Standard deviation of Gaussian distribution.
        /// @param seed Seed for random number generator.
        RandGauss(T mean, T stddev, unsigned int seed)
            : m_mean{mean}, m_stddev{stddev}, m_seed{seed}
        {
            prepare();
        }

        /// @brief Instantiates a RandGauss object with a seed of 0.
        /// @param mean Mean of Gaussian distribution.
        /// @param stddev Standard deviation of Gaussian distribution.
        RandGauss(T mean, T stddev)
            : m_mean{mean}, m_stddev{stddev}, m_seed{0}
        {
            prepare();
        }

        /// @brief Writes gaussianly distributed random values at an array pointer.
        /// @param data The output array pointer.
        /// @param length Number of values to write.
        void generate(T* data, int length);

        // Getters

        T getMean(){ return m_mean; }
        T getStddev(){ return m_stddev; }
        unsigned int getSeed(){ return m_seed; }

    private:
        T m_mean = 0;
        T m_stddev = 1;
        unsigned int m_seed = 0;
        ippe::vector<Ipp8u> rndObj;

        void prepare();
    };

    // Template specializations for prepare

    template <typename T>
    inline void RandGauss<T>::prepare()
    {
        throw std::runtime_error("RandGauss not implemented for generic types.");
    }

    // Ipp8u

    template <>
    inline void RandGauss<Ipp8u>::prepare()
    {
        IppStatus sts;
        // Get spec size
        int sizeRndObj;
        sts = ippsRandGaussGetSize_8u(&sizeRndObj);
        IPP_NO_ERROR(sts, "ippsRandGaussGetSize_8u");

        // Allocate memory
        rndObj.resize(sizeRndObj);
        // Initialize it
        sts = ippsRandGaussInit_8u((IppsRandGaussState_8u*)rndObj.data(), m_mean, m_stddev, m_seed);
        IPP_NO_ERROR(sts, "ippsRandGaussInit_8u");
    }

    // Ipp16s

    template <>
    inline void RandGauss<Ipp16s>::prepare()
    {
        IppStatus sts;
        // Get spec size
        int sizeRndObj;
        sts = ippsRandGaussGetSize_16s(&sizeRndObj);
        IPP_NO_ERROR(sts, "ippsRandGaussGetSize_16s");

        // Allocate memory
        rndObj.resize(sizeRndObj);
        // Initialize it
        sts = ippsRandGaussInit_16s((IppsRandGaussState_16s*)rndObj.data(), m_mean, m_stddev, m_seed);
        IPP_NO_ERROR(sts, "ippsRandGaussInit_16s");
    }

    // Ipp32f

    template <>
    inline void RandGauss<Ipp32f>::prepare()
    {
        IppStatus sts;
        // Get spec size
        int sizeRndObj;
        sts = ippsRandGaussGetSize_32f(&sizeRndObj);
        IPP_NO_ERROR(sts, "ippsRandGaussGetSize_32f");

        // Allocate memory
        rndObj.resize(sizeRndObj);
        // Initialize it
        sts = ippsRandGaussInit_32f((IppsRandGaussState_32f*)rndObj.data(), m_mean, m_stddev, m_seed);
        IPP_NO_ERROR(sts, "ippsRandGaussInit_32f");
    }

    // Ipp64f

    template <>
    inline void RandGauss<Ipp64f>::prepare()
    {
        IppStatus sts;
        // Get spec size
        int sizeRndObj;
        sts = ippsRandGaussGetSize_64f(&sizeRndObj);
        IPP_NO_ERROR(sts, "ippsRandGaussGetSize_64f");

        // Allocate memory
        rndObj.resize(sizeRndObj);
        // Initialize it
        sts = ippsRandGaussInit_64f((IppsRandGaussState_64f*)rndObj.data(), m_mean, m_stddev, m_seed);
        IPP_NO_ERROR(sts, "ippsRandGaussInit_64f");
    }

    // Template specializations for generate

    template <typename T>
    inline void RandGauss<T>::generate(T* data, int length)
    {
        throw std::runtime_error("RandGauss not implemented for generic types.");
    }

    // Ipp8u

    template <>
    inline void RandGauss<Ipp8u>::generate(Ipp8u* data, int length)
    {
        IppStatus sts = ippsRandGauss_8u(
            data, length, (IppsRandGaussState_8u*)rndObj.data()); 
        IPP_NO_ERROR(sts, "ippsRandGauss_8u");
    }

    // Ipp16s

    template <>
    inline void RandGauss<Ipp16s>::generate(Ipp16s* data, int length)
    {
        IppStatus sts = ippsRandGauss_16s(
            data, length, (IppsRandGaussState_16s*)rndObj.data());
        IPP_NO_ERROR(sts, "ippsRandGauss_16s");
    }

    // Ipp32f

    template <>
    inline void RandGauss<Ipp32f>::generate(Ipp32f* data, int length)
    {
        IppStatus sts = ippsRandGauss_32f(
            data, length, (IppsRandGaussState_32f*)rndObj.data());
        IPP_NO_ERROR(sts, "ippsRandGauss_32f");
    }

    // Ipp64f

    template <>
    inline void RandGauss<Ipp64f>::generate(Ipp64f* data, int length)
    {
        IppStatus sts = ippsRandGauss_64f(
            data, length, (IppsRandGaussState_64f*)rndObj.data());
        IPP_NO_ERROR(sts, "ippsRandGauss_64f");
    }
}