#pragma once

#define WIN32_LEAN_AND_MEAN
#include <wil/stl.h>
#include <wil/win32_helpers.h>
#include <windows.h>

namespace wil_extra {
template <typename string_type, std::size_t stackBufferLength = 256> HRESULT GetProcessImageFileNameW(HANDLE hProcess, string_type &result) WI_NOEXCEPT {
	return wil::AdaptFixedSizeToAllocatedResult<string_type, stackBufferLength>(result, [&](_Out_writes_(valueLength) PWSTR value, std::size_t valueLength, _Out_ std::size_t *valueLengthNeededWithNul) -> HRESULT {
		*valueLengthNeededWithNul = ::GetProcessImageFileNameW(hProcess, value, static_cast<DWORD>(valueLength));
		RETURN_LAST_ERROR_IF(*valueLengthNeededWithNul == 0);
		if (*valueLengthNeededWithNul < valueLength) {
			(*valueLengthNeededWithNul)++; // it fit, account for the null
		}
		return S_OK;
	});
}
} // namespace wil_extra
