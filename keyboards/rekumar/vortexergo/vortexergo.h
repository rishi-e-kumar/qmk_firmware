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
	L00, L01, L02, L03, L04, R00, R01, R02, R03, R04, \
	L10, L11, L12, L13, L14, R10, R11, R12, R13, R14, \
	L20, L21, L22, L23, L24, R20, R21, R22, R23, R24, \
	          LT0, LT1, LT2, RT2, RT1, RT0			  \
	) \
	{ \
		{L00,   L01,   L02, L03, L04, R00, R01, R02, R03,   R04 }, \
		{L10,   L11,   L12, L13, L14, R10, R11, R12, R13,   R14 }, \
		{L20,   L21,   L22, L23, L24, R20, R21, R22, R23,   R24 }, \
		{KC_NO, KC_NO, LT0, LT1, LT2, RT2, RT1, RT0, KC_NO, KC_NO } \
	}


