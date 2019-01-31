#ifndef HELPER_H
#define HELPER_H

#include<ctime>
#include<string>
#include<sstream>
#include<fstream>
namespace Helper
   {


   template <class T >

   std::string ToString(const T  &) ;

   struct DateTime
   {
int  D ,m, Y ,H , S , M ;
       DateTime()  //constructor
    {
         time_t ms  ;
         time(&ms) ;

         struct tm *info= localtime(&ms) ;

       D=info->tm_mday ;
       m =info->tm_mon+1 ;
       Y=1900+ info->tm_year ;
       H=info->tm_hour  ;
       M=info->tm_min ;
       S=info->tm_sec ;

    }
       DateTime(int D , int m , int Y , int H  , int M , int S ): D(D), m(m), Y(Y) ,H(H) ,M(M),S(S) {}
       DateTime(int D , int   m, int Y): D(D) , m(m) , Y(Y),H(0) ,M(0) ,S(0){}
       DateTime Now()const
      {
        return DateTime() ;
      }
//int  D ,m, Y ,H , S , M ;

std:: string GetDateString()
{
    return std::string(D<10 ? "0": "") +ToString(D) +
    std::string(m<10 ? ".0":".")+ ToString(m) + "."+
    ToString(Y) ;

}
std ::string GetTimeString ( const std:: string sep = ":")
{
    return std::string(H<10 ? "0" :"") + ToString(H) +sep +
    std::string(M<10 ? "0" : "")+ToString(M) + sep+
    std::string(S<10 ? "0": "") +ToString(S)  ;
}
std ::string GetDateTimeString(const std:: string sep=":")
{

    return GetDateString() + " " + GetTimeString(sep)  ;
}

   };

template <class T >

std::string ToString(const T  &s)
   {
     std::ostringstream   o  ;
       o<<s ;
       return o.str() ;
   }


   void WriteAppLog(const std::string &s)
   {
       std::ofstream file ;
       file.open("AppLog.txt" , std::ios::app) ;
       file<<"[" << Helper::DateTime().GetDateTimeString()<<"]"<<"\n"
       <<s<<std::endl<<"\n" ;
       file.close() ;
   }



   }

#endif // HELPER_H
