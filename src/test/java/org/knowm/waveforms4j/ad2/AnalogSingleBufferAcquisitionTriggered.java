package org.knowm.waveforms4j.ad2;

import org.knowm.waveforms4j.DWF;
import org.knowm.waveforms4j.DWF.AcquisitionMode;
import org.knowm.waveforms4j.DWF.AnalogTriggerCondition;
import org.knowm.waveforms4j.DWF.AnalogTriggerType;

/**
 * Samples the voltage on O-scope 0. You should hook it up to Digital I/O 0 to get 3.3 V to read.
 * 
 * @author timmolter
 */
public class AnalogSingleBufferAcquisitionTriggered {

  private static final int OSCILLOSCOPE_CHANNEL = 0;

  public static void main(String[] args) throws InterruptedException {

    DWF dwf = new DWF();

    boolean successful = dwf.FDwfDeviceOpen();
    System.out.println("successful: " + successful);

    // TURN ON CHANNEL 0 DIGITAL TO 3.3 V

    successful = dwf.FDwfDigitalIOOutputEnableSet(0b1111_1111);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfDigitalIOOutputSet(0b0000_0001);
    System.out.println("successful: " + successful);

    // TURN ON POWER SUPPLIES
    dwf.setPowerSupply(0, 5.0);
    dwf.setPowerSupply(1, -5.0);

    // GET ANALOG OUT FDwfDeviceTriggerInfo

    int pfstrigsrc = dwf.FDwfAnalogOutTriggerSourceInfo(0);
    System.out.println("Possible Trigger Sources: " + Integer.toBinaryString(pfstrigsrc));

    // SETUP ANALOG IN

    dwf.FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_1, true);
    dwf.FDwfAnalogInChannelRangeSet(DWF.OSCILLOSCOPE_CHANNEL_1, 2.5);
    dwf.FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_2, true);
    dwf.FDwfAnalogInChannelRangeSet(DWF.OSCILLOSCOPE_CHANNEL_2, 2.5);
    dwf.FDwfAnalogInFrequencySet(10_000 * 100);
    dwf.FDwfAnalogInBufferSizeSet(DWF.AD2_MAX_BUFFER_SIZE);
    dwf.FDwfAnalogInAcquisitionModeSet(AcquisitionMode.Single.getId());

    // SETUP ANALOG OUT

    // SET UP TRIGGER

    // Analog In
    dwf.FDwfAnalogInTriggerAutoTimeoutSet(0); // disable auto trigger
    dwf.FDwfAnalogInTriggerSourceSet(DWF.TriggerSource.trigsrcDetectorAnalogIn.getId()); // one of the analog in channels
    dwf.FDwfAnalogInTriggerTypeSet(AnalogTriggerType.trigtypeEdge.getId());
    dwf.FDwfAnalogInTriggerConditionSet(AnalogTriggerCondition.trigcondRisingPositive.getId());
    dwf.FDwfAnalogInTriggerChannelSet(0); // first channel
    dwf.FDwfAnalogInTriggerLevelSet(1.5); // 1.5V

    // RUN

    dwf.FDwfAnalogInConfigure(false, true);

    // // TAKE AN ANALOG SAMPLE
    //
    // successful = dwf.FDwfAnalogInChannelEnableSet(OSCILLOSCOPE_CHANNEL, true);
    // System.out.println("successful: " + successful);
    //
    // successful = dwf.FDwfAnalogInChannelRangeSet(OSCILLOSCOPE_CHANNEL, 10);
    // System.out.println("successful: " + successful);
    //
    // successful = dwf.FDwfAnalogInFrequencySet(20000000);
    // System.out.println("successful: " + successful);
    //
    // int buffersize = dwf.FDwfAnalogInBufferSizeMax();
    // System.out.println("buffersize: " + buffersize);
    //
    // successful = dwf.FDwfAnalogInBufferSizeSet(buffersize);
    // System.out.println("successful: " + successful);
    //
    // Thread.sleep(2000);
    //
    // successful = dwf.FDwfAnalogInConfigure(false, true);
    // System.out.println("successful: " + successful);
    //
    // double[] capturedData = dwf.FDwfAnalogInStatusData(0, buffersize);
    // System.out.println("capturedData: " + Arrays.toString(capturedData));

    successful = dwf.FDwfDeviceCloseAll();
    System.out.println("successful: " + successful);

  }

}
