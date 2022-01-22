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
    void addConfigDevice(DynamicJsonDocument& json);

  private:
    std::vector<String> connections;
    std::vector<String> identifiers;
};

class MQTTEntity {
  public:
    String availabilityTopic;
    String deviceClass;
    bool enabledByDefault = true;
    String icon;
    String name;
    String objectId;
    String stateTopic;
    String uniqueId;
    String unitOfMeasurement;
    String valueTemplate;

    static MQTTEntity createSensor(MQTTDevice mqttDevice, String name, String stateTopic);
    String getJsonSensor();

  private:
    MQTTDevice mqttDevice;
};

#endif