#include <fstream>                        //ifstream
#include <sstream>                        //std::stringstream
#include <cstring>

#include "Utils/Log.h"                        //logError

namespace CGE::Utils
{

    const char *readWholeFile(const char *filePath)
    {
        //read the file
        FILE *f = fopen(filePath, "r");

        //Check if the file isn't empty
        if (f == nullptr)
        logError("Failed to open " << filePath);

        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        char *file = new char[fsize + 1];
        fread(file, 1, fsize, f);
        fclose(f);

        return file;
    }

}
