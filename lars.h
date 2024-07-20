#pragma once
#include "includes.h"
// Header code that belongs to Lars here (@Larsos099)
using namespace std;
using namespace CryptoPP;
namespace fs = std::filesystem;
namespace lars {
    namespace logic {
        std::string getUnixMs() {
            auto now = chrono::system_clock::now();
            auto duration = now.time_since_epoch();
            auto ms = chrono::duration_cast<chrono::milliseconds>(duration).count();
            std::string milliseconds = std::to_string(ms);
            return milliseconds;
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
}
