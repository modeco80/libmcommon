#include <modeco/BinaryReader.h>

namespace mco {

	bool BinaryReader::ReadRawBuffer(char* buffer, std::size_t size) {
		if(!stream || !buffer)
			return false;

		if(size == 0)
			return true;

		stream.read((char*)buffer, size);
		return true;
	}

} // namespace mco