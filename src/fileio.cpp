#include "../include/fileio.h"

#include "../include/Logger.h"

Logger IOLog;

void ReadShader(const std::string& path, std::string& content)
{
    std::string line;
    std::ifstream myfile(path);
    if (myfile.is_open())
    {
        while (std::getline(myfile, line))
        {
            content.append(line + '\n');
        }
        myfile.close();
    }
    else
    {
        IOLog.Error("Unable to open file " + path + " !");
        exit(EXIT_FAILURE);
    }
}

void ReadConfig(const std::string& path, std::vector<std::pair<std::string, double>>& content)
{
    std::ifstream file(path);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream is_line(line);
            std::string key;
            if (std::getline(is_line, key, '='))
            {
                std::string value;
                if (std::getline(is_line, value))
                {
                    content.push_back(std::make_pair(key, std::stod(value)));
                    std::cout << "Config read: [ " << key << "] = <" << value << " >" << std::endl;
                }
            }
        }
    }
    else
    {
        IOLog.Error("Unable to open file " + path + " !");
        exit(EXIT_FAILURE);
    }
}