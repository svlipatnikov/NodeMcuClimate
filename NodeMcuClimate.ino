/* My climate for ESP8266
 *  
 * D1 - Првая линия One Wire для подключения датчиков температуры DS18B20 (питание 5V)
 * D2 - Вторая линия One Wire для подключения датчиков температуры DS18B20 (питание 5V)
 * 
 * D5,D6 - SDA, SCL (i2c) для соединения с Arduino Nano (на контакты A4, A5)  
 * 
 * v 2.0
 * 1) добавлено чтение датчика температуры ГВС
 * 2) добавлено управление насосом ГВС, котлом, бойлером
 * 3) добавлены расчеты на отключене насоса ГВС, котла, бойлера
 * 4) добавлены часы реального времени DS1307 на контактах D2 D3
 * 5) добавлено получение времени с сервера NTP и синхронизация часов DS1307
 * 
 * v30 - 23/12/19
 * изменены алгоритмы подключения к wi-fi и серверу blynk
 * изменен алгоритм периодичности запуска функций
 * 
 * v40 - 28/02/2020
 * - переработан под connect_func_05 
 * - сетевые функции перенесены в периодическое выполнение
 * - добавлена передача инфрмации о температуре в Blynk, удалены управляющие сигналы
 * - скорректирован прием DS18B20 (датчики 3 и 4 вместе не работают)
 * - загрузка через веб-сервер
 * 
 * v41 - 03/03/2020
 * Исправлен прием по i2c (DHT22)
 * 
 * v42 - 04/03/2020
 * Исправлен прием по i2c (DHT22)
 * Изменена очередь опроса датчиков DS18B20
 * 
 * v43 - 08/03/2020
 * добавлена функция перезагрузки датчиков DHT 
 * питание датчиков DHT22 через пин D4
 * 
 * v44 - 12/03/2020
 * исправлена ошибка в функции DHR_reboot
 * 
 * v50 - 12/03/2020
 * введена функция гистерезиса
 * Исключен BLYNK
 * Переход на MQTT сервер
 * переписывание функции get_i2c_data
 * 
 * v502 - 24/03/2020
 * исправлена функция мониторинга
 * Отлажен с arduino nano в УКБП
 * 
 * v503 - 25/03/2020
 * удалено время на OTA update
 * исправлены данные сервера Open Monitoring
 * 
 * v504 - 30/03/2020 - стабильная
 * скорректирована функция отправки данных на сервер Open Monitoring:
 * отправка только если есть данные от датчиков, иначе отправки нет
 * закомментированы функции NTP
 * 
 * v51 - 03/04/2020
 * изменено управление термоклапанами (управление не чаще чем раз в 10 мин)
 * добавлены функции MQTT 
 * 
 * v511 - 05/04/2020
 * добавлен топик синхронизацмм с MQTT
 * 
 * v52 - 07/04/2020
 * добавлена вторая линия для датчиков DS18B20 на пине D2
 * удалены функции часов реального времени (есть время из интернета)
 * 
 * v53 - 08/04/2020
 * добавлен уличный датчик DS_weather
 * 
 * v54 - 09/04/2020
 * добавлена функция отправки UDP пакета для включения вытяжки в ванной
 * 
 * v55 - 13/04/2020
 * исправлена функция ds read для чтения с разных пинов
 * 
 * v56 - 16/04/2020
 * изменен порядок отправки парамтеров в функции Monitoring
 * 
 * v57 - 17/05/2020
 * Значение влажности для автоматического включения вытяжки увеличено с 60 до 70
 * 
 * v60 - 24/05/2020
 * топики mqtt разделены на топики управления ctrl и топики статуса state
 * добавлены флаги retain вместо топиков синхронизации (connect_mqtt_v03)
 * функции NTP переведены на библиотеку NTPClient
 * 
 * v61 - 14/06/2020
 * добавлены топики публикации для всех значений
 * удален префикс state у топиков не меняемых пользователем
 * чтобы система отработала сразу добавлено обнуление переменных времени при получении пользовательских изменений через mqtt
 * добавлена инверсия сигналов на насосы (управляются низким уровнем)
 * исправлена функция гистерезиса
 * добавлены функции Tp_valve_state и Bat_valve_state для обнуления состояния гистерезиса 
 * добавлено управление насосом ГВС по времени от NTP
 * 
 * v62 - 15/06/2020
 * работа с connect_mqtt_v10
 * 
 * v63 - 16/06/2020
 * добавлен энергосберегающий режим длятермоклапанов теплого пола
 * 
 * v64 - 24/06/2020
 * исправлена ошибка в функции mqtt_get: payload заменен на localpayload
 * 
 * v65 - 27/06/2020
 * скорректирована логика вычисления energy_save_flag
 * гистерезис для пола изменен с 1.25 на 1.0
 * добавлена задержка 90с после включения на начало вычисления данных
 * константа HIGH_HUMIDITY изменена на 90
 * 
 * v70 - 12/07/2020
 * удалена технологическая печать: контроллер теперь в корпусе, технологическая печать не нужна
 * исправлена функция Calc_MID
 * функция вычисления Calc_climate_data разбита на отдельные функции
 * добавлены переменные для отключения функций автоматики 
 * добавлены топики для управления переменными отключения функций автоматики 
 * добавлена задержка включения режима ENERGY_SAVE_DELAY
 * 
 * v71 - 14/09/2020
 * в setup добавлена установка начального состояния сигналов
 * переписаны функции вычисления данных
 * функции mqtt вынесены в отдельный файл
 * изменены режимы для отопления, гвс и вентиляторов
 * 
 * v72 - 17/09/2020
 * скорректированы функции calcTpPump, calcHeaterData
 * удалены глобальные флаги relay_heater_timer_flag, tp_pump_timer_flag
 * скорректировано управление веткой в ванной от времени
 * 
 * v721 - 22/09/2020
 * скорректирована функция energySave
 * скорректированы вычисления ТП и насоса ТП в main_cycle
 * 
 * v722 - 24/09/2020
 * добавлено вычисление и передача на mqtt флагов dht_validity_flag, ds_validity_flag, bath_high_humidity_flag
 * скорректированы вычисления в main_cycle
 * значение VALVE_CTRL_PERIOD уменьшено с 10 до 2 минут
 * в Calc_tp_data добавил обогрев ТП в ванной утром
 * изменено вычисление energy_save_flag: =true если выше НИЖНЕЙ границы гистерезиса 
 * 
 * v73 - 10/10/2020
 * Добавлен топик и функционал для подогрева пола по команде
 * изменены функции calcTpPump, calcHeaterData
 * 
 * v74 - 14/10/2020
 * добавлена проверка исправности данных от arduino nano  
 * изменены функции get_i2c_data
 * 
 * v75 - 06/11/2020
 * Скооректирована функция calcHeaterData для отключения котла при отключенных батареях и превышении TP_IN_MAX (котлу некуда качать)
 * 
 * v76 - 19/11/2020
 * ветка теплого пола всегда включена
 * добавлено включение всех веток ТП если включена хотя бы одна (все что в петле гистерезиса будут греть)
 * отключен режим save_energy зимой
 * добавлен morning_heater_flag и подогрев пола утром
 */

