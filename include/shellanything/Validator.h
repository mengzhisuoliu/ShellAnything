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

#ifndef SA_VALIDATION_H
#define SA_VALIDATION_H

#include "shellanything/Context.h"
#include "shellanything/String.h"
#include <vector>

#define SA_DEFAULT_ATTRIBUTE_SEPARATOR_CHAR   ';'
#define SA_DEFAULT_ATTRIBUTE_SEPARATOR_STR    ";"
#define SA_PROPERTIES_ATTR_SEPARATOR_CHAR     SA_DEFAULT_ATTRIBUTE_SEPARATOR_CHAR
#define SA_PROPERTIES_ATTR_SEPARATOR_STR      SA_DEFAULT_ATTRIBUTE_SEPARATOR_STR 
#define SA_FILEEXTENSION_ATTR_SEPARATOR_CHAR  SA_DEFAULT_ATTRIBUTE_SEPARATOR_CHAR
#define SA_FILEEXTENSION_ATTR_SEPARATOR_STR   SA_DEFAULT_ATTRIBUTE_SEPARATOR_STR 
#define SA_INVERSE_ATTR_SEPARATOR_CHAR        SA_DEFAULT_ATTRIBUTE_SEPARATOR_CHAR
#define SA_INVERSE_ATTR_SEPARATOR_STR         SA_DEFAULT_ATTRIBUTE_SEPARATOR_STR 
#define SA_CLASS_ATTR_SEPARATOR_CHAR          SA_DEFAULT_ATTRIBUTE_SEPARATOR_CHAR
#define SA_CLASS_ATTR_SEPARATOR_STR           SA_DEFAULT_ATTRIBUTE_SEPARATOR_STR 
#define SA_EXISTS_ATTR_SEPARATOR_CHAR         SA_DEFAULT_ATTRIBUTE_SEPARATOR_CHAR
#define SA_EXISTS_ATTR_SEPARATOR_STR          SA_DEFAULT_ATTRIBUTE_SEPARATOR_STR 
#define SA_PATTERN_ATTR_SEPARATOR_CHAR        SA_DEFAULT_ATTRIBUTE_SEPARATOR_CHAR
#define SA_PATTERN_ATTR_SEPARATOR_STR         SA_DEFAULT_ATTRIBUTE_SEPARATOR_STR 
#define SA_ISTRUE_ATTR_SEPARATOR_CHAR         SA_DEFAULT_ATTRIBUTE_SEPARATOR_CHAR
#define SA_ISTRUE_ATTR_SEPARATOR_STR          SA_DEFAULT_ATTRIBUTE_SEPARATOR_STR 
#define SA_ISFALSE_ATTR_SEPARATOR_CHAR        SA_DEFAULT_ATTRIBUTE_SEPARATOR_CHAR
#define SA_ISFALSE_ATTR_SEPARATOR_STR         SA_DEFAULT_ATTRIBUTE_SEPARATOR_STR 

namespace shellanything
{

  class Validator
  {
  public:
    /// <summary>
    /// A list of Validator class pointers.
    /// </summary>
    typedef std::vector<Validator*> ValidatorPtrList;

    Validator();
    virtual ~Validator();

  private:
    // Disable copy constructor and copy operator
    Validator(const Validator&);
    Validator& operator=(const Validator&);
  public:

    /// <summary>
    /// Getter for the 'maxfiles' parameter.
    /// </summary>
    const int & GetMaxFiles() const;

    /// <summary>
    /// Setter for the 'maxfiles' parameter.
    /// </summary>
    void SetMaxFiles(const int & max_files);

    /// <summary>
    /// Getter for the 'maxdirectories' parameter.
    /// </summary>
    const int & GetMaxDirectories() const;

    /// <summary>
    /// Setter for the 'maxdirectories' parameter.
    /// </summary>
    void SetMaxDirectories(const int & max_directories);

    /// <summary>
    /// Getter for the 'properties' parameter.
    /// </summary>
    const String & GetProperties() const;

    /// <summary>
    /// Setter for the 'properties' parameter.
    /// </summary>
    void SetProperties(const String & properties);

    /// <summary>
    /// Getter for the 'fileextensions' parameter.
    /// </summary>
    const String & GetFileExtensions() const;

    /// <summary>
    /// Setter for the 'fileextensions' parameter.
    /// </summary>
    void SetFileExtensions(const String & file_extensions);

    /// <summary>
    /// Getter for the 'fileexists' parameter.
    /// </summary>
    const String & GetFileExists() const;

    /// <summary>
    /// Setter for the 'fileexists' parameter.
    /// </summary>
    void SetFileExists(const String & file_exists);

