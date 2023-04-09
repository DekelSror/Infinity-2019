/*==============================================================================
Unique Identifier
Module
Dekel Sror
Review: Erez Wilderman
Version 1
==============================================================================*/
#include <unistd.h> /* getpid  */

#include "ilrd_uid.h"

#define MEMBERS_STRUCT_UID (4)
#define BAD_VALUE (0)

ilrd_uid_t UIDGet(void)
{
    static size_t generated_uids_count = 0;

    struct timeval new_time = { 0 };
    ilrd_uid_t new_uid = { 0 };

    gettimeofday(&new_time, NULL);

    new_uid.time = new_time;
    new_uid.pid = getpid();
    new_uid.counter = generated_uids_count;

    ++generated_uids_count;

    return new_uid;
}

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
    int res = (uid1.pid == uid2.pid);

    res += (uid1.counter == uid2.counter);

    res += (uid1.time.tv_sec == uid2.time.tv_sec);

    res += (uid1.time.tv_usec == uid2.time.tv_usec);

    return (MEMBERS_STRUCT_UID == res);
}

int UIDIsBad(ilrd_uid_t uid)
{
    return UIDIsSame(uid, UIDGetBad());
}

ilrd_uid_t UIDGetBad(void)
{
    ilrd_uid_t new_bad = { BAD_VALUE };

    return new_bad;
}
