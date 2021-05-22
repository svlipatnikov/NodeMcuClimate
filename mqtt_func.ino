
//топики управления 
const char topic_heaterMode_state[] = "/sv.lipatnikov@gmail.com/climate/heaterMode_state";
const char topic_fanMode_state[] = "/sv.lipatnikov@gmail.com/climate/fanMode_state";
const char topic_gvsMode_state[] = "/sv.lipatnikov@gmail.com/climate/gvsMode_state";
const char topic_seasonMode_state[] = "/sv.lipatnikov@gmail.com/climate/seasonMode_state";
const char topic_emergencyHeater_state[] = "/sv.lipatnikov@gmail.com/climate/emergencyHeater_state";

const char topic_heaterMode_ctrl[] = "/sv.lipatnikov@gmail.com/climate/heaterMode_ctrl";
const char topic_fanMode_ctrl[] = "/sv.lipatnikov@gmail.com/climate/fanMode_ctrl";
const char topic_gvsMode_ctrl[] = "/sv.lipatnikov@gmail.com/climate/gvsMode_ctrl";
const char topic_seasonMode_ctrl[] = "/sv.lipatnikov@gmail.com/climate/seasonMode_ctrl";
const char topic_emergencyHeater_ctrl[] = "/sv.lipatnikov@gmail.com/climate/emergencyHeater_ctrl";

//топики для передачи данных
const char topic_tv_din[] = "/sv.lipatnikov@gmail.com/climate/tv_din";
const char topic_tv_det[] = "/sv.lipatnikov@gmail.com/climate/tv_det";
const char topic_tv_bed[] = "/sv.lipatnikov@gmail.com/climate/tv_bed";
const char topic_tv_bath[] = "/sv.lipatnikov@gmail.com/climate/tv_bath";

const char topic_h_din[] = "/sv.lipatnikov@gmail.com/climate/h_din";
const char topic_h_det[] = "/sv.lipatnikov@gmail.com/climate/h_det";
const char topic_h_bed[] = "/sv.lipatnikov@gmail.com/climate/h_bed";
const char topic_h_bath[] = "/sv.lipatnikov@gmail.com/climate/h_bath";

const char topic_tp_kit[] = "/sv.lipatnikov@gmail.com/climate/tp_kit";
const char topic_tp_din[] = "/sv.lipatnikov@gmail.com/climate/tp_din";
const char topic_tp_det[] = "/sv.lipatnikov@gmail.com/climate/tp_det";
const char topic_tp_bed[] = "/sv.lipatnikov@gmail.com/climate/tp_bed";

const char topic_tp_in[] = "/sv.lipatnikov@gmail.com/climate/tp_in";
const char topic_t_gvs[] = "/sv.lipatnikov@gmail.com/climate/t_gvs";
const char topic_t_weather[] = "/sv.lipatnikov@gmail.com/climate/t_weather";

const char topic_tp_valve_kit[]  = "/sv.lipatnikov@gmail.com/climate/tp_valve_kit";
const char topic_tp_valve_din[]  = "/sv.lipatnikov@gmail.com/climate/tp_valve_din";
const char topic_tp_valve_det[]  = "/sv.lipatnikov@gmail.com/climate/tp_valve_det";
const char topic_tp_valve_bed[]  = "/sv.lipatnikov@gmail.com/climate/tp_valve_bed";
const char topic_tp_valve_bath[] = "/sv.lipatnikov@gmail.com/climate/tp_valve_bath";
const char topic_bat_valve_din[] = "/sv.lipatnikov@gmail.com/climate/bat_valve_din";
const char topic_bat_valve_det[] = "/sv.lipatnikov@gmail.com/climate/bat_valve_det";
const char topic_bat_valve_bed[] = "/sv.lipatnikov@gmail.com/climate/bat_valve_bed";

