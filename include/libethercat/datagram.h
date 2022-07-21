/**
 * \file datagram.h
 *
 * \author Robert Burger <robert.burger@dlr.de>
 *
 * \date 24 Nov 2016
 *
 * \brief ethercat datagram
 *
 * These are EtherCAT datagram specific configuration functions.
 */

/*
 * This file is part of libethercat.
 *
 * libethercat is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libethercat is distributed in the hope that 
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libethercat
 * If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBETHERCAT_DATAGRAM_H
#define LIBETHERCAT_DATAGRAM_H

#include <stdint.h>
#include <stdlib.h>
#include "libethercat/common.h"

#define EC_WKC_SIZE     2u

typedef struct __attribute__((__packed__)) ec_frame {
    uint8_t mac_dest[6];        //!< destination mac address 
    uint8_t mac_src[6];         //!< source mac addres
    uint16_t ethertype;         //!< ethertype, should be 0x88A4
    
    uint16_t len        : 11;   //!< frame length
    uint16_t reserved   : 1;    //!< not used
    uint16_t type       : 4;    //!< protocol type, 4 - EtherCAT command
} ec_frame_t;

#define ec_frame_hdr_length     (sizeof(ec_frame_t))
#define ec_frame_length(f)      ((f)->len)
#define ec_frame_end(pframe)    ((uint8_t *)(pframe) + (pframe)->len)

typedef struct __attribute__((__packed__)) ec_datagram {
    uint8_t cmd;                //!< ethercat command
    uint8_t idx;                //!< datagram index
    //union {
    //    struct {
    //        uint16_t adp;       //!< auto inc/configured address
    //        uint16_t ado;       //!< physical mem address
    //    };
        uint32_t adr;           //!< logical address
    //};
    uint16_t len        : 11;   //!< datagram length
    uint16_t reserved   : 4;    //!< not used
    uint16_t next       : 1;    //!< 0 - last datagram, 1 - more follow
    uint16_t irq;               //!< reserved for future use
} ec_datagram_t;

#define ec_datagram_hdr_length  (sizeof(ec_datagram_t))
#define ec_datagram_length(pdg) \
    (ec_datagram_hdr_length + (pdg)->len + EC_WKC_SIZE)

#ifdef __cplusplus
extern "C" {
#endif

//! Initialize empty frame.
/*/
 * \param[in,out]   frame   Pointer to frame.
 *
 * \return EC_OK
 */
int ec_frame_init(ec_frame_t *frame);

//! Add datagram at the end of frame.
/*/
 * \param[in,out]   frame         Pointer to frame.
 * \param[in]       cmd           Ethercat command.
 * \param[in]       idx           Ethercat frame index.
 * \param[in]       adp           Auto inc/configured address.
 * \param[in]       ado           Physical mem address.
 * \param[in]       payload       Frame payload.
 * \param[in]       payload_len   Length of payload.
 */
void ec_frame_add_datagram_phys(ec_frame_t *frame, uint8_t cmd, uint8_t idx, 
        uint16_t adp, uint16_t ado, uint8_t *payload, size_t payload_len);

//! Add datagram at the end of frame.
/*/
 * \param[in,out]   frame         Pointer to frame.
 * \param[in]       cmd           Ethercat command.
 * \param[in]       idx           Ethercat frame index.
 * \param[in]       adr           Logical address.
 * \param[in]       payload       Frame payload.
 * \param[in]       payload_len   Length of payload.
 */
void ec_frame_add_datagram_log(ec_frame_t *frame, uint8_t cmd, uint8_t idx, 
        uint32_t adr, uint8_t *payload, size_t payload_len);

static inline ec_datagram_t *ec_datagram_cast(uint8_t *p) {
    // cppcheck-suppress misra-c2012-11.3
    return ((ec_datagram_t *)(&((uint8_t *)(p))[0]));
}

static inline void ec_datagram_mark_next(ec_datagram_t *pdg) {
    // cppcheck-suppress misra-c2012-11.3
    ((ec_datagram_t *)(pdg))->next = 1;
}

static inline ec_datagram_t *ec_datagram_first(ec_frame_t *pf) {
    // cppcheck-suppress misra-c2012-11.3
    return (ec_datagram_t *)(&(((uint8_t *)(pf))[sizeof(ec_frame_t)]));
}

static inline ec_datagram_t *ec_datagram_next(ec_datagram_t *pdg) {
    // cppcheck-suppress misra-c2012-11.3
    return (ec_datagram_t *)(&(((uint8_t *)(pdg))[ec_datagram_length((pdg))]));
}

static inline uint8_t *ec_datagram_payload(ec_datagram_t *pdg) {
    // cppcheck-suppress misra-c2012-11.3
    return (&(((uint8_t *)(pdg))[sizeof(ec_datagram_t)]));
}

static inline uint16_t ec_datagram_wkc(ec_datagram_t *pdg) {
    // cppcheck-suppress misra-c2012-11.3
    return (*(uint16_t *)(&(((uint8_t *)pdg)[ec_datagram_length(pdg) - 2u])));
}

#ifdef __cplusplus
}
#endif

#endif /* LIBETHERCAT_DATAGRAM_H */

