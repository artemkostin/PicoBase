/**
 * @file devinfo.c
 * @author Artem Kostin (artem.1.kostin@gmail.com)
 * @brief SmartGardenProject pot controller DevInfo implementation.
 * @version 0.1
 * @date 2021-09-24
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "devinfo.h"

static const devinfo_t devinfo = {
    .version_major = DEVINFO_VERSION_MAJOR,
    .version_minor = DEVINFO_VERSION_MINOR,
    .version_revision = DEVINFO_VERSION_REVISION,
    .address = DEVINFO_DEVICE_ADDRESS,
    .project = "SmartGarden",
    .role = "Pot"
};

const devinfo_t* UtDevInfo_GetInfo(void){
    return &(devinfo);
}