//
// Created by tursh on 1/23/19.
//

#include <Loader/Models/AnimatedModel.h>
#include <memory>
#include <tinyxml2.h>
#include <Utils/Log.h>

namespace CGE
{
    namespace Loader
    {
        std::shared_ptr<AnimatedModel> loadDAEFile(const char *filePath)
        {
            tinyxml2::XMLDocument doc;
            tinyxml2::XMLError success = doc.LoadFile(filePath);

            if (success != tinyxml2::XML_SUCCESS)
            logError("Could not load file: " << filePath);


        }
    }
}