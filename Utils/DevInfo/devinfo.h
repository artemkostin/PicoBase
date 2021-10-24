/**
 * @file devinfo.h
 * @author Artem Kostin (artem.1.kostin@gmail.com)
 * @brief SmartGardenProject pot controller DevInfo implementation.
 * @version 0.1
 * @date 2021-09-24
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef SGP_UTILS_DEVINFO
#define SGP_UTILS_DEVINFO

#ifndef DEVINFO_VERSION_MAJOR
    #define DEVINFO_VERSION_MAJOR 1
#endif

#ifndef DEVINFO_VERSION_MINOR
    #define DEVINFO_VERSION_MINOR 0
#endif

#ifndef DDEVINFO_VERSION_REVISION
    #define DEVINFO_VERSION_REVISION 0
#endif

#ifndef DEVINFO_DEVICE_ADDRESS
    #define DEVINFO_DEVICE_ADDRESS 0x01
#endif


typedef struct
{
    int         version_major;
    int         version_minor;
    int         version_revision;
    int         address;
    const char* project;
    const char* role;
}devinfo_t;

const devinfo_t* UtDevInfo_GetInfo(void);
#endif //SGP_UTILS_DEVINFO