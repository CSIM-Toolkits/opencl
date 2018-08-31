// This file was automatically generated by:
//  /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/SlicerExecutionModel-build/GenerateCLP/bin/GenerateCLP --InputXML /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/MeanFilter/MeanFilter.xml --OutputCxx /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build/MeanFilter/MeanFilterCLP.h
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <sstream>

#include "tclap/CmdLine.h"
#include "ModuleProcessInformation.h"

#ifdef _WIN32
#define Module_EXPORT __declspec(dllexport)
#else
#define Module_EXPORT
#endif

#if defined(main) && !defined(REGISTER_TEST)
// If main defined as a preprocessor symbol, redefine it to the expected entry point.
#undef main
#define main ModuleEntryPoint

extern "C" {
  Module_EXPORT char *GetXMLModuleDescription();
  Module_EXPORT int ModuleEntryPoint(int, char*[]);
}
#endif

extern "C" {
Module_EXPORT char XMLModuleDescription[] = 
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
"<executable>\n"
"  <category>OpenCL</category>\n"
"  <title>MeanFilter</title>\n"
"  <description><![CDATA[This is a CLI module that can be bundled in an extension]]></description>\n"
"  <version>0.0.1</version>\n"
"  <documentation-url>http://www.example.com/Slicer/Modules/MeanFilter</documentation-url>\n"
"  <license>Slicer</license>\n"
"  <contributor>FirstName LastName (Institution), FirstName LastName (Institution)</contributor>\n"
"  <acknowledgements>This work was partially funded by NIH grant NXNNXXNNNNNN-NNXN</acknowledgements>\n"
"  <parameters>\n"
"    <label>IO Mean Filter</label>\n"
"    <description><![CDATA[Input/output parameters]]></description>\n"
"\n"
"    <image>\n"
"      <name>inputVolume</name>\n"
"      <label>Input Volume</label>\n"
"      <channel>input</channel>\n"
"      <index>0</index>\n"
"      <description><![CDATA[Input volume]]></description>\n"
"    </image>\n"
"    <image>\n"
"      <name>outputVolume</name>\n"
"      <label>Output Volume</label>\n"
"      <channel>output</channel>\n"
"      <index>1</index>\n"
"      <description><![CDATA[Output Volume]]></description>\n"
"    </image>\n"
"\n"
"    <string-enumeration>\n"
"          <name>deviceType</name>\n"
"          <longflag>--devicetype</longflag>\n"
"          <description>Select the type of device to run</description>\n"
"          <label>Method Type</label>\n"
"          <element>GPU</element>\n"
"          <element>CPU</element>\n"
"          <default>GPU</default>\n"
"      </string-enumeration>\n"
"\n"
"      <integer>\n"
"      <name>meanRadius</name>\n"
"      <longflag>--radiusIn</longflag>\n"
"      <label>Size of Mask </label>\n"
"      <description>Select a radius of mean filter</description>\n"
"      <default>1.0</default>\n"
"      </integer>\n"
"\n"
"\n"
"  </parameters>\n"
"</executable>\n"
"\n"
;

}

void
splitString (const std::string &text,
             const std::string &separators,
             std::vector<std::string> &words)
{
  const std::string::size_type n = text.length();
  std::string::size_type start = text.find_first_not_of(separators);
  while (start < n)
    {
    std::string::size_type stop = text.find_first_of(separators, start);
    if (stop > n) stop = n;
    words.push_back(text.substr(start, stop - start));
    start = text.find_first_not_of(separators, stop+1);
    }
}

