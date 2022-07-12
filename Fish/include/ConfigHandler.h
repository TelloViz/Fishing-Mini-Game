/* This class should handle read/write to/from the config file for fish */



#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::map;  using std::ifstream; 
using std::vector; using std::fstream;

class ConfigHandler
{
public:
     bool ReadConfigFile();
     bool WriteConfigFile();
     bool FindConfig(string key, string& value);
     bool AlterValue(string key, string newVal);



private:
     
     bool ParseConfigFile(const vector<string>& lines);
     map<string, string> configValueMap;
     vector<string> keys;


};

