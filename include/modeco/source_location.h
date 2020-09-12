#pragma once

#include <modeco/types.h>

// Check if we have source_location at all in our standard library.
// If we do, then there's no use implementing the legacy object.

#if __has_include(<source_location>)
	#define HAS_SOURCE_LOCATION 1
	#include <source_location>
#endif

#if __has_include(<experimental/source_location>)
	#define HAS_SOURCE_LOCATION 2
	#include <experimental/source_location>
#endif

namespace mco {

#ifndef HAS_SOURCE_LOCATION

	// Legacy implementation of source_location that should let code compile and function
	// just like if we had a C++20 implementation.
	struct source_location {
		// create a source_location object
		// repressenting call site location.
		static constexpr source_location current(const unsigned int line = __builtin_LINE(),
	#if defined(_MSC_VER)
												 const unsigned int column = __builtin_COLUMN(),
	#else
												 const unsigned int column = 0,
	#endif
												 const char* filename = __builtin_FILE(),
												 const char* function_name = __builtin_FUNCTION()) noexcept {

			source_location loc {};

			loc._filename = filename;
			loc._function_name = function_name;
			loc._line = line;
			loc._column = column;
			return loc;
		}

		// getters for values stored in the source_location.

		constexpr unsigned int line() const noexcept {
			return _line;
		}

		constexpr unsigned int column() const noexcept {
			return _column;
		}

		constexpr const char* file_name() const noexcept {
			return _filename;
		}

		constexpr const char* function_name() const noexcept {
			return _function_name;
		}

	   private:
		// exposition only variables here
		unsigned int _line;
		unsigned int _column;
		const char* _filename;
		const char* _function_name;
	};
#else
	// We apparently have some variant of the C++20 source_location header.

	#if HAS_SOURCE_LOCATION == 1
	// We have first class support,
	// so use that.
	using std::source_location;
	#elif HAS_SOURCE_LOCATION == 2
	// We have experimental support,
	// use that.
	using std::experimental::source_location;
	#endif

#endif

// prevent leaking macros
#undef HAS_SOURCE_LOCATION

} // namespace mco