#include <Wire.h>

#include <OneWire.h>
OneWire oneWire(D1);
OneWire oneWire2(D2);

#include <DallasTemperature.h>
DallasTemperature DS(&oneWire);
DallasTemperature DS2(&oneWire2);
DeviceAddress tempDeviceAddress; //для поиска адресов
// датчики на пине D1
DeviceAddress ds_kit = {0x28, 0xAA, 0x92, 0x6C, 0x1D, 0x13, 0x02, 0x64};  // 1 corr +0.06 кухня
DeviceAddress ds_din = {0x28, 0xAA, 0xCF, 0x70, 0x1D, 0x13, 0x02, 0x37};  // 2 corr +0.18 гостинная
DeviceAddress ds_det = {0x28, 0xAA, 0x3D, 0x6F, 0x1D, 0x13, 0x02, 0xB0};  // 3 corr +0.00 детская
DeviceAddress ds_tpin = {0x28, 0x88, 0xD8, 0x79, 0x97, 0x08, 0x03, 0xC8}; // 6 температура на входном коллекторе ТП
// датчики на пине D2
DeviceAddress ds_bed = {0x28, 0xDD, 0x4E, 0xC6, 0x32, 0x14, 0x01, 0xF3}; // 4 corr +0.00 спальня
//DeviceAddress ds_gvs = { 0x28, 0xD0, 0x8B, 0x79, 0x97, 0x07, 0x03, 0x84 };   // 5 - не работает
DeviceAddress ds_weather = {0x28, 0xFD, 0xB7, 0x79, 0x97, 0x07, 0x03, 0xDD}; // 7 уличный датчик температуры
DeviceAddress ds_gvs = {0x28, 0x33, 0x9E, 0x79, 0x97, 0x07, 0x03, 0x5A};     // 8 ГВС

#include <ESP8266WiFi.h>
char *ssid = "welcome's wi-fi";
char *pass = "27101988";
const bool NEED_STATIC_IP = true;
IPAddress IP_Node_MCU(192, 168, 1, 71);
IPAddress IP_Fan_controller(192, 168, 1, 41);
IPAddress IP_Water_sensor_bath(192, 168, 1, 135);
IPAddress IP_Toilet_controller(192, 168, 1, 54);

#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

#include <PubSubClient.h>
WiFiClient NodeMCU_climate;
PubSubClient client(NodeMCU_climate);
const char *mqtt_client_name = "NodeMCU_climate"; // Имя клиента

#include <WiFiUdp.h>
WiFiUDP Udp;
unsigned int localPort = 8888;
char Buffer[UDP_TX_PACKET_MAX_SIZE];

#include <NTPClient.h>
NTPClient timeClient(Udp, "europe.pool.ntp.org"); //смещение на UTC+4

#include <string.h>
const char *host = "open-monitoring.online"; // Адрес сервера
const char *streamId = "938";                // ID                         (!)
const char *privateKey = "dXI0fy";           // Код доступа                (!)
const int SEND_PERIOD = 70 * 1000;           // Периодичность отправки пакетов на сервер >60сек
unsigned long last_send_time;
const byte count = 6;

struct dht_sensor
{
  float dataT[count];
  float dataH[count];
  float midT;
  float midH;
  byte index;
  byte ok = 0;
  byte err = 255;
};
dht_sensor _dht_din;
dht_sensor _dht_det;
dht_sensor _dht_bed;
dht_sensor _dht_bath;

