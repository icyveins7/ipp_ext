#include "ipp.h"

namespace ippe{
    namespace math{
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
    }
}
