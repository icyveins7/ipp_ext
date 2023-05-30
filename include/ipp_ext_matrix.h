#pragma once

#include "ipp_ext_vec.h"

namespace ippe
{
    /// @brief Matrix class that inherits from vector.
    /// This class has a concept of dimensions (rows and columns), along with appropriate accessors.
    /// It will also enable the use of math through public methods,
    /// like add().
    /// @tparam T Type of the matrix elements. Must be a type that satisfies ippe::vector.
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

            /// @brief Adds current matrix to another, writing result to a final matrix.
            /// @tparam U Type of the output matrix. In most cases this is the same type.
            /// but some integer calls upgrade the type for the output.
            /// @param other The second matrix to add.
            /// @param result The pre-allocated matrix to write the result to.
            template <typename U> // you don't need to put typename T here again since it's in scope
            void add(matrix<T>& other, matrix<U>& result);

            /// @brief Adds current matrix to another with integer scaling, writing result to a final matrix.
            /// @param other The second matrix to add.
            /// @param result The pre-allocated matrix to write the result to.
            /// @param scaleFactor The integer scaling factor. Output is multiplied by
            /// 2^(-scaleFactor).
            void add_Sfs(matrix& other, matrix& result, int scaleFactor);

            /// @brief Adds current matrix to another, writing the result in-place.
            /// @tparam U Type of the other matrix. In most cases this is the same type.
            /// @param other The second matrix to add.
            template <typename U>
            void add_I(matrix<U>& other);

            /// @brief Adds a constant value to the matrix, writing the result to a final matrix.
            /// @param val The constant value to add.
            /// @param result The pre-allocated matrix to write the result to.
            void addC(T val, matrix& result);

            /// @brief Adds a constant value to the matrix with integer scaling, writing the result to a final matrix.
            /// @param val The constant value to add.
            /// @param result The pre-allocated matrix to write the result to.
            /// @param scaleFactor The integer scaling factor. Output is multiplied by
            /// 2^(-scaleFactor).
            void addC_Sfs(T val, matrix& result, int scaleFactor);

            /// @brief Adds a constant value to the matrix, writing the result in-place.
            /// @param val The constant value to add.
            void addC_I(T val);

            /// @brief Adds a constant value to the matrix with integer scaling, writing the result in-place.
            /// @param val The constant value to add.
            /// @param scaleFactor The integer scaling factor. Output is multiplied by
            /// 2^(-scaleFactor).
            void addC_ISfs(T val, int scaleFactor);

            /// @brief Multiplies current matrix by another, writing result to a final matrix.
            /// @tparam U Type of the other matrix. In most cases this is the same type.
            /// @tparam V Type of the output matrix. In most cases this is the same type.
            /// @param other The second matrix to multiply.
            /// @param result The pre-allocated matrix to write the result to.
            template <typename U, typename V>
            void mul(matrix<U>& other, matrix<V>& result);

            /// @brief Multiplies current matrix by another with integer scaling, writing result to a final matrix.
            /// @tparam U Type of the other matrix. In most cases this is the same type.
            /// @tparam V Type of the output matrix. In most cases this is the same type.
            /// @param other The second matrix to multiply.
            /// @param result The pre-allocated matrix to write the result to.
            /// @param scaleFactor The integer scaling factor. Output is multiplied by
            /// 2^(-scaleFactor).
            template <typename U, typename V>
            void mul_Sfs(matrix<U>& other, matrix<V>& result, int scaleFactor);

            /// @brief Multiplies current matrix by another, writing the result in-place.
            /// @tparam U Type of the other matrix. In most cases this is the same type.
            /// @param other The second matrix to multiply.
            template <typename U>
            void mul_I(matrix<U>& other);

            /// @brief Multiplies current matrix by another with integer scaling, writing the result in-place.
            /// @param other The second matrix to multiply.
            /// @param scaleFactor The integer scaling factor. Output is multiplied by 2^(-scaleFactor).
            void mul_ISfs(matrix& other, int scaleFactor);

            /// @brief Multiplies current matrix with a constant value, writing the result to a final matrix.
            /// @param val The constant value to multiply.
            /// @param result The pre-allocated matrix to write the result to.
            void mulC(T val, matrix& result);

            /// @brief Multiplies current matrix with a constant value with integer scaling, writing the result to a final matrix.
            /// @tparam U Type of the output matrix. In most cases this is the same type.
            /// @param val The constant value to multiply.
            /// @param result The pre-allocated matrix to write the result to.
            /// @param scaleFactor The integer scaling factor. Output is multiplied by 2^(-scaleFactor).
            template <typename U>
            void mulC_Sfs(T val, matrix<U>& result, int scaleFactor);

            /// @brief Multiplies current matrix with a constant value, writing the result in-place.
            /// @param val The constant value to multiply.
            void mulC_I(T val);