struct ds_sensor
{
  float data[count];
  float mid;
  byte index;
  byte ok = 0;
  byte err = 255;
};
ds_sensor _ds_kit;
ds_sensor _ds_det;
ds_sensor _ds_din;
ds_sensor _ds_bed;
ds_sensor _ds_gvs;
ds_sensor _ds_tpin;
ds_sensor _ds_weather;

// Управляющие сигналы
bool tp_valve_kit, tp_valve_din, tp_valve_det, tp_valve_bed, tp_valve_bath; // термоклапаны теплого пола
bool tp_pump, gvs_pump;                                                     // насосы ТП, ГВС
bool bat_valve_kit, bat_valve_det, bat_valve_bed;                           // термоклапаны батарей
bool relay_heater, relay_boiler;                                            // реле котла и бойлера

// Переменные требуемых (заданных) значений температуры
float need_tp_kit = 24.5;
float need_tp_din = 25.1;
float need_tp_det = 25.5;
float need_tp_bed = 24.5;
float delta_tp = 1.0; // гистрезис температуры пола

float need_tv_din = 23.2;
float need_tv_det = 23.5;
float need_tv_bed = 23.1;
float delta_tv = 0.4; // гистрезис температуры воздуха

float need_gvs_temp = 37.0;
float delta_gvs_temp = 2.0; // гистрезис температуры ГВС
float delta_humidity = 2.5; // гистерезис для включения вытяжки в ванной
float delta_heater = 5.0;   // гистерезис температуры котла на входе в коллектор ТП 

//переменные для хранения времени крайнего управления термоклапанами
unsigned long change_tp_kit, change_tp_din, change_tp_det, change_tp_bed; // термоклапаны теплого пола
unsigned long change_tv_din, change_tv_det, change_tv_bed;                // термоклапаны батарей

// константы
const int RESTART_PERIOD = 10 * 60 * 1000;        // минимально время до ребута, если не удается подключиться к wi-fi
const int MAIN_CICLE_PERIOD = 1000;               // время переключения задач основного цикла
const int CHECK_PERIOD = 5 * 60 * 1000;           // периодичность проверки на подключение к сервисам
const int SYNH_MQTT_PERIOD = 30 * 1000;           // период отправки данных на mqtt сервер
const int VALVE_CTRL_PERIOD = 2 * 60 * 1000;      // изменять состояние термоклапанов не чаще чем 1 раз в 2 мин
const int START_TIMER = 90 * 1000;                // время после включения для сбора данных и устаканивания начальных процессов
const int HIGH_HUMIDITY = 90;                     // значение высокой влажности (для включения вытяжки в ванной)
const int TP_PUMP_DELAY = 120 * 1000;             // время задержки на включение насоса ТП (сек)
const int RELAY_HEATER_DELAY = 60 * 1000;         // время задержки на включение котла
const int ENERGY_SAVE_DELAY = 20 * 60 * 1000;     // время задержки перед включением режима energy_save
const int EMERGENCY_HEATER_TIME = 30 * 60 * 1000; // время подогрева по запросу
const int TP_IN_MAX = 37;                         // температура на входе коллектора ТП, выше которой котел отключается (при закрытых батареях и трехходовом клапане котлу некуда качать воду)

// переменные времени
unsigned long Last_online_time;       // время когда модуль был онлайн
unsigned long Last_main_cicle_time;   // время крайней итерации основного цикла
unsigned long Last_check_time;        // время крайней проверки подключения к сервисам
unsigned long Last_synh_MQTT_time;    // время крайней синхронизации с mqtt
unsigned long Last_get_ntp_time;      // время крайнего получения времени от сервера NTP
unsigned long currentCicleTime = 0;   // время на текущем такте ПО
unsigned long tp_pump_timer;          // таймер отключения насоса ТП
unsigned long relay_heater_timer;     // таймер отключения котла
unsigned long energySaveTime;         // время, начиная с которого выполняется условие energy_save_flag
unsigned long notEmergencyHeaterTime; // время включения подогрева (время крайнего не включенного состояния)

// прочие переменные
byte main_cicle_counter;      // счетчик основного цикла
bool energy_save_flag;        // флаг перевода всех термоклапанов ТП в нормальное состояние(напряжение отсутствует)
bool emergencyHeater;         // флаг для подогрева всех ТП на 30 мин
bool bath_high_humidity_flag; // Флаг большой влажности в ванной
bool dht_validity_flag;       // флаг валидности данных от датчиков DHT
bool ds_validity_flag;        // флаг валидности данных от датчиков DS18B20
float dht_i2c_data[8];        // массив принимаемых данных по i2c от arduino: temp1 , hum1, temp2, hum2, temp3, hum3, temp4, hum4
float mid_humidity = 100;     // средняя влажность в комнатах
bool fan_ON;                  // вытяжка в ванной
byte i2c_in_err = 100;        // счетчик ошибок данных от ардуино
bool dht_arduino_flag = true; // исправность данных от ардуино
bool morning_heater_flag = false; //флаг подогрева ТП утром
int heaterMinutes = 15;       // время подогрева ТП утром

// переменные включения/выключения основных функций
#define OFF 0
#define ON 1
#define AUTO 2
byte heaterMode = AUTO; // Режим автоматического управления отоплением
byte fanMode = AUTO;    // Режим автоматического управления вентилятором в ванной
byte gvsMode = AUTO;    // Режим автоматического управления ГВС

#define WINTER 0
#define SUMMER 1
bool seasonMode = SUMMER; // Режим котла для определения настроек "по умолчанию"

