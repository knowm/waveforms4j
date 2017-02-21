package org.knowm.waveforms4j;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Created by timmolter on 2/21/17.
 */
public class DWFException extends RuntimeException {

  private final Logger logger = LoggerFactory.getLogger(DWFException.class);

  public DWFException(String message) {

    super(message);
    logger.error(message);
  }
}
