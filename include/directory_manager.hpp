#ifndef DIRECTORY_MANAGER_HPP
#define DIRECTORY_MANAGER_HPP

#include <filesystem>

namespace Directory_Manager
{
    inline std::filesystem::path assets_dir()
    {
#ifdef SFML_SYSTEM_IOS
        return "";
#else
        return "../../../../assets/";
#endif
    }
}

#endif //DIRECTORY_MANAGER_HPP