//==========================================================================================================

void setup()
{
  // настройка DS18B20 линия 1
  DS.begin();
  DS.setResolution(ds_kit, 12);
  DS.setResolution(ds_din, 12);
  DS.setResolution(ds_det, 12);
  DS.setResolution(ds_tpin, 12);

  // настройка DS18B20 линия 2
  DS2.begin();
  DS2.setResolution(ds_bed, 12);
  DS2.setResolution(ds_gvs, 12);
  DS2.setResolution(ds_weather, 12);

  // i2c на контактах SDA=D5 и SCL=D6
  Wire.begin(D5, D6);

  // подключение к Wi-Fi
  Connect_WiFi(IP_Node_MCU, NEED_STATIC_IP);

  // подключение к MQTT
  Connect_mqtt(mqtt_client_name);
  MQTT_subscribe();

  // инициализация NTP клиента
  timeClient.begin();
  timeClient.setTimeOffset(4 * 60 * 60); //смещение на UTC+4

  //начальное состояние сигналов пока не будут вычислены все данные
  Tp_valve_state(true);
  Bat_valve_state(false);
  tp_pump = false;
  relay_heater = false;
  emergencyHeater = false;
}

//==========================================================================================================

void loop()
{
  // вермя текущего цикла
  currentCicleTime = millis(); // чтобы не вызывать функцию каждый раз, а использовать переменную

  // сетевые функции
  httpServer.handleClient(); // для обновления по воздуху
  client.loop();             // для функций MQTT

  // вычисляем среднюю влажность в комнатах без ванной
  if (dhtDataOk())
    mid_humidity = (_dht_din.midH + _dht_det.midH + _dht_bed.midH) / 3;
  else // робасность
    mid_humidity = 100;

  // автоматическое включение вытяжки в ванной
  if (fanMode == ON)
    Send_UDP("b1");
  if (fanMode == AUTO)
  { // если включен режим автоматического управления вентилятором
    if ((_dht_bath.midH > HIGH_HUMIDITY) && (_dht_bath.midH - mid_humidity > 20))
      Send_UDP("b1");
  }

  // запуск задач основного цикла
  if (currentCicleTime - Last_main_cicle_time > MAIN_CICLE_PERIOD)
  {
    Last_main_cicle_time = currentCicleTime;
    main_cicle(main_cicle_counter);
    main_cicle_counter++;
    main_cicle_counter %= 8;
  }

  // проверка подключения к wifi
  if (currentCicleTime - Last_check_time > CHECK_PERIOD)
  {
    Last_check_time = currentCicleTime;

    if (WiFi.status() != WL_CONNECTED)
    { // wi-fi
      Connect_WiFi(IP_Node_MCU, NEED_STATIC_IP);
      Restart(Last_online_time, RESTART_PERIOD);
    }
    else
      Last_online_time = currentCicleTime;

    if (!client.connected())
    { // mqtt
      Connect_mqtt(mqtt_client_name);
      MQTT_subscribe();
    }
  }
}

//=======================================================================================================
// Вычисление данных
//=======================================================================================================

// проверка данных датчиков DS
bool dsDataOk(void)
{
  if ((_ds_kit.ok >= count) && (_ds_din.ok >= count) && (_ds_det.ok >= count) && (_ds_bed.ok >= count))
    return true;
  else
    return false;
}

// проверка данных датчиков DHT
bool dhtDataOk(void)
{
  if ((_dht_din.ok >= count) && (_dht_det.ok >= count) && (_dht_bed.ok >= count) && (_dht_bath.ok >= count))
    return true;
  else
    return false;
}

// вычисление признака высокой влажности
bool bathHighHumidity(void)
{
  if (dhtDataOk() && (_dht_bath.midH > HIGH_HUMIDITY))
    return true;
  else
    return false;
}

// вычисление признака energy_save_flag (температура в каждой комнате выше НИЖНЕЙ границы гистерезиса)
// для экономии электричества, например, летом, когда отопление постоянно отключено
bool energySave(void)
{
  bool needTemp;
  if ((_ds_kit.mid > need_tp_kit - delta_tp) &&
      (_ds_din.mid > need_tp_din - delta_tp) &&
      (_ds_det.mid > need_tp_det - delta_tp) &&
      (_ds_bed.mid > need_tp_bed - delta_tp))
    needTemp = true;
  else {  
    energySaveTime = currentCicleTime;
    needTemp = false;
  }

  if (currentCicleTime < ENERGY_SAVE_DELAY) {  // если только что влючились (или после ребута)
    if (seasonMode == SUMMER) return true;
    if (seasonMode == WINTER) return false;
  }
  else if (seasonMode == WINTER) // Зимой не включам режим energy_save_flag
    return false;
  else if (needTemp && (currentCicleTime - energySaveTime > ENERGY_SAVE_DELAY)) //если в течение ENERGY_SAVE_DELAY выполняется условие energy_save_flag
    return true;  
  else
    return false;
}

