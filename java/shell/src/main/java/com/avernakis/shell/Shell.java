package com.avernakis.shell;

import com.avernakis.shell.commands.Command;
import com.avernakis.shell.commands.Help;

import java.util.LinkedList;

public class Shell implements Runnable {
  private LinkedList<Command> commandList;

  Shell() {
    commandList = new LinkedList<>();
    // Add all default commands into the support list.
    registerCommand(new char[]{'h', }, new Help(commandList));

    // Add help last so it includes all commands added.
    commandList.push(new Help(commandList));
  }

  void registerCommand(char[] tokens, Command command) {
    commandList.push(command);


  }

  @Override
  public void run() {

  }
}
