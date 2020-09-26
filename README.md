## libmcommon

The common library that I use in a lot (well, the things I *actually* maintain) of my stuff. 

Feel free to use in your own projects! The library API may change sometimes on the master branch though.

## Contents

- A relatively sane logger implementation.
	- Very simple sink interface, that's easy to slot in to existing code.
		- Already provided iostream sink.
		
- Endian detection code (This techinically overlaps with C++20 but allows compilation down to C++11).

- Standardized integer types from cstdint aliased into slightly easier to type names.
	- e.g: `std::uint8_t` becomes `(mco::)byte`

- A fully backwards compatible implementation of C++20's `std::source_location`.
	- Allows compilation of some code all the way back to C++14 (depending on how good your C++ compiler is)!

- A thread pool ready to use, with no dependencies besides the STL itself.
	