const char topic_tp_pump[] = "/sv.lipatnikov@gmail.com/climate/tp_pump";
const char topic_gvs_pump[] = "/sv.lipatnikov@gmail.com/climate/gvs_pump";
const char topic_heater[] = "/sv.lipatnikov@gmail.com/climate/heater";
const char topic_boiler[] = "/sv.lipatnikov@gmail.com/climate/boiler";

//флаги
const char topic_energy_save[] = "/sv.lipatnikov@gmail.com/climate/energy_save";
const char topic_dht_validity[] = "/sv.lipatnikov@gmail.com/climate/dht_validity";
const char topic_ds_validity[] = "/sv.lipatnikov@gmail.com/climate/ds_validity";
const char topic_bath_high_humidity[] = "/sv.lipatnikov@gmail.com/climate/bath_high_humidity";
const char topic_arduino_validity[] = "/sv.lipatnikov@gmail.com/climate/arduino_validity";

// топики управления заданными значениями температуры
const char topic_need_tv_din_ctrl[] = "/sv.lipatnikov@gmail.com/climate/need_tv_din_ctrl";
const char topic_need_tv_det_ctrl[] = "/sv.lipatnikov@gmail.com/climate/need_tv_det_ctrl";
const char topic_need_tv_bed_ctrl[] = "/sv.lipatnikov@gmail.com/climate/need_tv_bed_ctrl";
const char topic_need_tp_kit_ctrl[] = "/sv.lipatnikov@gmail.com/climate/need_tp_kit_ctrl";
const char topic_need_tp_din_ctrl[] = "/sv.lipatnikov@gmail.com/climate/need_tp_din_ctrl";
const char topic_need_tp_det_ctrl[] = "/sv.lipatnikov@gmail.com/climate/need_tp_det_ctrl";
const char topic_need_tp_bed_ctrl[] = "/sv.lipatnikov@gmail.com/climate/need_tp_bed_ctrl";
const char topic_need_t_gvs_ctrl[]  = "/sv.lipatnikov@gmail.com/climate/need_t_gvs_ctrl";

// топики состояния заданных значений температуры
const char topic_need_tv_din_state[] = "/sv.lipatnikov@gmail.com/climate/need_tv_din_state";
const char topic_need_tv_det_state[] = "/sv.lipatnikov@gmail.com/climate/need_tv_det_state";
const char topic_need_tv_bed_state[] = "/sv.lipatnikov@gmail.com/climate/need_tv_bed_state";
const char topic_need_tp_kit_state[] = "/sv.lipatnikov@gmail.com/climate/need_tp_kit_state";
const char topic_need_tp_din_state[] = "/sv.lipatnikov@gmail.com/climate/need_tp_din_state";
const char topic_need_tp_det_state[] = "/sv.lipatnikov@gmail.com/climate/need_tp_det_state";
const char topic_need_tp_bed_state[] = "/sv.lipatnikov@gmail.com/climate/need_tp_bed_state";
const char topic_need_t_gvs_state[]  = "/sv.lipatnikov@gmail.com/climate/need_t_gvs_state";


//=========================================================================================
//функции MQTT

// функция подписки на топики !!!
void MQTT_subscribe(void) {
  if (client.connected()){
    client.subscribe(topic_need_tv_din_ctrl); 
    client.subscribe(topic_need_tv_det_ctrl);      
    client.subscribe(topic_need_tv_bed_ctrl);
    
    client.subscribe(topic_need_tp_kit_ctrl);
    client.subscribe(topic_need_tp_din_ctrl);
    client.subscribe(topic_need_tp_det_ctrl);
    client.subscribe(topic_need_tp_bed_ctrl); 
    
    client.subscribe(topic_need_t_gvs_ctrl);
     
    client.subscribe(topic_heaterMode_ctrl); 
    client.subscribe(topic_gvsMode_ctrl); 
    client.subscribe(topic_fanMode_ctrl); 
    client.subscribe(topic_seasonMode_ctrl);
    client.subscribe(topic_emergencyHeater_ctrl);
  }
}

