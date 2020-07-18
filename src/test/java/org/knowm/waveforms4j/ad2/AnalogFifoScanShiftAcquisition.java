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

import java.util.Arrays;
import org.knowm.waveforms4j.DWF;
import org.knowm.xchart.SwingWrapper;
import org.knowm.xchart.XYChart;
import org.knowm.xchart.XYChartBuilder;

/**
 * Samples the voltage on O-scope 0. You should hook it up to Digital I/O 0 to get 3.3 V to read.
 *
 * @author timmolter
 */
public class AnalogFifoScanShiftAcquisition {

  private static final int OSCILLOSCOPE_CHANNEL = 0;
  final DWF dwf = new DWF();

  public static void main(String[] args) throws InterruptedException {

    AnalogFifoScanShiftAcquisition app = new AnalogFifoScanShiftAcquisition();

    app.go();
  }

  private void go() throws InterruptedException {

    XYChart chart = new XYChartBuilder().width(600).height(400).build();
    SwingWrapper<XYChart> sw = new SwingWrapper<>(chart);
    sw.displayChart();

    Runtime.getRuntime()
        .addShutdownHook(
            new Thread() {

              @Override
              public void run() {

                System.out.println("Inside Add Shutdown Hook");
                dwf.FDwfDigitalOutReset();
                dwf.FDwfDeviceCloseAll();
              }
            });

    boolean successful = dwf.FDwfDeviceOpen();
    System.out.println("successful: " + successful);

    // TOGGLE CHANNEL 0 DIGITAL

    double clock = dwf.FDwfDigitalOutInternalClockInfo();
    System.out.println("clock: " + clock);

    successful = dwf.FDwfDigitalOutEnableSet(0, true);
    System.out.println("successful: " + successful);

    // frequency set 2 Hz
    successful = dwf.FDwfDigitalOutDividerSet(0, 2);
    System.out.println("successful: " + successful);

    // 1 tick low, 1 tick high
    successful = dwf.FDwfDigitalOutCounterSet(0, 1, 1);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfDigitalOutConfigure(true);
    System.out.println("successful: " + successful);

    // TAKE AN ANALOG SHIFT SAMPLE

    successful = dwf.FDwfAnalogInChannelEnableSet(OSCILLOSCOPE_CHANNEL, true);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfAnalogInChannelRangeSet(OSCILLOSCOPE_CHANNEL, 10);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfAnalogInFrequencySet(100);
    System.out.println("successful: " + successful);

    // int buffersize = dwf.FDwfAnalogInBufferSizeMax();
    int buffersize = 200;
    System.out.println("buffersize: " + buffersize);

    successful = dwf.FDwfAnalogInBufferSizeSet(buffersize);
    System.out.println("successful: " + successful);

    successful = dwf.FDwfAnalogInAcquisitionModeSet(1);
    System.out.println("successful: " + successful);

    Thread.sleep(2000);

    successful = dwf.FDwfAnalogInConfigure(false, true);
    System.out.println("successful: " + successful);

    for (int i = 0; i < 10000; i++) {

      byte status = dwf.FDwfAnalogInStatus(true);
      System.out.println("status: " + status);

      int validSamples = dwf.FDwfAnalogInStatusSamplesValid();
      System.out.println("validSamples: " + validSamples);

      if (validSamples > 0) {
        double[] capturedData = dwf.FDwfAnalogInStatusData(OSCILLOSCOPE_CHANNEL, validSamples);
        System.out.println("capturedData: " + Arrays.toString(capturedData));
        if (chart.getSeriesMap().get("analog") == null) {
          chart.addSeries("analog", null, capturedData);
        } else {
          chart.updateXYSeries("analog", null, capturedData, null);
          sw.repaintChart();
        }
      }
    }
  }
}
