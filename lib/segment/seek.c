
/**
 * \file seek.c
 *
 * \brief Segment seek routines.
 *
 * This program is free software under the GNU General Public License
 * (>=v2). Read the file COPYING that comes with GRASS for details.
 *
 * \author GRASS GIS Development Team
 *
 * \date 2005-2009
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <grass/gis.h>
#include <grass/segment.h>


/**
 * \fn int segment_seek (SEGMENT *SEG, int n, int index)
 *
 * \brief Seek into a segment.
 *
 * \param[in,out] SEG segment
 * \param[in] n
 * \param[in] index
 * \return 0 on success
 * \return -1 if unable to seek
 */

#define SEG_SEEK_FAST(SEG, n, index) \
    ((((off_t) (n)) << (SEG)->sizebits) + (index) + (SEG)->offset)

#define SEG_SEEK_SLOW(SEG, n, index) \
    ((off_t) (n) * (SEG)->size + (index) + (SEG)->offset)

int segment_seek_fast(const SEGMENT * SEG, int n, int index)
{
    if (lseek((SEG)->fd, SEG_SEEK_FAST(SEG, n, index), 
        SEEK_SET) == (off_t) -1) {
	G_fatal_error("segment_seek: %s", strerror(errno));
    }

    return 0;
}

int segment_seek_slow(const SEGMENT * SEG, int n, int index)
{
    if (lseek((SEG)->fd, SEG_SEEK_SLOW(SEG, n, index), 
        SEEK_SET) == (off_t) -1) {
	G_fatal_error("segment_seek: %s", strerror(errno));
    }

    return 0;
}

int segment_seek(const SEGMENT * SEG, int n, int index)
{
    return SEG->segment_seek(SEG, n, index);
}
