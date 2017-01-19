#pragma once
#include <vector>

template<class Type, class Tag>
struct ScalarStorageBuilder
{
    ScalarStorageBuilder(std::size_t numConsts)
        : m_storage(numConsts)
    {}

    Type & getSingleValueRef()
    {
        return m_storage[m_current++];
    }

private:
    std::size_t m_current;
    std::vector<Type> m_storage;
};