void
splitFilenames (const std::string &text,
                std::vector<std::string> &words)
{
  const std::string::size_type n = text.length();
  bool quoted;
  std::string comma(",");
  std::string quote("\"");
  std::string::size_type start = text.find_first_not_of(comma);
  while (start < n)
    {
    quoted = false;
    std::string::size_type startq = text.find_first_of(quote, start);
    std::string::size_type stopq = text.find_first_of(quote, startq+1);
    std::string::size_type stop = text.find_first_of(comma, start);
    if (stop > n) stop = n;
    if (startq != std::string::npos && stopq != std::string::npos)
      {
      while (startq < stop && stop < stopq && stop != n)
         {
         quoted = true;
         stop = text.find_first_of(comma, stop+1);
         if (stop > n) stop = n;
         }
      }
    if (!quoted)
      {
      words.push_back(text.substr(start, stop - start));
      }
    else
      {
      words.push_back(text.substr(start+1, stop - start-2));
      }
    start = text.find_first_not_of(comma, stop+1);
    }
}

char *GetXMLModuleDescription()
{
   return XMLModuleDescription;
}

#define GENERATE_LOGO
#define GENERATE_XML \
  if (argc >= 2 && (strcmp(argv[1],"--xml") == 0)) \
    { \
    std::cout << GetXMLModuleDescription(); \
    return EXIT_SUCCESS; \
    }
#define GENERATE_TCLAP_PARSE \
    std::string inputVolume; \
    std::string outputVolume; \
    std::string deviceType = "GPU"; \
    std::vector<std::string> deviceTypeAllowed; \
    deviceTypeAllowed.push_back("GPU");  \
    deviceTypeAllowed.push_back("CPU");  \
    TCLAP::ValuesConstraint<std::string> deviceTypeAllowedVals (deviceTypeAllowed);  \
    int meanRadius = 1.0; \
    bool echoSwitch = false; \
    bool xmlSwitch = false; \
    std::string processInformationAddressString = "0"; \
    std::string returnParameterFile; \
    std::string fullDescription("Description: "); \
    fullDescription += "This is a CLI module that can be bundled in an extension"; \
    if (!std::string("FirstName LastName (Institution), FirstName LastName (Institution)").empty()) \
      { \
      fullDescription += "\nAuthor(s): FirstName LastName (Institution), FirstName LastName (Institution)"; \
      } \
    if (!std::string("This work was partially funded by NIH grant NXNNXXNNNNNN-NNXN").empty()) \
      { \
      fullDescription += "\nAcknowledgements: This work was partially funded by NIH grant NXNNXXNNNNNN-NNXN"; \
      } \
    TCLAP::CmdLine commandLine (fullDescription, \
       ' ', \
      "0.0.1" ); \
 \
      std::ostringstream msg; \
    msg.str("");msg << "Input volume";    TCLAP::UnlabeledValueArg<std::string> inputVolumeArg("inputVolume", msg.str(), 1, inputVolume, "std::string", commandLine); \
 \
    msg.str("");msg << "Output Volume";    TCLAP::UnlabeledValueArg<std::string> outputVolumeArg("outputVolume", msg.str(), 1, outputVolume, "std::string", commandLine); \
 \
    msg.str("");msg << "Select the type of device to run (default: " << deviceType << ")"; \
    TCLAP::ValueArg<std::string> deviceTypeArg("", "devicetype", msg.str(), 0, deviceType, &deviceTypeAllowedVals, commandLine); \
 \
    msg.str("");msg << "Select a radius of mean filter (default: " << meanRadius << ")"; \
    TCLAP::ValueArg<int > meanRadiusArg("", "radiusIn", msg.str(), 0, meanRadius, "int", commandLine); \
 \
    msg.str("");msg << "Echo the command line arguments (default: " << echoSwitch << ")"; \
    TCLAP::SwitchArg echoSwitchArg("", "echo", msg.str(), commandLine, echoSwitch); \
 \
    msg.str("");msg << "Produce xml description of command line arguments (default: " << xmlSwitch << ")"; \
    TCLAP::SwitchArg xmlSwitchArg("", "xml", msg.str(), commandLine, xmlSwitch); \
 \
    msg.str("");msg << "Address of a structure to store process information (progress, abort, etc.). (default: " << processInformationAddressString << ")"; \
    TCLAP::ValueArg<std::string > processInformationAddressStringArg("", "processinformationaddress", msg.str(), 0, processInformationAddressString, "std::string", commandLine); \
 \
    msg.str("");msg << "Filename in which to write simple return parameters (int, float, int-vector, etc.) as opposed to bulk return parameters (image, geometry, transform, measurement, table).";    TCLAP::ValueArg<std::string > returnParameterFileArg("", "returnparameterfile", msg.str(), 0, returnParameterFile, "std::string", commandLine); \
 \
