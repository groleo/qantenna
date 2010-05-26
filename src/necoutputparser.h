/***************************************************************************
 *   Copyright (C) 2005 by                                                 *
 *   Lisandro Damián Nicanor Pérez Meyer - perezmeyer en/at gmail.com      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef NECOUTPUTPARSER_H
#define NECOUTPUTPARSER_H

#include "necoutput.h"

/**
	This is the parser of NEC's output. It needs a pointer to NECOutput in order
	to call NECOutput::SetRadiationpattern() to pass the data.
	It could have been implemented using signals/slots, but I think it works great
	like this.
*/

int NECOutputParser(NECOutput * theNECOutput, QString theFileName);

#endif // NECOUTPUTPARSER_H

