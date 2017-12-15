#pragma once

#include <cstdint>

#include "CExoFile.hpp"
#include "CExoString.hpp"

namespace NWNXLib {

namespace API {

struct CERFKey
{
    char m_sName[16];
    uint32_t m_nID;
    uint16_t m_nType;
    uint8_t m_nUnused[2];

    // The below are auto generated stubs.
    CERFKey(const CERFKey&);
    CERFKey& operator=(const CERFKey&);

    CERFKey();
    ~CERFKey();
    int32_t Read();
    int32_t Reset();
    void SetName(CExoString&);
    int32_t Write(CExoFile&);
};

void CERFKey__CERFKeyCtor__0(CERFKey* thisPtr);
void CERFKey__CERFKeyDtor__0(CERFKey* thisPtr);
int32_t CERFKey__Read(CERFKey* thisPtr);
int32_t CERFKey__Reset(CERFKey* thisPtr);
void CERFKey__SetName(CERFKey* thisPtr, CExoString&);
int32_t CERFKey__Write(CERFKey* thisPtr, CExoFile&);

}

}