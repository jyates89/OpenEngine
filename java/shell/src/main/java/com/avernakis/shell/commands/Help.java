package com.avernakis.shell.commands;


import java.util.LinkedList;

public class Help implements Command {
  private LinkedList<Command> commandList;

  public Help(LinkedList<Command> supportedCommands) {
    commandList = supportedCommands;
  }

  @Override
  public String commandInfo() {
    return "help: Prints the help message.";
  }

  @Override
  public void execute() {
    for (Command command : commandList) {
      System.out.println(command.commandInfo());
    }
  }
}
