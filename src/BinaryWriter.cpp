#include <modeco/BinaryWriter.h>

namespace mco {

	bool BinaryWriter::WriteRawBuffer(char* buffer, std::size_t size) {
		if(!stream || !buffer)
			return false;

		if(size == 0)
			return true;

		stream.write(buffer, size);
		return true;
	}

} // namespace mco