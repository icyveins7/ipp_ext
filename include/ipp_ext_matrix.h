#pragma once

#include "ipp_ext_vec.h"

namespace ippe
{
    template <typename T>
    class matrix : public vector<T>
    {
        public:
            // Constructors
            matrix()
                : vector<T>()
            {
                // do nothing
            }

            // Standard constructor
            matrix(size_t rows, size_t columns)
                : vector<T>(rows * columns), m_rows(rows), m_columns(columns)
            {
                
            }

            // Explicit constructor which only specifies columns
            explicit matrix(size_t columns)
                : vector<T>(columns), m_rows(1), m_columns(columns)
            {

            }

            // Construct with certain value
            matrix(size_t rows, size_t columns, const T& value)
                : vector<T>(rows * columns, value), m_rows(rows), m_columns(columns)
            {
                
            }

            // Copy constructor
            matrix(const matrix& other)
                : vector<T>(other), m_rows(other.m_rows), m_columns(other.m_columns)
            {

            }

            // Assignment operator
            matrix& operator=(const matrix& other)
            {
                m_rows = other.m_rows;
                m_columns = other.m_columns;
                vector<T>::operator=(other);
                return *this;
            }

            // Destructor
            ~matrix()
            {
                
            }

            // Extra accessors
            size_t rows()
            {
                return m_rows;
            }

            size_t columns()
            {
                return m_columns;
            }

            // Access a row
            T& row(size_t rowIdx)
            {
                if (rowIdx >= m_rows)
                {
                    throw std::out_of_range("Row index out of range");
                }
                else
                    return this->m_data[m_columns * rowIdx]; 
                // you need this->, otherwise it fails compilation
                // see https://isocpp.org/wiki/faq/templates#nondependent-name-lookup-members
            }

            // Access a row and column
            T& index(size_t rowIdx, size_t columnIdx)
            {
                if (rowIdx >= m_rows || columnIdx >= m_columns)
                    throw std::out_of_range("Index out of range");
                else
                    return this->m_data[rowIdx * m_columns + columnIdx];
            }

            // Remove size adjustment methods (for now?)
            void push_back(T value) = delete;
            void resize(size_t new_count) = delete;
            void resize(size_t new_count, const T& value) = delete;

            // Mathematical operations (these generally require specializations)

            template <typename T, typename U>
            void add(matrix<T>& other, matrix<U>& result);

        private:
            size_t m_rows = 0;
            size_t m_columns = 0;

            bool sameDimensions(matrix& other)
            {
                return m_rows == other.m_rows && m_columns == other.m_columns;
            }
    };


    // Add Specializations
    template <typename T, typename U>
    inline void matrix<T>::add(matrix<T>& other, matrix<U>& result)
    {
        throw std::runtime_error("Matrix addition only implemented for specific types.");
    }

    // Ipp16s
    template <>
    inline void matrix<Ipp16s>::add(matrix<Ipp16s>& other, matrix<Ipp16s>& result)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_16s(this->data(), other.data(), result.data(), this->size());
    }

    // Ipp32f
    template <>
    inline void matrix<Ipp32f>::add(matrix<Ipp32f>& other, matrix<Ipp32f>& result)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_32f(this->data(), other.data(), result.data(), this->size());
    }

    // Ipp64f
    template <>
    inline void matrix<Ipp64f>::add(matrix<Ipp64f>& other, matrix<Ipp64f>& result)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_64f(this->data(), other.data(), result.data(), this->size());
    }

    // Ipp32fc
    template <>
    inline void matrix<Ipp32fc>::add(matrix<Ipp32fc>& other, matrix<Ipp32fc>& result)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_32fc(this->data(), other.data(), result.data(), this->size());
    }

    // Ipp64fc
    template <>
    inline void matrix<Ipp64fc>::add(matrix<Ipp64fc>& other, matrix<Ipp64fc>& result)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_64fc(this->data(), other.data(), result.data(), this->size());
    }

    // Ipp8u to Ipp16u
    template <>
    inline void matrix<Ipp8u>::add(matrix<Ipp8u>& other, matrix<Ipp16u>& result)
    {

    }
}

