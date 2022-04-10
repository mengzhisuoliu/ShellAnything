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

#ifndef SA_IATTRIBUTEVALIDATOR_H
#define SA_IATTRIBUTEVALIDATOR_H

#include "shellanything/export.h"
#include "shellanything/config.h"
#include "StringList.h"
#include "PropertyStore.h"
#include "SelectionContext.h"
#include <vector>
#include <string>

namespace shellanything
{

  /// <summary>
  /// Abstract attribute validation class.
  /// </summary>
  class SHELLANYTHING_EXPORT IAttributeValidator
  {
  public:
    /// <summary>
    /// A list of IAttributeValidator class pointers.
    /// </summary>
    typedef std::vector<IAttributeValidator*> IAttributeValidationPtrList;

    IAttributeValidator();
    virtual ~IAttributeValidator();

  private:
    // Disable copy constructor and copy operator
    IAttributeValidator(const IAttributeValidator&);
    IAttributeValidator& operator=(const IAttributeValidator&);
  public:

    /// <summary>
    /// Check if this instance support the given list of attribute names.
    /// </summary>
    /// <param name="names">A list of attribute names</param>
    /// <returns>Returns true if this instance supports all the given attributes. Returns false otherwise.</returns>
    virtual bool IsAttributesSupported(const StringList& names) const = 0;

    /// <summary>
    /// Get the list of attributes supported by this instance
    /// </summary>
    /// <returns>Returns a list of custom attributes supported by this instance</returns>
    virtual const StringList& GetAttributeNames() const = 0;

    /// <summary>
    /// Set the PropertyStore that contains the names and values supported by this instance.
    /// </summary>
    /// <param name="store">A property store that contains the names and values for the validator</param>
    virtual void SetAttributes(const PropertyStore& store) = 0;

    /// <summary>
    /// Validate the given context against a set of constraints.
    /// The possible constraints includes a minimum/maximum number of files/directories selected,
    /// a list of properties that must be defined,
    /// a list of file extensions,
    /// ...
    /// Note: this function is used to enable or disable a menu.
    /// </summary>
    /// <param name="context">The context used for validating.</param>
    /// <returns>Returns true if the given context is valid against the set of constraints. Returns false otherwise.</returns>
    virtual bool Validate(const SelectionContext& context) const = 0;

  };


} //namespace shellanything

#endif //SA_IATTRIBUTEVALIDATOR_H
