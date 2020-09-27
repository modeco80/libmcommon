#pragma once

#include <modeco/types.h>
#include <vector>
#include <iostream>

namespace mco {

	/**
	 * A helper object to write datatypes to a stream.
	 */
	struct BinaryWriter {
		constexpr BinaryWriter(std::ostream& stream)
			: stream(stream) {
		}

		/**
		 * Return reference to the raw stream.
		 */
		constexpr std::ostream& raw() {
			return stream;
		}

		/**
		 * Write a single type.
		 *
		 * \tparam T Type to read. Must be POD.
		 * \param[in] data The struct to read into.
		 */
		template <class T>
		inline bool WriteSingleType(const T& data) {
			if(!WriteRawBuffer((char*)&data, sizeof(T)))
				return false;

			return true;
		}

		/** 
		 * Write string.
		 *
		 * \param[in] str String to write.
		 */
		inline bool WriteString(const std::string& str) {
			if(!WriteRawBuffer((char*)str.data(), str.length() * sizeof(char)))
				return false;

			return true;
		}

		/**
		 * Write an array of T.
		 *
		 * \tparam T Type to read array of.
		 * \param[in] array Array to write.
		 */
		template <class T>
		inline bool WriteArray(const std::vector<T>& array) {
			auto length = array.size();

			for(auto i = 0; i < length; ++i) {
				if(!WriteSingleType(array[i]))
					return false;
			}

			return true;
		}

		/**
		 * Write a certain amount of data from a buffer to the stream.
		 *
		 * \param[in] buffer Buffer to read to. Must be valid.
		 * \param[in] size Size.
		 */
		bool WriteRawBuffer(char* buffer, std::size_t size);

	   private:
		/** 
		 * The stream this BinaryWriter object is managing.
		 */
		std::ostream& stream;
	};

} // namespace mco