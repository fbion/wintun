/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (C) 2018-2020 WireGuard LLC. All Rights Reserved.
 */

#include "pch.h"

_Success_(return != NULL)
WCHAR *
NormalizeStringAlloc(_In_ NORM_FORM NormForm, _In_z_ const WCHAR *Source)
{
    WCHAR *Result = NULL;
    HANDLE Heap = GetProcessHeap();
    int Len = NormalizeString(NormForm, Source, -1, NULL, 0);
    for (int i = 0; i < 10; ++i)
    {
        if (Result)
            HeapFree(Heap, 0, Result);
        Result = HeapAlloc(Heap, 0, sizeof(WCHAR) * Len);
        Len = NormalizeString(NormForm, Source, -1, Result, Len);
        if (Len > 0)
            return Result;
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
            break;
        Len = -Len;
    }
    if (Result)
        HeapFree(Heap, 0, Result);
    return NULL;
}

void
Bin2Hex(_In_bytecount_(Size) const void *Source, size_t Size, _Out_capcount_(Size * 2) WCHAR *Destination)
{
    for (size_t i = 0; i < Size; ++i)
    {
        static const WCHAR nibble[] = L"0123456789ABCDEF";
        *(Destination++) = nibble[(((unsigned char *)Source)[i] & 0xf0) >> 4];
        *(Destination++) = nibble[(((unsigned char *)Source)[i] & 0x0f)];
    }
}