// вычисление данных для теплого пола
void Calc_tp_data(void)
{
  // Если хотя бы один термоклапан открыт, то открываем остальные.
  // Дальше гистерезис отключит ненужные и оставит те что внутри гистерезисной петли
  if (tp_valve_kit || tp_valve_din || tp_valve_det || tp_valve_bed) 
    Tp_valve_state(true); 

  // термоклапаны 
  if ((currentCicleTime - change_tp_kit > VALVE_CTRL_PERIOD))
  {
    change_tp_kit = currentCicleTime;
    tp_valve_kit = Hysteresis(tp_valve_kit, _ds_kit.mid, need_tp_kit, delta_tp);
  }
  if ((currentCicleTime - change_tp_din > VALVE_CTRL_PERIOD))
  {
    change_tp_din = currentCicleTime;
    tp_valve_din = Hysteresis(tp_valve_din, _ds_din.mid, need_tp_din, delta_tp);
  }
  if ((currentCicleTime - change_tp_det > VALVE_CTRL_PERIOD))
  {
    change_tp_det = currentCicleTime;
    tp_valve_det = Hysteresis(tp_valve_det, _ds_det.mid, need_tp_det, delta_tp);
  }
  if ((currentCicleTime - change_tp_bed > VALVE_CTRL_PERIOD))
  {
    change_tp_bed = currentCicleTime;
    tp_valve_bed = Hysteresis(tp_valve_bed, _ds_bed.mid, need_tp_bed, delta_tp);
  }

  

  // ветка теплого пола в ванной, туалете, коридоре
  tp_valve_bath = true; // всегда включена
/*  
  if (timeClient.getHours() >= 6 && timeClient.getHours() <= 21)
  {                                               // днем
    int hotPercent = (int)(20 - _ds_weather.mid); // получаем процент: сколько времени греть
    if (hotPercent < 0)
      hotPercent = 0;
    int minPercent = (int)((timeClient.getMinutes() / 60) * 100); // получем процент минтут в часе
    if (minPercent < hotPercent)
      tp_valve_bath = true;
    else
      tp_valve_bath = false;
  }
  else if (timeClient.getHours() == 5 && timeClient.getMinutes() > 40) // чтобы с утра полы были теплые греем с 5:40 до 6:00
    tp_valve_bath = true;
  else // ночью
    tp_valve_bath = false;
    */

  
}

// насос теплого пола
void calcTpPump(byte tpMode)
{
  switch (tpMode)
  {
  case OFF:
    tp_pump = false;
    tp_pump_timer = currentCicleTime;
    break;

  case ON:
    if (currentCicleTime - tp_pump_timer > TP_PUMP_DELAY) // включаем насос ТП не сразу
      tp_pump = true;
    else
      tp_pump = false;
    break;

  case AUTO:
    if (!tp_valve_kit && !tp_valve_din && !tp_valve_det && !tp_valve_bed)
    {
      tp_pump = false;
      tp_pump_timer = currentCicleTime;
    }
    else if (currentCicleTime - tp_pump_timer > TP_PUMP_DELAY) // включаем насос ТП не сразу
      tp_pump = true;
    else
      tp_pump = false;
    break;
  }
}

// батареи
void Calc_bat_data(void)
{
  if ((currentCicleTime - change_tv_din > VALVE_CTRL_PERIOD))
  {
    change_tv_din = currentCicleTime;
    bat_valve_kit = Hysteresis(bat_valve_kit, _dht_din.midT, need_tv_din, delta_tv);
  }
  if ((currentCicleTime - change_tv_det > VALVE_CTRL_PERIOD))
  {
    change_tv_det = currentCicleTime;
    bat_valve_det = Hysteresis(bat_valve_det, _dht_det.midT, need_tv_det, delta_tv);
  }
  if ((currentCicleTime - change_tv_bed > VALVE_CTRL_PERIOD))
  {
    change_tv_bed = currentCicleTime;
    bat_valve_bed = Hysteresis(bat_valve_bed, _dht_bed.midT, need_tv_bed, delta_tv);
  }
}

//насос ГВС
void Calc_gvs_data(void)
{
  if (timeClient.getHours() >= 5 && timeClient.getHours() <= 22)
    gvs_pump = Hysteresis(gvs_pump, _ds_gvs.mid, need_gvs_temp, delta_gvs_temp); //днем
  else
    gvs_pump = false; //ночью
}

// котел (сухие контакты)
void calcHeaterData(byte heaterMode)
{
  switch (heaterMode)
  {
  case OFF:
    relay_heater = false;
    relay_heater_timer = currentCicleTime;
    break;

  case ON:
    if ((currentCicleTime - relay_heater_timer) > RELAY_HEATER_DELAY) // включаем котел не сразу
      relay_heater = true;
    else
      relay_heater = false;
    break;

  case AUTO:
    if (!bat_valve_kit && !bat_valve_det && !bat_valve_bed && !tp_pump)
    { // если все батареи и теплый пол выключены
      relay_heater = false;
      relay_heater_timer = currentCicleTime;
    }
    else if (tp_pump && !bat_valve_kit && !bat_valve_det && !bat_valve_bed)
    { // если включен только теплый пол (задержка не нужна т.к. она есть в tp_pump)
      if (ds_validity_flag)
        relay_heater = Hysteresis(relay_heater, _ds_tpin.mid, TP_IN_MAX, delta_heater); // гистерезис для отключения котла при превышении TP_IN_MAX (трехходовой клапан закрыт, котлу некуда качать)
      else
      { //робасность
        if (seasonMode == SUMMER) relay_heater = false;
        if (seasonMode == WINTER) relay_heater = true;
      }
    }
    else if ((currentCicleTime - relay_heater_timer) > RELAY_HEATER_DELAY) // если включены батареи: задержка включения котла (ждем пока термоклапаны батарей сработают)
      relay_heater = true;
    else
      relay_heater = false;
    break;
  }
}

