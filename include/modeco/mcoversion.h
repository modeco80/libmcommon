#pragma once

namespace mco {

	constexpr static int version_major = 1;
	constexpr static int version_minor = 0;

	// special part of version, meanings:
	//
	//  0 (default) - normal mcommon
	//  1 - reserved for xb2at branch
	//  2-... unused, may be used if a new stable version ever is needed
	constexpr static int version_special = 0;

} // namespace mco
