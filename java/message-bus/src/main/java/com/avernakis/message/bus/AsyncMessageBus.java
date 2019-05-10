package com.avernakis.message.bus;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

public class AsyncMessageBus extends MessageBus implements Runnable {
  private Thread asyncThread;

  AsyncMessageBus() {
    messageQueue = new ConcurrentLinkedQueue<>();
    handlerMap = new ConcurrentHashMap<>();
  }

  @SuppressWarnings("WeakerAccess")
  public void start() {
    asyncThread = new Thread(this);
    asyncThread.start();
  }

  @Override
  public void run() {
    while (!asyncThread.isInterrupted()) {
      processMessage();
      try {
        Thread.sleep(1);
      } catch (InterruptedException e) {
        break;
      }
    }
  }

  @SuppressWarnings("WeakerAccess")
  public void stop() {
    asyncThread.interrupt();
  }
}
