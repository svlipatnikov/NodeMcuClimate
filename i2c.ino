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
