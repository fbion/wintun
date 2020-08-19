/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (C) 2018-2020 WireGuard LLC. All Rights Reserved.
 */

#pragma once

#include <Windows.h>

_Success_(return != NULL)
WCHAR *
NormalizeStringAlloc(_In_ NORM_FORM NormForm, _In_z_ const WCHAR *Source);

void
Bin2Hex(_In_bytecount_(Size) const void *Source, size_t Size, _Out_capcount_(Size * 2) WCHAR *Destination);