// Гистерезис
bool Hysteresis(bool curent_state, float data, float data_need, float delta)
{
  if (data > data_need + delta)
    return false;
  else if (data < data_need - delta)
    return true;
  else
    return curent_state;
}

// Функция для быстрого обнуления состояния всех клапанов ТП
void Tp_valve_state(bool state)
{
  tp_valve_kit = state;
  tp_valve_din = state;
  tp_valve_det = state;
  tp_valve_bed = state;
  tp_valve_bath = state;
}

// Функция для быстрого обнуления состояния всех клапанов батарей
void Bat_valve_state(bool state)
{
  bat_valve_kit = state;
  bat_valve_det = state;
  bat_valve_bed = state;
}

//=======================================================================================================
// функция получения данных по i2c
byte last_i2c_in_isp;

bool get_i2c_data()
{

  byte bite_counter = 0;             // число принятых бит
  byte i2c_in_data[26];              // массив для приема данных i2c
  byte data100, data10, data1, data; //

  Wire.requestFrom(8, 26); // запрос данных с 8 адреса, размер 26 символов (по 3 символа на температуру и влажность, х3 датчика, +2 символа исправности )
  while (Wire.available())
  {
    byte x = Wire.read() - '0';
    i2c_in_data[bite_counter] = x;
    bite_counter++;
  }

  if (bite_counter == 26)
  {
    for (byte num = 0; num < 8; num++)
    {
      dht_i2c_data[num] = ((float)i2c_in_data[num * 3] * 10) + ((float)i2c_in_data[(num * 3) + 1] * 1) + ((float)i2c_in_data[(num * 3) + 2] / 10);
      if (dht_i2c_data[num] == 0)
        dht_i2c_data[num] = NAN;
    }
    byte i2c_in_isp = (i2c_in_data[24] * 10) + i2c_in_data[25];
    if (i2c_in_isp != last_i2c_in_isp)
      return true;
    else
      return false;
    last_i2c_in_isp = i2c_in_isp;
  }
  else
    return false;
}

//=======================================================================================================
// Функция передачи данных по i2c
int i2c_out_isp;

void send_i2c_data(bool tp1, bool tp2, bool tp3, bool tp4, bool tp5,
                   bool bat1, bool bat2, bool bat3,
                   bool heater, bool boiler,
                   bool pump_tp, bool pump_gvs)
{
  i2c_out_isp++;
  i2c_out_isp %= 100; //инкремент исправности
  char Text[14];
  tp1 = !tp1;
  tp2 = !tp2;
  tp3 = !tp3;
  tp4 = !tp4;
  tp5 = !tp5;       //инверсия сигналов на термоклапаны ТП (нормально открытые)
  heater = !heater; //управление отключением котла   (по умолчанию включен)
  boiler = !boiler; //управление отключением бойлера (по умолчанию включен)
  pump_gvs = !pump_gvs;
  pump_tp = !pump_tp; //инверсия сигналов управления насосами (управляются низким уровнем)
  sprintf(Text, "%u%u%u%u%u%u%u%u%u%u%u%u%2.0u", tp1, tp2, tp3, tp4, tp5, bat1, bat2, bat3, heater, boiler, pump_tp, pump_gvs, i2c_out_isp);
  Wire.beginTransmission(8);
  Wire.write(Text);
  Wire.endTransmission();
}

//=======================================================================================================
// функция вычисления данных датчиков DHT22
dht_sensor Read_DHT(float temp, float hum, dht_sensor dht)
{
  if (!isnan(temp) && !isnan(hum) && (temp > 10) && (temp < 50))
  {
    dht.index++;
    dht.index %= count;
    dht.dataT[dht.index] = temp;
    dht.dataH[dht.index] = hum;
    dht.err = 0;
    if (dht.ok < count * 2)
      dht.ok++;
  }
  else
  {
    dht.ok--;
    if (dht.err < 255)
      dht.err++;
  }

  dht.midT = Calc_MID(dht.dataT);
  dht.midH = Calc_MID(dht.dataH);
  return dht;
}

//=======================================================================================================
// функция чтения данных с датчика DS18B20
ds_sensor Read_DS18B20(DeviceAddress DS_adress, ds_sensor ds, byte DS_pin)
{
  float temp;

  if (DS_pin == 1)
    temp = DS.getTempC(DS_adress);
  if (DS_pin == 2)
    temp = DS2.getTempC(DS_adress);

  if (!isnan(temp) && (temp > -50) && (temp < 60))
  {
    ds.index++;
    ds.index %= count;
    ds.data[ds.index] = temp;
    ds.err = 0;
    if (ds.ok < count * 2)
      ds.ok++;
  }
  else
  {
    ds.ok--;
    if (ds.err < 255)
      ds.err++;
  }

  ds.mid = Calc_MID(ds.data);
  return ds;
}

//=======================================================================================================
// функция вычисления среднего значния массива из 5 чисел
float Calc_MID(float data[count])
{
  float data_sum = 0, data_min = 100, data_max = -100;
  for (int i = 0; i < count; i++)
  {
    data_min = min(data[i], data_min);
    data_max = max(data[i], data_max);
    data_sum = data_sum + data[i];
  }
  float mid = ((data_sum - data_max) - data_min) / (count - 2);
  return mid;
}

