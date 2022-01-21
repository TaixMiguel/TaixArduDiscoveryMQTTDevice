#ifndef MQTTDiscovery_hpp
#define MQTTDiscovery_hpp

#define ARDUINOJSON_USE_LONG_LONG 1
#include <ArduinoJson.h>

/**
 * @author TaixMiguel
 */
class MQTTDevice {
  public:
    String configurationUrl;
    String manufacturer;
    String model;
    String name;
    String suggestedArea;
    String swVersion;
    String viaDevice;

    void addConnection(String connection);
    void addIdentifier(String identifier);
    void addConfigDevice(StaticJsonDocument<1000> json);

  private:
    std::vector<String> connections;
    std::vector<String> identifiers;
};

#endif