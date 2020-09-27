#pragma once
#include <modeco/types.h>

#if __has_include(<bit>)
	#include <bit>
#endif

namespace mco {
#if !__has_include(<bit>)

	/**
	 * Endian enumeration
	 */
	enum class endian : byte {
		little,
		big,
	};

	#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ || defined(_WIN32)
	constexpr endian current_endian = endian::little;
	#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	constexpr endian current_endian = endian::big;
	#endif

#else
	using std::endian;

	// code that uses mco::endian may freak out i'm not sure
	// but this is a wrapper to ensure that they (might) at least compile

	constexpr mco::endian current_endian = std::endian::native;
#endif

} // namespace mco