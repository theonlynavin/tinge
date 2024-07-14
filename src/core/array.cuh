#pragma once
#include "handle.cuh"
#include <vector>

/// Array (host and device)
template <class T>
class Array
{
private:
    T* m_data;
    size_t m_count;
public:
    /// @brief Initializes an empty array
    __host__ __device__ Array()
        : m_count(0)
    {
    }

    /// @brief Initializes the array with the given data
    /// @param data Elements of the array
    __host__ __device__ Array(const std::initializer_list<T>& data)
        : m_count(data.size())
    {
        m_data = (T*)malloc(data.size() * sizeof(T));
        memcpy(m_data, data.begin(), data.size() * sizeof(T));
    }

    /// @brief Initializes the array with the given data
    /// @param data Elements of the array
    __host__ __device__ Array(const std::vector<T>& data)
        : m_count(data.size())
    {
        m_data = (T*)malloc(data.size() * sizeof(T));
        memcpy(m_data, data.data(), data.size() * sizeof(T));
    }

    /// @brief Initializes the array with *a copy* the given data
    /// @param data Pointer to the elements of the array
    /// @param count Number of elements
    __host__ __device__ Array(T* data, size_t count)
        : m_count(count)
    {
        m_data = (T*)malloc(count * sizeof(T));
        memcpy(m_data, data, count * sizeof(T));
    }

    /// @brief Default destructor, frees reserved memory
    __host__ __device__ ~Array()
    {
        free(m_data);
    }

    /// @brief Clears the array elements
    __host__ __device__ void clear()
    {
        memset(m_data, 0, getSize());
    }

    /// @brief De-allocates all reserved memory 
    __host__ __device__ void clear()
    {
        free(m_data);
    }

    /// @brief Reserves memory to store elements
    /// @param totalCount Total number of elements in the array after reserving
    __host__ __device__ void reserve(size_t totalCount)
    {
        if (totalCount < m_count)
        {
            T* tmp = (T*)malloc(totalCount * sizeof(T));
            memcpy(tmp, m_data, totalCount * sizeof(T));
            free(m_data);
            m_data = tmp;
            m_count = totalCount;
        }
        else if (totalCount > m_count)
        {
            T* tmp = (T*)malloc(totalCount * sizeof(T));
            memcpy(tmp, m_data, m_count * sizeof(T));
            free(m_data);
            m_data = tmp;
            m_count = totalCount;
        }
    }

    __host__ __device__ __forceinline__ T& operator[](int idx) 
    { 
        return m_data[idx]; 
    }

    __host__ __device__ __forceinline__ const T& operator[](int idx) const 
    { 
        return m_data[idx]; 
    }
    
    /// @return Pointer to the data
    __host__ __device__ __forceinline__ constexpr T* ptr() const 
    { 
        return m_data; 
    }
    
    /// @return Number of bytes reserved
    __host__ __device__ __forceinline__ constexpr size_t size() const 
    { 
        return m_count * sizeof(T); 
    }

    /// @return Number of elements stored
    __host__ __device__ __forceinline__ constexpr size_t count() const 
    { 
        return m_count; 
    }   
};