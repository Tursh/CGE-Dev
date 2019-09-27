#pragma once

namespace CGE::Utils
{

    /**
     * Transfer a file content to an char array
     * @param filePath The file location
     * @return The file content
     */
    const char *readWholeFile(const char *filePath);

}