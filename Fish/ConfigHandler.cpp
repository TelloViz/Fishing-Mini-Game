#include "ConfigHandler.h"

bool ConfigHandler::ReadConfigFile()
{
     string filename("config.txt");
     vector<string> lines{};
     string line{};

     ifstream input_file(filename);
     if (!input_file.is_open()) {
          cerr << "Could not open the file - '"
               << filename << "'" << endl;
          return EXIT_FAILURE;
     }

     
     while (getline(input_file, line)) {
          if(!line.empty() && line.front() != '\n' && line.front() != '/')
               lines.push_back(line);          
     }

     for (const auto& i : lines)
          cout << i << endl;

     input_file.close();

     ParseConfigFile(lines);

     return EXIT_SUCCESS;
}

bool ConfigHandler::WriteConfigFile()
{
     string filename("config.txt");
     fstream file_out;

     file_out.open(filename, std::ios_base::out);
     if (!file_out.is_open()) {
          cout << "failed to open " << filename << '\n';
     }
     else {
         // TODO Writing logic here
          
          for (auto const& x : keys)
          {
               file_out << x  // string (key)
                    << '='
                    << configValueMap.at(x) // string's value 
                    << std::endl;
          }
          
          file_out.close();
          // file_out << "Some random text to write." << endl;
          cout << "Done Writing!" << endl;
     }

     return EXIT_SUCCESS;
}

bool ConfigHandler::FindConfig(string key, string& value)
{
     if (configValueMap.empty()) return false;
     try
     {
          value = configValueMap.at(key);
     }
     catch (const std::exception&)
     {

     }
     
     return true;
}

bool ConfigHandler::AlterValue(string key, string newVal)
{
     configValueMap.at(key) = newVal;
     return true;
}

bool ConfigHandler::ParseConfigFile(const vector<string>& lines)
{
     string k{}, v{};
     bool equalsFound = false;
     for (auto const& line : lines)
     {
          for (auto const& i : line)
          {
               if(i == '=')
               {
                    equalsFound = true;
               }
               else
               {    
                    if (equalsFound)
                    {
                         v.push_back(i);
                    }
                    else
                    {
                        k.push_back(i);
                    }
               }            
               
               
          }
          keys.push_back(k);
          configValueMap.insert(std::pair<string, string>(k, v));
          v = k = string{};
          equalsFound = false;


          
     }


     return true;
}
