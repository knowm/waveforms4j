/**
 * Waveforms4j is distributed under the GNU General Public License version 3
 * and is also available under alternative licenses negotiated directly
 * with Knowm, Inc.
 *
 * Copyright (c) 2016-2017 Knowm Inc. www.knowm.org
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

import java.util.Arrays;

import org.knowm.waveforms4j.DWF;

/**
 * Samples the voltage on O-scope 0. You should hook it up to Digital I/O 0 to get 3.3 V to read.
 * 
 * @author timmolter
 */
public class AnalogSingleBufferAcquisition {

  private static final int OSCILLOSCOPE_CHANNEL = 0;

  public static void main(String[] args) throws InterruptedException {

    DWF dwf = new DWF();

    boolean successful = dwf.FDwfDeviceOpen();
    System.out.println("successful: " + successful);

    // TURN ON CHANNEL 0 DIGIATAL TO 3.3 V

    successful = dwf.FDwfDigitalIOOutputEnableSet(0b1111_1111);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfDigitalIOOutputSet(0b0000_0001);
    System.out.println("successful: " + successful);

    // TAKE AN ANALOG SAMPLE

    successful = dwf.FDwfAnalogInChannelEnableSet(OSCILLOSCOPE_CHANNEL, true);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfAnalogInChannelRangeSet(OSCILLOSCOPE_CHANNEL, 10);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfAnalogInFrequencySet(20000000);
    System.out.println("successful: " + successful);

    int buffersize = dwf.FDwfAnalogInBufferSizeMax();
    System.out.println("buffersize: " + buffersize);

    successful = dwf.FDwfAnalogInBufferSizeSet(buffersize);
    System.out.println("successful: " + successful);

    Thread.sleep(2000);

    successful = dwf.FDwfAnalogInConfigure(false, true);
    System.out.println("successful: " + successful);

    double[] capturedData = dwf.FDwfAnalogInStatusData(0, buffersize);
    System.out.println("capturedData: " + Arrays.toString(capturedData));

    successful = dwf.FDwfDeviceCloseAll();
    System.out.println("successful: " + successful);

  }

}
