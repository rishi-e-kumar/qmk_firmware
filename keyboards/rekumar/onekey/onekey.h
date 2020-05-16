/* Copyright 2019
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

#define LAYOUT( \
    l00, l01, l02, l03, l04, l05, \
    l10, l11, l12, l13, l14, l15, \
    l20, l21, l22, l23, l24, l25, \
    l30, l31, l32, l33, l34, l35, \
              l06, l16, l26, l36 \
  ) { \
    { l00, l01, l02, l03, l04, l05, l06 },  \
    { l10, l11, l12, l13, l14, l15, l16 },  \
    { l20, l21, l22, l23, l24, l25, l26 },  \
    { l30, l31, l32, l33, l34, l35, l36 }  \
}
