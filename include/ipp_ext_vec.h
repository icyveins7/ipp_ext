/*
Note that all specializations are inlined in order to ensure that
multiply defined symbols errors do not occur.
*/

#pragma once

#include "ipp.h"
#include <stdexcept>
#include <string>
#include "ipp_ext_errors.h"

namespace ippe
{
	const size_t INITIAL_CAP = 128;
	
	template <typename T>
	class vector
	{
		protected:
			size_t numel = 0;
			size_t cap = 0;
			T *m_data = nullptr; // initialise as nullptr to prevent segfaults on first reserve
		
            // Helper functions
            bool isZero(const T &value); // see specializations below

		public:
		    // Constructors

			// Default constructor
			vector()
			{
				// do nothing
			}

            // Construct with certain size (unlike std::vector, we will not zero out the memory,
            // since it may not be inherently obvious what the default-insertable value for all Ipp types are)
            // If zero-ing is required, the next constructor with the value should be used instead
			explicit vector(size_t count)
			{
				numel = count;
				reserve(numel); // even if count is 0, reserve() will do nothing
			}

            vector(size_t count, const T &value)
            {
                numel = count;
                reserve(numel); // even if count is 0, reserve() will do nothing
                if (isZero(value))
                    zero(); // zero the entire vector
                else
                    set(value); // set the entire vector to value  
            }

            // Copy constructor
            vector(const vector &other)
            {
                // set size
                numel = other.numel;
                // set cap
                reserve(numel); // even if count is 0, reserve() will do nothing
                // copy data
                for (size_t i = 0; i < numel; i++)
                    m_data[i] = other.m_data[i]; // TODO: write using ippsCopy? would require template specializations
            }

            // Assignment operator
            vector& operator=(const vector &other)
            {
                // set size
                numel = other.numel;
                // set cap
                reserve(numel); // even if count is 0, reserve() will do nothing
                // copy data
                for (size_t i = 0; i < numel; i++)
                    m_data[i] = other.m_data[i]; // TODO: write using ippsCopy? would require template specializations
                return *this;
            }

			~vector()
			{
				ippsFree(m_data);
			}

			void resize(size_t new_count)
			{
				// if count is more than capacity then reserve more
				if (new_count > cap)
					reserve(new_count); // this sets cap to new_count

                // no matter what, set the numel to the new count
				numel = new_count; 
			}

            void resize(size_t new_count, const T& value)
            {
                // keep the old size
                size_t oldsize = numel;

                // resize as per normal
                resize(new_count);

                // write the values from the old to the new (strictly if its larger)
                if (numel > oldsize)
                {
                    if (isZero(value))
                        zero(oldsize, numel-oldsize); // zero up to the new count
                    else
                        set(oldsize, numel-oldsize, value); // set the value up to the new count

                }
            }

			// These only have specializations, see below
			void reserve(size_t new_cap);
			void zero(int start, int length);
            void zero()
            {
                zero(0, numel); // simply call the other one to fill the whole vector with 0
            }

            void set(int start, int length, const T& value);
            void set(const T& value)
            {
                set(0, numel, value); // simply call the other one to fill the whole vector
            }
            // end of specializations


			// Everything else below is to do with read-only access
			T* data(){
				return m_data;
			}
			
			T& back(){
				return m_data[numel-1];
			}
			
			T& front(){
				return m_data[0];
			}
			
			T& at(size_t pos)
			{
				if (pos < numel && pos >= 0)
					return m_data[pos];
				else
					throw std::out_of_range(std::string("ippe::vector::range_check: Size is ") + std::to_string(numel));
			}

            // true to std::vector, this will not perform bounds checking
			T& operator[](size_t pos)
			{
				return m_data[pos];
			}
			
			void push_back(T value) // for now lets not deal with lvalue/rvalue refs
			{
				// check size
				if (numel == cap){
					reserve(cap * 2); // we double the capacity, similar to how std::vector does it
				}
				
				m_data[numel] = value;
				numel++;
			}
			
			size_t size()
			{
				return numel;
			}
			
			size_t capacity()
			{
				return cap;
			}
			
			void clear()
			{
				numel = 0;
			}
			
