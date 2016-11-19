package org.knowm.waveforms4j.ad2;

import org.knowm.waveforms4j.DWF;

/**
 * Holds digital pin (0) high
 * 
 * @author timmolter
 */
public class ToggleDigitalIO {

  public static void main(String[] args) throws InterruptedException {

    DWF dwf = new DWF();

    boolean successful = dwf.FDwfDeviceOpen();
    System.out.println("successful: " + successful);

    successful = dwf.FDwfDigitalIOOutputEnableSet(0b1111_1111);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfDigitalIOOutputSet(0b0000_0001);
    System.out.println("successful: " + successful);

    Thread.sleep(10000);

    successful = dwf.FDwfDeviceCloseAll();
    System.out.println("successful: " + successful);

  }

}
