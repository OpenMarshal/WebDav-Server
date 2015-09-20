#include "Datagram.h"

Datagram::Datagram()
    : homemadeData(false),
    addr()
{ }

Datagram::Datagram(char* data, uint maxLen)
    : homemadeData(false),
    addr(),
    data(data),
    maxLen(maxLen),
    len(0)
{ }

Datagram::Datagram(char* data, sint len, uint maxLen)
    : homemadeData(false),
    addr(),
    data(data),
    len(len),
    maxLen(maxLen)
{ }