    /// <summary>
    /// Getter for the 'class' parameter.
    /// </summary>
    const String & GetClass() const;

    /// <summary>
    /// Setter for the 'class' parameter.
    /// </summary>
    void SetClass(const String & classes);

    /// <summary>
    /// Getter for the 'pattern' parameter.
    /// </summary>
    const String & GetPattern() const;

    /// <summary>
    /// Setter for the 'pattern' parameter.
    /// </summary>
    void SetPattern(const String & pattern);

    /// <summary>
    /// Getter for the 'exprtk' parameter.
    /// </summary>
    const String & GetExprtk() const;

    /// <summary>
    /// Setter for the 'exprtk' parameter.
    /// </summary>
    void SetExprtk(const String & exprtk);

    /// <summary>
    /// Getter for the 'istrue' parameter.
    /// </summary>
    const String & GetIsTrue() const;

    /// <summary>
    /// Setter for the 'istrue' parameter.
    /// </summary>
    void SetIsTrue(const String & istrue);

    /// <summary>
    /// Getter for the 'isfalse' parameter.
    /// </summary>
    const String & GetIsFalse() const;

    /// <summary>
    /// Setter for the 'isfalse' parameter.
    /// </summary>
    void SetIsFalse(const String & isfalse);

    /// <summary>
    /// Getter for the 'isempty' parameter.
    /// </summary>
    const String & GetIsEmpty() const;

    /// <summary>
    /// Setter for the 'isempty' parameter.
    /// </summary>
    void SetIsEmpty(const String & isempty);

    /// <summary>
    /// Getter for the 'inserve' parameter.
    /// </summary>
    const String & GetInserve() const;

    /// <summary>
    /// Setter for the 'inserve' parameter.
    /// </summary>
    void SetInserve(const String & inserve);

    /// <summary>
    /// Returns true if the given attribute name is in the list of inversed attributes.
    /// The accepted attribute names matches the list of attributes of <validity> or <visibility> elements in a Configuration File.
    /// See the 'User Manual' for details.
    /// </summary>
    /// <param name="name">The name of the attribute. The name is case sensitive.</param>
    /// <returns>Returns true if the given attribute name is in the list of inversed attributes. Returns false otherwise.</returns>
    bool IsInversed(const char * name) const;

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
    bool Validate(const Context & context) const;

    /// <summary>
    /// Validates if a given string can be evaluated as logical true.
    /// </summary>
    /// <remarks>
    /// The following values shall be evaluated to true:
    ///    true (case insensitive)
    ///    yes (case insensitive)
    ///    ok
    ///    on
    ///    1
    ///    ${system.true}
    /// </remarks>
    /// <param name="value">The value to test as true</param>
    /// <returns>Returns true if the given value can be evaluated as logical true. Returns false otherwise.</returns>
    static bool IsTrue(const String & value);

    /// <summary>
    /// Validates if a given string can be evaluated as logical true.
    /// </summary>
    /// <remarks>
    /// The following values shall be evaluated to false:
    ///    false (case insensitive)
    ///    no (case insensitive)
    ///    fail
    ///    off
    ///    0
    ///    ${system.false}
    /// </remarks>
    /// <param name="value">The value to test as true</param>
    /// <returns>Returns true if the given value can be evaluated as logical true. Returns false otherwise.</returns>
    static bool IsFalse(const String & value);

  private:
    bool ValidateProperties(const Context & context, const String & properties, bool inversed) const;
    bool ValidateFileExtensions(const Context & context, const String & file_extensions, bool inversed) const;
    bool ValidateExists(const Context & context, const String & file_exists, bool inversed) const;
    bool ValidateClass(const Context & context, const String & class_, bool inversed) const;
    bool ValidateSingleFileMultipleClasses(const String & path, const String & class_, bool inversed) const;
    bool ValidateSingleFileSingleClass(const String & path, const String & class_, bool inversed) const;
    bool ValidatePattern(const Context & context, const String & pattern, bool inversed) const;
    bool ValidateExprtk(const Context & context, const String & exprtk, bool inversed) const;
    bool ValidateIsTrue(const Context & context, const String & istrue, bool inversed) const;
    bool ValidateIsFalse(const Context & context, const String & isfalse, bool inversed) const;
    bool ValidateIsEmpty(const Context & context, const String & isempty, bool inversed) const;

  private:
    int mMaxFiles;
    int mMaxDirectories;
    String mProperties;
    String mFileExtensions;
    String mFileExists;
    String mClass;
    String mPattern;
    String mExprtk;
    String mIsTrue;
    String mIsFalse;
    String mIsEmpty;
    String mInverse;
  };

} //namespace shellanything

#endif //SA_VALIDATION_H
