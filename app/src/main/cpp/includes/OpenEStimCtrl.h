/*
OpenEStimCtrl
Copyright (C) 2023 Personal/SoundReload

This program is free software: you can redistribute it and/or modify
        it under the terms of the GNU Affero General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
        along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef OPENESTIMCTRL_OPENESTIMCTRL_H
#define OPENESTIMCTRL_OPENESTIMCTRL_H

#include <cstdint>
#include <cstring>

#ifdef __GNUC__
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif


#if BYTE_ORDER == __ORDER_BIG_ENDIAN__
PACK(class be_uint16_t {
public:
    be_uint16_t() : be_val_(0) {
    }
    // Transparently cast from uint16_t
    explicit be_uint16_t(const uint16_t &val) : be_val_(val) {
    }
    // Transparently cast to uint16_t
    explicit operator uint16_t() const {
        return be_val_;
    }
private:
    uint16_t be_val_;
});
#else
#ifdef _WINDOWS
#include <WinSock2.h>
#else
#include <arpa/inet.h>
#endif
#include <cstdint>
PACK(class be_uint16_t {
public:
        be_uint16_t() : be_val_(0) {
        }
        // Transparently cast from uint16_t
        explicit be_uint16_t(const uint16_t &val) : be_val_(htons(val)) {
        }
        // Transparently cast to uint16_t
        explicit operator uint16_t() const {
                return ntohs(be_val_);
        }
private:
        uint16_t be_val_;
});
#endif

typedef void (*SendDataCallback)(const char* serviceUuid, const char* characteristicUuid, uint8_t* data, int length, void* userData);

#endif //OPENESTIMCTRL_OPENESTIMCTRL_H
