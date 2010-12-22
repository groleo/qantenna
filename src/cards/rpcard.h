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

#ifndef RPCARD_H
#define RPCARD_H

#include "genericcard.h"
#include <QString>

/**
 * \brief RP card: Radiation Pattern. Specify radiation pattern sampling
 * parameters and to cause program execution.
 *
 * Options for a field computation include a radial wire ground screen, a cliff,
 * or surface-wave fields.
 */
class RPCard : public GenericCard
{
public:
  /**
   * \param theModeOfCalculation (I1) This integer selects the mode of
   * calculation for the radiated field.
   * Some values of (I1) will affect the meaning of the remaining parameters on
   * the cart. Options available for I1 are:
   * - O: normal mode. Space-wave fields are computed. An infinite ground plane
   * is included if it has been specified previously on a GN cart; otherwise,
   * antenna is in free space.
   * - 1: surface wave propagating along ground is added to the normal space
   * wave. This option changes the meaning of some of the other parameters on
   * the RP cart as explained below, and the results appear in a special output
   * format. Ground parameters must have been input on a GN card.
   * The following options cause calculation of only the space wave but with
   * special ground conditions. ground conditions include a two medium ground
   * (cliff) where the media join in a circle or a line, and a radial wire
   * ground screen. Ground parameters and dimensions must be input on a GN or GD
   * card before the RP card is read. The RP card only selects the option for
   * inclusion in the field calculation. (Refer to the GN and GD cards for
   * further explanation.)
   * - 2: linear cliff with antenna above upper level. Lower medium parameters
   * are as specified for the second medium on the GN cart or on the GD card.
   * - 3: circular cliff centered at origin of coordinate system: with antenna
   * above upper level. Lower medium parameters are as specified for the second
   * medium on the GN card or on the GD card.
   * - 4: radial wire ground screen centered at origin.
   * - 5: both radial wire ground screen and linear cliff.
   * - 6: both radial wire ground screen ant circular cliff.
   * The field point is specified in spherical coordinates (R. sigma, theta),
   * illustrated in figure 18, except when the surface wave is computed. For
   * computing the surface wave field (I1 = 1), cylindrical coordinates (phi,
   * theta, z) are used to accurately define points near the ground plane at
   * large radial distances. The RP cart allows automatic stepping of the field
   * point to compute the field over a region about the antenna at uniformly
   * spaced points. The integers I2 and I3 and floating point numbers Fl, F2, F3
   * and F4 control the field-point stepping.
   *
   * \param theNumberOfValuesOfTheta Number of values of theta.
   * Number of values of theta (e) at which the field is to be computed (number
   * of values of z for I1 = 1).
   *
   * \param theNumberOfValuesOfPhi Number of values of phi.
   * Number of values of phi (f) at which field is to be computed. The total
   * number of field points requested by the card is NTH x NPH. If I2 or I3 is
   * left blank, a value of one will be assumed.
   *
   * \param theXNDA (I4) - This optional integer consists of four independent
   * digits in columns 17, 18, 19 and 20, each having a different function.
   * The mnemonic XNDA is not a variable name in the program. Rather, each
   * letter represents a mnemonic for the corresponding digit in I4. If I1 = 1,
   * then I4 has no effect and should be left blank.
   *
   * - X - (column l7) control output format.
   * - X = 0 major axis, minor axis and total gain printed.
   * - X = 1 vertical, horizontal ant total gain printed.
   *
   * N - (column 18) causes normalized gain for the specified field points to be
   * printed after the standard gain output. The number of field points for
   * which the normalized gain can be printed is limited by an array dimension
   * in the program. In the demonstration program, the limit is 600 points. If
   * the number of field points exceeds this limit, the remaining points will be
   * omitted from the normalized gain. The gain may be normalized to its maximum
   * or to a value input in field F6. The type of gain that is normalized is
   * determined by the value of N as follows:
   *
   * - N = 0 no normalized gain.
   * - N = 1 major axis gain normalized.
   * - N = 2 minor axis gain normalized.
   * - N = 3 vertical axis gain normalized.
   * - N = 4 horizontal axis gain normalized.
   * - N = 5 total gain normalized.
   *
   * D - (column 19) selects either power gain or directive gain for both
   * standard printing ant normalization. If the structure excitation is an
   * incident plane wave, the quantities printed under the heading gain will
   * actually be the scattering cross section (a/lambda 2 ) and will not be
   * affected by the value of D. The column heading for the output will still
   * read "power" or "directive gain," however.
   *
   * - D = 0 power gain.
   * - D = 1 directive gain.
   * - A - (column 20) requests calculation of average power gain over the
   * region covered by field points.
   *
   * - A = 0 no averaging.
   * - A = 1 average gain computed.
   * - A = 2 average gain computed, printing of gain at the field points used
   * for averaging is suppressed. If NTH or NPH is equal to one, average gain
   * will not be computed for any value of A since the area of the region
   * covered by field points vanishes.
   *
   * \brief theInitialTheta Initial theta angle in degrees (initial z coordinate
   * in meters if I1 = 1)
   *
   * \brief theInitialPhi Initial phi angle in degrees.
   *
   * \brief theIncrementTheta Increment for theta in degrees (increment for z
   * in meters if I1 = 1).
   *
   * \brief theIncrementPhi Increment for phi in degrees.
   *
   * \brief theRadialDistance Radial distance (R) of field point from the origin
   * in meters. RFLD is optional. If it is blank, the radiated electric field
   * will have the factor exp(-jkR)/R omitted. If a value of R is specified, it
   * should represent a point in the far-field region since near components of
   * the field cannot be obtained with an RP cart. (If I1 = 1, then RFLD
   * represents the cylindrical coordinate phi in meters and is not optional.
   * It must be greater than about one wavelength).
   *
   * \brief theGainNormalization GNOR Determines the gain normalization factor
   * if normalization has been requested in the I4 field. If GNOR is blank or
   * zero,the gain will be normalized to its maximum value. If GNOR is not zero,
   * the gain w111 be normalized to the value of GNOR.
   */
  RPCard(int theModeOfCalculation, int theNumberOfValuesOfTheta,
         int theNumberOfValuesOfPhi, int theXNDA, double theInitialTheta,
         double theInitialPhi, double theIncrementTheta,
         double theIncrementPhi, double theRadialDistance,
         double theGainNormalization);

  int getModeOfCalculation() const;
  int getNumberOfValuesOfTheta() const;
  int getNumberOfValuesOfPhi() const;
  int getXNDA() const;
  double getInitialTheta() const;
  double getInitialPhi() const;
  double getIncrementTheta() const;
  double getIncrementPhi() const;
  double getRadialDistance() const;
  double getGainMormalization() const;

  void setModeOfCalculation(int theModeOfCalculation);
  void setNumberOfValuesOfTheta(int theNumberOfValuesOfTheta);
  void setNumberOfValuesOfPhi(int theNumberOfValuesOfPhi);
  void setXNDA(int theXNDA);
  void setInitialTheta(double theInitialTheta);
  void setInitialPhi(double theInitialPhi);
  void setIncrementTheta(double theIncrementTheta);
  void setIncrementPhi(double theIncrementPhi);
  void setRadialDistance(double theRadialDistance);
  void setGainMormalization(double theGainNormalization);

  QString getCard();

private:
  int modeOfCalculation;
  int numberOfValuesOfTheta;
  int numberOfValuesOfPhi;
  int xnda;
  double initialTheta;
  double initialPhi;
  double incrementTheta;
  double incrementPhi;
  double radialDistance;
  double gainNormalization;
};

#endif // RPCARD_H