// получение данных от сервера
void mqtt_get(char* topic, byte* payload, unsigned int length) {
 
  char localPayload[length + 1]; // создаем копию полученных данных
  for (int i = 0; i < length; i++) { 
    localPayload[i] = (char)payload[i]; 
  }
  localPayload[length] = 0;
  float value = atof((char*)localPayload); 
  
  // присваиваем переменным значения в зависимости от топика   
  if (strcmp(topic, topic_need_tv_din_ctrl) == 0) {
    need_tv_din = value;  
    MQTT_publish_float(topic_need_tv_din_state, need_tv_din);
    last_change_bat_valve = 0;    // обнуляем время, чтобы после ручных изменений система сразу отреагировала
  }
  else if (strcmp(topic, topic_need_tv_det_ctrl) == 0) {
    need_tv_det = value;  
    MQTT_publish_float(topic_need_tv_det_state, need_tv_det);
    last_change_bat_valve = 0;
  }
  else if (strcmp(topic, topic_need_tv_bed_ctrl) == 0) {
    need_tv_bed = value;
    MQTT_publish_float(topic_need_tv_bed_state, need_tv_bed);
    last_change_bat_valve = 0;
  }
  else if (strcmp(topic, topic_need_tp_kit_ctrl) == 0) {
    need_tp_kit = value;
    MQTT_publish_float(topic_need_tp_kit_state, need_tp_kit);
    last_change_tp_valve = 0;
  }
  else if (strcmp(topic, topic_need_tp_din_ctrl) == 0) {
    need_tp_din = value;
    MQTT_publish_float(topic_need_tp_din_state, need_tp_din);
    last_change_tp_valve = 0; 
  }
  else if (strcmp(topic, topic_need_tp_det_ctrl) == 0) {
    need_tp_det = value;
    MQTT_publish_float(topic_need_tp_det_state, need_tp_det);
    last_change_tp_valve = 0;
  }
  else if (strcmp(topic, topic_need_tp_bed_ctrl) == 0) {
    need_tp_bed = value;
    MQTT_publish_float(topic_need_tp_bed_state, need_tp_bed);
    last_change_tp_valve = 0;
  }
  else if (strcmp(topic, topic_need_t_gvs_ctrl) == 0) {
    need_gvs_temp = value; 
    MQTT_publish_float(topic_need_t_gvs_state, need_gvs_temp);
    gvs_pump = false;   // обнуляем переменную, чтобы обнулить состояние гистерезиса
  }
  else if (strcmp(topic, topic_heaterMode_ctrl) == 0) {
    int ivalue = 0; sscanf(localPayload, "%d", &ivalue);
    heaterMode = (byte)ivalue; 
    MQTT_publish_int(topic_heaterMode_state, heaterMode);    
  }
  else if (strcmp(topic, topic_gvsMode_ctrl) == 0) {
    int ivalue = 0; sscanf(localPayload, "%d", &ivalue);
    gvsMode = (byte)ivalue; 
    MQTT_publish_int(topic_gvsMode_state, gvsMode);    
  }
  else if (strcmp(topic, topic_fanMode_ctrl) == 0) {
    int ivalue = 0; sscanf(localPayload, "%d", &ivalue);
    fanMode = (byte)ivalue; 
    MQTT_publish_int(topic_fanMode_state, fanMode);    
  }
  else if (strcmp(topic, topic_seasonMode_ctrl) == 0) {
    int ivalue = 0; sscanf(localPayload, "%d", &ivalue);
    seasonMode = (byte)ivalue; 
    MQTT_publish_int(topic_seasonMode_state, seasonMode);    
  }
  else if (strcmp(topic, topic_emergencyHeater_ctrl) == 0) {
    int ivalue = 0; sscanf(localPayload, "%d", &ivalue);
    emergencyHeater = (bool)ivalue; 
    MQTT_publish_int(topic_emergencyHeater_state, emergencyHeater);    
  }
}

