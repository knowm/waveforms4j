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
package org.knowm.waveforms4j;

import java.io.IOException;

import cz.adamh.utils.NativeUtils;
import org.multibit.platform.builder.OSUtils;

public class DWF {

  static {
    try {
      if (OSUtils.isMac()) {
        NativeUtils.loadLibraryFromJar("/waveforms4j.dylib");
      }
      else if (OSUtils.isLinux()) {
        NativeUtils.loadLibraryFromJar("/waveforms4j.so");
      }
      else if (OSUtils.isWindows()) {
        NativeUtils.loadLibraryFromJar("/waveforms4j.dll");
      }
    } catch (IOException e) {
      e.printStackTrace(); // This is probably not the best way to handle exception :-)
    }
  }

  public static final int WAVEFORM_CHANNEL_1 = 0;
  public static final int WAVEFORM_CHANNEL_2 = 1;
  public static final int OSCILLOSCOPE_CHANNEL_1 = 0;
  public static final int OSCILLOSCOPE_CHANNEL_2 = 1;

  public static final int AD2_MAX_BUFFER_SIZE = 8192;

  public enum Waveform {

    DC(0), Sine(1), Square(2), Triangle(3), RampUp(4), RampDown(5), Noise(6), Custom(30), Play(31);

    private final int id;

    private Waveform(int id) {

      this.id = id;
    }

    public int getId() {

      return id;
    }
  }

  public enum AcquisitionMode {

    Single(0), ScanShift(1), ScanScreen(2), Record(3);

    private final int id;

    private AcquisitionMode(int id) {

      this.id = id;
    }

    public int getId() {

      return id;
    }
  }

  public enum AnalogOutIdle {

    Disable(0), Offset(1), Initial(2);

    private final int id;

    private AnalogOutIdle(int id) {

      this.id = id;
    }

    public int getId() {

      return id;
    }
  }

  public enum TriggerSource {

    trigsrcNone(0), trigsrcPC(1), trigsrcDetectorAnalogIn(2), trigsrcDetectorDigitalIn(3), trigsrcAnalogIn(4), trigsrcDigitalIn(5), trigsrcDigitalOut(6), trigsrcAnalogOut1(7), trigsrcAnalogOut2(8),
    trigsrcExternal1(11), trigsrcExternal2(12);

    private final int id;

    private TriggerSource(int id) {

      this.id = id;
    }

    public int getId() {

      return id;
    }
  }

  public enum AnalogTriggerType {

    trigtypeEdge(0), trigtypePulse(1), trigtypeTransition(2);

    private final int id;

    private AnalogTriggerType(int id) {

      this.id = id;
    }

    public int getId() {

      return id;
    }
  }

  public enum AnalogTriggerCondition {

    trigcondRisingPositive(0), trigcondFallingNegative(1);

    private final int id;

    private AnalogTriggerCondition(int id) {

      this.id = id;
    }

    public int getId() {

      return id;
    }
  }

  /////////////////////////////////////////////////////////////
  // Device ///////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////

  public native boolean FDwfDeviceOpen();

  public native boolean FDwfDeviceCloseAll();

  public native String FDwfGetLastErrorMsg();

  public native boolean FDwfDeviceAutoConfigureSet(boolean autoConfigure); // if set true (default), all calls to any Set* method re configures the device which takes a few milliseconds. See https://forum.digilentinc.com/topic/3468-correct-way-to-changeupdate-analogout-waveform-for-waveforms-sdk/

  /////////////////////////////////////////////////////////////
  // Digital I/O //////////////////////////////////////////////
  /////////////////////////////////////////////////////////////

  public native boolean FDwfDigitalIOOutputEnableSet(int outputEnableMask);

  public native boolean FDwfDigitalIOOutputSet(int outputSetMask);

  public native boolean FDwfDigitalIOReset();

  public native boolean FDwfDigitalIOStatus();

  public native int FDwfDigitalIOInputStatus();

  public native boolean FDwfDigitalIOConfigure();

  public int getDigitalIOStatus() {

    FDwfDigitalIOStatus();
    return FDwfDigitalIOInputStatus();
  }

