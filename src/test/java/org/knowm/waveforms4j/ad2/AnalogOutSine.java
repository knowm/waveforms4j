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

public class AnalogOutSine {

  final DWF dwf = new DWF();

  public static void main(String[] args) throws InterruptedException {

    AnalogOutSine app = new AnalogOutSine();

    app.go();

  }

  private void go() throws InterruptedException {

    boolean successful = dwf.FDwfDeviceOpen();
    System.out.println("successful: " + successful);

    successful = dwf.FDwfAnalogOutNodeEnableSet(0, true);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfAnalogOutNodeFunctionSet(0, 1);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfAnalogOutNodeFrequencySet(0, 10);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfAnalogOutNodeAmplitudeSet(0, 1.414);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfAnalogOutNodeOffsetSet(0, 1.414);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfAnalogOutConfigure(0, true);
    System.out.println("successful: " + successful);

    Thread.sleep(5000);

    // successful = dwf.FDwfDigitalOutReset();
    // System.out.println("successful: " + successful);

    successful = dwf.FDwfDeviceCloseAll();
    System.out.println("successful: " + successful);
  }
}
