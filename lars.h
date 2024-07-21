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
		SecByteBlock extractKey(const std::string& path) {
			std::ifstream inFile(path, std::ios::binary);
			std::vector<byte> buffer(16);
			inFile.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
			return SecByteBlock(buffer.data(), buffer.size());
		}
		SecByteBlock extractIV(const std::string& path) {
			std::ifstream inFile(path, std::ios::binary);
			std::vector<byte> buffer(16);
			inFile.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
			return SecByteBlock(buffer.data() + 16, 16);
		}
	}
	namespace aes {
		void encrypt(std::string& path, CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock IV) {
			CBC_Mode<AES>::Encryption e;
			e.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, IV);
			FileSource fs(path.c_str(), true,
				new StreamTransformationFilter(e,
					new FileSink(path.c_str()),
					BlockPaddingSchemeDef::PKCS_PADDING)
			);

			std::stringstream s;
			s << key;
			s << IV;
			std::string keypair = s.str();
			std::stringstream ssasPath;
			ssasPath << path;
			ssasPath << ":keyandiv";
			std::string asPath = ssasPath.str();
			std::ofstream as(asPath);
			if (as.is_open()) {
				as.write(reinterpret_cast<const char*>(key.data()), key.size());
				as.write(reinterpret_cast<const char*>(IV.data()), IV.size());
			}
			as.close();
			return;
		}



		void decrypt(std::string& path, CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock IV, std::string& outpath) {
			// W.I.P 
			// (tried to do it, returned empty file without any error?)
		}
	}
}