  /////////////////////////////////////////////////////////////
  // Digital Pattern Out //////////////////////////////////////
  /////////////////////////////////////////////////////////////

  public native boolean FDwfDigitalOutEnableSet(int idxChannel, boolean enable);

  public native double FDwfDigitalOutInternalClockInfo();

  public native boolean FDwfDigitalOutDividerSet(int idxChannel, int frequency);

  public native boolean FDwfDigitalOutCounterSet(int idxChannel, int low, int high);

  public native boolean FDwfDigitalOutCounterInitSet(int idxChannel, boolean high, int dividerValue);

  public native boolean FDwfDigitalOutConfigure(boolean start);

  public native boolean FDwfDigitalOutReset();

  /////////////////////////////////////////////////////////////
  // Analog In ////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////

  public native boolean FDwfAnalogInChannelEnableSet(int idxChannel, boolean enable);

  /**
   * Volts range is a bit confusing. For the AD2, there are only two choices: set 'voltsRange' below 5, it will use the -2.5 to +2.5V (5V pk2pk) range and if I set 'voltsRange' above 5, it will use
   * the -25 to +25V (50V pk2pk) range.
   *
   * @param idxChannel
   * @param voltsRange
   * @return
   */
  public native boolean FDwfAnalogInChannelRangeSet(int idxChannel, double voltsRange);

  public native boolean FDwfAnalogInFrequencySet(double hzFrequency);

  public native int FDwfAnalogInBufferSizeMax();

  public native boolean FDwfAnalogInBufferSizeSet(int size);

  public native byte FDwfAnalogInStatus(boolean readData);

  public native int FDwfAnalogInStatusSamplesValid();

  public native double[] FDwfAnalogInStatusData(int idxChannel, int size);

  public native boolean FDwfAnalogInConfigure(boolean reconfigure, boolean start);

  public native boolean FDwfAnalogInAcquisitionModeSet(int mode);

