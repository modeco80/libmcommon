## libmcommon

The common library that I use in a lot of my stuff. 

Feel free to use, however the library API may change sometimes.

Contains:

- A relatively sane logger implementation.
	- Sink interface too.
		- Already provided std::cout sink.
		
- Endian detection code.

- Standardized integer types.

- A fully backwards compatible implementation of C++20 `std::source_location`.
	- Allows compilation all the way back to C++14!