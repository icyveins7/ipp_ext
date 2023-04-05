#include "../include/ipp_ext_vec.h"


/* 
==================================================
=================== CONSTRUCTOR ================== 
==================================================
 */

// Ipp8u ctor
template <>
inline ippe::vector<Ipp8u>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_8u_L(cap);
    check_malloc();
}

// Ipp16u ctor
template <>
inline ippe::vector<Ipp16u>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_16u_L(cap);
    check_malloc();
}

// Ipp32u ctor
template <>
inline ippe::vector<Ipp32u>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_32u_L(cap);
    check_malloc();
}

// Ipp8s ctor
template <>
inline ippe::vector<Ipp8s>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_8s_L(cap);
    check_malloc();
}

// Ipp16s ctor
template <>
inline ippe::vector<Ipp16s>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_16s_L(cap);
    check_malloc();
}

// Ipp32s ctor
template <>
inline ippe::vector<Ipp32s>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_32s_L(cap);
    check_malloc();
}

// Ipp64s ctor
template <>
inline ippe::vector<Ipp64s>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_64s_L(cap);
    check_malloc();
}

// Ipp32f ctor
template <>
inline ippe::vector<Ipp32f>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_32f_L(cap);
    check_malloc();
}

// Ipp64f ctor
template <>
inline ippe::vector<Ipp64f>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_64f_L(cap);
    check_malloc();
}

// Ipp8sc ctor
template <>
inline ippe::vector<Ipp8sc>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_8sc_L(cap);
    check_malloc();
}

// Ipp16sc ctor
template <>
inline ippe::vector<Ipp16sc>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_16sc_L(cap);
    check_malloc();
}

// Ipp32sc ctor
template <>
inline ippe::vector<Ipp32sc>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_32sc_L(cap);
    check_malloc();
}

// Ipp64sc ctor
template <>
inline ippe::vector<Ipp64sc>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_64sc_L(cap);
    check_malloc();
}

// Ipp32fc ctor
template <>
inline ippe::vector<Ipp32fc>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_32fc_L(cap);
    check_malloc();
}

// Ipp64fc ctor
template <>
inline ippe::vector<Ipp64fc>::vector(size_t count)
{
    vector_base(count);
    m_data = ippsMalloc_64fc_L(cap);
    check_malloc();
}


/* 
==================================================
==================== RESIZE ====================== 
==================================================
 */

// Ipp8u resize
template <>
inline void ippe::vector<Ipp8u>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp8u *newm_data = ippsMalloc_8u_L(cap);
        ippsCopy_8u(m_data, newm_data, copylen);
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}
// Ipp16u resize, copy function does not exist
template <>
inline void ippe::vector<Ipp16u>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp16u *newm_data = ippsMalloc_16u_L(cap);
        ippsCopy_16s((Ipp16s*)m_data, (Ipp16s*)newm_data, copylen); // reuse 16s for non-existent 16u
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}
// Ipp32u resize, copy function does not exist
template <>
inline void ippe::vector<Ipp32u>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp32u *newm_data = ippsMalloc_32u_L(cap);
        ippsCopy_32s((Ipp32s*)m_data, (Ipp32s*)newm_data, copylen); // reuse 32s
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}
// Ipp8s resize, copy function does not exist
template <>
inline void ippe::vector<Ipp8s>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp8s *newm_data = ippsMalloc_8s_L(cap);
        ippsCopy_8u((Ipp8u*)m_data, (Ipp8u*)newm_data, copylen); // reuse 8u
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}
// Ipp16s resize
template <>
inline void ippe::vector<Ipp16s>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp16s *newm_data = ippsMalloc_16s_L(cap);
        ippsCopy_16s(m_data, newm_data, copylen);
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}
// Ipp32s resize
template <>
inline void ippe::vector<Ipp32s>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp32s *newm_data = ippsMalloc_32s_L(cap);
        ippsCopy_32s(m_data, newm_data, copylen);
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}
// Ipp64s resize
template <>
inline void ippe::vector<Ipp64s>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp64s *newm_data = ippsMalloc_64s_L(cap);
        ippsCopy_64s(m_data, newm_data, copylen);
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}
// Ipp32f resize
template <>
inline void ippe::vector<Ipp32f>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp32f *newm_data = ippsMalloc_32f_L(cap);
        ippsCopy_32f(m_data, newm_data, copylen);
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}
// Ipp64f resize
template <>
inline void ippe::vector<Ipp64f>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp64f *newm_data = ippsMalloc_64f_L(cap);
        ippsCopy_64f(m_data, newm_data, copylen);
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}
// Ipp8sc resize, copy function does not exist
template <>
inline void ippe::vector<Ipp8sc>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp8sc *newm_data = ippsMalloc_8sc_L(cap);
        ippsCopy_16s((Ipp16s*)m_data, (Ipp16s*)newm_data, copylen); // reuse 16s
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}
// Ipp16sc resize
template <>
inline void ippe::vector<Ipp16sc>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp16sc *newm_data = ippsMalloc_16sc_L(cap);
        ippsCopy_16sc(m_data, newm_data, copylen);
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}
// Ipp32sc resize
template <>
inline void ippe::vector<Ipp32sc>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp32sc *newm_data = ippsMalloc_32sc_L(cap);
        ippsCopy_32sc(m_data, newm_data, copylen);
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}
// Ipp64sc resize
template <>
inline void ippe::vector<Ipp64sc>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp64sc *newm_data = ippsMalloc_64sc_L(cap);
        ippsCopy_64sc(m_data, newm_data, copylen);
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}
// Ipp32fc resize
template <>
inline void ippe::vector<Ipp32fc>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp32fc *newm_data = ippsMalloc_32fc_L(cap);
        ippsCopy_32fc(m_data, newm_data, copylen);
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}
// Ipp64fc resize
template <>
inline void ippe::vector<Ipp64fc>::resize(size_t count)
{
    base_resize(count);
            
    if (reMalloc){
        Ipp64fc *newm_data = ippsMalloc_64fc_L(cap);
        ippsCopy_64fc(m_data, newm_data, copylen);
        ippsFree(m_data);
        m_data = newm_data;
        check_malloc();
        reMalloc = false;
    }
}