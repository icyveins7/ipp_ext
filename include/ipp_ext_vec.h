#pragma once

#include "ipp.h"
#include <stdexcept>
#include <string>

#define NO_DEFAULT -1

namespace ippe
{
	const size_t INITIAL_CAP = 128;
	
	template <typename T>
	class vector
	{
		private:
			size_t numel;
			size_t cap;
			size_t copylen;
			bool reMalloc;
			T *m_data;
		
			void vector_base(size_t count)
			{
				// std::cout << "Base ctor for all specialized types." << std::endl;
				numel = count;
				cap = INITIAL_CAP;
				
				if (numel > cap){
					cap = numel;
				}
				reMalloc = false;
			}

			void check_malloc()
			{
				if (m_data == nullptr) { throw std::runtime_error("Malloc Failed"); }
			}
		public:
			vector<T>(size_t count = 0);
			
			// common methods
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
				if (pos < numel){
					return m_data[pos];
				}
				else{
					throw std::out_of_range(std::string("ippe::vector::range_check: Size is ") + std::to_string(numel));
				}
			}

			T& operator[](size_t pos)
			{
				if (pos < numel){
					return m_data[pos];
				}
				else{
					throw std::out_of_range(std::string("ippe::vector::range_check: Size is ") + std::to_string(numel));
				}
			}
			
			void push_back(T value) // for now lets not deal with lvalue/rvalue refs
			{
				// check size
				if (numel == cap){
					resize(cap * 2);
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
			
			void base_resize(size_t count)
			{
				// std::cout << "Base class resize." << std::endl;
				if (count > cap)
				{
					copylen = numel; // old, shorter length
					numel = count; // the new length
					cap = count; // capacity = new length
					reMalloc = true;
				}
				else{
					numel = count;
				}
			}
	
			void resize(size_t count);
			
			~vector()
			{
				// std::cout<<"Destructing base ipp vector."<<std::endl;
				
				ippsFree(m_data);
			}
	};
	
	// ========== specialized ctor
	
	// default ctor
	template <typename T>
	inline vector<T>::vector(size_t count)
	{
		// std::cout<<"There is no default template for IPP vectors. Please specify a valid IPP type." << std::endl;
		throw NO_DEFAULT;
	}
	
	// See ipp_ext_vec.cpp for the implementations
	template <>	inline vector<Ipp8u>::vector(size_t count);
	template <>	inline vector<Ipp16u>::vector(size_t count);
	template <>	inline vector<Ipp32u>::vector(size_t count);
	template <>	inline vector<Ipp8s>::vector(size_t count);
	template <>	inline vector<Ipp16s>::vector(size_t count);
	template <>	inline vector<Ipp32s>::vector(size_t count);
	template <>	inline vector<Ipp64s>::vector(size_t count);
	template <>	inline vector<Ipp32f>::vector(size_t count);
	template <>	inline vector<Ipp64f>::vector(size_t count);
	template <>	inline vector<Ipp8sc>::vector(size_t count);
	template <>	inline vector<Ipp16sc>::vector(size_t count);
	template <>	inline vector<Ipp32sc>::vector(size_t count);
	template <>	inline vector<Ipp64sc>::vector(size_t count);
	template <>	inline vector<Ipp32fc>::vector(size_t count);
	template <>	inline vector<Ipp64fc>::vector(size_t count);
	
	// ========== specialized resize, but some of them don't exist
	
	// default resize
	template <typename T>
	inline void vector<T>::resize(size_t count)
	{
		// std::cout << "No default resize. This should never happen, should have been caught in ctor." << std::endl;
		throw NO_DEFAULT;
	}
	
	// See ipp_ext_vec.cpp for the implementations
	template <>	inline void vector<Ipp8u>::resize(size_t count);
	template <>	inline void vector<Ipp16u>::resize(size_t count);
	template <>	inline void vector<Ipp32u>::resize(size_t count);
	template <>	inline void vector<Ipp8s>::resize(size_t count);
	template <>	inline void vector<Ipp16s>::resize(size_t count);
	template <>	inline void vector<Ipp32s>::resize(size_t count);
	template <>	inline void vector<Ipp64s>::resize(size_t count);
	template <>	inline void vector<Ipp32f>::resize(size_t count);
	template <>	inline void vector<Ipp64f>::resize(size_t count);
	template <>	inline void vector<Ipp8sc>::resize(size_t count);
	template <>	inline void vector<Ipp16sc>::resize(size_t count);
	template <>	inline void vector<Ipp32sc>::resize(size_t count);
	template <>	inline void vector<Ipp64sc>::resize(size_t count);
	template <>	inline void vector<Ipp32fc>::resize(size_t count);
	template <> inline void vector<Ipp64fc>::resize(size_t count);
}