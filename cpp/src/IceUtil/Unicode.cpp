// **********************************************************************
//
// Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/Unicode.h>
#include <IceUtil/ConvertUTF.h>

using namespace std;
using namespace IceUtil;
using namespace IceUtilInternal;

namespace
{
//
// Helper class, base never defined
// Usage: WstringHelper<sizeof(wchar_t)>::toUTF8 and fromUTF8.
//
template<size_t wcharSize> 
struct WstringHelper
{
    static ConversionResult toUTF8(
        const wchar_t*& sourceStart, const wchar_t* sourceEnd, 
        Byte*& targetStart, Byte* targetEnd, ConversionFlags flags);

    static ConversionResult fromUTF8(
        const Byte*& sourceStart, const Byte* sourceEnd, 
        wchar_t*& targetStart, wchar_t* targetEnd, ConversionFlags flags);
};

template<>
struct WstringHelper<2>
{
    static ConversionResult toUTF8(
        const wchar_t*& sourceStart, const wchar_t* sourceEnd, 
        Byte*& targetStart, Byte* targetEnd, ConversionFlags flags)
    {
        return ConvertUTF16toUTF8(
            reinterpret_cast<const UTF16**>(&sourceStart),
            reinterpret_cast<const UTF16*>(sourceEnd),
            &targetStart, targetEnd, flags);
    }
    
    static ConversionResult fromUTF8(
        const Byte*& sourceStart, const Byte* sourceEnd, 
        wchar_t*& targetStart, wchar_t* targetEnd, ConversionFlags flags)
    {
        return ConvertUTF8toUTF16(
            &sourceStart, sourceEnd,
            reinterpret_cast<UTF16**>(&targetStart),
            reinterpret_cast<UTF16*>(targetEnd), flags);
    }
};

template<>
struct WstringHelper<4>
{
    static ConversionResult toUTF8(
        const wchar_t*& sourceStart, const wchar_t* sourceEnd, 
        Byte*& targetStart, Byte* targetEnd, ConversionFlags flags)
    {
        return ConvertUTF32toUTF8(
            reinterpret_cast<const UTF32**>(&sourceStart),
            reinterpret_cast<const UTF32*>(sourceEnd),
            &targetStart, targetEnd, flags);
    }
    
    static ConversionResult fromUTF8(
        const Byte*& sourceStart, const Byte* sourceEnd, 
        wchar_t*& targetStart, wchar_t* targetEnd, ConversionFlags flags)
    {
        return ConvertUTF8toUTF32(
            &sourceStart, sourceEnd,
            reinterpret_cast<UTF32**>(&targetStart),
            reinterpret_cast<UTF32*>(targetEnd), flags);
    }
};
}

//
// convertXXX functions
//

ConversionResult 
IceUtilInternal::convertUTFWstringToUTF8(
    const wchar_t*& sourceStart, const wchar_t* sourceEnd, 
    Byte*& targetStart, Byte* targetEnd, ConversionFlags flags)
{
    return WstringHelper<sizeof(wchar_t)>::toUTF8(
        sourceStart, sourceEnd, targetStart, targetEnd, flags);
}

ConversionResult
IceUtilInternal::convertUTF8ToUTFWstring(
    const Byte*& sourceStart, const Byte* sourceEnd, 
    wchar_t*& targetStart, wchar_t* targetEnd, ConversionFlags flags)
{
    return WstringHelper<sizeof(wchar_t)>::fromUTF8(
        sourceStart, sourceEnd, targetStart, targetEnd, flags);
}

ConversionResult 
IceUtilInternal::convertUTF8ToUTFWstring(const Byte*& sourceStart, const Byte* sourceEnd, 
                                 std::wstring& target, ConversionFlags flags)
{
    //
    // Could be reimplemented without this temporary wchar_t buffer
    //
    size_t size = static_cast<size_t>(sourceEnd - sourceStart);
    wchar_t* outBuf = new wchar_t[size];
    wchar_t* targetStart = outBuf; 
    wchar_t* targetEnd = targetStart + size;

    ConversionResult result =  
        convertUTF8ToUTFWstring(sourceStart, sourceEnd, targetStart,
                                targetEnd, flags);

    if(result == conversionOK)
    {
        std::wstring s(outBuf, static_cast<size_t>(targetStart - outBuf));
        s.swap(target);
    }
    delete[] outBuf;
    return result;
}