//==================================================================================
// периодическая отправка данных на сервер для синхронизации
void Send_MQTT_data(void)
{
  // DHT temp
  MQTT_publish_float(topic_tv_din, _dht_din.midT);
  MQTT_publish_float(topic_tv_det, _dht_det.midT);
  MQTT_publish_float(topic_tv_bed, _dht_bed.midT);
  MQTT_publish_float(topic_tv_bath, _dht_bath.midT);

  // DHT humidity
  MQTT_publish_float(topic_h_din, _dht_din.midH);
  MQTT_publish_float(topic_h_det, _dht_det.midH);
  MQTT_publish_float(topic_h_bed, _dht_bed.midH);
  MQTT_publish_float(topic_h_bath, _dht_bath.midH);  

  // DS temp
  MQTT_publish_float(topic_tp_kit, _ds_kit.mid);
  MQTT_publish_float(topic_tp_din, _ds_din.mid);
  MQTT_publish_float(topic_tp_det, _ds_det.mid);
  MQTT_publish_float(topic_tp_bed, _ds_bed.mid);

  MQTT_publish_float(topic_tp_in, _ds_tpin.mid);
  MQTT_publish_float(topic_t_gvs, _ds_gvs.mid);
  MQTT_publish_float(topic_t_weather, _ds_weather.mid);

  // Target temp
  MQTT_publish_float(topic_need_tv_din_state, need_tv_din);
  MQTT_publish_float(topic_need_tv_det_state, need_tv_det);
  MQTT_publish_float(topic_need_tv_bed_state, need_tv_bed);
  
  MQTT_publish_float(topic_need_tp_kit_state, need_tp_kit);
  MQTT_publish_float(topic_need_tp_din_state, need_tp_din);
  MQTT_publish_float(topic_need_tp_det_state, need_tp_det);
  MQTT_publish_float(topic_need_tp_bed_state, need_tp_bed);

  MQTT_publish_float(topic_need_t_gvs_state, need_gvs_temp);

  // Valve state
  MQTT_publish_int(topic_tp_valve_kit, tp_valve_kit); 
  MQTT_publish_int(topic_tp_valve_din, tp_valve_din);
  MQTT_publish_int(topic_tp_valve_det, tp_valve_det);
  MQTT_publish_int(topic_tp_valve_bed, tp_valve_bed);
  MQTT_publish_int(topic_tp_valve_bath, tp_valve_bath);
  MQTT_publish_int(topic_bat_valve_din, bat_valve_din);
  MQTT_publish_int(topic_bat_valve_det, bat_valve_det);
  MQTT_publish_int(topic_bat_valve_bed, bat_valve_bed);
  MQTT_publish_int(topic_tp_pump, tp_pump);
  MQTT_publish_int(topic_gvs_pump, gvs_pump);
  MQTT_publish_int(topic_heater, relay_heater);
  MQTT_publish_int(topic_boiler, relay_boiler);
  
  // флаги
  MQTT_publish_int(topic_bath_high_humidity, bath_high_humidity_flag);
  MQTT_publish_int(topic_energy_save, energy_save_flag);
  MQTT_publish_int(topic_dht_validity, dht_validity_flag);
  MQTT_publish_int(topic_ds_validity, ds_validity_flag);  
  MQTT_publish_int(topic_arduino_validity, arduino_validity_flag);  
  
  // Func Mode
  MQTT_publish_int(topic_heaterMode_state, heaterMode);
  MQTT_publish_int(topic_gvsMode_state, gvsMode);
  MQTT_publish_int(topic_fanMode_state, fanMode); 
  MQTT_publish_int(topic_seasonMode_state, seasonMode);
  MQTT_publish_int(topic_emergencyHeater_state, emergencyHeater);
}
