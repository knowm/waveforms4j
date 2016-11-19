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
