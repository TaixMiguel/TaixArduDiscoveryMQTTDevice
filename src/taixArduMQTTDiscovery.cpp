#include "taixArduMQTTDiscovery.hpp"

void MQTTDevice::addConnection(String connection) {
  connections.push_back(connection);
}

void MQTTDevice::addIdentifier(String identifier) {
  identifiers.push_back(identifier);
}

void addParamIfNotEmpty(DynamicJsonDocument& json, String abbreviation, String data) {
  if (!data.isEmpty()) json[abbreviation] = data;
}
void addParamIfNotEmpty(DynamicJsonDocument& json, String abbreviation, bool data) {
  json[abbreviation] = data;
}
void addParamIfNotEmpty(JsonObject& json, String abbreviation, String data) {
  if (!data.isEmpty()) json[abbreviation] = data;
}

void addArrayIfNotEmpty(JsonObject& json, String abbreviation, std::vector<String> vData) {
  if (!vData.empty()) {
    JsonArray array = json.createNestedArray(abbreviation);
    for (auto iData : vData) array.add(iData);
  }
}

void MQTTDevice::addConfigDevice(DynamicJsonDocument& json) {
  JsonObject device = json.createNestedObject("dev");
  addParamIfNotEmpty(device, "cu", configurationUrl);
  addArrayIfNotEmpty(device, "cns", connections);
  addArrayIfNotEmpty(device, "ids", identifiers);
  addParamIfNotEmpty(device, "mf", manufacturer);
  addParamIfNotEmpty(device, "mdl", model);
  addParamIfNotEmpty(device, "name", name);
  addParamIfNotEmpty(device, "sa", suggestedArea);
  addParamIfNotEmpty(device, "sw", swVersion);
  addParamIfNotEmpty(device, "via_device", viaDevice);
}


MQTTEntity MQTTEntity::createSensor(MQTTDevice mqttDevice, String name, String stateTopic, String objectId = "") {
  MQTTEntity mqttEntity;
  mqttEntity.mqttDevice = mqttDevice;
  mqttEntity.stateTopic = stateTopic;
  mqttEntity.objectId = objectId;
  mqttEntity.uniqueId = objectId;
  return mqttEntity;
}

String MQTTEntity::getJsonSensor() {
  DynamicJsonDocument json(1024);

  addParamIfNotEmpty(json, "avty_t", availabilityTopic);
  addParamIfNotEmpty(json, "dev_cla", deviceClass);
  addParamIfNotEmpty(json, "enabled_by_default", enabledByDefault);
  addParamIfNotEmpty(json, "ic", icon);
  addParamIfNotEmpty(json, "name", name);
  addParamIfNotEmpty(json, "obj_id", objectId);
  addParamIfNotEmpty(json, "stat_t", stateTopic);
  addParamIfNotEmpty(json, "uniq_id", uniqueId);
  addParamIfNotEmpty(json, "unit_of_meas", unitOfMeasurement);
  addParamIfNotEmpty(json, "val_tpl", valueTemplate);
  mqttDevice.addConfigDevice(json);

  // TODO: eliminar en futuras versiones
  serializeJsonPretty(json, Serial);
  String payload;
  serializeJson(json, payload);
  return payload;
}