package com.avernakis.shell.commands;

/**
 * The interface Command.
 */
public interface Command {
  /**
   * Get the command information (help).
   * @return String command help string
   */
  String commandInfo();

  /**
   * Execute.
   */
  void execute();

  String toString();
}
