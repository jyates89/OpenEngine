package com.avernakis.openengine.tools.game.server;

import com.avernakis.openengine.common.VersionInfo;
import picocli.CommandLine;

import java.util.concurrent.Callable;

@CommandLine.Command(
    name = "OpenEngine Game Server",
    description = "Generic game server used for testing and debugging net-code.",
    versionProvider = VersionInfo.class)
public class GameServer implements Callable<Integer> {
  @CommandLine.Option(
      names = {"-V", "--version"},
      description = "Print the version of the application.",
      versionHelp = true
  )
  private Boolean versionRequest;

  @CommandLine.Option(
      names = {"-h", "--help"},
      description = "Prints the help message and exits.",
      usageHelp = true
  )
  private Boolean helpRequest;

  @Override
  public Integer call() {
    return 0;
  }

  public static void main(String[] args) {

  }
}