try \
  { \
    /* Build a map of flag aliases to the true flag */ \
    std::map<std::string,std::string> flagAliasMap; \
    std::map<std::string,std::string> deprecatedFlagAliasMap; \
    std::map<std::string,std::string> longFlagAliasMap; \
    std::map<std::string,std::string> deprecatedLongFlagAliasMap; \
    /* Remap flag aliases to the true flag */ \
    std::vector<std::string> targs; \
    std::map<std::string,std::string>::iterator ait; \
    std::map<std::string,std::string>::iterator dait; \
    size_t ac; \
    for (ac=0; ac < static_cast<size_t>(argc); ++ac)  \
       {  \
       if (strlen(argv[ac]) == 2 && argv[ac][0]=='-') \
         { \
         /* short flag case */ \
         std::string tflag(argv[ac], 1, strlen(argv[ac])-1); \
         ait = flagAliasMap.find(tflag); \
         dait = deprecatedFlagAliasMap.find(tflag); \
         if (ait != flagAliasMap.end() || dait != deprecatedFlagAliasMap.end()) \
           { \
           if (ait != flagAliasMap.end()) \
             { \
             /* remap the flag */ \
             targs.push_back("-" + (*ait).second); \
             } \
           else if (dait != deprecatedFlagAliasMap.end()) \
             { \
             std::cout << "Flag \"" << argv[ac] << "\" is deprecated. Please use flag \"-" << (*dait).second << "\" instead. " << std::endl; \
             /* remap the flag */ \
             targs.push_back("-" + (*dait).second); \
             } \
           } \
         else \
           { \
           targs.push_back(argv[ac]); \
           } \
         } \
       else if (strlen(argv[ac]) > 2 && argv[ac][0]=='-' && argv[ac][1]=='-') \
         { \
         /* long flag case */ \
         std::string tflag(argv[ac], 2, strlen(argv[ac])-2); \
         ait = longFlagAliasMap.find(tflag); \
         dait = deprecatedLongFlagAliasMap.find(tflag); \
         if (ait != longFlagAliasMap.end() || dait != deprecatedLongFlagAliasMap.end()) \
           { \
           if (ait != longFlagAliasMap.end()) \
             { \
             /* remap the flag */ \
             targs.push_back("--" + (*ait).second); \
             } \
           else if (dait != deprecatedLongFlagAliasMap.end()) \
             { \
             std::cout << "Long flag \"" << argv[ac] << "\" is deprecated. Please use long flag \"--" << (*dait).second << "\" instead. " << std::endl; \
             /* remap the flag */ \
             targs.push_back("--" + (*dait).second); \
             } \
           } \
         else \
           { \
           targs.push_back(argv[ac]); \
           } \
         } \
       else if (strlen(argv[ac]) > 2 && argv[ac][0]=='-' && argv[ac][1]!='-') \
         { \
         /* short flag case where multiple flags are given at once ala */ \
         /* "ls -ltr" */ \
         std::string tflag(argv[ac], 1, strlen(argv[ac])-1); \
         std::string rflag("-"); \
         for (std::string::size_type fi=0; fi < tflag.size(); ++fi) \
           { \
           std::string tf(tflag, fi, 1); \
           ait = flagAliasMap.find(tf); \
           dait = deprecatedFlagAliasMap.find(tf); \
           if (ait != flagAliasMap.end() || dait != deprecatedFlagAliasMap.end()) \
             { \
             if (ait != flagAliasMap.end()) \
               { \
               /* remap the flag */ \
               rflag += (*ait).second; \
               } \
             else if (dait != deprecatedFlagAliasMap.end()) \
               { \
               std::cout << "Flag \"-" << tf << "\" is deprecated. Please use flag \"-" << (*dait).second << "\" instead. " << std::endl; \
               /* remap the flag */ \
               rflag += (*dait).second; \
               } \
             } \
           else \
             { \
             rflag += tf; \
             } \
           } \
         targs.push_back(rflag); \
         } \
       else \
         { \
         /* skip the argument without remapping (this is the case for any */ \
         /* arguments for flags */ \
         targs.push_back(argv[ac]); \
         } \
       } \
 \
   /* Remap args to a structure that CmdLine::parse() can understand*/ \
   std::vector<char*> vargs; \
   for (ac = 0; ac < targs.size(); ++ac) \
     {  \
     vargs.push_back(const_cast<char *>(targs[ac].c_str())); \
     } \
    commandLine.parse ( vargs.size(), (char**) &(vargs[0]) ); \
  } \
