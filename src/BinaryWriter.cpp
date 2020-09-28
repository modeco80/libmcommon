// non-templated and non-inlined functions for BinaryWriter

#include <modeco/defines.h>
#include <modeco/BinaryWriter.h>

namespace mco {

	bool BinaryWriter::WriteRawBuffer(char* buffer, std::size_t size) {
#if defined(DOPT_ASSERT)
		if(!buffer)
			return false;

		if(size == 0)
			return true;
#endif

		stream.write(buffer, size);
		return true;
	}

} // namespace mco