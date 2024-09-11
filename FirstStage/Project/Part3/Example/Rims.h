 #ifndef Rims_h
 #define Rims_h
 
 // -------------------------- OPTIONAL EXTENSIONS ------------------------------
 #define WITH_W25QFLASH                     
 // -----------------------------------------------------------------------------
 
 #define SAMPLETIME 1000
 #define SSRWINDOWSIZE 5000
 
 #define DEFAULTSP 68
 #define DEFAULTTIME 5400
 
 #define PROBE_RTD 0
 #define PROBE_THERM 1
 #define PROBE_CUSTOM 2
 
 #define DEFAULTPROBETYPE PROBE_RTD
 #define DEFAULTPROBE0 -247.1087
 #define DEFAULTPROBE1 2.23511
 #define DEFAULTPROBE2 0.001659
 #define DEFAULTPROBE3 0.0
 #define DEFAULTRES1 124.5
 
 #define RTDAMPGAIN 5.0
 #define RTDAMPREF 2.5
 #define TEMPSUPPLY 5.0
 #define ADCFILTERTAU 30.0
 
 #define MAXTEMPVAR 1.0
 #define SCREENSWITCHTIME 10000
 
 #define NOTIMELIMIT 4E9
 
 #define DEFAULTFLOWLOWBOUND 3.0
 #define DEFAULTFLOWUPBOUND 5.0
 
 #define ADDRSESSIONTABLE    0x000000 // 1st sector
 #define ADDRDATACOUNT       0x001000 // 2nd sector
 #define ADDRBREWDATA        0x002000 // 3rd sector
 #define BYTESPERDATA        20
 #define MEMSIZEBYTES        1048576
 
 #include "Arduino.h"
 #include "utility/UIRims.h"
 #include "utility/PID_v1mod.h"
 #include "utility/w25qflash.h"
 
 
 void isrFlow();
 extern volatile unsigned long g_flowLastTime;
 extern volatile unsigned long g_flowCurTime;
 
 class Rims
 {
     friend class RimsIdent;
     friend class RimsTuner;
     
 public:
     Rims(UIRims* uiRims, byte analogPinPV, byte ssrPin, 
          double* currentTemp, double* ssrControl, double* settedTemp);
 
     void setTempProbe(byte probeType, float probeCoefs[],float res1);
     void setPinLED(byte pinLED);
     void setFlowSensor(byte pinFlow, float flowFactor, 
                        float lowBound = DEFAULTFLOWLOWBOUND, 
                        float upBound = DEFAULTFLOWUPBOUND,
                        float criticalFlow = DEFAULTFLOWLOWBOUND);
     void setHeaterPowerDetect(char pinHeaterVolt);
     
     void setTuningPID(float Kp, float Ki, float Kd, float tauFilter,
                       int mashWaterQty = -1);
 #ifdef WITH_W25QFLASH
     void setMemCSPin(byte csPin);
     void checkMemAccessMode();
 #endif
     
     void run();
     
     float getTempPV();
     float getFlow();
     bool getHeaterVoltage();
     
     void stopHeating(bool state);
     
 protected:
     
     virtual void _initialize();
     void         _initSession();
     void         _endSession();
 
     virtual void _iterate();
     void         _refreshTimer();
     void         _refreshDisplay();
     void         _refreshSSR();
     void         _serialPrintBrewData();
 
 #ifdef WITH_W25QFLASH
     unsigned int  _memCountSessions();
     unsigned long _memCountSessionData();
     void          _memInitSP();
     void          _memAddBrewData();
     void          _memDumpBrewData();
     void          _memFreeSpace();
     void          _memClearAll();
 #endif
     
 private:
     
     // ===GENERAL===
     UIRims* _ui;
     PIDmod _myPID;
     byte _analogPinPV;
     byte _pinCV;
     byte _pinLED;
     char _pinHeaterVolt;
 #ifdef WITH_W25QFLASH
     W25QFlash _myMem;
 #endif
     
     // ===STATE DATAS===
     bool _rimsInitialized;
     bool _noPower;
     bool _buzzerState;
     bool _memConnected;
     
     // ===MULTIPLE PIDs===
     byte _pidQty;
     byte _currentPID;
     int _mashWaterValues[4];
     
     // ===TEMP PROBE===
     byte  _probeType;
     float _probeCoefs[4];
     float _res1;
     float _filterCstADC;
     float _lastTempADC;
     
     // ===PID I/O===
     double* _setPointPtr;
     double* _processValPtr;
     double* _controlValPtr; 
     
     // ===PID PARAMS===
     float _kps[4];
     float _kis[4];
     float _kds[4];
     float _tauFilter[4];
     
     // ===TIMER===
     unsigned long _currentTime;             
     unsigned long _settedTime;              
     unsigned long _rimsStartTime;           
     unsigned long _windowStartTime;         
     unsigned long _runningTime;             
     unsigned long _timerRemaining;          
     unsigned long _totalStoppedTime;        
     unsigned long _timerStopTime;           
     unsigned long _timerStartTime;          
     unsigned long _lastScreenSwitchTime;    
     unsigned long _lastSampleTime;          
     bool _sumStoppedTime;
     bool _sessionFinished;
     
     // ===FLOW SENSOR===
     float _flowFactor; 
     float _flow;
     float _criticalFlow;
     
 #ifdef WITH_W25QFLASH
     // ===FLASH MEM===
     unsigned long _memNextAddr;
     unsigned long _memDataQty;
 #endif
     
 };
 #endif