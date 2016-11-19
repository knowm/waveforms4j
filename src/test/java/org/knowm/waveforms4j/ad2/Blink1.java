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
