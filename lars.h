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
	}
}