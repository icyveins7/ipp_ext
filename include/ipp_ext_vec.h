/*
Note that all specializations are inlined in order to ensure that
multiply defined symbols errors do not occur.
*/

#pragma once

#include "ipp.h"
#include <stdexcept>
#include <string>

namespace ippe
{
	const size_t INITIAL_CAP = 128;
	
	template <typename T>
	class vector
	{
		private:
			size_t numel = 0;
			size_t cap = 0;
			T *m_data = nullptr; // initialise as nullptr to prevent segfaults on first reserve
		
		public:
		    // Constructors

			// Default constructor
			vector()
			{
				// do nothing
			}

            // Construct with certain size, auto-zeroed (following std::vector 'default-insert')
			explicit vector(size_t count)
			{
				numel = count;
				reserve(numel); // even if count is 0, reserve() will do nothing
				zero();
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

			// These only have specializations, see below
			void reserve(size_t new_cap);
			void zero();

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
				if (pos < numel && pos >= 0){
					return m_data[pos];
				}
				else{
					throw std::out_of_range(std::string("ippe::vector::range_check: Size is ") + std::to_string(numel));
				}
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
			// copy the existing data first
			ippsCopy_8u(m_data, newm_data, (int)cap);
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
            // copy the existing data first
            ippsCopy_16s((Ipp16s*)m_data, (Ipp16s*)newm_data, (int)cap); // wrap as 16s
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
            // copy the existing data first
            ippsCopy_32s((Ipp32s*)m_data, (Ipp32s*)newm_data, (int)cap); // wrap as 32s
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
            // copy the existing data first
            ippsCopy_64s((Ipp64s*)m_data, (Ipp64s*)newm_data, (int)cap); // wrap as 64s
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
            // copy the existing data first
            ippsCopy_8u((Ipp8u*)m_data, (Ipp8u*)newm_data, (int)cap); // wrap as 8u
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
            // copy the existing data first
            ippsCopy_16s((Ipp16s*)m_data, (Ipp16s*)newm_data, (int)cap);
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
            // copy the existing data first
            ippsCopy_32s((Ipp32s*)m_data, (Ipp32s*)newm_data, (int)cap);
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
            // copy the existing data first
            ippsCopy_64s((Ipp64s*)m_data, (Ipp64s*)newm_data, (int)cap);
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
            // copy the existing data first
            ippsCopy_32f((Ipp32f*)m_data, (Ipp32f*)newm_data, (int)cap);
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
            // copy the existing data first
            ippsCopy_64f((Ipp64f*)m_data, (Ipp64f*)newm_data, (int)cap);
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
            // copy the existing data first
            ippsCopy_16s((Ipp16s*)m_data, (Ipp16s*)newm_data, (int)cap); // wrap as 16s
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
            // copy the existing data first
            ippsCopy_16sc((Ipp16sc*)m_data, (Ipp16sc*)newm_data, (int)cap);
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
            // copy the existing data first
            ippsCopy_32sc((Ipp32sc*)m_data, (Ipp32sc*)newm_data, (int)cap);
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
            // copy the existing data first
            ippsCopy_64sc((Ipp64sc*)m_data, (Ipp64sc*)newm_data, (int)cap);
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
            // copy the existing data first
            ippsCopy_32fc((Ipp32fc*)m_data, (Ipp32fc*)newm_data, (int)cap);
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
            // copy the existing data first, if it exists
            ippsCopy_64fc((Ipp64fc*)m_data, (Ipp64fc*)newm_data, (int)cap);
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
	inline void vector<T>::zero()
	{
		throw std::runtime_error("There is no default template for IPP vectors. Please specify a valid IPP type.");
	}

	// Note that not all of them have zeros for their type, but we use the same word length ones to replace it.
	// Ipp8u zero
	template <> inline void vector<Ipp8u>::zero(){
		if (m_data != nullptr) ippsZero_8u((Ipp8u*)m_data, (int)numel);
	}

	// Ipp16u zero
	template <> inline void vector<Ipp16u>::zero(){
        if (m_data!= nullptr) ippsZero_16s((Ipp16s*)m_data, (int)numel);
    }

    // Ipp32u zero
    template <> inline void vector<Ipp32u>::zero(){
        if (m_data!= nullptr) ippsZero_32s((Ipp32s*)m_data, (int)numel);
    }

    // Ipp64u zero
    template <> inline void vector<Ipp64u>::zero(){
        if (m_data!= nullptr) ippsZero_64s((Ipp64s*)m_data, (int)numel);
    }

    // Ipp8s zero
	template <> inline void vector<Ipp8s>::zero(){
        if (m_data!= nullptr) ippsZero_8u((Ipp8u*)m_data, (int)numel);
    }

    // Ipp16s zero
    template <> inline void vector<Ipp16s>::zero(){
        if (m_data!= nullptr) ippsZero_16s((Ipp16s*)m_data, (int)numel);
    }

    // Ipp32s zero
    template <> inline void vector<Ipp32s>::zero(){
        if (m_data!= nullptr) ippsZero_32s((Ipp32s*)m_data, (int)numel);
    }

    // Ipp64s zero
	template <> inline void vector<Ipp64s>::zero(){
		if (m_data!= nullptr) ippsZero_64s((Ipp64s*)m_data, (int)numel);
	}
	
    // Ipp32f zero
	template <> inline void vector<Ipp32f>::zero(){
        if (m_data!= nullptr) ippsZero_32f((Ipp32f*)m_data, (int)numel);
    }

    // Ipp64f zero
    template <> inline void vector<Ipp64f>::zero(){
        if (m_data!= nullptr) ippsZero_64f((Ipp64f*)m_data, (int)numel);
    }

	// Ipp8sc zero
	template <> inline void vector<Ipp8sc>::zero(){
        if (m_data!= nullptr) ippsZero_16s((Ipp16s*)m_data, (int)numel);
    }

    // Ipp16sc zero
    template <> inline void vector<Ipp16sc>::zero(){
        if (m_data!= nullptr) ippsZero_16sc((Ipp16sc*)m_data, (int)numel);
    }

    // Ipp32sc zero
    template <> inline void vector<Ipp32sc>::zero(){
        if (m_data!= nullptr) ippsZero_32sc((Ipp32sc*)m_data, (int)numel);
    }

    // Ipp64sc zero
    template <> inline void vector<Ipp64sc>::zero(){
        if (m_data!= nullptr) ippsZero_64sc((Ipp64sc*)m_data, (int)numel);
    }

    // Ipp32fc zero
	template <> inline void vector<Ipp32fc>::zero(){
        if (m_data!= nullptr) ippsZero_32fc((Ipp32fc*)m_data, (int)numel);
    }

    // Ipp64fc zero
    template <> inline void vector<Ipp64fc>::zero(){
        if (m_data!= nullptr) ippsZero_64fc((Ipp64fc*)m_data, (int)numel);
    }
}