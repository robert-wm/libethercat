/**
 * \file common.h
 *
 * \author Robert Burger <robert.burger@dlr.de>
 *
 * \date 23 Nov 2016
 *
 * \brief ethercat master common stuff
 *
 * 
 */

/*
 * This file is part of libethercat.
 *
 * libethercat is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * 
 * libethercat is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with libethercat (LICENSE.LGPL-V3); if not, write 
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth 
 * Floor, Boston, MA  02110-1301, USA.
 * 
 * Please note that the use of the EtherCAT technology, the EtherCAT 
 * brand name and the EtherCAT logo is only permitted if the property 
 * rights of Beckhoff Automation GmbH are observed. For further 
 * information please contact Beckhoff Automation GmbH & Co. KG, 
 * Hülshorstweg 20, D-33415 Verl, Germany (www.beckhoff.com) or the 
 * EtherCAT Technology Group, Ostendstraße 196, D-90482 Nuremberg, 
 * Germany (ETG, www.ethercat.org).
 *
 */

#ifndef LIBETHERCAT_COMMON_H
#define LIBETHERCAT_COMMON_H

#include <libethercat/config.h>

#include <libosal/types.h>

#include <stdint.h>

#ifdef LIBETHERCAT_MAX_SLAVES
#define LEC_MAX_SLAVES                      ( (osal_size_t)LIBETHERCAT_MAX_SLAVES )
#else
#define LEC_MAX_SLAVES                      (      256u)
#endif

#ifdef LIBETHERCAT_MAX_GROUPS
#define LEC_MAX_GROUPS                      ( (osal_size_t)LIBETHERCAT_MAX_GROUPS )
#else
#define LEC_MAX_GROUPS                      (        8u)
#endif

#ifdef LIBETHERCAT_MAX_PDLEN
#define LEC_MAX_PDLEN                       ( (osal_size_t)LIBETHERCAT_MAX_PDLEN )
#else
#define LEC_MAX_PDLEN                       (2u * 1518u)
#endif

#ifdef LIBETHERCAT_MAX_MBX_ENTRIES
#define LEC_MAX_MBX_ENTRIES                 ( (osal_size_t)LIBETHERCAT_MAX_MBX_ENTRIES )
#else
#define LEC_MAX_MBX_ENTRIES                 (       16u)
#endif

#ifdef LIBETHERCAT_MAX_INIT_CMD_DATA
#define LEC_MAX_INIT_CMD_DATA               ( (osal_size_t)LIBETHERCAT_MAX_INIT_CMD_DATA )
#else
#define LEC_MAX_INIT_CMD_DATA               (     2048u)
#endif

#ifdef LIBETHERCAT_MAX_SLAVE_FMMU
#define LEC_MAX_SLAVE_FMMU                  ( (osal_size_t)LIBETHERCAT_MAX_SLAVE_FMMU )
#else
#define LEC_MAX_SLAVE_FMMU                  (        8u)
#endif

#ifdef LIBETHERCAT_MAX_SLAVE_SM
#define LEC_MAX_SLAVE_SM                    ( (osal_size_t)LIBETHERCAT_MAX_SLAVE_SM )
#else
#define LEC_MAX_SLAVE_SM                    (        8u)
#endif

#ifdef LIBETHERCAT_MAX_DATAGRAMS                   
#define LEC_MAX_DATAGRAMS                   ( (osal_size_t)LIBETHERCAT_MAX_DATAGRAMS )
#else
#define LEC_MAX_DATAGRAMS                   (      100u)
#endif 

#ifdef LIBETHERCAT_MAX_EEPROM_CAT_SM
#define LEC_MAX_EEPROM_CAT_SM               ( (osal_size_t)LIBETHERCAT_MAX_EEPROM_CAT_SM )
#else
#define LEC_MAX_EEPROM_CAT_SM               (LEC_MAX_SLAVE_SM)
#endif

#ifdef LIBETHERCAT_MAX_EEPROM_CAT_FMMU
#define LEC_MAX_EEPROM_CAT_FMMU             ( (osal_size_t)LIBETHERCAT_MAX_EEPROM_CAT_FMMU )
#else
#define LEC_MAX_EEPROM_CAT_FMMU             (LEC_MAX_SLAVE_FMMU)
#endif

#ifdef LIBETHERCAT_MAX_EEPROM_CAT_PDO
#define LEC_MAX_EEPROM_CAT_PDO              ( (osal_size_t)LIBETHERCAT_MAX_EEPROM_CAT_PDO )
#else
#define LEC_MAX_EEPROM_CAT_PDO              (      128u)
#endif

