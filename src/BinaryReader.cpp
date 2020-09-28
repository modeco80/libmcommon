// non-templated and non-inlined functions for BinaryReader

#include <modeco/defines.h>
#include <modeco/BinaryReader.h>

namespace mco {

	bool BinaryReader::ReadRawBuffer(char* buffer, std::size_t size) {

#if defined(DOPT_ASSERT)
		if(!buffer)
			return false;

		if(size == 0)
			return true;
#endif

		// directly check the EOF bit instead of using !stream (which checks multiple bits)
		// this might help performance in some cases
		if(stream.eof())
			return false;

		stream.read((char*)buffer, size);
		return true;
	}

} // namespace mco