// Загрузка данных сохраненных в файл  configs.json
bool loadConfig() {
  File configFile = SPIFFS.open("/configs.json", "r");
  if (!configFile) {
  // если файл не найден  
    Serial.println("Failed to open config file");
  //  Создаем файл запиав в него аные по умолчанию
    saveConfig();
    return false;
  }
  // Проверяем размер файла, будем использовать файл размером меньше 1024 байта
  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }

// загружаем файл конфигурации в глобальную переменную
  jsonConfig = configFile.readString();
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(jsonConfig);
  // Теперь можно получить значения из root  
    _ssidAP      = root["ssidAPName"].as<String>(); // Так получаем строку
    _passwordAP  = root["ssidAPPassword"].as<String>();
    _SSDP_Name    = root["SSDPName"].as<String>();
    _ssid        = root["ssidName"].as<String>();
    _password    = root["ssidPassword"].as<String>();
    HTTPRequest  = root["HTTPRequest"].as<String>();
    return true;
      Serial.println("---------CONFIG LOADED---------");
}

// Запись данных в файл config.json
bool saveConfig() {
  // Резервируем памяь для json обекта буфер может рости по мере необходимти предпочтительно для ESP8266 
  DynamicJsonBuffer jsonBuffer;
  //  вызовите парсер JSON через экземпляр jsonBuffer
  JsonObject& json = jsonBuffer.parseObject(jsonConfig);
  // Заполняем поля json 
  json["SSDPName"] = _SSDP_Name;
  json["ssidAPName"] = _ssidAP;
  json["ssidAPPassword"] = _passwordAP;
  json["ssidName"] = _ssid;
  json["ssidPassword"] = _password;
  json["HTTPRequest"] = HTTPRequest;
  json.printTo(jsonConfig);
  // Открываем файл для записи
  File configFile = SPIFFS.open("/configs.json", "w");
  if (!configFile) {
    //Serial.println("Failed to open config file for writing");
    return false;
  }
  // Записываем строку json в файл 
  json.printTo(configFile);
  Serial.println("---------CONFIG SAVED----------");
  return true;
  }




