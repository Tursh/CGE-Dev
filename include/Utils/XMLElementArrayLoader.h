//
// Created by tursh on 1/24/19.
//

#pragma once

#include <tinyxml2.h>
#include <vector>

namespace CGE::Utils
{

	/**
	 * Get array in XML element
	 * @tparam Type Array type
	 * @param element XML element
	 * @return The array in the XML element
	 */
    template<class Type>
    std::vector<Type> getArray(tinyxml2::XMLElement *element)
    {
        //Get the offsets element
        char *pEnd;
        auto size = std::strtol(element->FindAttribute("count")->Value(), &pEnd, 10);

        std::vector<Type> array;
        array.reserve(size);

        // Build an istream that holds the input string
        std::istringstream iss(element->GetText());

        // Iterate over the istream, using >> to grab unsigned int
        // and push_back to store them in the vector
        std::copy(std::istream_iterator<Type>(iss),
                  std::istream_iterator<Type>(),
                  std::back_inserter(array));

        return array;
    }

}