/**
 * Waveforms4j is distributed under the GNU General Public License version 3 and is also available
 * under alternative licenses negotiated directly with Knowm, Inc.
 *
 * <p>Copyright (c) 2016-2017 Knowm Inc. www.knowm.org
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
package org.knowm.waveforms4j;

import cz.adamh.utils.NativeUtils;
import java.io.IOException;
import org.multibit.platform.builder.OSUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class DWF {

  private static final Logger logger = LoggerFactory.getLogger(DWF.class);

  static {
    try {
      if (OSUtils.isMac()) {
        NativeUtils.loadLibraryFromJar("/waveforms4j.dylib");
      } else if (OSUtils.isLinux()) {
        NativeUtils.loadLibraryFromJar("/waveforms4j.so");
      } else if (OSUtils.isWindows()) {
        NativeUtils.loadLibraryFromJar("/waveforms4j.dll");
      }
    } catch (IOException e) {
      e.printStackTrace(); // This is probably not the best way to handle exception :-)
    }
  }

  public static final int WAVEFORM_CHANNEL_BOTH = -1;
  public static final int WAVEFORM_CHANNEL_1 = 0;
  public static final int WAVEFORM_CHANNEL_2 = 1;
  public static final int OSCILLOSCOPE_CHANNEL_1 = 0;
  public static final int OSCILLOSCOPE_CHANNEL_2 = 1;

  public static final int AD2_MAX_BUFFER_SIZE = 8192;

  public enum Waveform {
    DC(0),
    Sine(1),
    Square(2),
    Triangle(3),
    RampUp(4),
    RampDown(5),
    Noise(6),
    Custom(30),
    Play(31);

    private final int id;

    private Waveform(int id) {

      this.id = id;
    }

    public int getId() {

      return id;
    }
  }

  public enum AcquisitionMode {
    Single(0),
    ScanShift(1),
    ScanScreen(2),
    Record(3);

    private final int id;

    private AcquisitionMode(int id) {

      this.id = id;
    }

    public int getId() {

      return id;
    }
  }

  public enum AnalogOutIdle {
    Disable(0),
    Offset(1),
    Initial(2);

    private final int id;

    private AnalogOutIdle(int id) {

      this.id = id;
    }

    public int getId() {

      return id;
    }
  }

  public enum TriggerSource {
    trigsrcNone(0),
    trigsrcPC(1),
    trigsrcDetectorAnalogIn(2),
    trigsrcDetectorDigitalIn(3),
    trigsrcAnalogIn(4),
    trigsrcDigitalIn(5),
    trigsrcDigitalOut(6),
    trigsrcAnalogOut1(7),
    trigsrcAnalogOut2(8),
    trigsrcExternal1(11),
    trigsrcExternal2(12);

    private final int id;

    private TriggerSource(int id) {

      this.id = id;
    }

    public int getId() {

      return id;
    }
  }

  public enum AnalogTriggerType {
    trigtypeEdge(0),
    trigtypePulse(1),
    trigtypeTransition(2);

    private final int id;

    private AnalogTriggerType(int id) {

      this.id = id;
    }

    public int getId() {

      return id;
    }
  }

  public enum AnalogTriggerCondition {
    trigcondRisingPositive(0),
    trigcondFallingNegative(1);

    private final int id;

    private AnalogTriggerCondition(int id) {

      this.id = id;
    }

    public int getId() {

      return id;
    }
  }

  // ///////////////////////////////////////////////////////////
  // Device ///////////////////////////////////////////////////
  // ///////////////////////////////////////////////////////////

  public native boolean FDwfDeviceOpen();

  public native boolean FDwfDeviceCloseAll();

  public native String FDwfGetLastErrorMsg();

  public native boolean FDwfDeviceAutoConfigureSet(
      boolean
          autoConfigure); // if set true (default), all calls to any Set* method re configures the
  // device which takes a few milliseconds. See
  // https://forum.digilentinc.com/topic/3468-correct-way-to-changeupdate-analogout-waveform-for-waveforms-sdk/

  // ///////////////////////////////////////////////////////////
  // Digital I/O //////////////////////////////////////////////
  // ///////////////////////////////////////////////////////////

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

  // ///////////////////////////////////////////////////////////
  // Digital Pattern Out //////////////////////////////////////
  // ///////////////////////////////////////////////////////////

  public native boolean FDwfDigitalOutEnableSet(int idxChannel, boolean enable);

  public native double FDwfDigitalOutInternalClockInfo();

  public native boolean FDwfDigitalOutDividerSet(int idxChannel, int frequency);

  public native boolean FDwfDigitalOutCounterSet(int idxChannel, int low, int high);

  public native boolean FDwfDigitalOutCounterInitSet(
      int idxChannel, boolean high, int dividerValue);

  public native boolean FDwfDigitalOutConfigure(boolean start);

  public native boolean FDwfDigitalOutReset();

  // ///////////////////////////////////////////////////////////
  // Analog In ////////////////////////////////////////////////
  // ///////////////////////////////////////////////////////////

  public native boolean FDwfAnalogInChannelEnableSet(int idxChannel, boolean enable);

  /**
   * Volts range is a bit confusing. For the AD2, there are only two choices: set 'voltsRange' below
   * 5, it will use the -2.5 to +2.5V (5V pk2pk) range and if I set 'voltsRange' above 5, it will
   * use the -25 to +25V (50V pk2pk) range.
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

  public native double[] FDwfAnalogInTriggerPositionInfo();

  public native boolean FDwfAnalogInTriggerPositionSet(double secPosition);

  public native boolean FDwfAnalogInConfigure(boolean reconfigure, boolean start);

  public native boolean FDwfAnalogInAcquisitionModeSet(int mode);

  public native double[] FDwfAnalogInStatusData(int idxChannel, int size);

  public boolean stopAnalogCaptureBothChannels() {

    return FDwfAnalogInConfigure(true, false);
  }

  /**
   * this is for triggering immediately
   *
   * <p>Volts range is a bit confusing. For the AD2, there are only two choices: set 'voltsRange'
   * below 5, it will use the -2.5 to +2.5V (5V pk2pk) range and if I set 'voltsRange' above 5, it
   * will use the -25 to +25V (50V pk2pk) range.
   *
   * @param frequency
   * @param buffersize
   * @param acquisitionMode
   * @return
   */
  public boolean startAnalogCaptureBothChannelsImmediately(
      double frequency, int buffersize, AcquisitionMode acquisitionMode) {

    boolean success = true;
    success = success && FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_1, true);
    success = success && FDwfAnalogInChannelRangeSet(DWF.OSCILLOSCOPE_CHANNEL_1, 2.5);
    success = success && FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_2, true);
    success = success && FDwfAnalogInChannelRangeSet(DWF.OSCILLOSCOPE_CHANNEL_2, 2.5);
    success = success && FDwfAnalogInFrequencySet(frequency);
    success = success && FDwfAnalogInBufferSizeSet(buffersize);
    success = success && FDwfAnalogInAcquisitionModeSet(acquisitionMode.getId());
    success = success && FDwfAnalogInConfigure(true, true);
    success = success && FDwfAnalogInConfigure(true, true);
    if (!success) {
      FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_1, true);
      FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_2, true);
      FDwfAnalogInConfigure(false, false);
      throw new DWFException(FDwfGetLastErrorMsg());
    }
    return true;
  }

  /**
   * this is for triggering from the analog in channel
   *
   * <p>Volts range is a bit confusing. For the AD2, there are only two choices: set 'voltsRange'
   * below 5, it will use the -2.5 to +2.5V (5V pk2pk) range and if I set 'voltsRange' above 5, it
   * will use the -25 to +25V (50V pk2pk) range.
   *
   * @param sampleFrequency
   * @param triggerLevel
   * @param bufferSize
   * @return
   */
  public boolean startAnalogCaptureBothChannelsLevelTrigger(
      double sampleFrequency, double triggerLevel, int bufferSize) {

    // System.out.println("triggerLevel = " + triggerLevel);
    if (bufferSize > DWF.AD2_MAX_BUFFER_SIZE) {
      logger.error("Buffer size larger than allowed size. Setting to " + DWF.AD2_MAX_BUFFER_SIZE);
      bufferSize = DWF.AD2_MAX_BUFFER_SIZE;
    }

    boolean success = true;
    success = success && FDwfAnalogInFrequencySet(sampleFrequency);
    success = success && FDwfAnalogInBufferSizeSet(bufferSize);
    success =
        success
            && FDwfAnalogInTriggerPositionSet(
                (bufferSize / 2) / sampleFrequency); // no buffer prefill

    success = success && FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_1, true);
    success = success && FDwfAnalogInChannelRangeSet(DWF.OSCILLOSCOPE_CHANNEL_1, 2.5);
    success = success && FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_2, true);
    success = success && FDwfAnalogInChannelRangeSet(DWF.OSCILLOSCOPE_CHANNEL_2, 2.5);
    success = success && FDwfAnalogInAcquisitionModeSet(AcquisitionMode.Single.getId());
    // Trigger single capture on rising edge of analog signal pulse
    success = success && FDwfAnalogInTriggerAutoTimeoutSet(0); // disable auto trigger
    success =
        success
            && FDwfAnalogInTriggerSourceSet(
                DWF.TriggerSource.trigsrcDetectorAnalogIn.getId()); // one of the analog in channels
    success = success && FDwfAnalogInTriggerTypeSet(AnalogTriggerType.trigtypeEdge.getId());
    success = success && FDwfAnalogInTriggerChannelSet(0); // first channel
    // Trigger Level
    if (triggerLevel > 0) {
      success =
          success
              && FDwfAnalogInTriggerConditionSet(
                  AnalogTriggerCondition.trigcondRisingPositive.getId());
      success = success && FDwfAnalogInTriggerLevelSet(triggerLevel);
    } else {
      success =
          success
              && FDwfAnalogInTriggerConditionSet(
                  AnalogTriggerCondition.trigcondFallingNegative.getId());
      success = success && FDwfAnalogInTriggerLevelSet(triggerLevel);
    }

    // arm the capture
    success = success && FDwfAnalogInConfigure(true, true);
    if (!success) {
      FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_1, true);
      FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_2, true);
      FDwfAnalogInConfigure(false, false);
      throw new DWFException(FDwfGetLastErrorMsg());
    }
    return true;
  }

  /**
   * this is for triggering from the analog out channel instead of analog in
   *
   * <p>Volts range is a bit confusing. For the AD2, there are only two choices: set 'voltsRange'
   * below 5, it will use the -2.5 to +2.5V (5V pk2pk) range and if I set 'voltsRange' above 5, it
   * will use the -25 to +25V (50V pk2pk) range.
   *
   * @param waveformGenerator
   * @param sampleFrequency
   * @param bufferSize
   * @param isScale2Volts
   * @return
   */
  public boolean startAnalogCaptureBothChannelsTriggerOnWaveformGenerator(
      int waveformGenerator, double sampleFrequency, int bufferSize, boolean isScale2Volts) {

    if (bufferSize > DWF.AD2_MAX_BUFFER_SIZE) {
      logger.warn("Buffer size larger than allowed size. Setting to " + DWF.AD2_MAX_BUFFER_SIZE);
      bufferSize = DWF.AD2_MAX_BUFFER_SIZE;
    }

    boolean success = true;
    success = success && FDwfAnalogInFrequencySet(sampleFrequency);
    success = success && FDwfAnalogInBufferSizeSet(bufferSize);
    success =
        success
            && FDwfAnalogInTriggerPositionSet(
                (bufferSize / 2) / sampleFrequency); // no buffer prefill

    success = success && FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_1, true);
    success =
        success && FDwfAnalogInChannelRangeSet(DWF.OSCILLOSCOPE_CHANNEL_1, isScale2Volts ? 2 : 6);
    success = success && FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_2, true);
    success =
        success && FDwfAnalogInChannelRangeSet(DWF.OSCILLOSCOPE_CHANNEL_2, isScale2Volts ? 2 : 6);

    success = success && FDwfAnalogInAcquisitionModeSet(AcquisitionMode.Single.getId());

    // Trigger single capture on rising edge of analog signal pulse
    success = success && FDwfAnalogInTriggerAutoTimeoutSet(0); // disable auto trigger

    if (waveformGenerator == DWF.WAVEFORM_CHANNEL_1) {
      success =
          success
              && FDwfAnalogInTriggerSourceSet(
                  DWF.TriggerSource.trigsrcAnalogOut1.getId()); // one of the analog in channels
    } else if (waveformGenerator == DWF.WAVEFORM_CHANNEL_2) {
      success =
          success
              && FDwfAnalogInTriggerSourceSet(
                  DWF.TriggerSource.trigsrcAnalogOut2.getId()); // one of the analog in channels
    }

    success = success && FDwfAnalogInTriggerTypeSet(AnalogTriggerType.trigtypeEdge.getId());
    success = success && FDwfAnalogInTriggerChannelSet(0); // first channel

    // arm the capture
    success = success && FDwfAnalogInConfigure(true, true);
    if (!success) {
      FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_1, true);
      FDwfAnalogInChannelEnableSet(DWF.OSCILLOSCOPE_CHANNEL_2, true);
      FDwfAnalogInConfigure(false, false);
      throw new DWFException(FDwfGetLastErrorMsg());
    }
    return true;
  }

  // TRIGGER SETTINGS
  public native boolean FDwfAnalogInTriggerAutoTimeoutSet(double secTimeout);

  public native boolean FDwfAnalogInTriggerSourceSet(int trigsrc);

  public native boolean FDwfAnalogInTriggerTypeSet(int trigtype);

  public native boolean FDwfAnalogInTriggerConditionSet(int trigcond);

  public native boolean FDwfAnalogInTriggerChannelSet(int idxChannel);

  public native boolean FDwfAnalogInTriggerLevelSet(double voltsLevel);

  // ///////////////////////////////////////////////////////////
  // Analog Out ///////////////////////////////////////////////
  // ///////////////////////////////////////////////////////////

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

  public boolean startWave(
      int idxChannel,
      Waveform waveform,
      double frequency,
      double amplitude,
      double offset,
      double dutyCycle) {

    boolean success = true;
    success = success && FDwfAnalogOutNodeEnableSet(idxChannel, true);
    success = success && FDwfAnalogOutNodeFunctionSet(idxChannel, waveform.getId());
    success = success && FDwfAnalogOutNodeFrequencySet(idxChannel, frequency);
    success = success && FDwfAnalogOutNodeAmplitudeSet(idxChannel, amplitude);
    success = success && FDwfAnalogOutNodeOffsetSet(idxChannel, offset);
    success = success && FDwfAnalogOutNodeSymmetrySet(idxChannel, dutyCycle);
    success = success && FDwfAnalogOutConfigure(idxChannel, true);
    if (!success) {
      FDwfAnalogOutNodeEnableSet(idxChannel, false);
      FDwfAnalogOutConfigure(idxChannel, false);
      throw new DWFException(FDwfGetLastErrorMsg());
    }
    return true;
  }

  public boolean stopWave(int idxChannel) {

    FDwfAnalogOutNodeOffsetSet(
        idxChannel, 0); // shouldn't need this in theory, but DC offset is always lingering
    // (https://forum.digilentinc.com/topic/3465-waveforms-sdk-correctly-start-and-stop-analog-out/)
    return FDwfAnalogOutConfigure(idxChannel, false);
  }

  public native boolean FDwfAnalogOutRepeatSet(int idxChannel, int repeat);

  public native boolean FDwfAnalogOutRunSet(int idxChannel, double secRun);

  public native boolean FDwfAnalogOutIdleSet(int idxChannel, int idle);

  /**
   * The Analog outputs have the following specs: AC amplitude (max): ±5 V, DC Offset (max): ±5 V.
   * Here, we hardcode the amplitude to 5V allowing for the maximum voltage range possible for the
   * analog out. The waveform data defined in the `rgdData` parameter must be scaled against this 5
   * V output range with values between -1 and +1. For example, a rgdData value of 1.0 will result
   * in an output voltage of 5.0 V, a rgdData value of 0.2 will result in an output voltage of 1.0
   * V...
   *
   * @param idxChannel
   * @param frequency
   * @param offset
   * @param numPulses
   * @param rgdData - scaled between -1.0 and +1.0 against an anaolg output voltage of +/-5V.
   * @return
   */
  public boolean startCustomPulseTrain(
      int idxChannel, double frequency, double offset, int numPulses, double[] rgdData) {

    boolean success = true;

    success = success && FDwfAnalogOutRepeatSet(idxChannel, 1);
    double secRun = 1 / frequency * numPulses;
    success = success && FDwfAnalogOutRunSet(idxChannel, secRun);
    success =
        success
            && FDwfAnalogOutIdleSet(
                idxChannel,
                AnalogOutIdle.Offset
                    .getId()); // when idle, what's the DC level? answer: the offset level
    success = success && FDwfAnalogOutNodeEnableSet(idxChannel, true);
    success = success && FDwfAnalogOutNodeFunctionSet(idxChannel, Waveform.Custom.getId());
    success = success && FDwfAnalogOutNodeFrequencySet(idxChannel, frequency);
    success =
        success && FDwfAnalogOutNodeAmplitudeSet(idxChannel, 5.0); // manually set to full amplitude
    //    success = success && FDwfAnalogOutNodeAmplitudeSet(idxChannel, 1.0);
    success = success && FDwfAnalogOutNodeOffsetSet(idxChannel, offset);
    success = success && FDwfAnalogOutNodeDataSet(idxChannel, rgdData, rgdData.length);
    success = success && FDwfAnalogOutConfigure(idxChannel, true);
    if (!success) {
      FDwfAnalogOutNodeEnableSet(idxChannel, false);
      FDwfAnalogOutConfigure(idxChannel, false);
      throw new DWFException(FDwfGetLastErrorMsg());
    }
    return true;
  }

  /**
   * The Analog outputs have the following specs: AC amplitude (max): ±5 V, DC Offset (max): ±5 V.
   * Here, we hardcode the amplitude to 5V allowing for the maximum voltage range possible for the
   * analog out. The waveform data defined in the `rgdData` parameter must be scaled against this 5
   * V output range with values between -1 and +1. For example, a rgdData value of 1.0 will result
   * in an output voltage of 5.0 V, a rgdData value of 0.2 will result in an output voltage of 1.0
   * V...
   *
   * @param idxChannel
   * @param frequency
   * @param offset
   * @param numPulses
   * @param rgdData - scaled between -1.0 and +1.0 against an anaolg output voltage of +/-5V.
   * @return
   */
  public boolean setCustomPulseTrain(
      int idxChannel, double frequency, double offset, int numPulses, double[] rgdData) {

    boolean success = true;

    success = success && FDwfAnalogOutRepeatSet(idxChannel, 1);
    double secRun = 1 / frequency * numPulses;
    success = success && FDwfAnalogOutRunSet(idxChannel, secRun);
    success =
        success
            && FDwfAnalogOutIdleSet(
                idxChannel,
                AnalogOutIdle.Offset
                    .getId()); // when idle, what's the DC level? answer: the offset level
    success = success && FDwfAnalogOutNodeFunctionSet(idxChannel, Waveform.Custom.getId());
    success = success && FDwfAnalogOutNodeFrequencySet(idxChannel, frequency);
    success =
        success && FDwfAnalogOutNodeAmplitudeSet(idxChannel, 5.0); // manually set to full amplitude
    success = success && FDwfAnalogOutNodeOffsetSet(idxChannel, offset);
    success = success && FDwfAnalogOutNodeDataSet(idxChannel, rgdData, rgdData.length);
    if (!success) {
      FDwfAnalogOutNodeEnableSet(idxChannel, false);
      FDwfAnalogOutConfigure(idxChannel, false);
      throw new DWFException(FDwfGetLastErrorMsg());
    }
    return true;
  }

  public boolean startPulseTrain(int idxChannel) {

    boolean success = true;

    success = success && FDwfAnalogOutNodeEnableSet(idxChannel, true);
    success = success && FDwfAnalogOutConfigure(idxChannel, true);
    if (!success) {
      FDwfAnalogOutNodeEnableSet(idxChannel, false);
      FDwfAnalogOutConfigure(idxChannel, false);
      throw new DWFException(FDwfGetLastErrorMsg());
    }
    return true;
  }

  // ///////////////////////////////////////////////////////////
  // Analog I/O ///////////////////////////////////////////////
  // ///////////////////////////////////////////////////////////

  public native boolean FDwfAnalogIOChannelNodeSet(int idxChannel, int idxNode, double value);

  public native boolean FDwfAnalogIOEnableSet(boolean enable);

  public native boolean FDwfAnalogIOConfigure();

  public boolean setPowerSupply(int idxChannel, double value) {

    boolean success = true;
    success = success && FDwfAnalogIOChannelNodeSet(idxChannel, 0, 1);
    success = success && FDwfAnalogIOChannelNodeSet(idxChannel, 1, value);
    success = success && FDwfAnalogIOEnableSet(true);
    success = success && FDwfAnalogIOConfigure();
    if (!success) {
      FDwfAnalogIOEnableSet(false);
      FDwfAnalogIOConfigure();
      throw new DWFException(FDwfGetLastErrorMsg());
    }
    return true;
  }
}
