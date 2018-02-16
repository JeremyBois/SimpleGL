#include "Utility/StreamUtility.hpp"

#include <fstream>
#include <sstream>

namespace simpleGL
{
    std::string StreamUtility::ReadFile(const std::string& _path)
    {
        std::string content;
        std::ifstream readStream(_path, std::ios::in);

        if(!readStream.is_open())
        {
            std::cerr << "Could not read file " << _path << ". File does not exist." << std::endl;
            return "";
        }

        // Get content of stream buffer loaded in sstr
        std::stringstream sstr;
        sstr << readStream.rdbuf();
        content =  sstr.str();

        readStream.close();
        return content;
    }
}
