#ifndef INCLUDE_IMAGE_LINE
#define INCLUDE_IMAGE_LINE

#include <cstddef>
#include <ostream>
#include <memory>

class ImageLine
{
	struct CodedLine {
		CodedLine(char* data, size_t len)
			: m_Data(data), m_Len(len) {};
		char* m_Data;
		size_t m_Len;
		void allocate();
	};

	struct RawLine {
		RawLine() : RawLine(nullptr, 0) {}
		RawLine(char* data, size_t len) : m_Data(data), m_Len(len) {};
		RawLine(const RawLine& other)
			: m_Data(other.m_Data), m_Len(other.m_Len) {};

		RawLine& operator=(const RawLine& other) {
			m_Data = other.m_Data;
			m_Len  = other.m_Len;
		}
		bool isValid() { return (m_Len > 0) && (m_Data != nullptr); }

		char* m_Data;
		size_t m_Len;
	};

	struct Encoder {
		Encoder(unsigned char first, int shift) : m_Shift(shift) {
			m_Data = first << shift;
		}
		unsigned short m_Data;
		int m_Shift;
		unsigned char next(unsigned char n) {
			m_Data = (m_Data<<8) | n<<m_Shift;
			return m_Data>>8;
		}
	};

public:
	ImageLine(): m_Coded(0) {};
	virtual ~ImageLine(){ delete m_Coded; }

	virtual bool isEmpty() { return m_Coded != 0; }
	void setHPos(int h) { m_HPos = h; }
	void setCoded(char* data, size_t len) {
		m_Coded = new CodedLine(data, len);
	}

	void setRaw(char* data, size_t len) {
		m_Raw = RawLine(data, len);
	}

	void writeRaw(std::ostream& os, size_t len);

	void encode();

	int codedLen() { return (m_Coded?m_Coded->m_Len:0); }
	void writeCoded(std::ostream& os);

protected:
	RawLine m_Raw;
	CodedLine* m_Coded;
	int m_HPos;
};

typedef std::shared_ptr<ImageLine> ImageLineSptr;

#endif // INCLUDE_IMAGE_LINE
