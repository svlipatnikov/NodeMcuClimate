/* v.02 - 01/01/2020
 *  Устраенна ошибка с первым подключением к wi-fi
 *  Уделен алгоритм увеличения времени до ребута (после рестарта он все равно обнуляется)
 *  
 *  v03 - 15/01/2020
 *  удалено управление светодиодом из функции Connect (не везде есть свободные пины)
 *  
 *  v04 - 04/02/2020
 *  Введено ограничение по времени на поключение к Blynk
 *  
 *  v05 - 18/02/2020 
 *  - static IP (не работает с Blynk, закомментирован)
 *  - упрощен алгоритм подключения к Blynk
 *  
 *  v06 - 21/02/2020
 *  - доработан Connect_WiFi функции запуска серверов перенесены внутрь временного условия
 *  
 *  v10 - 17/03/2020
 *  добавлено подключение к MQTT серверу  mqtt.by
 *  из функций удалены проверки на время крайнейнего вызова
 *  добавлены аргументы static_ip функции Connect_WiFi
 *  
 * v101 - 18/03/2020 
 * переход с mqtt.by на mqtt.dioty.co 
 * 
 * v102 - 21/03/2020
 * Удалена функция подключения к MQTT - должна быть вынесена в отдельный файл
 */

 
//===================================================================================================
// Подключение к wi-fi и udp 

IPAddress gateway (192, 168, 1, 1);
IPAddress mask (255, 255, 255, 255);
  
void Connect_WiFi(IPAddress device_ip, bool static_ip){
  WiFi.mode(WIFI_STA);  
  if (static_ip) WiFi.config(device_ip, gateway, mask);   
  WiFi.begin(ssid, pass);    
  byte i=0;  while ((WiFi.status() != WL_CONNECTED) && (i<5)) { delay(1000); i++; }     // подключаемся к wi-fi или выходим через 5 сек     
  
  if (WiFi.status() == WL_CONNECTED)  {
    Udp.begin(localPort);                                  // запуск UDP 
    httpUpdater.setup(&httpServer); httpServer.begin();    // web-сервер для обновления по воздуху  
  }
} 


//===================================================================================================
// Функция рестарта модуля при долгом отсутствии подключения к wi-fi

void Restart (unsigned long Online_time, const int max_offline_time) {
  if ((long)millis() - Online_time > max_offline_time) {  
    WiFi.disconnect();
    ESP.eraseConfig();
    delay(1000);
    ESP.reset();
  }
}