catch ( TCLAP::ArgException e ) \
  { \
  std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; \
  return ( EXIT_FAILURE ); \
  }
#define GENERATE_TCLAP_ASSIGNMENT \
      inputVolume = inputVolumeArg.getValue(); \
      outputVolume = outputVolumeArg.getValue(); \
      deviceType = deviceTypeArg.getValue(); \
      meanRadius = meanRadiusArg.getValue(); \
      echoSwitch = echoSwitchArg.getValue(); \
      xmlSwitch = xmlSwitchArg.getValue(); \
      processInformationAddressString = processInformationAddressStringArg.getValue(); \
      returnParameterFile = returnParameterFileArg.getValue(); \

#define GENERATE_TCLAP GENERATE_TCLAP_PARSE;GENERATE_TCLAP_ASSIGNMENT
#define GENERATE_TCLAP_ASSIGNMENT_IFSET \
    if( inputVolumeArg.isSet() ) \
      { \
      inputVolume = inputVolumeArg.getValue(); \
      } \
    if( outputVolumeArg.isSet() ) \
      { \
      outputVolume = outputVolumeArg.getValue(); \
      } \
    if( deviceTypeArg.isSet() ) \
      { \
      deviceType = deviceTypeArg.getValue(); \
      } \
    if( meanRadiusArg.isSet() ) \
      { \
      meanRadius = meanRadiusArg.getValue(); \
      } \
    if( echoSwitchArg.isSet() ) \
      { \
      echoSwitch = echoSwitchArg.getValue(); \
      } \
    if( xmlSwitchArg.isSet() ) \
      { \
      xmlSwitch = xmlSwitchArg.getValue(); \
      } \
    if( processInformationAddressStringArg.isSet() ) \
      { \
      processInformationAddressString = processInformationAddressStringArg.getValue(); \
      } \
    if( returnParameterFileArg.isSet() ) \
      { \
      returnParameterFile = returnParameterFileArg.getValue(); \
      } \

#define GENERATE_ECHOARGS \
if (echoSwitch) \
{ \
std::cout << "Command Line Arguments" << std::endl; \
std::cout << "    inputVolume: " << inputVolume << std::endl; \
std::cout << "    outputVolume: " << outputVolume << std::endl; \
std::cout << "    deviceType: " << deviceType << std::endl; \
std::cout << "    meanRadius: " << meanRadius << std::endl; \
std::cout << "    echoSwitch: " << echoSwitch << std::endl; \
std::cout << "    xmlSwitch: " << xmlSwitch << std::endl; \
std::cout << "    processInformationAddressString: " << processInformationAddressString << std::endl; \
std::cout << "    returnParameterFile: " << returnParameterFile << std::endl; \
}
#define GENERATE_ProcessInformationAddressDecoding \
ModuleProcessInformation *CLPProcessInformation = 0; \
if (processInformationAddressString != "") \
{ \
sscanf(processInformationAddressString.c_str(), "%p", &CLPProcessInformation); \
}
#define PARSE_ARGS GENERATE_LOGO;GENERATE_XML;GENERATE_TCLAP;GENERATE_ECHOARGS;GENERATE_ProcessInformationAddressDecoding;
