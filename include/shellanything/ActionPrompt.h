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

#ifndef SA_ACTION_PROMPT_H
#define SA_ACTION_PROMPT_H

#include "shellanything/Action.h"

namespace shellanything
{

  /// <summary>
  /// Action class that prompts the user for a value.
  /// </summary>
  class ActionPrompt : public Action
  {
  public:
    ActionPrompt();
    virtual ~ActionPrompt();

    /// <summary>
    /// Returns true if the ActionPrompt is configued as a Yes/No question.
    /// </summary>
    /// <returns>Returns true if the ActionPrompt is configued as a Yes/No question. Returns false otherwise.</returns>
    virtual bool isYesNoQuestion() const;

    /// <summary>
    /// Returns true if the ActionPrompt is configued as a OK only question.
    /// </summary>
    /// <returns>Returns true if the ActionPrompt is configued as a OK question. Returns false otherwise.</returns>
    virtual bool isOkQuestion() const;

    /// <summary>
    /// Prompts the user for a value.
    /// </summary>
    /// <param name="iContext">The current context of execution.</param>
    /// <returns>Returns true if the execution is successful. Returns false otherwise.</returns>
    virtual bool execute(const Context & iContext) const;

    /// <summary>
    /// Getter for the 'name' parameter.
    /// </summary>
    const std::string & getName() const;

    /// <summary>
    /// Setter for the 'name' parameter.
    /// </summary>
    void setName(const std::string & iName);

    /// <summary>
    /// Getter for the 'type' parameter.
    /// </summary>
    const std::string & getType() const;

    /// <summary>
    /// Setter for the 'type' parameter.
    /// </summary>
    void setType(const std::string & iType);

    /// <summary>
    /// Getter for the 'title' parameter.
    /// </summary>
    const std::string & getTitle() const;

    /// <summary>
    /// Setter for the 'title' parameter.
    /// </summary>
    void setTitle(const std::string & iTitle);

    /// <summary>
    /// Getter for the 'default' parameter.
    /// </summary>
    const std::string & getDefault() const;

    /// <summary>
    /// Setter for the 'default' parameter.
    /// </summary>
    void setDefault(const std::string & iDefault);

    /// <summary>
    /// Getter for the 'valueyes' parameter.
    /// </summary>
    const std::string & getValueYes() const;

    /// <summary>
    /// Setter for the 'valueyes' parameter.
    /// </summary>
    void setValueYes(const std::string & iValueYes);

    /// <summary>
    /// Getter for the 'valueno' parameter.
    /// </summary>
    const std::string & getValueNo() const;

    /// <summary>
    /// Setter for the 'valueno' parameter.
    /// </summary>
    void setValueNo(const std::string & iValueNo);

  private:
    std::string mType;
    std::string mName;
    std::string mTitle;
    std::string mDefault;
    std::string mValueYes;
    std::string mValueNo;
  };

} //namespace shellanything

#endif //SA_ACTION_PROMPT_H
