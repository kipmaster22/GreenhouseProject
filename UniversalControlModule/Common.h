#ifndef _COMMON_H
#define _COMMON_H
//----------------------------------------------------------------------------------------------------------------
#define UNUSED(expr) do { (void)(expr); } while (0)
//----------------------------------------------------------------------------------------------------------------
//Структура передаваемая мастеру и обратно
//----------------------------------------------------------------------------------------------------------------
enum {RS485FromMaster = 1, RS485FromSlave = 2};
enum 
{
  RS485ControllerStatePacket = 1, 
  RS485SensorDataPacket = 2, 
  RS485WindowsPositionPacket = 3,
  RS485RequestCommandsPacket = 4,
  RS485CommandsToExecuteReceipt = 5
};
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
  byte header1;
  byte header2;

  byte direction; // направление: 1 - от меги, 2 - от слейва
  byte type; // тип: 1 - пакет исполнительного модуля, 2 - пакет модуля с датчиками

  byte data[23]; // N байт данных, для исполнительного модуля в этих данных содержится состояние контроллера
  // для модуля с датчиками: первый байт - тип датчика, 2 байт - его индекс в системе. В обратку модуль с датчиками должен заполнить показания (4 байта следом за индексом 
  // датчика в системе и отправить пакет назад, выставив direction и type.

  byte tail1;
  byte tail2;
  byte crc8;
  
} RS485Packet; // пакет, гоняющийся по RS-485 туда/сюда (30 байт)
//----------------------------------------------------------------------------------------------------------------
enum // команды с модуля управления
{
  emCommandNone = 0,          // нет команды
  emCommandOpenWindows,       // открыть все окна
  emCommandCloseWindows,      // закрыть все осна
  emCommandOpenWindow,        // открыть определённое окно
  emCommandCloseWindow,       // закрыть определённое окно
  emCommandWaterOn,           // включить волив
  emCommandWaterOff,          // выключить полив
  emCommandWaterChannelOn,    // включить канал полива
  emCommandWaterChannelOff,   // выключить канал полива
  emCommandLightOn,           // включить досветку
  emCommandLigntOff,          // выключить досветку
  emCommandPinOn,             // включить пин
  emCommandPinOff,            // выключить пин
};
//----------------------------------------------------------------------------------------------------------------
typedef struct
{ 
  byte whichCommand;
  byte param1;
  byte param2;
  
} CommandToExecute;
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
  byte pin;
  byte whichCommand;
  byte param1;
  byte param2;
  
} BUTTON;
//----------------------------------------------------------------------------------------------------------------
typedef struct
{
  byte moduleID; // ID модуля, от которого пришла команда
  CommandToExecute commands[7]; // 21 байт
  byte reserved; // добитие до 23 байт
  
} CommandsToExecutePacket; // пакет с командами на выполнение
//----------------------------------------------------------------------------------------------------------------
#endif