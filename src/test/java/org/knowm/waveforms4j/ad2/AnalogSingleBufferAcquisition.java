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
