#pragma once

#include "ipp_ext_vec.h"
// We include math functions experimentally
#include "ipp_ext_math.h"

#ifndef NDEBUG
#define DEBUG(x) printf(x);
#else
#define DEBUG(x)
#endif

namespace ippe
{
    /// @brief Matrix class that inherits from vector.
    /// This class has a concept of dimensions (rows and columns), along with appropriate accessors.
    /// @tparam T Type of the matrix elements. Must be a type that satisfies ippe::vector.
    template <typename T>
    class matrix : public vector<T>
    {
        public:
            // Constructors
            matrix()
                : vector<T>()
            {
                DEBUG("matrix()\n");
                // do nothing
            }

            // Standard constructor
            matrix(size_t rows, size_t columns)
                : vector<T>(rows * columns), m_rows(rows), m_columns(columns)
            {
                DEBUG("matrix(size_t rows, size_t columns)\n");
            }

            // Explicit constructor which only specifies columns
            explicit matrix(size_t columns)
                : vector<T>(columns), m_rows(1), m_columns(columns)
            {
                DEBUG("matrix(size_t columns)\n");
            }

            // Construct with certain value
            matrix(size_t rows, size_t columns, const T& value)
                : vector<T>(rows * columns, value), m_rows(rows), m_columns(columns)
            {
                DEBUG("matrix(size_t rows, size_t columns, const T& value)\n");
            }

            // Copy constructor
            matrix(const matrix& other)
                : vector<T>(other), m_rows(other.m_rows), m_columns(other.m_columns)
            {
                DEBUG("matrix(const matrix& other)\n");
            }

            // Copy Assignment operator
            matrix& operator=(const matrix& other)
            {
                DEBUG("matrix& operator=(const matrix& other)\n");
                m_rows = other.m_rows;
                m_columns = other.m_columns;
                vector<T>::operator=(other);
                return *this;
            }

            // Move constructor
            matrix(matrix&& other)
                : vector<T>(std::move(other)), m_rows(other.m_rows), m_columns(other.m_columns)
            {
                DEBUG("matrix(matrix&& other)\n");
            }

            // Move Assignment operator
            matrix& operator=(matrix&& other)
            {
                DEBUG("matrix& operator=(matrix&& other)\n");
                m_rows = other.m_rows;
                m_columns = other.m_columns;
                vector<T>::operator=(std::move(other));
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
            T* row(size_t rowIdx)
            {
                if (rowIdx >= m_rows)
                {
                    throw std::out_of_range("Row index out of range");
                }
                else
                    return &this->m_data[m_columns * rowIdx]; 
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

            // Simple math functions

            /// @brief Creates a new matrix of the same shape by addition.
            /// @param other The other matrix.
            /// @return New matrix containing the sum.
            matrix operator+(matrix& other)
            {
                // Ensure same shape
                if (!sameDimensions(other))
                    throw std::out_of_range("Dimension mismatch for operator+");

                // Perform add using the ippe math functions
                matrix result(this->rows(), this->columns());
                ippe::math::Add(this->data(), other.data(), result.data(), result.size());

                return result;
            }

            /// @brief Creates a new matrix of the same shape by subtraction.
            /// @param other The other matrix.
            /// @return New matrix containing the difference.
            matrix operator-(matrix& other)
            {
                // Ensure same shape
                if (!sameDimensions(other))
                    throw std::out_of_range("Dimension mismatch for operator+");

                // Perform sub using the ippe math functions
                matrix result(this->rows(), this->columns());
                ippe::math::Sub(other.data(), this->data(), result.data(), result.size());

                return result;
            }

            matrix& operator+=(matrix &other)
            {
                // Ensure same shape
                if (!sameDimensions(other))
                    throw std::out_of_range("Dimension mismatch for operator+");

                // Perform add using the ippe math functions
                ippe::math::Add_I(other.data(), this->data(), this->size());

                return *this;
            }

            matrix& operator-=(matrix &other)
            {
                // Ensure same shape
                if (!sameDimensions(other))
                    throw std::out_of_range("Dimension mismatch for operator+");

                // Perform sub using the ippe math functions
                ippe::math::Sub_I(other.data(), this->data(), this->size());

                return *this;
            }

            // Remove size adjustment methods (for now?)
            void push_back(T value) = delete;
            void resize(size_t new_count) = delete;
            void resize(size_t new_count, const T& value) = delete;

        private:
            size_t m_rows = 0;
            size_t m_columns = 0;

            /// @brief Checks if the other matrix has the same dimensions.
            /// @tparam U Type of the other matrix.
            /// @param other The other matrix.
            /// @return True if same dimensions, false otherwise.
            template <typename U>
            bool sameDimensions(matrix<U>& other)
            {
                return m_rows == other.rows() && m_columns == other.columns();
            }
    };


}