//=======================================================================================================
// функции UDP

unsigned long Last_UDP_send_time; // время крайней отправки по udp
const int UDP_SEND_PERIOD = 3000; // частота отправки пакетов UDP

// функция отправки по UDP
void Send_UDP(char data[UDP_TX_PACKET_MAX_SIZE])
{
  if (currentCicleTime - Last_UDP_send_time > UDP_SEND_PERIOD)
  {
    Last_UDP_send_time = currentCicleTime;
    Udp.beginPacket(IP_Fan_controller, 8888);
    Udp.write(data);
    Udp.endPacket();
  }
}

//=======================================================================================================
// функции отправки данных на сервер мониторинга
void Monitoring(void)
{
  if (currentCicleTime - last_send_time > SEND_PERIOD)
  {
    last_send_time = currentCicleTime;
    Monitoring_data_send(); // Отправка данных на сервер
  }
}

// функция отправки данных на сервер open-monitoring.online
void Monitoring_data_send(void)
{
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort))
    return;

  // строка для отправки GET запросом
  String url = "/get?cid=" + (String)streamId + "&key=" + (String)privateKey;

  char float_data[4];
  if (_ds_kit.err < 5)
  {
    sprintf(float_data, "&p1=%2.1f", _ds_kit.mid);
    url += (String)float_data;
  }
  if (_ds_din.err < 5)
  {
    sprintf(float_data, "&p2=%2.1f", _ds_din.mid);
    url += (String)float_data;
  }
  if (_ds_det.err < 5)
  {
    sprintf(float_data, "&p3=%2.1f", _ds_det.mid);
    url += (String)float_data;
  }
  if (_ds_bed.err < 5)
  {
    sprintf(float_data, "&p4=%2.1f", _ds_bed.mid);
    url += (String)float_data;
  }
  if (_ds_tpin.err < 5)
  {
    sprintf(float_data, "&p5=%2.1f", _ds_tpin.mid);
    url += (String)float_data;
  }
  if (_ds_gvs.err < 5)
  {
    sprintf(float_data, "&p6=%2.1f", _ds_gvs.mid);
    url += (String)float_data;
  }
  if (_ds_weather.err < 5)
  {
    sprintf(float_data, "&p7=%2.1f", _ds_weather.mid);
    url += (String)float_data;
  }

  if (_dht_din.err < 5)
  {
    sprintf(float_data, "&p8=%2.1f", _dht_din.midT);
    url += (String)float_data;
  }
  if (_dht_det.err < 5)
  {
    sprintf(float_data, "&p9=%2.1f", _dht_det.midT);
    url += (String)float_data;
  }
  if (_dht_bed.err < 5)
  {
    sprintf(float_data, "&p10=%2.1f", _dht_bed.midT);
    url += (String)float_data;
  }
  if (_dht_bath.err < 5)
  {
    sprintf(float_data, "&p11=%2.1f", _dht_bath.midT);
    url += (String)float_data;
  }
  if (_dht_din.err < 5)
  {
    sprintf(float_data, "&p12=%2.1f", _dht_din.midH);
    url += (String)float_data;
  }
  if (_dht_det.err < 5)
  {
    sprintf(float_data, "&p13=%2.1f", _dht_det.midH);
    url += (String)float_data;
  }
  if (_dht_bed.err < 5)
  {
    sprintf(float_data, "&p14=%2.1f", _dht_bed.midH);
    url += (String)float_data;
  }
  if (_dht_bath.err < 5)
  {
    sprintf(float_data, "&p15=%2.1f", _dht_bath.midH);
    url += (String)float_data;
  }

  char send_data[200];
  sprintf(send_data, "&p16=%d&p17=%d&p18=%d&p19=%d&p20=%d&p21=%d&p22=%d&p23=%d&p24=%d&p25=%d&p26=%d&p27=%d",
          tp_valve_kit,
          tp_valve_din,
          tp_valve_det,
          tp_valve_bed,
          tp_valve_bath,
          bat_valve_kit,
          bat_valve_det,
          bat_valve_bed,
          tp_pump,
          gvs_pump,
          relay_heater,
          emergencyHeater);

  url += (String)send_data;

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = currentCicleTime;
  while (client.available() == 0)
  {
    if ((long)millis() - timeout > 5000)
    {
      client.stop();
      return;
    }
  }
}

