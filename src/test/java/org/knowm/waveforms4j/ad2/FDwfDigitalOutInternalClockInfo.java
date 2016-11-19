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