			bool empty()
			{
				if (numel == 0){return true;}
				else{ return false;}
			}

	};

	/* ===============================================
	============== RESERVE SPECIALIZATIONS ===========
	GOAL IS TO USE ippsMalloc_.._L() and ippsCopy_..()
	============================================== */
	// default reserve
	template <typename T>
    inline void vector<T>::reserve(size_t new_cap)
	{
		throw std::domain_error("There is no default template for IPP vectors. Please specify a valid IPP type.");
	}

	// Ipp8u reserve
	template <>
    inline void vector<Ipp8u>::reserve(size_t new_cap)
	{
		if (new_cap > cap)
		{
			// allocate new memory
			Ipp8u *newm_data = ippsMalloc_8u_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

			// copy the existing data first
			IppStatus sts = ippsCopy_8u(m_data, newm_data, (int)cap);
            IPP_NO_ERROR(sts, "ippsCopy_8u");

			// free the old memory
			ippsFree(m_data);
			// set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
		}
	}

	// Ipp16u reserve
	template <>
    inline void vector<Ipp16u>::reserve(size_t new_cap)
	{
		if (new_cap > cap)
        {
            // allocate new memory
            Ipp16u *newm_data = ippsMalloc_16u_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first
            IppStatus sts = ippsCopy_16s((Ipp16s*)m_data, (Ipp16s*)newm_data, (int)cap); // wrap as 16s
            IPP_NO_ERROR(sts, "ippsCopy_16s");

            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
        }
	}

	// Ipp32u reserve
	template <>
    inline void vector<Ipp32u>::reserve(size_t new_cap)
	{
		if (new_cap > cap)
        {
            // allocate new memory
            Ipp32u *newm_data = ippsMalloc_32u_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first
            IppStatus sts = ippsCopy_32s((Ipp32s*)m_data, (Ipp32s*)newm_data, (int)cap); // wrap as 32s
            IPP_NO_ERROR(sts, "ippsCopy_32s");

            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
        }
	}

	// Ipp64u reserve
	template <>
    inline void vector<Ipp64u>::reserve(size_t new_cap)
	{
		if (new_cap > cap)
        {
            // allocate new memory
            Ipp64u *newm_data = (Ipp64u*)ippsMalloc_64s_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first
            IppStatus sts = ippsCopy_64s((Ipp64s*)m_data, (Ipp64s*)newm_data, (int)cap); // wrap as 64s
            IPP_NO_ERROR(sts, "ippsCopy_64s");

            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
            // set the new capacity
            cap = new_cap;
        }
	}

	// Ipp8s reserve
	template <>
    inline void vector<Ipp8s>::reserve(size_t new_cap)
	{
		if (new_cap > cap)
        {
            // allocate new memory
            Ipp8s *newm_data = ippsMalloc_8s_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first
            IppStatus sts = ippsCopy_8u((Ipp8u*)m_data, (Ipp8u*)newm_data, (int)cap); // wrap as 8u
            IPP_NO_ERROR(sts, "ippsCopy_8u");

            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
        }
	}

	// Ipp16s reserve
	template <>
    inline void vector<Ipp16s>::reserve(size_t new_cap)
	{
		if (new_cap > cap)
        {
            // allocate new memory
            Ipp16s *newm_data = ippsMalloc_16s_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first
            IppStatus sts = ippsCopy_16s((Ipp16s*)m_data, (Ipp16s*)newm_data, (int)cap);
            IPP_NO_ERROR(sts, "ippsCopy_16s");


            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
        }
	}

	// Ipp32s reserve
	template <>
    inline void vector<Ipp32s>::reserve(size_t new_cap)
	{
		if (new_cap > cap)
        {
            // allocate new memory
            Ipp32s *newm_data = ippsMalloc_32s_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first
            IppStatus sts = ippsCopy_32s((Ipp32s*)m_data, (Ipp32s*)newm_data, (int)cap);
            IPP_NO_ERROR(sts, "ippsCopy_32s");

            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
        }
	}