#ifdef LIBETHERCAT_MAX_EEPROM_CAT_PDO_ENTRIES
#define LEC_MAX_EEPROM_CAT_PDO_ENTRIES      ( (osal_size_t)LIBETHERCAT_MAX_EEPROM_CAT_PDO_ENTRIES )
#else
#define LEC_MAX_EEPROM_CAT_PDO_ENTRIES      (       32u)
#endif

#ifdef LIBETHERCAT_MAX_EEPROM_CAT_STRINGS      
#define LEC_MAX_EEPROM_CAT_STRINGS          ( (osal_size_t)LIBETHERCAT_MAX_EEPROM_CAT_STRINGS )
#else
#define LEC_MAX_EEPROM_CAT_STRINGS          (      128u)
#endif

#ifdef LIBETHERCAT_MAX_EEPROM_CAT_DC      
#define LEC_MAX_EEPROM_CAT_DC               ( (osal_size_t)LIBETHERCAT_MAX_EEPROM_CAT_DC )
#else
#define LEC_MAX_EEPROM_CAT_DC               (        8u)
#endif

#ifdef LIBETHERCAT_MAX_STRING_LEN
#define LEC_MAX_STRING_LEN                  ( (osal_size_t)LIBETHERCAT_MAX_STRING_LEN )
#else
#define LEC_MAX_STRING_LEN                  (      128u)
#endif

#ifdef LIBETHERCAT_MAX_DATA
#define LEC_MAX_DATA                        ( (osal_size_t)LIBETHERCAT_MAX_DATA )
#else
#define LEC_MAX_DATA                        (     4096u)
#endif

#ifdef LIBETHERCAT_MAX_DS402_SUBDEVS
#define LEC_MAX_DS402_SUBDEVS               ( (osal_size_t)LIBETHERCAT_MAX_DS402_SUBDEVS )
#else
#define LEC_MAX_DS402_SUBDEVS               (        4u)
#endif

#ifdef LIBETHERCAT_MAX_COE_EMERGENCIES
#define LEC_MAX_COE_EMERGENCIES             ( (osal_size_t)LIBETHERCAT_MAX_COE_EMERGENCIES )
#else
#define LEC_MAX_COE_EMERGENCIES             (       10u)
#endif

#ifdef LIBETHERCAT_MAX_COE_EMERGENCY_MSG_LEN
#define LEC_MAX_COE_EMERGENCY_MSG_LEN       ( (osal_size_t)LIBETHERCAT_MAX_COE_EMERGENCY_MSG_LEN )
#else
#define LEC_MAX_COE_EMERGENCY_MSG_LEN       (       32u)
#endif

#define PACKED __attribute__((__packed__))

#ifndef min
#define min(a, b)  ((a) < (b) ? (a) : (b))
#endif

typedef osal_uint8_t ec_data_t[LEC_MAX_DATA]; /* variants for easy data access */

//! process data structure
typedef struct ec_pd {
    osal_uint8_t *pd;        //!< pointer to process data
    osal_size_t len;         //!< process data length
} ec_pd_t;

typedef osal_uint16_t ec_state_t;
#define EC_STATE_UNKNOWN     ((osal_uint16_t)(0x0000u))       //!< \brief unknown state
#define EC_STATE_INIT        ((osal_uint16_t)(0x0001u))       //!< \brief EtherCAT INIT state
#define EC_STATE_PREOP       ((osal_uint16_t)(0x0002u))       //!< \brief EtherCAT PREOP state
#define EC_STATE_BOOT        ((osal_uint16_t)(0x0003u))       //!< \brief EtherCAT BOOT state
#define EC_STATE_SAFEOP      ((osal_uint16_t)(0x0004u))       //!< \brief EtherCAT SAFEOP state
#define EC_STATE_OP          ((osal_uint16_t)(0x0008u))       //!< \brief EtherCAT OP state
#define EC_STATE_MASK        ((osal_uint16_t)(0x000Fu))       //!< \brief EtherCAT state mask
#define EC_STATE_ERROR       ((osal_uint16_t)(0x0010u))       //!< \brief EtherCAT ERROR
#define EC_STATE_RESET       ((osal_uint16_t)(0x0010u))       //!< \brief EtherCAT ERROR reset

#endif // LIBETHERCAT_COMMON_H

