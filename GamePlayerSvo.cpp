#include "GamePlayerSvo.h"
long GamePlayerSvo::GetAddress()
{
    return (long)this;
}

GamePlayerSvo::GamePlayerSvo() 
{
    Id = GetAddress();
}
