/**
 * Waveforms4j is distributed under the GNU General Public License version 3
 * and is also available under alternative licenses negotiated directly
 * with Knowm, Inc.
 *
 * Copyright (c) 2016 Knowm Inc. www.knowm.org
 *
 * This package also includes various components that are not part of
 * Waveforms4j itself:
 *
 * * `NativeUtils`: Copyright 2012 Adam Heinrich, MIT License
 * * `dwf.h`: Copyright 2013 Digilent Inc., no license defined
 * * `Multibit`: Copyright 2011 multibit.org, MIT License
 *
 * Knowm, Inc. holds copyright
 * and/or sufficient licenses to all components of the Waveforms4j
 * package, and therefore can grant, at its sole discretion, the ability
 * for companies, individuals, or organizations to create proprietary or
 * open source (even if not GPL) modules which may be dynamically linked at
 * runtime with the portions of Waveforms4j which fall under our
 * copyright/license umbrella, or are distributed under more flexible
 * licenses than GPL.
 *
 * The 'Knowm' name and logos are trademarks owned by Knowm, Inc.
 *
 * If you have any questions regarding our licensing policy, please
 * contact us at `contact@knowm.org`.
 */
package org.knowm.waveforms4j.ad2;

import org.knowm.waveforms4j.DWF;

/**
 * Blinks digital pin (0) where all the blinking code is in Java
 *
 * @author timmolter
 */
public class Blink1 {

  public static void main(String[] args) throws InterruptedException {

    DWF dwf = new DWF();

    boolean successful = dwf.FDwfDeviceOpen();
    System.out.println("successful: " + successful);

    double clock = dwf.FDwfDigitalOutInternalClockInfo();
    System.out.println("clock: " + clock);

    successful = dwf.FDwfDigitalOutEnableSet(0, true);
    System.out.println("successful: " + successful);

    // frequency set 2 Hz
    successful = dwf.FDwfDigitalOutDividerSet(0, 5);
    System.out.println("successful: " + successful);

    // 1 tick low, 1 tick high
    successful = dwf.FDwfDigitalOutCounterSet(0, 1, 1);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfDigitalOutConfigure(true);
    System.out.println("successful: " + successful);

    Thread.sleep(10000);

    successful = dwf.FDwfDigitalOutReset();
    System.out.println("successful: " + successful);

    successful = dwf.FDwfDeviceCloseAll();
    System.out.println("successful: " + successful);

  }

}
