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

#include "TestConfiguration.h"
#include "shellanything/ConfigManager.h"
#include "shellanything/Configuration.h"
#include "shellanything/Menu.h"
#include "shellanything/ActionExecute.h"

#include "rapidassist/filesystem.h"
#include "rapidassist/gtesthelp.h"
#include "rapidassist/time_.h"

#include "PropertyManager.h"
#include "Platform.h"

namespace shellanything { namespace test
{
  static const Configuration * INVALID_CONFIGURATION = NULL;

  //--------------------------------------------------------------------------------------------------
  void TestConfiguration::SetUp()
  {
  }
  //--------------------------------------------------------------------------------------------------
  void TestConfiguration::TearDown()
  {
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestConfiguration, testDefault)
  {
    //fake the implementation
    Configuration * config = new Configuration();
    config->setFilePath("C:\\Users\\MartyMcfly\\Documents\\ShellAnything\\default.xml");
    
    // <menu name="Command line from here...">
    //   <icon path="C:\Windows\System32\shell32.dll" index="3" />
    //   <validity folder="true" />
    //   <actions>
    //     <exec path="C:\windows\system32\cmd.exe" basedir="${selection.path}" />
    //   </actions>
    // </menu>
    Menu * menu = new Menu();
    menu->setName("Command line from here...");
    Validator validity;
    validity.setMaxFiles(0); //no files accepted
    validity.setMaxDirectories(1); //a single directory is accepted
    Validator visibility; //no requirement, always visible
    ActionExecute * action = new ActionExecute();
    action->setPath("C:\\windows\\system32\\cmd.exe");
    action->setBaseDir("C:\\Users\\MartyMcfly\\AppData\\Local\\Temp");

    //link everything
    config->addChild(menu);
    menu->setValidity(validity);
    menu->setVisibility(visibility);
    menu->addAction(action);
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestConfiguration, testIsValidConfigFile)
  {
    static const char * files[] = {
      //default configuration files
      "configurations\\default.xml",
      "configurations\\Microsoft Office 2003.xml",
      "configurations\\Microsoft Office 2007.xml",
      "configurations\\Microsoft Office 2010.xml",
      "configurations\\Microsoft Office 2013.xml",
      "configurations\\Microsoft Office 2016.xml",
      "configurations\\shellanything.xml",
      "configurations\\WinDirStat.xml",

      //test configuration files
      "test_files\\samples.xml",
      "test_files\\test_issue011.xml",
      "test_files\\TestConfigManager.testAssignCommandId.1.xml",
      "test_files\\TestConfigManager.testAssignCommandId.2.xml",
      "test_files\\TestConfigManager.testAssignCommandIdsInvalid.xml",
      "test_files\\TestConfigManager.testClear.xml",
      "test_files\\TestConfigManager.testDetectNewFile.xml",
      "test_files\\TestConfigManager.testFileModifications.xml",
      "test_files\\TestConfigManager.testParentWithoutChildren.xml",
      "test_files\\TestConfiguration.testLoadProperties.xml",
      "test_files\\TestObjectFactory.testParseActionPrompt.xml",
      "test_files\\TestObjectFactory.testParseDefaults.xml",
      "test_files\\TestObjectFactory.testParseIcon.xml",
      "test_files\\TestObjectFactory.testParseValidator.xml",
      "test_files\\tests.xml",
    };
    const size_t num_files = sizeof(files)/sizeof(files[0]);

    //for each test files
    for(size_t i=0; i<num_files; i++)
    {
      const std::string path = files[i];
      ASSERT_TRUE( ra::filesystem::fileExists(path.c_str()) ) << "File '" << path.c_str() << "' is not found.";
      ASSERT_TRUE( shellanything::Configuration::isValidConfigFile(path) ) << "The file '" << path.c_str() << "' is not a valid configuration file.";
    }
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestConfiguration, testLoadFile)
  {
    const std::string path = "configurations/default.xml";
    std::string error_message = ra::gtesthelp::getTestQualifiedName(); //init error message to an unexpected string
    Configuration * config = Configuration::loadFile(path, error_message);

    ASSERT_TRUE( error_message.empty() ) << "error_message=" << error_message;
    ASSERT_NE( INVALID_CONFIGURATION, config );

    //cleanup
    delete config;
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestConfiguration, testLoadProperties)
  {
    ConfigManager & cmgr = ConfigManager::getInstance();
 
    static const std::string path_separator = ra::filesystem::getPathSeparatorStr();
 
    //copy test template file to a temporary subdirectory to allow editing the file during the test
    std::string test_name = ra::gtesthelp::getTestQualifiedName();
    std::string template_source_path = std::string("test_files") + path_separator + test_name + ".xml";
    std::string template_target_path = std::string("test_files") + path_separator + test_name + path_separator + "tmp.xml";
 
    //make sure the target directory exists
    std::string template_target_dir = ra::filesystem::getParentPath(template_target_path);
    ASSERT_TRUE( ra::filesystem::createFolder(template_target_dir.c_str()) ) << "Failed creating directory '" << template_target_dir << "'.";
 
    //copy the file
    ASSERT_TRUE( copyFile(template_source_path, template_target_path) ) << "Failed copying file '" << template_source_path << "' to file '" << template_target_path << "'.";
    
    //wait to make sure that the next files not dated the same date as this copy
    ra::time::millisleep(1500);

    //cleanup properties
    PropertyManager & pmgr = PropertyManager::getInstance();
    pmgr.clear();

    //setup ConfigManager to read files from template_target_dir
    cmgr.clearSearchPath();
    cmgr.addSearchPath(template_target_dir);
    cmgr.refresh();
 
    //ASSERT the file is loaded
    Configuration::ConfigurationPtrList configs = cmgr.getConfigurations();
    ASSERT_EQ( 1, configs.size() );
 
    //ASSERT that properties was applied
    static const std::string EMPTY_STRING;
    std::string services_command_start = pmgr.getProperty("services.command.start");
    std::string services_command_stop  = pmgr.getProperty("services.command.stop");
    ASSERT_NE( EMPTY_STRING, services_command_start );
    ASSERT_NE( EMPTY_STRING, services_command_stop  );

    //cleanup
    ASSERT_TRUE( ra::filesystem::deleteFile(template_target_path.c_str()) ) << "Failed deleting file '" << template_target_path << "'.";
  }
  //--------------------------------------------------------------------------------------------------

} //namespace test
} //namespace shellanything
