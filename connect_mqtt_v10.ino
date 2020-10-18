/* v01 - 24/03/2020
 * подключения к MQTT выделены отдельно из connect_func 
 * 
 * v02 - 25/03/2020
 * функции передачи MQTT_publish_int и MQTT_publish_float перенесены в connect_mqtt
 * 
 * v03 - 22/05/2020
 * добавлен флаг ratain = true при публикации сообщений на сервер
 * 
 * v10 - 15/06/2020
 * исправлена функция MQTT_publish_float (заменена sprintf на dtostrf)
 */

 
//===================================================================================================
// подключение к MQTT 
const char *mqtt_server = "mqtt.dioty.co";          // Имя сервера MQTT
const int   mqtt_port = 1883;                       // Порт для подключения к серверу MQTT
const char *mqtt_user = "sv.lipatnikov@gmail.com";  // Логин от сервера
const char *mqtt_pass = "83eb5858";                 // Пароль от сервера

void Connect_mqtt(const char* client_name) {
  if (WiFi.status() == WL_CONNECTED) {
    client.setServer(mqtt_server, mqtt_port);            
    if (client.connect(client_name, mqtt_user, mqtt_pass)) 
      client.setCallback(mqtt_get);
  }
}


// Функция отправки int на сревер mqtt
void MQTT_publish_int(const char* topic , int data){
  char msg[5];
  sprintf (msg, "%u", data);    
  client.publish(topic, msg, true);
}


// Функция отправки float на сревер mqtt
void MQTT_publish_float(const char* topic , float data){
  char msg[5];
  dtostrf(data, 4, 1, msg);
  //sprintf (msg, "%2.1f", data);    
  client.publish(topic, msg, true);
}
