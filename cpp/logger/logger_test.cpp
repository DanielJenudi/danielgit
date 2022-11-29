/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Author: Daniel Jenudi
- Date: 20/09/22
- Reviwer: Hagar Gur-Arie
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "logger.hpp"

using namespace ilrd;

int main()
{
    Logger *log = Singleton<Logger>::GetInstance();

    log->Log("I NEED VACATION");

    log->SetPath("./diary.txt");

    log->Log("I NEED VACATION");
    log->Log("I NEED VACATION");
    log->Log("I NEED VACATION");

    return 0;
}