	// Ipp64s reserve
	template <>
    inline void vector<Ipp64s>::reserve(size_t new_cap)
	{
		if (new_cap > cap)
        {
            // allocate new memory
            Ipp64s *newm_data = ippsMalloc_64s_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first
            IppStatus sts = ippsCopy_64s((Ipp64s*)m_data, (Ipp64s*)newm_data, (int)cap);
            IPP_NO_ERROR(sts, "ippsCopy_64s");

            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
        }
	}

	// Ipp32f reserve
	template <>
    inline void vector<Ipp32f>::reserve(size_t new_cap)
	{
		if (new_cap > cap)
        {
            // allocate new memory
            Ipp32f *newm_data = ippsMalloc_32f_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first
            IppStatus sts = ippsCopy_32f((Ipp32f*)m_data, (Ipp32f*)newm_data, (int)cap);
            IPP_NO_ERROR(sts, "ippsCopy_32f");

            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
        }
	}

	// Ipp64f reserve
	template <>
    inline void vector<Ipp64f>::reserve(size_t new_cap)
	{
		if (new_cap > cap)
        {
            // allocate new memory
            Ipp64f *newm_data = ippsMalloc_64f_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first
            IppStatus sts = ippsCopy_64f((Ipp64f*)m_data, (Ipp64f*)newm_data, (int)cap);
            IPP_NO_ERROR(sts, "ippsCopy_64f");

            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
        }
	}

	// Ipp8sc reserve
	template <>
    inline void vector<Ipp8sc>::reserve(size_t new_cap)
	{
		if (new_cap > cap)
        {
            // allocate new memory
            Ipp8sc *newm_data = ippsMalloc_8sc_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first
            IppStatus sts = ippsCopy_16s((Ipp16s*)m_data, (Ipp16s*)newm_data, (int)cap); // wrap as 16s
            IPP_NO_ERROR(sts, "ippsCopy_16s");

            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
        }
	}

	// Ipp16sc reserve
	template <>
    inline void vector<Ipp16sc>::reserve(size_t new_cap)
	{
		if (new_cap > cap)
        {
            // allocate new memory
            Ipp16sc *newm_data = ippsMalloc_16sc_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first
            IppStatus sts = ippsCopy_16sc((Ipp16sc*)m_data, (Ipp16sc*)newm_data, (int)cap);
            IPP_NO_ERROR(sts, "ippsCopy_16sc");

            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
        }
	}

	// Ipp32sc reserve
	template <>
    inline void vector<Ipp32sc>::reserve(size_t new_cap)
	{
		if (new_cap > cap)
        {
            // allocate new memory
            Ipp32sc *newm_data = ippsMalloc_32sc_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first
            IppStatus sts = ippsCopy_32sc((Ipp32sc*)m_data, (Ipp32sc*)newm_data, (int)cap);
            IPP_NO_ERROR(sts, "ippsCopy_32sc");

            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
        }
	}

	// Ipp64sc reserve
	template <>
    inline void vector<Ipp64sc>::reserve(size_t new_cap)
    {
        if (new_cap > cap)
        {
            // allocate new memory
            Ipp64sc *newm_data = ippsMalloc_64sc_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first
            IppStatus sts = ippsCopy_64sc((Ipp64sc*)m_data, (Ipp64sc*)newm_data, (int)cap);
            IPP_NO_ERROR(sts, "ippsCopy_64sc");

            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
        }
    }

	// Ipp32fc reserve
	template <>
    inline void vector<Ipp32fc>::reserve(size_t new_cap)
    {
        if (new_cap > cap)
        {
            // allocate new memory
            Ipp32fc *newm_data = ippsMalloc_32fc_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first
            IppStatus sts = ippsCopy_32fc((Ipp32fc*)m_data, (Ipp32fc*)newm_data, (int)cap);
            IPP_NO_ERROR(sts, "ippsCopy_32fc");

            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
        }
    }

	// Ipp64fc reserve
	template <>
    inline void vector<Ipp64fc>::reserve(size_t new_cap)
    {
        if (new_cap > cap)
        {
            // allocate new memory
            Ipp64fc *newm_data = ippsMalloc_64fc_L(new_cap);
            // check that memory was allocated
            if (newm_data == NULL)
                throw std::bad_alloc();

            // copy the existing data first, if it exists
            IppStatus sts = ippsCopy_64fc((Ipp64fc*)m_data, (Ipp64fc*)newm_data, (int)cap);
            IPP_NO_ERROR(sts, "ippsCopy_64fc");

            // free the old memory
            ippsFree(m_data);
            // set the new data
            m_data = newm_data;
			// set the new capacity
			cap = new_cap;
        }
    }

