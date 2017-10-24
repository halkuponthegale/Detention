#include <map>
#include <fstream>
#include <sstream>
class File {
public:
	static std::map<std::string, int> readFile(std::string fileName) {
		std::map<std::string, int> out;
		std::ifstream infile(fileName.c_str);
		std::string key;
		int value;
		std::string line;
		while (std::getline(infile, line)) {
			std::istringstream str(line);
			str >> key >> value;
			out.insert(std::pair<std::string, int>(key, value));
		}
		return out;
	}
	static void writeFile(std::string fileName, std::pair<std::string, int> data) {
		std::ofstream of;
		of.open(fileName.c_str, std::ios_base::app);
		of << data.first << " " << data.second;
	}
};
