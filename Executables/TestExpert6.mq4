//+------------------------------------------------------------------+
//|                                                  TestExpert6.mq4 |
//|                                               Vano101 Freelancer |
//|                                            http://no.link.please |
//+------------------------------------------------------------------+
#property copyright "Vano101 Freelancer"
#property link      "http://no.link.please"
#property version   "1.00"
#property strict

#import "Prediction.dll"
int GetPrediction(string username, string password);
#import

//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+
int OnInit()
  {
//---
   int result = GetPrediction("kmorton", "test");
//---
   return(INIT_SUCCEEDED);
  }
//+------------------------------------------------------------------+
//| Expert deinitialization function                                 |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
  {
//---
   
  }
//+------------------------------------------------------------------+
//| Expert tick function                                             |
//+------------------------------------------------------------------+
void OnTick()
  {
//---
   
  }
//+------------------------------------------------------------------+
