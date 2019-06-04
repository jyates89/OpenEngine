package com.avernakis.openengine.common;

import picocli.CommandLine;

import java.util.List;

public class PicoCLIHelper {

  public static void run(CommandLine parser, String[] args) {
    parser.setCaseInsensitiveEnumValuesAllowed(true);
    // The parseWithHandlers method calls _call_ after parsing the
    // arguments provided.
    List<Object> results = parser.parseWithHandlers(
        new CommandLine.RunLast()
            .useOut(System.out)
            .useAnsi(CommandLine.Help.Ansi.AUTO),
        new CommandLine.DefaultExceptionHandler<List<Object>>()
            .useErr(System.err)
            .useAnsi(CommandLine.Help.Ansi.AUTO),
        args);
    System.exit(results == null || results.isEmpty() ? 1
        : (Integer) results.get(0));
  }
}