  public boolean startAnalogCaptureBothChannels(double frequency, int buffersize, AcquisitionMode acquisitionMode) {

    FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_1, true);
    FDwfAnalogInChannelRangeSet(DWF.OSCILLOSCOPE_CHANNEL_1, 2.5);
    FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_2, true);
    FDwfAnalogInChannelRangeSet(DWF.OSCILLOSCOPE_CHANNEL_2, 2.5);
    FDwfAnalogInFrequencySet(frequency);
    FDwfAnalogInBufferSizeSet(buffersize);
    FDwfAnalogInAcquisitionModeSet(acquisitionMode.getId());
    return FDwfAnalogInConfigure(true, true);
  }

  public boolean stopAnalogCaptureBothChannels() {

    return FDwfAnalogInConfigure(true, false);
  }

  // TRIGGER SETTINGS
  public native boolean FDwfAnalogInTriggerAutoTimeoutSet(double secTimeout);

  public native boolean FDwfAnalogInTriggerSourceSet(int trigsrc);

  public native boolean FDwfAnalogInTriggerTypeSet(int trigtype);

  public native boolean FDwfAnalogInTriggerConditionSet(int trigcond);

  public native boolean FDwfAnalogInTriggerChannelSet(int idxChannel);

  public native boolean FDwfAnalogInTriggerLevelSet(double voltsLevel);

  /////////////////////////////////////////////////////////////
  // Analog Out ///////////////////////////////////////////////
  /////////////////////////////////////////////////////////////

  public native int FDwfAnalogOutTriggerSourceInfo(int idxChannel);

  public native boolean FDwfAnalogOutNodeEnableSet(int idxChannel, boolean enable);

  public native boolean FDwfAnalogOutNodeFunctionSet(int idxChannel, int func);

  public native boolean FDwfAnalogOutNodeFrequencySet(int idxChannel, double hzFrequency);

  public native boolean FDwfAnalogOutNodeAmplitudeSet(int idxChannel, double amplitude);

  public native boolean FDwfAnalogOutNodeOffsetSet(int idxChannel, double offset);

  public native boolean FDwfAnalogOutNodeSymmetrySet(int idxChannel, double dutyCycle);

  public native boolean FDwfAnalogOutConfigure(int idxChannel, boolean start);

  public native int[] FDwfAnalogOutNodeDataInfo(int idxChannel);

  public native boolean FDwfAnalogOutNodeDataSet(int idxChannel, double[] rgdData, int size);

  public boolean startWave(int idxChannel, Waveform waveform, double frequency, double amplitude, double offset, double dutyCycle) {

    if (!FDwfAnalogOutNodeEnableSet(idxChannel, true)) return false;
    if (!FDwfAnalogOutNodeFunctionSet(idxChannel, waveform.getId())) return false;
    if (!FDwfAnalogOutNodeFrequencySet(idxChannel, frequency)) return false;
    if (!FDwfAnalogOutNodeAmplitudeSet(idxChannel, amplitude)) return false;
    if (!FDwfAnalogOutNodeOffsetSet(idxChannel, offset)) return false;
    if (!FDwfAnalogOutNodeSymmetrySet(idxChannel, dutyCycle)) return false;
    if (!FDwfAnalogOutConfigure(idxChannel, true)) return false;
    return true;
  }

  public boolean stopWave(int idxChannel) {

    FDwfAnalogOutNodeOffsetSet(idxChannel, 0); // shouldn't need this in theory, but DC offset is always lingering (https://forum.digilentinc.com/topic/3465-waveforms-sdk-correctly-start-and-stop-analog-out/)
    return FDwfAnalogOutConfigure(idxChannel, false);
  }

  public native boolean FDwfAnalogOutRepeatSet(int idxChannel, int repeat);

  public native boolean FDwfAnalogOutRunSet(int idxChannel, double secRun);

  public native boolean FDwfAnalogOutIdleSet(int idxChannel, int idle);

  public boolean startSinglePulse(int idxChannel, Waveform waveform, double frequency, double amplitude, double offset, double dutyCycle) {

    FDwfAnalogOutRepeatSet(idxChannel, 1);
    double secRun = 1 / frequency / 2;
    FDwfAnalogOutRunSet(idxChannel, secRun);
    FDwfAnalogOutIdleSet(idxChannel, AnalogOutIdle.Offset.getId()); // when idle, what's the DC level? answer: the offset level
    return startWave(idxChannel, waveform, frequency, amplitude, offset, dutyCycle);
  }

  public boolean startCustomPulseTrain(int idxChannel, double frequency, double offset, int numPulses, double[] rgdData) {

    FDwfAnalogOutRepeatSet(idxChannel, 1);
    double secRun = 1 / frequency * numPulses;
    FDwfAnalogOutRunSet(idxChannel, secRun);
    FDwfAnalogOutIdleSet(idxChannel, AnalogOutIdle.Offset.getId()); // when idle, what's the DC level? answer: the offset level

    if (!FDwfAnalogOutNodeEnableSet(idxChannel, true)) return false;
    if (!FDwfAnalogOutNodeFunctionSet(idxChannel, Waveform.Custom.getId())) return false;
    if (!FDwfAnalogOutNodeFrequencySet(idxChannel, frequency)) return false;
    if (!FDwfAnalogOutNodeAmplitudeSet(idxChannel, 5.0)) return false; // manually set to full amplitude
    if (!FDwfAnalogOutNodeOffsetSet(idxChannel, offset)) return false;

    FDwfAnalogOutNodeDataSet(idxChannel, rgdData, rgdData.length);

    if (!FDwfAnalogOutConfigure(idxChannel, true)) return false;

    return true;
  }

  /////////////////////////////////////////////////////////////
  // Analog I/O ///////////////////////////////////////////////
  /////////////////////////////////////////////////////////////

  public native boolean FDwfAnalogIOChannelNodeSet(int idxChannel, int idxNode, double value);

  public native boolean FDwfAnalogIOEnableSet(boolean enable);

  public native boolean FDwfAnalogIOConfigure();

  public boolean setPowerSupply(int idxChannel, double value) {

    FDwfAnalogIOChannelNodeSet(idxChannel, 0, 1);
    FDwfAnalogIOChannelNodeSet(idxChannel, 1, value);
    FDwfAnalogIOEnableSet(true);
    return FDwfAnalogIOConfigure();
  }
}
