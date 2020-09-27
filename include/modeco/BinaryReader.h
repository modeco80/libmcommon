#pragma once

#include <modeco/types.h>
#include <iostream>
#include <optional>
#include <vector>

namespace mco {

	/**
	 * A helper object to read datatypes from a stream.
	 * Attempts to be optimized by not copying data as much.
	 */
	struct BinaryReader {
		constexpr BinaryReader(std::istream& stream)
			: stream(stream) {
		}

		/**
		 * Return reference to the raw stream.
		 */
		constexpr std::istream& raw() {
			return stream;
		}

		/**
		 * Read any POD type.
		 * You can use this to, for instance,
		 * read a header in one shot instead of reading in 
		 * *each* and every member.
		 * Validation and checking is still up to you, though.
		 *
		 * \tparam T Type to read. Must be POD.
		 * \param[in] data The struct to read into.
		 */
		template <class T>
		inline bool ReadSingleType(T& data) {
			if(!ReadRawBuffer((char*)&data, sizeof(T)))
				return false;

			return true;
		}

		/**
		 * Read any POD type (returning it instead of reading into a reference).
		 *
		 * \tparam T Type to read. Must be POD.
		 */
		template <class T>
		inline std::optional<T> ReadSingleType() {
			T temp {};

			if(!ReadRawBuffer((char*)&temp, sizeof(T)))
				return {};

			return temp;
		}

		/**
		 * Read a string, stopping when a NUL is reached or the stream goes bac..
		 */
		inline std::string ReadString() {
			std::string str;

			while(true) {
				char c;

				if(!ReadRawBuffer(&c, sizeof(char)))
					break;

				if(c == '\0')
					break;

				str += c;
			}

			return str;
		}

		/** 
		 * Read a string (either wide or ASCII), stopping at the specified length.
		 * Really only useful if you're absoultely sure that the string has a fixed size.
		 * Otherwise just use the overload that takes no arguments.
		 *
		 * \param[in] length Length of the string.
		 */
		inline std::string ReadString(std::size_t length) {
			std::string str;
			str.resize(length);

			if(!ReadRawBuffer(str.data(), length * sizeof(char)))
				return "";

			return str;
		}

		/**
		 * Read an array of T.
		 *
		 * \tparam T Type to read array of.
		 * \param[in] length Length of the array.
		 */
		template <class T>
		inline std::vector<T> ReadArray(std::size_t length) {
			std::vector<T> array;

			for(int i = 0; i < length; ++i) {
				T item;

				if(!ReadSingleType<T>(item))
					break;

				array.push_back(item);
			}

			return array;
		}

		/**
		 * Read a certain amount of data into buffer.
		 *
		 * \param[in] buffer Buffer to write to. Must be valid.
		 * \param[in] size Size.
		 */
		bool ReadRawBuffer(char* buffer, std::size_t size);

	   private:
		/** 
		 * The stream this BinaryReader object is managing.
		 */
		std::istream& stream;
	};

} // namespace mco