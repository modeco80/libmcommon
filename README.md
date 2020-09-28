## libmcommon

The common library that I use in a lot (well, the things I *actually* maintain) of my stuff. 

Designed to have stuff to get you going easily, without having to think about reinventing the wheel multiple times.

No dependencies, except for the STL. 

Feel free to use in your own projects! The master branch may have experimental additions that may break your code, however.

## Contents

- A relatively sane logger implementation.
	- Very simple sink interface, that's easy to slot in to existing code.
		- An already provided sink allows you to log to the console without much work.
		
- Compile time endian detection (This techinically overlaps with C++20 but allows compilation down to C++11).

- Standardized integer types from cstdint aliased into slightly easier to type names.
	- e.g: `std::uint8_t` becomes `(mco::)byte`.

- A backwards compatible implementation of C++20's `std::source_location`.
	- Allows compilation all the way back to C++14 (depending on how good your C++ compiler is)!
	
- Binary reading/writing API using standard IOStreams.

- A ready-to-use thread pool.
	