//=======================================================================================================
// основной цикл
void main_cicle(byte main_cicle_counter)
{
  switch (main_cicle_counter)
  {
  case 0: // Получение по i2c данных из ARDUINO NANO от датчиков DHT22
    if (get_i2c_data())
    {
      _dht_din = Read_DHT(dht_i2c_data[0], dht_i2c_data[1], _dht_din);
      _dht_det = Read_DHT(dht_i2c_data[2], dht_i2c_data[3], _dht_det);
      _dht_bed = Read_DHT(dht_i2c_data[4], dht_i2c_data[5], _dht_bed);
      _dht_bath = Read_DHT(dht_i2c_data[6], dht_i2c_data[7], _dht_bath);
      i2c_in_err = 0;
    }
    else if (i2c_in_err < 255)
      i2c_in_err++;
    i2c_in_err < 10 ? dht_arduino_flag = true : dht_arduino_flag = false;
    break;

  case 1: // Чтение с датчиков DS18B20
    DS.requestTemperatures();
    _ds_kit = Read_DS18B20(ds_kit, _ds_kit, 1);
    _ds_din = Read_DS18B20(ds_din, _ds_din, 1);
    _ds_det = Read_DS18B20(ds_det, _ds_det, 1);
    _ds_tpin = Read_DS18B20(ds_tpin, _ds_tpin, 1);
    DS2.requestTemperatures();
    _ds_weather = Read_DS18B20(ds_weather, _ds_weather, 2);
    _ds_bed = Read_DS18B20(ds_bed, _ds_bed, 2);
    _ds_gvs = Read_DS18B20(ds_gvs, _ds_gvs, 2);
    break;

  case 2: // Вычисления
    // получение времени от NTP сервера
    timeClient.update();

    // признак валидности данных от датчиков DHT
    dht_validity_flag = dhtDataOk();

    // признак валидности данных от датчиков DS
    ds_validity_flag = dsDataOk();

    // признак большой влажности в ванной
    if (dht_validity_flag)
      bath_high_humidity_flag = bathHighHumidity();
    else //робасность
      bath_high_humidity_flag = false;

    // признак режима экономии энергии
    if (ds_validity_flag)
      energy_save_flag = energySave();
    else //робасность
      energy_save_flag = false;

    //вычисление emergencyHeater
    if (!emergencyHeater)
      notEmergencyHeaterTime = currentCicleTime;                                // запоминаем время отсутствия подогрева через emergencyHeater
    else if (currentCicleTime - notEmergencyHeaterTime > EMERGENCY_HEATER_TIME) // через EMERGENCY_HEATER_TIME сбрасываем флаг
      emergencyHeater = false;

    // признак подогрева полов утром
    if (ds_validity_flag) {
      heaterMinutes = 20 - _ds_weather.mid;
      heaterMinutes = constrain (heaterMinutes, 0, 60);
    }
    else { // робасность
      if (seasonMode == SUMMER) heaterMinutes = 15;
      if (seasonMode == WINTER) heaterMinutes = 30;
    }
    if (timeClient.getHours() == 5 && timeClient.getMinutes() > 60 - (int)heaterMinutes) // чтобы с утра полы были теплые с 5:30 до 6:00
      morning_heater_flag = true;

    // термоклапаны теплого пола и насос ТП
    if (emergencyHeater) {
      Tp_valve_state(true);
      calcTpPump(ON);
    }
    else if (morning_heater_flag) {
      calcTpPump(ON);
      if (seasonMode == SUMMER) tp_valve_bath = true;  // летом греем только ветку в ванной
      if (seasonMode == WINTER) Tp_valve_state(true);  // зимой греем все
    }
    else if (bath_high_humidity_flag) {  // если большая влажность в ванной     
      if (seasonMode == SUMMER) Tp_valve_state(false);
      if (seasonMode == WINTER) Tp_valve_state(true);
      Calc_tp_data();
      tp_valve_bath = true;
      calcTpPump(ON);
    }
    else if (energy_save_flag) {
      Tp_valve_state(true);     // термоклапаны теплого пола нормально-открытые, true = отсутствие напряжения
      calcTpPump(OFF);
    }
    else if (ds_validity_flag) {
      Calc_tp_data();
      calcTpPump(AUTO);
    }
    else   //робасность
    { 
      if (seasonMode == SUMMER) {
        Tp_valve_state(false); 
        calcTpPump(OFF);
      }
      if (seasonMode == WINTER) {
        Tp_valve_state(true);
        calcTpPump(ON);
      }
    }

    // батареи
    if (dht_validity_flag) // если данные температуры воздуха корректные
      Calc_bat_data();
    else                   // робасность для батарей
    { 
      if (seasonMode == SUMMER)
        Bat_valve_state(false);
      if (seasonMode == WINTER)
        Bat_valve_state(true);
    }

    // котел - вычисляем всегда на основании расчитанных данных или робасности
    calcHeaterData(AUTO);

    // насос ГВС
    if (ds_validity_flag)
      Calc_gvs_data();
    else // робасность: если датчик неисправен насос всегда ВКЛ
      gvs_pump = true;

    break;

  case 3: // Передача данных в ARDUINO NANO для управления реле

    if (heaterMode == OFF)
    { // если отопление принудительно отключено
      Tp_valve_state(true);
      Bat_valve_state(false);
      tp_pump = false;
      relay_heater = false;
    }
    if (heaterMode == ON)
    { // если отопление принудительно включено
      Tp_valve_state(true);
      Bat_valve_state(true);
      calcTpPump(ON);
      calcHeaterData(ON);
    }

    if (gvsMode == OFF) //если управление ГВС принудительно отключено
      gvs_pump = false;
    if (gvsMode == ON) //если управление ГВС принудительно включено
      gvs_pump = true;

    send_i2c_data(
        tp_valve_kit, tp_valve_din, tp_valve_det, tp_valve_bed, tp_valve_bath,
        bat_valve_kit, bat_valve_det, bat_valve_bed,
        relay_heater, relay_boiler,
        tp_pump, gvs_pump);
    break;

  case 4: // передача данных для построения графиков
    Monitoring();
    break;

  case 5: // Публикация на MQTT сервер
    if (currentCicleTime - Last_synh_MQTT_time > SYNH_MQTT_PERIOD)
    {
      Last_synh_MQTT_time = currentCicleTime;
      Send_MQTT_data();
    }
    break;
  }
}
