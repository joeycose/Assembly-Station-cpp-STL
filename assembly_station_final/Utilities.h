


#ifndef SDDS_UTILITIES__
#define SDDS_UTILITIES__
#include <string>

namespace sdds {

	//Class alled Utilities containing spacing helpers
	class Utilities {
		size_t m_widthField;
		static char m_delimiter;

	//Public functions contianing fucntions related to spacing
	//sizing
	public:
		Utilities();
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};

}
#endif
