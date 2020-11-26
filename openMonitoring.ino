#include <string.h>
const char *host = "open-monitoring.online"; // Адрес сервера
const char *streamId = "938";                // ID                         (!)
const char *privateKey = "dXI0fy";           // Код доступа                (!)
const int SEND_PERIOD = 70 * 1000;           // Периодичность отправки пакетов на сервер >60сек
unsigned long last_send_time;

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

// функции добавления данных DS и DHT к строке
String addDsData (String str, byte paramNum, ds_sensor ds) {
  char float_data[4];
  if (ds.err < 5) {
    sprintf(float_data, "&p%u=%2.1f", paramNum, ds.mid);
    str += (String)float_data;
  }
}

String addDhtTemp (String str, byte paramNum, dht_sensor dht) {
  char float_data[4];
  if (dht.err < 5) {
    sprintf(float_data, "&p%u=%2.1f", paramNum, dht.midT);
    str += (String)float_data;
  }
  return str;
}

String addDhtHum (String str, byte paramNum, dht_sensor dht) {
  char float_data[4];
  if (dht.err < 5) {
    sprintf(float_data, "&p%u=%2.1f", paramNum, dht.midH);
    str += (String)float_data;
  }
  return str;
}

String addBoolData (String str, byte paramNum, bool data) {
  char bool_data[4];
  sprintf(bool_data, "&p%u=%d", paramNum, data);
  str += (String)bool_data;
  return str;
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

  char send_data[230];
  sprintf(send_data, "&p16=%d&p17=%d&p18=%d&p19=%d&p20=%d&p21=%d&p22=%d&p23=%d&p24=%d&p25=%d&p26=%d&p27=%d&p28=%d&p29=%d&p30=%d",
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
          emergencyHeater,
          dht_validity_flag,
          ds_validity_flag,
          arduino_validity_flag
          );

  url += (String)send_data;
  //url = addBoolData(url, 28, dht_validity_flag);
  //url = addBoolData(url, 29, ds_validity_flag);
  //url = addBoolData(url, 30, arduino_validity_flag);
  
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
