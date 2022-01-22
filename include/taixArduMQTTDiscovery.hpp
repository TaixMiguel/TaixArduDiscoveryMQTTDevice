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
    String objectId, uniqueId;
    String stateTopic, valueTemplate;
    String commandTopic, commandTemplate;
    String unitOfMeasurement;
    float step, min, max;

    static MQTTEntity createSensor(MQTTDevice mqttDevice, String name, String stateTopic, String objectId="");
    static MQTTEntity createNumber(MQTTDevice mqttDevice, String name, String commandTopic, String objectId="", float min=1, float max=100, String stateTopic="");
    String getJSON();

  private:
    MQTTDevice mqttDevice;
};

#endif