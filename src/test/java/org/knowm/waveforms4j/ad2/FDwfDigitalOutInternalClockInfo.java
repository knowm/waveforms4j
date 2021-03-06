/**
 * Waveforms4j is distributed under the GNU General Public License version 3 and is also available
 * under alternative licenses negotiated directly with Knowm, Inc.
 *
 * <p>Copyright (c) 2016-2020 Knowm Inc. www.knowm.org
 *
 * <p>This package also includes various components that are not part of Waveforms4j itself:
 *
 * <p>* `NativeUtils`: Copyright 2012 Adam Heinrich, MIT License * `dwf.h`: Copyright 2013 Digilent
 * Inc., no license defined * `Multibit`: Copyright 2011 multibit.org, MIT License
 *
 * <p>Knowm, Inc. holds copyright and/or sufficient licenses to all components of the Waveforms4j
 * package, and therefore can grant, at its sole discretion, the ability for companies, individuals,
 * or organizations to create proprietary or open source (even if not GPL) modules which may be
 * dynamically linked at runtime with the portions of Waveforms4j which fall under our
 * copyright/license umbrella, or are distributed under more flexible licenses than GPL.
 *
 * <p>The 'Knowm' name and logos are trademarks owned by Knowm, Inc.
 *
 * <p>If you have any questions regarding our licensing policy, please contact us at
 * `contact@knowm.org`.
 */
package org.knowm.waveforms4j.ad2;

import org.knowm.waveforms4j.DWF;

public class FDwfDigitalOutInternalClockInfo {

  public static void main(String[] args) {

    DWF dwf = new DWF();

    boolean successful = dwf.FDwfDeviceOpen();
    System.out.println("successful: " + successful);

    double clock = dwf.FDwfDigitalOutInternalClockInfo();
    System.out.println("clock: " + clock);

    successful = dwf.FDwfDeviceCloseAll();
    System.out.println("successful: " + successful);
  }
}
