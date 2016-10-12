#pragma once

#ifndef __ENUMDEFITNITIONS__

#define __ENUMDEFITNITIONS__

enum PacketType
{
    Request     = 0,
    Response    = 1,
    Push        = 2,
};

enum TargetType
{
    Building    = 0,
    Floor       = 1,
    Room        = 2,
    Device      = 3,
    Paired      = 4,
};

enum RequestType
{
    Enumeration = 0,
    Get         = 1,
    Set         = 2,
    Execute     = 3,
};

#endif