            /// @brief Multiplies current matrix with a constant value with integer scaling, writing the result in-place.
            /// @tparam U Type of the constant value. In most cases this is the same type.
            /// @param val The constant value to multiply.
            /// @param scaleFactor The integer scaling factor. Output is multiplied by 2^(-scaleFactor).
            template <typename U>
            void mulC_ISfs(U val, int scaleFactor);

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

    /*
    Note: for specializations, make sure you leave a gap after the type comment,
    so that the intellisense reverts to the detailed versions in the class
    definition above.
    */ 

    // ============================
    // ============================ 
    //     Add Specializations
    // ============================
    // ============================

    template <typename T> // Template for the calling class
    template <typename U> // Additional template for the member function
    inline void matrix<T>::add(matrix<T>& other, matrix<U>& result)
    {
        throw std::runtime_error("Matrix addition only implemented for specific types.");
    }

    // Ipp16s

    template <>
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
    template <>
    inline void matrix<Ipp8u>::add(matrix<Ipp8u>& other, matrix<Ipp16u>& result)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_8u16u(this->data(), other.data(), result.data(), this->size());
    }

    // Ipp16u
    
    template <>
    template <>
    inline void matrix<Ipp16u>::add(matrix<Ipp16u>& other, matrix<Ipp16u>& result)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_16u(this->data(), other.data(), result.data(), this->size());
    }

    // Ipp32u

    template <>
    template <>
    inline void matrix<Ipp32u>::add(matrix<Ipp32u>& other, matrix<Ipp32u>& result)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_32u(this->data(), other.data(), result.data(), this->size());
    }

    // Ipp16s to Ipp32f

    template <>
    template <>
    inline void matrix<Ipp16s>::add(matrix<Ipp16s>& other, matrix<Ipp32f>& result)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_16s32f(this->data(), other.data(), result.data(), this->size());
    }

    // ============================
    // ============================ 
    //     Add_Sfs Specializations
    // ============================
    // ============================

    template <typename T>
    inline void matrix<T>::add_Sfs(matrix& other, matrix& result, int scaleFactor)
    {
        throw std::runtime_error("Matrix addition only implemented for specific types.");
    }

    // Ipp8u

    template <>
    inline void matrix<Ipp8u>::add_Sfs(matrix& other, matrix& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_8u_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor);
    }

    // Ipp16u

    template <>
    inline void matrix<Ipp16u>::add_Sfs(matrix& other, matrix& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_16u_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor);
    }

    // Ipp16s

    template <>
    inline void matrix<Ipp16s>::add_Sfs(matrix& other, matrix& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_16s_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor);
    }

    // Ipp32s

    template <>
    inline void matrix<Ipp32s>::add_Sfs(matrix& other, matrix& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_32s_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor);
    }

    // Ipp16sc

    template <>
    inline void matrix<Ipp16sc>::add_Sfs(matrix& other, matrix& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_16sc_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor);
    }

    // Ipp32sc

    template <>
    inline void matrix<Ipp32sc>::add_Sfs(matrix& other, matrix& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_32sc_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor);
    }

    // Ipp64s

    template <>
    inline void matrix<Ipp64s>::add_Sfs(matrix& other, matrix& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAdd_64s_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor);
    }

    // ============================
    // ============================ 
    // Add (in-place) Specializations
    // ============================
    // ============================

    template <typename T> 
    template <typename U> 
    inline void matrix<T>::add_I(matrix<U>& other)
    {
        throw std::runtime_error("Matrix addition only implemented for specific types.");
    }

    // Ipp16s

    template <>
    template <>
    inline void matrix<Ipp16s>::add_I(matrix<Ipp16s>& other)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform in-place addition
        ippsAdd_16s_I(other.data(), this->data(), this->size());
    }

    // Ipp32f

    template <>
    template <>
    inline void matrix<Ipp32f>::add_I(matrix<Ipp32f>& other)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform in-place addition
        ippsAdd_32f_I(other.data(), this->data(), this->size());
    }

    // Ipp64f

    template <>
    template <>
    inline void matrix<Ipp64f>::add_I(matrix<Ipp64f>& other)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform in-place addition
        ippsAdd_64f_I(other.data(), this->data(), this->size());
    }

    // Ipp32fc

    template <>
    template <>
    inline void matrix<Ipp32fc>::add_I(matrix<Ipp32fc>& other)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform in-place addition
        ippsAdd_32fc_I(other.data(), this->data(), this->size());
    }

    // Ipp64fc

    template <>
    template <>
    inline void matrix<Ipp64fc>::add_I(matrix<Ipp64fc>& other)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform in-place addition
        ippsAdd_64fc_I(other.data(), this->data(), this->size());
    }

    // Ipp16s from Ipp32s

    template <>
    template <>
    inline void matrix<Ipp32s>::add_I(matrix<Ipp16s>& other)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform in-place addition
        ippsAdd_16s32s_I(other.data(), this->data(), this->size());
    }

    // Ipp32u

    template <>
    template <>
    inline void matrix<Ipp32u>::add_I(matrix<Ipp32u>& other)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform in-place addition
        ippsAdd_32u_I(other.data(), this->data(), this->size());
    }

    // ============================
    // ============================ 
    // AddC specializations
    // ============================
    // ============================

    template <typename T>
    inline void matrix<T>::addC(T value, matrix& result)
    {
        throw std::runtime_error("Matrix addition only implemented for specific types.");
    }

    // Ipp32f

    template <>
    inline void matrix<Ipp32f>::addC(Ipp32f value, matrix<Ipp32f>& result)
    {
        // Check dimensions
        if (!sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAddC_32f(this->data(), value, result.data(), this->size());
    }

    // Ipp64f

    template <>
    inline void matrix<Ipp64f>::addC(Ipp64f value, matrix<Ipp64f>& result)
    {
        // Check dimensions
        if (!sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAddC_64f(this->data(), value, result.data(), this->size());
    }

    // Ipp32fc

    template <>
    inline void matrix<Ipp32fc>::addC(Ipp32fc value, matrix<Ipp32fc>& result)
    {
        // Check dimensions
        if (!sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAddC_32fc(this->data(), value, result.data(), this->size());
    }

    // Ipp64fc

    template <>
    inline void matrix<Ipp64fc>::addC(Ipp64fc value, matrix<Ipp64fc>& result)
    {
        // Check dimensions
        if (!sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAddC_64fc(this->data(), value, result.data(), this->size());
    }

    // ============================
    // ============================ 
    // addC_Sfs specializations
    // ============================
    // ============================

    template <typename T>
    inline void matrix<T>::addC_Sfs(T value, matrix& result, int scaleFactor)
    {
        throw std::runtime_error("Matrix addition only implemented for specific types.");
    }

    // Ipp8u

    template <>
    inline void matrix<Ipp8u>::addC_Sfs(Ipp8u value, matrix<Ipp8u>& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        // Perform out-of-place addition
        ippsAddC_8u_Sfs(this->data(), value, result.data(), this->size(), scaleFactor);
    }
    
    // Ipp16s

    template <>
    inline void matrix<Ipp16s>::addC_Sfs(Ipp16s value, matrix<Ipp16s>& result, int scaleFactor)
    {
        if (!sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        ippsAddC_16s_Sfs(this->data(), value, result.data(), this->size(), scaleFactor);
    }

    // Ipp16u

    template <>
    inline void matrix<Ipp16u>::addC_Sfs(Ipp16u value, matrix<Ipp16u>& result, int scaleFactor)
    {
        if (!sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        ippsAddC_16u_Sfs(this->data(), value, result.data(), this->size(), scaleFactor);
    }

    // Ipp32s

    template <>
    inline void matrix<Ipp32s>::addC_Sfs(Ipp32s value, matrix<Ipp32s>& result, int scaleFactor)
    {
        if (!sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        ippsAddC_32s_Sfs(this->data(), value, result.data(), this->size(), scaleFactor);
    }

    // Ipp16sc

    template <>
    inline void matrix<Ipp16sc>::addC_Sfs(Ipp16sc value, matrix<Ipp16sc>& result, int scaleFactor)
    {
        if (!sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        ippsAddC_16sc_Sfs(this->data(), value, result.data(), this->size(), scaleFactor);
    }

    // Ipp32sc

    template <>
    inline void matrix<Ipp32sc>::addC_Sfs(Ipp32sc value, matrix<Ipp32sc>& result, int scaleFactor)
    {
        if (!sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        ippsAddC_32sc_Sfs(this->data(), value, result.data(), this->size(), scaleFactor);
    }

    // Ipp64u

    template <>
    inline void matrix<Ipp64u>::addC_Sfs(Ipp64u value, matrix<Ipp64u>& result, int scaleFactor)
    {
        if (!sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        ippsAddC_64u_Sfs(this->data(), value, result.data(), this->size(), scaleFactor, ippRndZero);
    }

    // Ipp64s

    template <>
    inline void matrix<Ipp64s>::addC_Sfs(Ipp64s value, matrix<Ipp64s>& result, int scaleFactor)
    {
        if (!sameDimensions(result))
            throw std::runtime_error("Dimensions must all be identical.");

        ippsAddC_64s_Sfs(this->data(), value, result.data(), this->size(), scaleFactor, ippRndZero);
    }

    // ============================
    // ============================ 
    // addC_I specializations
    // ============================
    // ============================

    template <typename T>
    inline void matrix<T>::addC_I(T value)
    {
        throw std::runtime_error("Matrix addition only implemented for specific types.");
    }

    // Ipp16s

    template <>
    inline void matrix<Ipp16s>::addC_I(Ipp16s value)
    {
        IppStatus sts;
        // Perform out-of-place addition
        if ((sts = ippsAddC_16s_I(value, this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsAddC_16s_I failed with error " + std::to_string(sts));
    }

    // Ipp32f

    template <>
    inline void matrix<Ipp32f>::addC_I(Ipp32f value)
    {
        IppStatus sts;
        // Perform out-of-place addition
        if ((sts = ippsAddC_32f_I(value, this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsAddC_32f_I failed with error " + std::to_string(sts));
    }

    // Ipp64f

    template <>
    inline void matrix<Ipp64f>::addC_I(Ipp64f value)
    {
        IppStatus sts;
        // Perform out-of-place addition
        if ((sts = ippsAddC_64f_I(value, this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsAddC_64f_I failed with error " + std::to_string(sts));
    }

    // Ipp32fc

    template <>
    inline void matrix<Ipp32fc>::addC_I(Ipp32fc value)
    {
        IppStatus sts;
        // Perform out-of-place addition
        if ((sts = ippsAddC_32fc_I(value, this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsAddC_32fc_I failed with error " + std::to_string(sts));
    }

    // Ipp64fc

    template <>
    inline void matrix<Ipp64fc>::addC_I(Ipp64fc value)
    {
        IppStatus sts;
        // Perform out-of-place addition
        if ((sts = ippsAddC_64fc_I(value, this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsAddC_64fc_I failed with error " + std::to_string(sts));
    }

    // ============================
    // ============================ 
    // addC_ISfs specializations
    // ============================
    // ============================

    template <typename T>
    inline void matrix<T>::addC_ISfs(T value, int scaleFactor)
    {
        throw std::runtime_error("Matrix addition only implemented for specific types.");
    }

    // Ipp8u

    template <>
    inline void matrix<Ipp8u>::addC_ISfs(Ipp8u value, int scaleFactor)
    {
        IppStatus sts;
        // Perform out-of-place addition
        if ((sts = ippsAddC_8u_ISfs(value, this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsAddC_8u_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp16u

    template <>
    inline void matrix<Ipp16u>::addC_ISfs(Ipp16u value, int scaleFactor)
    {
        IppStatus sts;
        // Perform out-of-place addition
        if ((sts = ippsAddC_16u_ISfs(value, this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsAddC_16u_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp16s

    template <>
    inline void matrix<Ipp16s>::addC_ISfs(Ipp16s value, int scaleFactor)
    {
        IppStatus sts;
        // Perform out-of-place addition
        if ((sts = ippsAddC_16s_ISfs(value, this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsAddC_16s_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp32s

    template <>
    inline void matrix<Ipp32s>::addC_ISfs(Ipp32s value, int scaleFactor)
    {
        IppStatus sts;
        // Perform out-of-place addition
        if ((sts = ippsAddC_32s_ISfs(value, this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsAddC_32s_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp16sc

    template <>
    inline void matrix<Ipp16sc>::addC_ISfs(Ipp16sc value, int scaleFactor)
    {
        IppStatus sts;
        // Perform out-of-place addition
        if ((sts = ippsAddC_16sc_ISfs(value, this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsAddC_16sc_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp32sc

    template <>
    inline void matrix<Ipp32sc>::addC_ISfs(Ipp32sc value, int scaleFactor)
    {
        IppStatus sts;
        // Perform out-of-place addition
        if ((sts = ippsAddC_32sc_ISfs(value, this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsAddC_32sc_ISfs failed with error " + std::to_string(sts));
    }

    // ============================
    // ============================ 
    // Mul Specializations
    // ============================
    // ============================

    template <typename T>
    template <typename U, typename V>
    inline void matrix<T>::mul(matrix<U>& other, matrix<V>& result)
    {
        throw std::runtime_error("Matrix element-wise multiplication only implemented for specific types.");
    }

    // Ipp16s

    template <>
    template <>
    inline void matrix<Ipp16s>::mul(matrix<Ipp16s>& other, matrix<Ipp16s>& result)
    {
        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_16s(this->data(), other.data(), result.data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_16s failed with error " + std::to_string(sts));
    }

    // Ipp32f

    template <>
    template <>
    inline void matrix<Ipp32f>::mul(matrix<Ipp32f>& other, matrix<Ipp32f>& result)
    {
        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_32f(this->data(), other.data(), result.data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_32f failed with error " + std::to_string(sts));
    }

    // Ipp64f

    template <>
    template <>
    inline void matrix<Ipp64f>::mul(matrix<Ipp64f>& other, matrix<Ipp64f>& result)
    {
        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_64f(this->data(), other.data(), result.data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_64f failed with error " + std::to_string(sts));
    }

    // Ipp32fc

    template <>
    template <>
    inline void matrix<Ipp32fc>::mul(matrix<Ipp32fc>& other, matrix<Ipp32fc>& result)
    {
        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_32fc(this->data(), other.data(), result.data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_32fc failed with error " + std::to_string(sts));
    }

    // Ipp64fc

    template <>
    template <>
    inline void matrix<Ipp64fc>::mul(matrix<Ipp64fc>& other, matrix<Ipp64fc>& result)
    {
        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_64fc(this->data(), other.data(), result.data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_64fc failed with error " + std::to_string(sts));
    }

    // Ipp8u,Ipp8u to Ipp16u

    template <>
    template <>
    inline void matrix<Ipp8u>::mul(matrix<Ipp8u>& other, matrix<Ipp16u>& result)
    {
        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_8u16u(this->data(), other.data(), result.data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_8u16u failed with error " + std::to_string(sts));
    }

    // Ipp32f,Ipp32fc to Ipp32fc (this is the only non-symmetric input one)

    template <>
    template <>
    inline void matrix<Ipp32f>::mul(matrix<Ipp32fc>& other, matrix<Ipp32fc>& result)
    {
        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_32f32fc(this->data(), other.data(), result.data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_32f32fc failed with error " + std::to_string(sts));
    }

    // The reverse of the above

    template <>
    template <>
    inline void matrix<Ipp32fc>::mul(matrix<Ipp32f>& other, matrix<Ipp32fc>& result)
    {
        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_32f32fc(other.data(), this->data(), result.data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_32f32fc failed with error " + std::to_string(sts));
    }

    // Ipp16s to Ipp32f

    template <>
    template <>
    inline void matrix<Ipp16s>::mul(matrix<Ipp16s>& other, matrix<Ipp32f>& result)
    {
        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_16s32f(this->data(), other.data(), result.data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_16s32f failed with error " + std::to_string(sts));
    }

    // ============================
    // ============================ 
    // Mul_Sfs Specializations
    // ============================
    // ============================

    template <typename T>
    template <typename U, typename V>
    inline void matrix<T>::mul_Sfs(matrix<U>& other, matrix<V>& result, int scaleFactor)
    {
        throw std::runtime_error("Matrix element-wise multiplication only implemented for specific types.");
    }

    // Ipp8u

    template <>
    template <>
    inline void matrix<Ipp8u>::mul_Sfs(matrix<Ipp8u>& other, matrix<Ipp8u>& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_8u_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_8u_Sfs failed with error " + std::to_string(sts));
    }

    // Ipp16u

    template <>
    template <>
    inline void matrix<Ipp16u>::mul_Sfs(matrix<Ipp16u>& other, matrix<Ipp16u>& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_16u_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_16u_Sfs failed with error " + std::to_string(sts));
    }

    // Ipp16s

    template <>
    template <>
    inline void matrix<Ipp16s>::mul_Sfs(matrix<Ipp16s>& other, matrix<Ipp16s>& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_16s_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_16s_Sfs failed with error " + std::to_string(sts));
    }

    // Ipp32s

    template <>
    template <>
    inline void matrix<Ipp32s>::mul_Sfs(matrix<Ipp32s>& other, matrix<Ipp32s>& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_32s_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_32s_Sfs failed with error " + std::to_string(sts));
    }

    // Ipp16sc

    template <>
    template <>
    inline void matrix<Ipp16sc>::mul_Sfs(matrix<Ipp16sc>& other, matrix<Ipp16sc>& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_16sc_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_16sc_Sfs failed with error " + std::to_string(sts));
    }

    // Ipp32sc

    template <>
    template <>
    inline void matrix<Ipp32sc>::mul_Sfs(matrix<Ipp32sc>& other, matrix<Ipp32sc>& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_32sc_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_32sc_Sfs failed with error " + std::to_string(sts));
    }

    // Ipp16s to Ipp32s
    
    template <>
    template <>
    inline void matrix<Ipp16s>::mul_Sfs(matrix<Ipp16s>& other, matrix<Ipp32s>& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_16s32s_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_16s32s_Sfs failed with error " + std::to_string(sts));
    }

    // Ipp16u,Ipp16s to Ipp16s

    template <>
    template <>
    inline void matrix<Ipp16u>::mul_Sfs(matrix<Ipp16s>& other, matrix<Ipp16s>& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_16u16s_Sfs(this->data(), other.data(), result.data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_16u16s_Sfs failed with error " + std::to_string(sts));
    }

    // Ipp16s,Ipp16u to Ipp16s

    template <>
    template <>
    inline void matrix<Ipp16s>::mul_Sfs(matrix<Ipp16u>& other, matrix<Ipp16s>& result, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other) || !sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        // Perform out-of-place multiplication
        if ((sts = ippsMul_16u16s_Sfs(other.data(), this->data(), result.data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_16s16u_Sfs failed with error " + std::to_string(sts));
    }

    // ============================
    // ============================ 
    // Mul_I Specializations
    // ============================
    // ============================

    template <typename T>
    template <typename U>
    inline void matrix<T>::mul_I(matrix<U>& other)
    {
        throw std::runtime_error("Matrix element-wise multiplication only implemented for specific types.");
    }

    // Ipp16s

    template <>
    template <>
    inline void matrix<Ipp16s>::mul_I(matrix<Ipp16s>& other)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Matrix dimensions do not match.");

        // Perform in-place multiplication
        IppStatus sts;
        if ((sts = ippsMul_16s_I(other.data(), this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_16s_I failed with error " + std::to_string(sts));
    }

    // Ipp32f

    template <>
    template <>
    inline void matrix<Ipp32f>::mul_I(matrix<Ipp32f>& other)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Matrix dimensions do not match.");

        // Perform in-place multiplication
        IppStatus sts;
        if ((sts = ippsMul_32f_I(other.data(), this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_32f_I failed with error " + std::to_string(sts));
    }

    // Ipp64f

    template <>
    template <>
    inline void matrix<Ipp64f>::mul_I(matrix<Ipp64f>& other)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Matrix dimensions do not match.");

        // Perform in-place multiplication
        IppStatus sts;
        if ((sts = ippsMul_64f_I(other.data(), this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_64f_I failed with error " + std::to_string(sts));
    }

    // Ipp32fc

    template <>
    template <>
    inline void matrix<Ipp32fc>::mul_I(matrix<Ipp32fc>& other)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Matrix dimensions do not match.");

        // Perform in-place multiplication
        IppStatus sts;
        if ((sts = ippsMul_32fc_I(other.data(), this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_32fc_I failed with error " + std::to_string(sts));
    }

    // Ipp64fc

    template <>
    template <>
    inline void matrix<Ipp64fc>::mul_I(matrix<Ipp64fc>& other)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Matrix dimensions do not match.");

        // Perform in-place multiplication
        IppStatus sts;
        if ((sts = ippsMul_64fc_I(other.data(), this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_64fc_I failed with error " + std::to_string(sts));
    }

    // Ipp32f to Ipp32fc

    template <>
    template <>
    inline void matrix<Ipp32fc>::mul_I(matrix<Ipp32f>& other)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Matrix dimensions do not match.");

        // Perform in-place multiplication
        IppStatus sts;
        if ((sts = ippsMul_32f32fc_I(other.data(), this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMul_32f32fc_I failed with error " + std::to_string(sts));
    }

    // ============================
    // ============================ 
    // Mul_ISfs Specializations
    // ============================
    // ============================

    template <typename T>
    inline void matrix<T>::mul_ISfs(matrix<T>& other, int scaleFactor)
    {
        throw std::runtime_error("Matrix element-wise multiplication only implemented for specific types.");
    }

    // Ipp8u

    template <>
    inline void matrix<Ipp8u>::mul_ISfs(matrix<Ipp8u>& other, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Matrix dimensions do not match.");
            
        // Perform in-place multiplication
        IppStatus sts;
        if ((sts = ippsMul_8u_ISfs(other.data(), this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_8u_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp16u

    template <>
    inline void matrix<Ipp16u>::mul_ISfs(matrix<Ipp16u>& other, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Matrix dimensions do not match.");

        // Perform in-place multiplication
        IppStatus sts;
        if ((sts = ippsMul_16u_ISfs(other.data(), this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_16u_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp16s

    template <>
    inline void matrix<Ipp16s>::mul_ISfs(matrix<Ipp16s>& other, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Matrix dimensions do not match.");

        // Perform in-place multiplication
        IppStatus sts;
        if ((sts = ippsMul_16s_ISfs(other.data(), this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_16s_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp32s

    template <>
    inline void matrix<Ipp32s>::mul_ISfs(matrix<Ipp32s>& other, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Matrix dimensions do not match.");

        // Perform in-place multiplication
        IppStatus sts;
        if ((sts = ippsMul_32s_ISfs(other.data(), this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_32s_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp16sc

    template <>
    inline void matrix<Ipp16sc>::mul_ISfs(matrix<Ipp16sc>& other, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Matrix dimensions do not match.");

        // Perform in-place multiplication
        IppStatus sts;
        if ((sts = ippsMul_16sc_ISfs(other.data(), this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_16sc_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp32sc

    template <>
    inline void matrix<Ipp32sc>::mul_ISfs(matrix<Ipp32sc>& other, int scaleFactor)
    {
        // Check dimensions
        if (!sameDimensions(other))
            throw std::runtime_error("Matrix dimensions do not match.");

        // Perform in-place multiplication
        IppStatus sts;
        if ((sts = ippsMul_32sc_ISfs(other.data(), this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMul_32sc_ISfs failed with error " + std::to_string(sts));
    }


    // ============================
    // ============================ 
    // MulC Specializations
    // ============================
    // ============================

    template <typename T>
    inline void matrix<T>::mulC(T value, matrix<T>& result)
    {
        throw std::runtime_error("Matrix element-wise multiplication only implemented for specific types.");
    }

    // Ipp32f

    template <>
    inline void matrix<Ipp32f>::mulC(Ipp32f value, matrix<Ipp32f>& result)
    {
        // Check dimensions
        if (!sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        // Perform out-of-place multiplication
        IppStatus sts;
        if ((sts = ippsMulC_32f(this->data(), value, result.data(), result.size())) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_32f failed with error " + std::to_string(sts));
    }

    // Ipp64f

    template <>
    inline void matrix<Ipp64f>::mulC(Ipp64f value, matrix<Ipp64f>& result)
    {
        if (!sameDimensions(result)) 
            throw std::runtime_error("Matrix dimensions do not match.");
        IppStatus sts;
        if ((sts = ippsMulC_64f(this->data(), value, result.data(), result.size())) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_64f failed with error " + std::to_string(sts));
    }

    // Ipp32fc

    template <>
    inline void matrix<Ipp32fc>::mulC(Ipp32fc value, matrix<Ipp32fc>& result)
    {
        if (!sameDimensions(result)) 
            throw std::runtime_error("Matrix dimensions do not match.");
        IppStatus sts;
        if ((sts = ippsMulC_32fc(this->data(), value, result.data(), result.size())) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_32fc failed with error " + std::to_string(sts));
    }

    // Ipp64fc

    template <>
    inline void matrix<Ipp64fc>::mulC(Ipp64fc value, matrix<Ipp64fc>& result)
    {
        if (!sameDimensions(result)) 
            throw std::runtime_error("Matrix dimensions do not match.");
        IppStatus sts;
        if ((sts = ippsMulC_64fc(this->data(), value, result.data(), result.size())) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_64fc failed with error " + std::to_string(sts));
    }


    // ============================
    // ============================ 
    // MulC_Sfs Specializations
    // ============================
    // ============================

    template <typename T>
    template <typename U>
    inline void matrix<T>::mulC_Sfs(T value, matrix<U>& result, int scaleFactor)
    {
        throw std::runtime_error("Matrix element-wise multiplication only implemented for specific types.");
    }

    // Ipp8u

    template <>
    template <>
    inline void matrix<Ipp8u>::mulC_Sfs(Ipp8u value, matrix<Ipp8u>& result, int scaleFactor)
    {
        if (!sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        if ((sts = ippsMulC_8u_Sfs(this->data(), value, result.data(), result.size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_8u_Sfs failed with error " + std::to_string(sts));
    }

    // Ipp16s

    template <>
    template <>
    inline void matrix<Ipp16s>::mulC_Sfs(Ipp16s value, matrix<Ipp16s>& result, int scaleFactor)
    {
        if (!sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        if ((sts = ippsMulC_16s_Sfs(this->data(), value, result.data(), result.size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_16s_Sfs failed with error " + std::to_string(sts));
    }

    // Ipp16u

    template <>
    template <>
    inline void matrix<Ipp16u>::mulC_Sfs(Ipp16u value, matrix<Ipp16u>& result, int scaleFactor)
    {
        if (!sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        if ((sts = ippsMulC_16u_Sfs(this->data(), value, result.data(), result.size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_16u_Sfs failed with error " + std::to_string(sts));
    }

    // Ipp32s

    template <>
    template <>
    inline void matrix<Ipp32s>::mulC_Sfs(Ipp32s value, matrix<Ipp32s>& result, int scaleFactor)
    {
        if (!sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        if ((sts = ippsMulC_32s_Sfs(this->data(), value, result.data(), result.size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_32s_Sfs failed with error " + std::to_string(sts));
    }

    // Ipp16sc

    template <>
    template <>
    inline void matrix<Ipp16sc>::mulC_Sfs(Ipp16sc value, matrix<Ipp16sc>& result, int scaleFactor)
    {
        if (!sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        if ((sts = ippsMulC_16sc_Sfs(this->data(), value, result.data(), result.size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_16sc_Sfs failed with error " + std::to_string(sts));
    }

    // Ipp32sc

    template <>
    template <>
    inline void matrix<Ipp32sc>::mulC_Sfs(Ipp32sc value, matrix<Ipp32sc>& result, int scaleFactor)
    {
        if (!sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        if ((sts = ippsMulC_32sc_Sfs(this->data(), value, result.data(), result.size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_32sc_Sfs failed with error " + std::to_string(sts));
    }

    // Ipp32f to Ipp16s

    template <>
    template <>
    inline void matrix<Ipp32f>::mulC_Sfs(Ipp32f value, matrix<Ipp16s>& result, int scaleFactor)
    {
        if (!sameDimensions(result))
            throw std::runtime_error("Matrix dimensions do not match.");

        IppStatus sts;
        if ((sts = ippsMulC_32f16s_Sfs(this->data(), value, result.data(), result.size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_32f16s_Sfs failed with error " + std::to_string(sts));
    }
    
    // ============================
    // ============================ 
    // MulC_I Specializations
    // ============================
    // ============================

    template <typename T>
    inline void matrix<T>::mulC_I(T value)
    {
        throw std::runtime_error("Matrix element-wise multiplication only implemented for specific types.");
    }

    // Ipp16s

    template <>
    inline void matrix<Ipp16s>::mulC_I(Ipp16s value)
    {
        IppStatus sts;
        if ((sts = ippsMulC_16s_I(value, this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_16s_I failed with error " + std::to_string(sts));
    }

    // Ipp32f

    template <>
    inline void matrix<Ipp32f>::mulC_I(Ipp32f value)
    {
        IppStatus sts;
        if ((sts = ippsMulC_32f_I(value, this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_32f_I failed with error " + std::to_string(sts));
    }

    // Ipp64f

    template <>
    inline void matrix<Ipp64f>::mulC_I(Ipp64f value)
    {
        IppStatus sts;
        if ((sts = ippsMulC_64f_I(value, this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_64f_I failed with error " + std::to_string(sts));
    }

    // Ipp32fc

    template <>
    inline void matrix<Ipp32fc>::mulC_I(Ipp32fc value)
    {
        IppStatus sts;
        if ((sts = ippsMulC_32fc_I(value, this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_32fc_I failed with error " + std::to_string(sts));
    }

    // Ipp64fc

    template <>
    inline void matrix<Ipp64fc>::mulC_I(Ipp64fc value)
    {
        IppStatus sts;
        if ((sts = ippsMulC_64fc_I(value, this->data(), this->size())) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_64fc_I failed with error " + std::to_string(sts));
    }

    // ============================
    // ============================ 
    // MulC_ISfs Specializations
    // ============================
    // ============================

    template <typename T>
    template <typename U>
    inline void matrix<T>::mulC_ISfs(U value, int scaleFactor)
    {
        throw std::runtime_error("Matrix element-wise multiplication only implemented for specific types.");
    }

    // Ipp8u

    template <>
    template <>
    inline void matrix<Ipp8u>::mulC_ISfs(Ipp8u value, int scaleFactor)
    {
        IppStatus sts;
        if ((sts = ippsMulC_8u_ISfs(value, this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_8u_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp16u

    template <>
    template <>
    inline void matrix<Ipp16u>::mulC_ISfs(Ipp16u value, int scaleFactor)
    {
        IppStatus sts;
        if ((sts = ippsMulC_16u_ISfs(value, this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_16u_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp16s

    template <>
    template <>
    inline void matrix<Ipp16s>::mulC_ISfs(Ipp16s value, int scaleFactor)
    {
        IppStatus sts;
        if ((sts = ippsMulC_16s_ISfs(value, this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_16s_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp32s

    template <>
    template <>
    inline void matrix<Ipp32s>::mulC_ISfs(Ipp32s value, int scaleFactor)
    {
        IppStatus sts;
        if ((sts = ippsMulC_32s_ISfs(value, this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_32s_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp64f into Ipp64s

    template <>
    template <>
    inline void matrix<Ipp64s>::mulC_ISfs(Ipp64f value, int scaleFactor)
    {
        IppStatus sts;
        if ((sts = ippsMulC_64f64s_ISfs(value, this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_64f64s_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp16sc

    template <>
    template <>
    inline void matrix<Ipp16sc>::mulC_ISfs(Ipp16sc value, int scaleFactor)
    {
        IppStatus sts;
        if ((sts = ippsMulC_16sc_ISfs(value, this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_16sc_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp32sc

    template <>
    template <>
    inline void matrix<Ipp32sc>::mulC_ISfs(Ipp32sc value, int scaleFactor)
    {
        IppStatus sts;
        if ((sts = ippsMulC_32sc_ISfs(value, this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_32sc_ISfs failed with error " + std::to_string(sts));
    }

    // Ipp64s

    template <>
    template <>
    inline void matrix<Ipp64s>::mulC_ISfs(Ipp64s value, int scaleFactor)
    {
        IppStatus sts;
        if ((sts = ippsMulC_64s_ISfs(value, this->data(), this->size(), scaleFactor)) != ippStsNoErr)
            throw std::runtime_error("ippsMulC_64s_ISfs failed with error " + std::to_string(sts));
    }


}


