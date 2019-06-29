/**********************************************************************************
 * MIT License
 * 
 * Copyright (c) 2018 Antoine Beauchamp
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *********************************************************************************/

#ifndef SA_NODEFACTORY_H
#define SA_NODEFACTORY_H

#include "shellanything/Menu.h"
#include "shellanything/Action.h"
#include "shellanything/Icon.h"
#include "shellanything/Validator.h"
#include "shellanything/DefaultSettings.h"
#include "tinyxml2.h"

namespace shellanything
{

  /// <summary>
  /// An utility class for parsing this procet's classes from xml
  /// </summary>
  class ObjectFactory
  {
  private:
    ObjectFactory();
    virtual ~ObjectFactory();

    // Disable copy constructor and copy operator
    ObjectFactory(const ObjectFactory&);
    ObjectFactory& operator=(const ObjectFactory&);

  public:
    static ObjectFactory & getInstance();

    /// <summary>
    /// Parses an Icon class from xml. Returns false if the parsing failed.
    /// </summary>
    /// <param name="element">The xml element that contains an Icon to parse.</param>
    /// <param name="error">The error description if the parsing failed.</param>
    /// <returns>Returns true if the object was properly parsed. Returns false otherwise.</returns>
    bool parseIcon(const tinyxml2::XMLElement * element, Icon & icon, std::string & error);

    /// <summary>
    /// Parses a Validator class from xml. Returns false if the parsing failed.
    /// </summary>
    /// <param name="element">The xml element that contains an Validator to parse.</param>
    /// <param name="error">The error description if the parsing failed.</param>
    /// <returns>Returns true if the object was properly parsed. Returns false otherwise.</returns>
    bool parseValidator(const tinyxml2::XMLElement * element, Validator & validator, std::string & error);

    /// <summary>
    /// Parses a Action class from xml. Returns NULL if the parsing failed.
    /// </summary>
    /// <param name="element">The xml element that contains an Action to parse.</param>
    /// <param name="error">The error description if the parsing failed.</param>
    /// <returns>Returns a valid Action pointer if the object was properly parsed. Returns NULL otherwise.</returns>
    Action * parseAction(const tinyxml2::XMLElement * element, std::string & error);

    /// <summary>
    /// Parses a Menu class from xml. Returns NULL if the parsing failed.
    /// </summary>
    /// <param name="element">The xml element that contains an Menu to parse.</param>
    /// <param name="error">The error description if the parsing failed.</param>
    /// <returns>Returns a valid Menu pointer if the object was properly parsed. Returns NULL otherwise.</returns>
    Menu * parseMenu(const tinyxml2::XMLElement * element, std::string & error);

    /// <summary>
    /// Parses a DefaultSettings class from xml. Returns NULL if the parsing failed.
    /// </summary>
    /// <param name="element">The xml element that contains an DefaultSettings to parse.</param>
    /// <param name="error">The error description if the parsing failed.</param>
    /// <returns>Returns a valid DefaultSettings pointer if the object was properly parsed. Returns NULL otherwise.</returns>
    DefaultSettings * parseDefaults(const tinyxml2::XMLElement * element, std::string & error);
  };

} //namespace shellanything

#endif //SA_NODEFACTORY_H
