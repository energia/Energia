/*
 * This file is part of Arduino.
 *
 * Copyright 2017 Arduino LLC (http://www.arduino.cc/)
 *
 * Arduino is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As a special exception, you may use this file as part of a free software
 * library without restriction.  Specifically, if other files instantiate
 * templates or use macros or inline functions from this file, or you compile
 * this file and link it with other files to produce an executable, this
 * file does not by itself cause the resulting executable to be covered by
 * the GNU General Public License.  This exception does not however
 * invalidate any other reasons why the executable file might be covered by
 * the GNU General Public License.
 */

package processing.app;

import static org.junit.Assert.assertEquals;

import java.io.File;

import org.apache.commons.compress.utils.IOUtils;
import org.junit.Before;
import org.junit.Test;

import processing.app.helpers.OSUtils;

public class CommandLineTest {

  File buildPath;
  File arduinoPath;

  @Before
  public void findBuildPaths() throws Exception {
    buildPath = new File(System.getProperty("user.dir"));
    while (!new File(buildPath, "build").isDirectory()) {
      buildPath = buildPath.getParentFile();
      if (buildPath == null) {
        throw new Exception("Could not determine build path");
      }
    }
    System.out.println("found buildpath: " + buildPath);
    if (OSUtils.isLinux()) {
      arduinoPath = new File(buildPath, "build/linux/work/arduino");
    }
    if (OSUtils.isWindows()) {
      arduinoPath = new File(buildPath, "build/windows/work/arduino");
    }
    if (OSUtils.isMacOS()) {
      arduinoPath = new File(buildPath,
          "build/macosx/work/Arduino.app/Contents/MacOS/Arduino");
    }
    if (!arduinoPath.canExecute()) {
      throw new Exception("Could not determine arduino location");
    }
    System.out.println("found arduino: " + arduinoPath);
  }

  @Test
  public void testCommandLineBuildWithRelativePath() throws Exception {
    Runtime rt = Runtime.getRuntime();
    File wd = new File(buildPath, "build/shared/examples/01.Basics/Blink/");
    Process pr = rt
        .exec(arduinoPath + " --board arduino:avr:uno --verify Blink.ino", null,
              wd);
    IOUtils.copy(pr.getInputStream(), System.out);
    pr.waitFor();
    assertEquals(0, pr.exitValue());
  }

}