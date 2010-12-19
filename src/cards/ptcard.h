/***************************************************************************
 *   Copyright (C) 2007 by                                                 *
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

#ifndef PTCARD_H
#define PTCARD_H

#include "genericcard.h"
#include <QString>

/**
 * PT card: Page title / print control for current on wires.
 */
class PTCard : public GenericCard
{
public:
  PTCard(int thePrintControl, int theTagNumberToPrint);
  PTCard(int thePrintControl, int theTagNumberToPrint,
         int theEqualToM, int theEqualToN);

  int getPrintControl() const;
  int getTagNumberToPrint() const;
  int getEqualToM() const;
  int getEqualToN() const;

  QString getCard();

private:
  /**
    IPTFLG - Print control flag, specifies the type of format used in
    printing segment currents. The options are:
    -2 - all currents printed. This it a default value for the program if the
    card is Omitted.
    -1 - suppress printing of all wire segment currents.
    O - current printing will be limited to the segments specified by the next
    three parameters.
    1 - currents are printed by using a format designed for a receiving pattern
    (refer to output section in this manual Only currents for the segments
    specified by the next three parameters are printed.
    2 - same as for 1 above; in addition, however, the current for one Segment
    will Cue normalized to its maximum, ant the normalized values along with
    the relative strength in tB will be printed in a table. If the currents for
    more than one segment are being printed, only currents from the last
    segment in the group appear in the normalized table.
    3 - only normalized currents from one segment are printed for the receiving
    pattern case.
  */
  int printControl;
  /**
    IPTAG (I2) - Tag number of the segments for which currents will be
    printed.
  */
  int tagNumberToPrint;
  /**
    IPTAGF (I3) - Equal to m, specifies the mth segment of the set of segments
    having the tag numbers of IPTAG, at which printing of currents starts. If
    IPTAG is zero or blank, then IPTAGF refers to an absolute segment number.
    If IPTAGF is blank, the current is printed for all segments.
  */
  int equalToM;
  /**
    IPTAGT (I4) - Equal to n specifies the nth segment of the set of segments
    having tag numbers of IPTAG. Currents are printed for segments having tag
    number IPTAG starting at the m th segment in the set and ending at the nth
    segment. If IPTAG is zero or blank, then IPTAGF and IPTAGT refer to
    absolute segment numbers. In IPTAGT is left blank, it is set to IPTAGF.
  */
  int equalToN;
};

#endif // PTCARD_H

