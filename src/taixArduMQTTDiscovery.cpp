#include "taixArduMQTTDiscovery.hpp"

void MQTTDevice::addConnection(String connection) {
  connections.push_back(connection);
}

void MQTTDevice::addIdentifier(String identifier) {
  identifiers.push_back(identifier);
}

void addParamIfNotEmpty(StaticJsonDocument<1000> json, String abbreviation, String data) {
  if (!data.isEmpty()) json[abbreviation] = data;
}

void addArrayIfNotEmpty(StaticJsonDocument<1000> json, String abbreviation, std::vector<String> vData) {
  if (!vData.empty()) {
    JsonArray array = json.createNestedArray(abbreviation);
    for (auto iData : vData) array.add(iData);
  }
}

void MQTTDevice::addConfigDevice(StaticJsonDocument<1000> json) {
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