	/* ===============================================
	============== ZERO SPECIALIZATIONS ===========
	GOAL IS TO USE ippsZero_..() ==================
	============================================== */
	template <typename T>
	inline void vector<T>::zero(int start, int length)
	{
		throw std::runtime_error("There is no default template for IPP vectors. Please specify a valid IPP type.");
	}

	// Note that not all of them have zeros for their type, but we use the same word length ones to replace it.
	// Ipp8u zero
	template <> inline void vector<Ipp8u>::zero(int start, int length){
		if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_8u((Ipp8u*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp8u>::zero() - index out of range or nullptr found.");
	}

	// Ipp16u zero
	template <> inline void vector<Ipp16u>::zero(int start, int length){
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_16s((Ipp16s*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp16u>::zero() - index out of range or nullptr found.");
    }

    // Ipp32u zero
    template <> inline void vector<Ipp32u>::zero(int start, int length){
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_32s((Ipp32s*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp32u>::zero() - index out of range or nullptr found.");
    }

    // Ipp64u zero
    template <> inline void vector<Ipp64u>::zero(int start, int length){
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_64s((Ipp64s*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp64u>::zero() - index out of range or nullptr found.");
    }

    // Ipp8s zero
	template <> inline void vector<Ipp8s>::zero(int start, int length){
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_8u((Ipp8u*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp8s>::zero() - index out of range or nullptr found.");
    }

    // Ipp16s zero
    template <> inline void vector<Ipp16s>::zero(int start, int length){
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_16s((Ipp16s*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp16s>::zero() - index out of range or nullptr found.");
    }

    // Ipp32s zero
    template <> inline void vector<Ipp32s>::zero(int start, int length){
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_32s((Ipp32s*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp32s>::zero() - index out of range or nullptr found.");
    }

    // Ipp64s zero
	template <> inline void vector<Ipp64s>::zero(int start, int length){
		if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_64s((Ipp64s*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp64s>::zero() - index out of range or nullptr found.");
	}
	
    // Ipp32f zero
	template <> inline void vector<Ipp32f>::zero(int start, int length){
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_32f((Ipp32f*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp32f>::zero() - index out of range or nullptr found.");
    }

    // Ipp64f zero
    template <> inline void vector<Ipp64f>::zero(int start, int length){
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_64f((Ipp64f*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp64f>::zero() - index out of range or nullptr found.");
    }

	// Ipp8sc zero
	template <> inline void vector<Ipp8sc>::zero(int start, int length){
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_16s((Ipp16s*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp8sc>::zero() - index out of range or nullptr found.");
    }

    // Ipp16sc zero
    template <> inline void vector<Ipp16sc>::zero(int start, int length){
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_16sc((Ipp16sc*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp16sc>::zero() - index out of range or nullptr found.");
    }

    // Ipp32sc zero
    template <> inline void vector<Ipp32sc>::zero(int start, int length){
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_32sc((Ipp32sc*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp32sc>::zero() - index out of range or nullptr found.");
    }

    // Ipp64sc zero
    template <> inline void vector<Ipp64sc>::zero(int start, int length){
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_64sc((Ipp64sc*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp64sc>::zero() - index out of range or nullptr found.");
    }

    // Ipp32fc zero
	template <> inline void vector<Ipp32fc>::zero(int start, int length){
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_32fc((Ipp32fc*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp32fc>::zero() - index out of range or nullptr found.");
    }

    // Ipp64fc zero
    template <> inline void vector<Ipp64fc>::zero(int start, int length){
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsZero_64fc((Ipp64fc*)&m_data[start], (int)(length < 0 ? numel - start : length));
        else
            throw std::out_of_range("vector<Ipp64fc>::zero() - index out of range or nullptr found.");
    }

    /* ===============================================
	============== isZero SPECIALIZATIONS ===========
	============================================== */
	template <typename T>
	inline bool vector<T>::isZero(const T& value){ return value == 0; }
    // Now just specialize the complex valued ones
    template <> inline bool vector<Ipp8sc>::isZero(const Ipp8sc& value){ return (value.re == 0 && value.im == 0); }
    template <> inline bool vector<Ipp16sc>::isZero(const Ipp16sc& value){ return (value.re == 0 && value.im == 0); }
    template <> inline bool vector<Ipp32sc>::isZero(const Ipp32sc& value){ return (value.re == 0 && value.im == 0); }
    template <> inline bool vector<Ipp64sc>::isZero(const Ipp64sc& value){ return (value.re == 0 && value.im == 0); }
    template <> inline bool vector<Ipp32fc>::isZero(const Ipp32fc& value){ return (value.re == 0 && value.im == 0); }
    template <> inline bool vector<Ipp64fc>::isZero(const Ipp64fc& value){ return (value.re == 0 && value.im == 0); }

    /* ===============================================
	============== set SPECIALIZATIONS ===========
	GOAL IS TO USE ippsSet_..(), but must cast for those that have missing functions
    Note that Set only has functions for:
    8u, 16s, 16sc, 32s, 32f, 32sc, 32fc, 64s, 64f, 64sc, 64fc
	============================================== */
    template <typename T>
    inline void vector<T>::set(int start, int length, const T& value)
    {
        throw std::runtime_error("There is no default template for IPP vectors. Please specify a valid IPP type.");
    }

    // Ipp8u specialization
    template <> inline void vector<Ipp8u>::set(int start, int length, const Ipp8u& value)
    {
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsSet_8u(
                *reinterpret_cast<const Ipp8u*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp8u*)&m_data[start],
                (int)(length < 0 ? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp8u>::set() - index out of range or nullptr found.");
    }

    // Ipp16u specialization
    template <> inline void vector<Ipp16u>::set(int start, int length, const Ipp16u& value)
    {
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsSet_16s(
                *reinterpret_cast<const Ipp16s*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp16s*)&m_data[start],
                (int)(length < 0 ? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp16u>::set() - index out of range or nullptr found.");
    }

    // Ipp32u specialization
    template <> inline void vector<Ipp32u>::set(int start, int length, const Ipp32u& value)
    {
        if (m_data != nullptr && start >= 0 && start + length <= numel) 
            ippsSet_32s(
                *reinterpret_cast<const Ipp32s*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp32s*)&m_data[start],
                (int)(length < 0 ? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp32u>::set() - index out of range or nullptr found.");
    }

    // Ipp64u specialization
    template <> inline void vector<Ipp64u>::set(int start, int length, const Ipp64u& value)
    {
        if (m_data!= nullptr && start >= 0 && start + length <= numel) 
            ippsSet_64s(
                *reinterpret_cast<const Ipp64s*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp64s*)&m_data[start],
                (int)(length < 0? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp64u>::set() - index out of range or nullptr found.");
    }

    // Ipp8s specialization
    template <> inline void vector<Ipp8s>::set(int start, int length, const Ipp8s& value)
    {
        if (m_data!= nullptr && start >= 0 && start + length <= numel) 
            ippsSet_8u(
                *reinterpret_cast<const Ipp8u*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp8u*)&m_data[start],
                (int)(length < 0? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp8s>::set() - index out of range or nullptr found.");
    }

    // Ipp16s specialization
    template <> inline void vector<Ipp16s>::set(int start, int length, const Ipp16s& value)
    {
        if (m_data!= nullptr && start >= 0 && start + length <= numel) 
            ippsSet_16s(
                *reinterpret_cast<const Ipp16s*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp16s*)&m_data[start],
                (int)(length < 0? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp16s>::set() - index out of range or nullptr found.");
    }

    // Ipp32s specialization
    template <> inline void vector<Ipp32s>::set(int start, int length, const Ipp32s& value)
    {
        if (m_data!= nullptr && start >= 0 && start + length <= numel) 
            ippsSet_32s(
                *reinterpret_cast<const Ipp32s*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp32s*)&m_data[start],
                (int)(length < 0? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp32s>::set() - index out of range or nullptr found.");
    }

    // Ipp64s specialization
    template <> inline void vector<Ipp64s>::set(int start, int length, const Ipp64s& value)
    {
        if (m_data!= nullptr && start >= 0 && start + length <= numel) 
            ippsSet_64s(
                *reinterpret_cast<const Ipp64s*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp64s*)&m_data[start],
                (int)(length < 0? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp64s>::set() - index out of range or nullptr found.");
    }

    // Ipp32f specialization
    template <> inline void vector<Ipp32f>::set(int start, int length, const Ipp32f& value)
    {
        if (m_data!= nullptr && start >= 0 && start + length <= numel) 
            ippsSet_32f(
                *reinterpret_cast<const Ipp32f*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp32f*)&m_data[start],
                (int)(length < 0? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp32f>::set() - index out of range or nullptr found.");
    }

    // Ipp64f specialization
    template <> inline void vector<Ipp64f>::set(int start, int length, const Ipp64f& value)
    {
        if (m_data!= nullptr && start >= 0 && start + length <= numel) 
            ippsSet_64f(
                *reinterpret_cast<const Ipp64f*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp64f*)&m_data[start],
                (int)(length < 0? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp64f>::set() - index out of range or nullptr found.");
    }

    // Ipp8sc specialization
    template <> inline void vector<Ipp8sc>::set(int start, int length, const Ipp8sc& value)
    {
        // 8sc doesn't have a set, we ASSUME it is packed well into 16bits, so invoke accordingly
        if (m_data!= nullptr && start >= 0 && start + length <= numel) 
            ippsSet_16s(
                *reinterpret_cast<const Ipp16s*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp16s*)&m_data[start],
                (int)(length < 0? numel - start : length)
            );
        // if this causes problems next time we'll fix it...
        else
            throw std::out_of_range("vector<Ipp8sc>::set() - index out of range or nullptr found.");
    }

    // Ipp16sc specialization
    template <> inline void vector<Ipp16sc>::set(int start, int length, const Ipp16sc& value)
    {
        // 16sc does have a set
        if (m_data!= nullptr && start >= 0 && start + length <= numel) 
            ippsSet_16sc(
                *reinterpret_cast<const Ipp16sc*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp16sc*)&m_data[start],
                (int)(length < 0? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp16sc>::set() - index out of range or nullptr found.");
    }

    // Ipp32sc specialization
    template <> inline void vector<Ipp32sc>::set(int start, int length, const Ipp32sc& value)
    {
        // 32sc does have a set
        if (m_data!= nullptr && start >= 0 && start + length <= numel) 
            ippsSet_32sc(
                *reinterpret_cast<const Ipp32sc*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp32sc*)&m_data[start],
                (int)(length < 0? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp32sc>::set() - index out of range or nullptr found.");
    }

    // Ipp64sc specialization
    template <> inline void vector<Ipp64sc>::set(int start, int length, const Ipp64sc& value)
    {
        // 64sc does have a set
        if (m_data!= nullptr && start >= 0 && start + length <= numel) 
            ippsSet_64sc(
                *reinterpret_cast<const Ipp64sc*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp64sc*)&m_data[start],
                (int)(length < 0? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp64sc>::set() - index out of range or nullptr found.");
    }

    // Ipp32fc specialization
    template <> inline void vector<Ipp32fc>::set(int start, int length, const Ipp32fc& value)
    {
        // 32fc does have a set
        if (m_data!= nullptr && start >= 0 && start + length <= numel) 
            ippsSet_32fc(
                *reinterpret_cast<const Ipp32fc*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp32fc*)&m_data[start],
                (int)(length < 0? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp32fc>::set() - index out of range or nullptr found.");
    }

    // Ipp64fc specialization
    template <> inline void vector<Ipp64fc>::set(int start, int length, const Ipp64fc& value)
    {
        // 64fc does have a set
        if (m_data!= nullptr && start >= 0 && start + length <= numel) 
            ippsSet_64fc(
                *reinterpret_cast<const Ipp64fc*>(&value), // note that we have reinterpreted the value as a similar sized word, in order to call Set
                (Ipp64fc*)&m_data[start],
                (int)(length < 0? numel - start : length)
            );
        else
            throw std::out_of_range("vector<Ipp64fc>::set() - index out of range or nullptr found.");
    }



}