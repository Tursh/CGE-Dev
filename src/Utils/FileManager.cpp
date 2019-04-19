#include <fstream>                        //ifstream
#include <sstream>                        //std::stringstream
#include <cstring>

#include "Utils/Log.h"                        //logError

namespace CGE::Utils
{

    const char *readWholeFile(const char *filePath)
    {
        //read the file
        std::ifstream stream(filePath, std::ifstream::in);
        std::string line;
        std::ostringstream buffer;
        while (getline(stream, line))
            buffer << line << '\n';
        //Copy file to a char pointer
        char *file;
        strcpy(file, buffer.str().c_str());
        //Close the buffer
        stream.close();
        //Check if the file isn't empty
        if (file == nullptr)
        logError("Failed to open " << filePath);
        return file;
    }

}
