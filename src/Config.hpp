//
//  Config.hpp
//  opencraft
//
//  Created by Максим Фалалеев on 08/04/2017.
//
//

#ifndef Config_hpp
#define Config_hpp

#include <iostream>

class Config {
public:
    Config(const std::string & appName, unsigned int width, unsigned int height, bool fullscreen) : _appName(appName),
    _width(width), _height(height), _fullscreen(fullscreen) {};
    
    std::string getAppName() { return this->_appName; };
    unsigned int getWidth() { return this->_width; };
    unsigned int getHeight() { return this->_height; };
    unsigned int getFramerate() { return this->_framerate; };
    bool getFullscreen() { return this->_fullscreen; };
    
private:
    std::string _appName = "Application";
    unsigned int _width = 800;
    unsigned int _height = 600;
    unsigned int _framerate = 60;
    bool _fullscreen = false;
};

#endif /* Config_hpp */
