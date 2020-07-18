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
    dwf.FDwfAnalogInTriggerSourceSet(
        DWF.TriggerSource.trigsrcDetectorAnalogIn.getId()); // one of the analog in channels
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
