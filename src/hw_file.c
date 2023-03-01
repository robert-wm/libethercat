/**
 * \file hw_file_ll.c
 *
 * \author Robert Burger <robert.burger@dlr.de>
 *
 * \date 24 Nov 2016
 *
 * \brief hardware access functions
 *
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
 * If not, see <www.gnu.org/licenses/>.
 */

#include <libethercat/config.h>
#include <libethercat/hw.h>
#include <libethercat/ec.h>
#include <libethercat/idx.h>
#include <libethercat/error_codes.h>

#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <inttypes.h>

#if LIBETHERCAT_HAVE_UNISTD_H == 1
#include <unistd.h>
#endif

#if LIBETHERCAT_HAVE_NETINET_IN_H == 1
#include <netinet/in.h>
#endif

#if LIBETHERCAT_HAVE_WINSOCK_H == 1
#include <winsock.h>
#endif

//! Opens EtherCAT hw device.
/*!
 * \param[in]   phw         Pointer to hw handle. 
 * \param[in]   devname     Null-terminated string to EtherCAT hw device name.
 *
 * \return 0 or negative error code
 */
int hw_device_open(hw_t *phw, const osal_char_t *devname) {
    int ret = EC_OK;
    static const osal_uint8_t mac_dest[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    static const osal_uint8_t mac_src[] = {0x00, 0x30, 0x64, 0x0f, 0x83, 0x35};

    /* we use file link layer device driver */
    // cppcheck-suppress misra-c2012-7.1
    phw->sockfd = open(devname, O_RDWR, 0644);
    if (phw->sockfd <= 0) {
        ec_log(1, "HW_OPEN", "error opening %s: %s\n", devname, strerror(errno));
    } else {
        phw->mtu_size = 1480;
    }
    
    (void)memcpy(((ec_frame_t *)phw->send_frame)->mac_dest, mac_dest, 6);
    (void)memcpy(((ec_frame_t *)phw->send_frame)->mac_src, mac_src, 6);

    return ret;
}

//! Receive a frame from an EtherCAT hw device.
/*!
 * \param[in]   phw         Pointer to hw handle. 
 * \param[in]   frame       Pointer to frame buffer.
 *
 * \return 0 or negative error code
 */
int hw_device_recv(hw_t *phw) {
    // cppcheck-suppress misra-c2012-11.3
    ec_frame_t *pframe = (ec_frame_t *) &phw->recv_frame;

    // using tradional recv function
    osal_ssize_t bytesrx = read(phw->sockfd, pframe, ETH_FRAME_LEN);

    if (bytesrx > 0) {
        hw_process_rx_frame(phw, pframe);
    }

    return EC_OK;
}

//! Get a free tx buffer from underlying hw device.
/*!
 * \param[in]   phw         Pointer to hw handle. 
 * \param[in]   ppframe     Pointer to return frame buffer pointer.
 *
 * \return 0 or negative error code
 */
int hw_device_get_tx_buffer(hw_t *phw, ec_frame_t **ppframe) {
    assert(phw != NULL);
    assert(ppframe != NULL);

    int ret = EC_OK;
    ec_frame_t *pframe = NULL;
    
    // cppcheck-suppress misra-c2012-11.3
    pframe = (ec_frame_t *)phw->send_frame;

    // reset length to send new frame
    pframe->ethertype = htons(ETH_P_ECAT);
    pframe->type = 0x01;
    pframe->len = sizeof(ec_frame_t);

    *ppframe = pframe;

    return ret;
}

//! Send a frame from an EtherCAT hw device.
/*!
 * \param[in]   phw         Pointer to hw handle. 
 * \param[in]   pframe      Pointer to frame buffer.
 *
 * \return 0 or negative error code
 */
int hw_device_send(hw_t *phw, ec_frame_t *pframe) {
    assert(phw != NULL);
    assert(pframe != NULL);

    int ret = EC_OK;

    // no more datagrams need to be sent or no more space in frame
    osal_ssize_t bytestx = write(phw->sockfd, pframe, pframe->len);

    if ((osal_ssize_t)pframe->len != bytestx) {
        ec_log(1, "HW_TX", "got only %" PRId64 " bytes out of %d bytes "
                "through.\n", bytestx, pframe->len);

        if (bytestx == -1) {
            ec_log(1, "HW_TX", "error: %s\n", strerror(errno));
        }

        ret = EC_ERROR_HW_SEND;
    }

    return ret;
}

