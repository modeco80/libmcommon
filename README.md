## libmcommon

The common library that I use in a lot (well, the things I *actually* maintain) of my stuff. No dependencies, except for the STL. 

Feel free to use in your own projects! The master branch may have experimental additions that may break your code, however.

## Contents

- A relatively sane logger implementation.
	- Very simple sink interface, that's easy to slot in to existing code.
		- An already provided sink allows you to log to the console without much work.
		
- Endian detection code (This techinically overlaps with C++20 but allows compilation down to C++11).

- Standardized integer types from cstdint aliased into slightly easier to type names.
	- e.g: `std::uint8_t` becomes `(mco::)byte`

- A fully backwards compatible implementation of C++20's `std::source_location`.
	- Allows compilation of some code all the way back to C++14 (depending on how good your C++ compiler is)!
	
- Binary reading/writing API using standard IOStreams.

- A thread pool ready to use, with no dependencies besides the STL itself.
	