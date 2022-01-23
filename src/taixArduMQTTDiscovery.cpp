#include "taixArduMQTTDiscovery.hpp"

void MQTTDevice::addConnection(String connection) {
  connections.push_back(connection);
}

void MQTTDevice::addIdentifier(String identifier) {
  identifiers.push_back(identifier);
}

void addParamIfNotEmpty(DynamicJsonDocument& json, String key, String data) {
  if (!data.isEmpty()) json[key] = data;
}
void addParamIfNotEmpty(JsonObject& json, String key, String data) {
  if (!data.isEmpty()) json[key] = data;
}

void addArrayIfNotEmpty(DynamicJsonDocument& json, String key, std::vector<String> vData) {
  if (!vData.empty()) {
    JsonArray array = json.createNestedArray(key);
    for (auto iData : vData) array.add(iData);
  }
}
void addArrayIfNotEmpty(JsonObject& json, String key, std::vector<String> vData) {
  if (!vData.empty()) {
    JsonArray array = json.createNestedArray(key);
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

MQTTEntity MQTTEntity::createGeneric(MQTTDevice mqttDevice, String name, String objectId, String stateTopic, String commandTopic) {
  MQTTEntity mqttEntity;
  mqttEntity.mqttDevice = mqttDevice;
  mqttEntity.stateTopic = stateTopic;
  mqttEntity.commandTopic = commandTopic;
  mqttEntity.objectId = objectId;
  mqttEntity.uniqueId = objectId;
  mqttEntity.name = name;
  return mqttEntity;
}

MQTTEntity MQTTEntity::createSensor(MQTTDevice mqttDevice, String name, String stateTopic, String objectId) {
  return MQTTEntity::createGeneric(mqttDevice, name, objectId, stateTopic);
}

MQTTEntity MQTTEntity::createNumber(MQTTDevice mqttDevice, String name, String commandTopic, String objectId, float step, float min, float max, String stateTopic) {
  MQTTEntity mqttEntity = MQTTEntity::createGeneric(mqttDevice, name, objectId, stateTopic, commandTopic);
  mqttEntity.deviceType = Number;
  mqttEntity.step = step;
  mqttEntity.min = min;
  mqttEntity.max = max;
  return mqttEntity;
}

MQTTEntity MQTTEntity::createSwitch(MQTTDevice mqttDevice, String name, String commandTopic, String objectId, String payloadOn, String payloadOff, String stateTopic) {
  MQTTEntity mqttEntity = MQTTEntity::createGeneric(mqttDevice, name, objectId, stateTopic, commandTopic);
  mqttEntity.deviceType = Switch;
  mqttEntity.payloadOff = payloadOff;
  mqttEntity.payloadOn = payloadOn;
  return mqttEntity;
}

MQTTEntity MQTTEntity::createSelect(MQTTDevice mqttDevice, String name, String commandTopic, std::vector<String> options, String objectId, String stateTopic) {
  MQTTEntity mqttEntity = MQTTEntity::createGeneric(mqttDevice, name, objectId, stateTopic, commandTopic);
  mqttEntity.options = options;
  return mqttEntity;
}

String MQTTEntity::getJSON() {
  DynamicJsonDocument json(1024);

  addParamIfNotEmpty(json, "avty_t", availabilityTopic);
  addParamIfNotEmpty(json, "pl_off", payloadOff);
  addParamIfNotEmpty(json, "pl_on", payloadOn);
  addParamIfNotEmpty(json, "dev_cla", deviceClass);
  if (deviceType == Switch) json["enabled_by_default"] = enabledByDefault;
  addParamIfNotEmpty(json, "ic", icon);
  addParamIfNotEmpty(json, "name", name);
  addParamIfNotEmpty(json, "obj_id", objectId);
  addParamIfNotEmpty(json, "stat_t", stateTopic);
  addParamIfNotEmpty(json, "cmd_t", commandTopic);
  addParamIfNotEmpty(json, "uniq_id", uniqueId);
  addParamIfNotEmpty(json, "unit_of_meas", unitOfMeasurement);
  addParamIfNotEmpty(json, "val_tpl", valueTemplate);
  addParamIfNotEmpty(json, "cmd_tpl", commandTemplate);
  if (deviceType == Number) {
    json["min"] = min;
    json["max"] = max;
    json["step"] = step;
  }
  addArrayIfNotEmpty(json, "options", options);
  mqttDevice.addConfigDevice(json);

  // TODO: eliminar en futuras versiones
  serializeJsonPretty(json, Serial);
  String payload;
  serializeJson(json, payload);
  return payload;
}