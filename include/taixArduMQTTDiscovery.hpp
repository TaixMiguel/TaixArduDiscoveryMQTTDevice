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

    static MQTTEntity createSensor(MQTTDevice mqttDevice, String name, String stateTopic, String objectId="");
    static MQTTEntity createNumber(MQTTDevice mqttDevice, String name, String commandTopic, String objectId="", float step=1, float min=1, float max=100, String stateTopic="");
    static MQTTEntity createSwitch(MQTTDevice mqttDevice, String name, String commandTopic, String objectId="", String payloadOn="ON", String payloadOff="OFF", String stateTopic="");
    static MQTTEntity createSelect(MQTTDevice mqttDevice, String name, String commandTopic, std::vector<String> options, String objectId="", String stateTopic="");
    String getJSON();

  private:
    enum DeviceType { Default, Number, Switch };
    DeviceType deviceType = Default;
    MQTTDevice mqttDevice;
    float step, min, max;
    std::vector<String> options;
    String payloadOn, payloadOff;

    static MQTTEntity createGeneric(MQTTDevice mqttDevice, String name, String objectId="", String stateTopic="", String commandTopic="");
};

#endif