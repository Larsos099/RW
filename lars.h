// Code that only I use and that only I write (lars)
#pragma once
#include "includes.h"
using namespace CryptoPP;
namespace fs = std::filesystem;
namespace lars {
	namespace logic {
		std::string getUnixMS() {
			auto now = std::chrono::system_clock::now();
			auto duration = now.time_since_epoch();
			auto rawUnixMS = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
			return std::to_string(rawUnixMS);
		}
		SecByteBlock strToSbb(std::string str) {
			CryptoPP::SecByteBlock secBlock(reinterpret_cast<const byte*>(str.data()), str.size());
			return secBlock;
		}
		void collect_files(const fs::path& path, std::vector<fs::path>& file_paths) {
			try {
				if (fs::exists(path) && fs::is_directory(path)) {
					for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
						if (fs::exists(entry) && fs::is_regular_file(entry)) {
							file_paths.push_back(entry.path());
						}
					}
				}
				else {
					std::cerr << "Path does not exist or is not a directory." << std::endl;
				}
			}
			catch (const std::filesystem::filesystem_error& e) {
				std::cerr << "Filesystem error: " << e.what() << std::endl;
			}
		}

	}
	namespace aes { // Waiting for socket functionality, so I can send things
		void encrypt() {
			std::cout << "W.I.P function";
			return;
		}
		void decrypt() {
			std::cout << "W.I.P function";
			return;
		}
	}
}