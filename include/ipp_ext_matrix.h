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

        private:
            size_t m_rows = 0;
            size_t m_columns = 0;
    };
}