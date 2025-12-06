#include "./include/configuration.h"
#include "./include/ScreenManager.h"

int main() {
    Configuration config;
    config.load(); 
    
    ScreenManager manager(config); 
    manager.run();

    return 0;
}